#define _DEFAULT_SOURCE 

#include <stdio.h> /* printf */
#include <string.h> /* memset */
#include <stdlib.h> /* getenv */
#include <semaphore.h> /* sempahore */
#include <unistd.h> /* execlp */
#include <pthread.h> /* pthread_create */
#include <semaphore.h> /* semaphore functions */
#include <fcntl.h> /* O_CREAT */

#include "watchdog.h"
#include "scheduler.h"

enum status
{
    SUCCESS = 0,
    ERROR = 1
};


typedef void (*sem_func_t)(sem_t *sem);
typedef char **(*create_arg_func_t)(char **argv, const char *file_name, size_t argc);

typedef struct sigaction sigaction_t;

#define UNUSED(x) (void)(x)

/************************    Custom Structures    ****************************/

struct watchdog
{
    sch_t *scheduler;
    sem_t *sem;
    char **arg_list;
    int is_first_process_to_run;
};

/*******************    Utiliy functions declarations    **********************/

static watch_dog_t *CreateData(char *argv[], sch_t *scheduler, int is_first_process_to_run);
static int InitSignalHandler(sigaction_t *signal);
static int InitScheduler(sch_t *scheduler, void *data);
static void *KeepAlive(void *thread_data);
static void SignalHandler(int signal, siginfo_t *signal_info, void *ucontext);
static void SemWait(sem_t *sem);
static void SemPost(sem_t *sem);
static int CreateProcess(char **argv);
static int task1(sch_t *sch, unique_id_t uid, void *param);
static int task2(sch_t *sch, unique_id_t uid, void *param);
static int InitSignalHandler2(sigaction_t *signal);
static void FreeResources(watch_dog_t *data);
static void SignalHandler2(int signal, siginfo_t *signal_info, void *ucontext);
static char **CreateUserAppArgList(char **argv, const char *file_name, size_t argc);
static char **CreateWDArgList(char **argv, const char *file_name, size_t argc);

/************************    Global Variables    ******************************/

sig_atomic_t has_program_ended = 0;
static sig_atomic_t is_alive = 0;
static pid_t pid = 0;
static const char *wd_file_name = "/home/itay/git/system_programming/watchdog/watch_dog/watchdog.Debug.out";
static const char *curr_process_file_name = NULL;
static const sem_func_t sem_functions[] = {SemPost, SemWait};
static const create_arg_func_t create_arg_functions[] = {CreateUserAppArgList, CreateWDArgList};

/***************************   API Functions    *******************************/

/* Function recieve argc, argv and process identity - for user app, value should
    be 1 */
watch_dog_t *MMI(int argc, char *argv[])
{
    pthread_t thread = {0};
    watch_dog_t *data = NULL;
    sigaction_t signal;
    sigaction_t signal2;
    char **arg_list = argv;
    sch_t *scheduler = NULL;
    int is_wd_app = 0;
    int is_first_process_to_run = 0;

    /*Init signal handler */
    if(ERROR == InitSignalHandler(&signal))
    {
        return(NULL);
    }

   /*Init signal second handler */
    if(ERROR == InitSignalHandler2(&signal2))
    {
        return(NULL);
    }

    UNUSED(argc);

    /* assign file name */
    curr_process_file_name = argv[0];
    
    /* check if it is a watchdog process */
    is_wd_app = !strcmp(curr_process_file_name, wd_file_name);

    /* Create arg list */
    arg_list = create_arg_functions[is_wd_app](argv, wd_file_name, argc);

    if(!arg_list)
	{
		return(NULL);
	}

    /* if there is no env var - first run from console terminal */
    if(!getenv("WATCHDOG"))
    {    
        /* create env var */ 
        if(0 != putenv("WATCHDOG=EXIST"))
        {
            return(NULL);
        }

        /* Turn on flag that indicate creating env var */
        is_first_process_to_run = 1;

        /* Create watchdog process */
        if(ERROR == CreateProcess(arg_list))
        {            
            return(NULL);
        }
    }

    /* Create scheduler */
    scheduler = SchCreate();

    if(!scheduler)
    {
        return(NULL);
    }

    /* Create Data */
    data = CreateData(arg_list, scheduler, is_first_process_to_run);
    
    if(!data)
    {
        SchDestroy(scheduler);

        return(NULL);
    }

    /* Insert tasks to scheduler */
    if(ERROR == InitScheduler(data->scheduler, data))
    {
        free(data);
        SchDestroy(scheduler);

        return (NULL);
    }

    /* Do sem_wait or sem_post. if it is the first process to run - wait.
        Otherwise - post */ 
    sem_functions[data->is_first_process_to_run](data->sem);

    pthread_create(&thread, NULL, KeepAlive, data);	
    pthread_detach(thread);

    return(data);
}

/*----------------------------------------------------------------------------*/

int DNR(watch_dog_t *wd)
{
    printf("ARRIVED TO DNR pid %d\n", getpid());
    printf("SEND KILL TO PID %d \n", pid);
 
    /* send SIGUSR2 signal */
    if(-1 == kill(pid, SIGUSR2))
    {
        printf("KIll was failed!\n");
        return (ERROR);
    }

    printf("Free Resources %d \n", pid);
    /* free resources */
    FreeResources(wd);

    /* Destroy semaphore */
    sem_unlink("/sem");
    printf("Out of DNR %d \n", getpid());
 
    return(SUCCESS);
}

/***************************   Utility Functions  *****************************/

static int CreateProcess(char **arg_list)
{
    pid_t child_pid = 0;
    int is_wd_app = 0;

    /* create watchdog process */
    child_pid = fork();

    if(-1 == child_pid)
    {
        return(ERROR);
    }

    if(0 == child_pid)
    {
        /* check if process is watchdog */
        is_wd_app = !strcmp(curr_process_file_name, wd_file_name);

        if (-1 == execvp(arg_list[is_wd_app], arg_list + is_wd_app))
        {   
            return(ERROR);
        }
    }

    /* assign child pid to pid (global variable), in order to send it signal 
    later */
    pid = child_pid;

    return(SUCCESS);
}

/*----------------------------------------------------------------------------*/

static void *KeepAlive(void *thread_data)
{
    watch_dog_t *data = (watch_dog_t *)thread_data;

    SchRun(data->scheduler);

    return(NULL);
}

/*----------------------------------------------------------------------------*/

static void SemWait(sem_t *sem)
{
    sem_wait(sem);
}

/*----------------------------------------------------------------------------*/

static void SemPost(sem_t *sem)
{
    sem_post(sem);
}

/*----------------------------------------------------------------------------*/

static void SignalHandler(int signal, siginfo_t *signal_info, 
								void *ucontext)
{
    UNUSED(ucontext);
    UNUSED(signal);

    printf("Got signal - %d\n", getpid());
    printf("---------------------------------\n");

    /* Set pid to pid of the process that sent the signal */
    pid = signal_info->si_pid;

    is_alive = 1;
}

/*----------------------------------------------------------------------------*/

static int InitScheduler(sch_t *scheduler, void *data)
{
    if(UIDIsSame(SchTimerStart(scheduler, 1, task1, data), UIDGetBadUID()))
    {
        return(ERROR);
    }

    if (UIDIsSame(SchTimerStart(scheduler, 3, task2, data), UIDGetBadUID()))
    {
        return(ERROR);
    }

    return(SUCCESS);
}

/*----------------------------------------------------------------------------*/

static int InitSignalHandler(sigaction_t *signal)
{
    memset(signal, 0, sizeof(sigaction_t));
    /*SIGINFO = The  signal handler takes three arguments, not one*/
    signal->sa_flags = SA_SIGINFO;
    /*because SIGINFO, we use "sa_sigaction"*/
	signal->sa_sigaction = SignalHandler;
 
    if(-1 == sigaction(SIGUSR1, signal, NULL))
    {
        return(ERROR);
    }

    return(SUCCESS);
}

/*----------------------------------------------------------------------------*/

static watch_dog_t *CreateData(char *arg_list[], sch_t *scheduler,
                         int is_first_process_to_run)
{
    watch_dog_t *data = NULL;

    data = (watch_dog_t *)malloc(sizeof(watch_dog_t));

    if (!data)
    {
        return(NULL);
    }

    data->sem = sem_open("/sem", O_CREAT | O_EXCL, 0666, 0);

    if(SEM_FAILED == data->sem)
    {
        data->sem = sem_open("/sem", O_CREAT);

        if (SEM_FAILED == data->sem)
        {
            printf("Semaphore creation failed\n");

            return (NULL);
        }
    }

    data->scheduler = scheduler;
    data->arg_list = arg_list;
    data->is_first_process_to_run = is_first_process_to_run;

    return(data);
}

/*----------------------------------------------------------------------------*/

static int task1(sch_t *sch, unique_id_t uid, void *param)
{
    printf("Signal was sent - %d\n", getpid());
    printf("---------------------------------\n");

    UNUSED(sch);
    UNUSED(uid);
    UNUSED(param);

    /* Send SIGUSR1 to pid */
    kill(pid, SIGUSR1);

    return(1);
}

/*----------------------------------------------------------------------------*/

static int task2(sch_t *sch, unique_id_t uid, void *param)
{
    watch_dog_t *data = (watch_dog_t *)param;

    UNUSED(sch);
    UNUSED(uid);

    printf("file - %s Signal was checked - %d\n", data->arg_list[0], getpid());
    printf("---------------------------------\n");

    if(is_alive && !has_program_ended)
    {
        is_alive = 0;
    }

    else
    {
        printf(" get pid - %d \n", getpid());
        printf("This is time to create new process! \n");
        
        /* Create a new process */
        if(ERROR == CreateProcess(data->arg_list))
        {
            return(ERROR);
        }

        sem_wait(data->sem);
    }  

    return(1);
}

/*----------------------------------------------------------------------------*/

static void FreeResources(watch_dog_t *data)
{
    /* Stop and Destory scheduler */
    SchStop(data->scheduler);
    SchDestroy(data->scheduler);
    printf("SCHEDULER DESTROYED - pid %d\n", getpid());

    /* free arg_list */
    if(strcmp(curr_process_file_name, wd_file_name))
    {
        free(data->arg_list);
        printf("ARG_LIST FREE - pid %d\n", getpid());
    }

   /* free data */         
    free(data);
   	data = NULL;

    printf("free data - pid %d\n", getpid());
}

/*----------------------------------------------------------------------------*/

static int InitSignalHandler2(sigaction_t *signal)
{
    memset(signal, 0, sizeof(sigaction_t));
    signal->sa_flags = SA_SIGINFO;
	signal->sa_sigaction = SignalHandler2;
 
    if(-1 == sigaction(SIGUSR2, signal, NULL))
    {
        return(ERROR);
    }

    return(SUCCESS);
}

/*----------------------------------------------------------------------------*/

static void SignalHandler2(int signal, siginfo_t *signal_info, 
								void *ucontext)
{
    UNUSED(ucontext);
    UNUSED(signal);
    UNUSED(signal_info);

    printf("Signal handler 2\n");
    printf("---------------------------------\n");

    has_program_ended = 1;
}

/*----------------------------------------------------------------------------*/

static char **CreateUserAppArgList(char **argv, const char *file_name,
                                     size_t argc)
{
    char **arg_list = NULL;
    size_t i = 0;

    arg_list = (char **)malloc(sizeof(char *) * (argc + 2));

    if(!arg_list)
    {
        return (NULL);
    }

    /* create arg_list */
    arg_list[0] = (char *)file_name;

    for (i = 0; i < argc + 1; ++i)
    {
        arg_list[i + 1] = argv[i]; 
    }
    
    arg_list[i] = NULL;

    return (arg_list);
}

/*----------------------------------------------------------------------------*/

static char **CreateWDArgList(char **argv, const char *file_name, size_t argc)
{
    UNUSED(file_name);
    UNUSED(argc);

    return (argv);
}

/*----------------------------------------------------------------------------*/
