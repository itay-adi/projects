#define _DEFAULT_SOURCE

#include <stdio.h> /*printf*/
#include <unistd.h> /*sleep*/

#include "watchdog.h"

/******************************************************************************/

enum status
{
    SUCCESS = 0,
    FAIL = 1
};

/******************************************************************************/

int main(int argc, char **argv)
{
    int i = 0;
    int j = 0;
    watch_dog_t *wd_handler = NULL;

    printf("Starting the user's app: %d\n", getpid());
    printf("argc = %d\n", argc);

    for(i = 0; i < argc; ++i)
    {
        printf("arg[%d] = %s\n", i, argv[i]);
    }

    wd_handler = MMI(argc, argv);

    if(!wd_handler)
    {
        printf("MMI failed\n");

        return(FAIL);
    }

    for(j = 0; j < 1000000; ++j)
    {
        if(j%12 == 0)
        {
            printf("%d\n", j);
        }

        sleep(1);
    }

    if(1 == DNR(wd_handler))
    {
        printf("DNR failed.\n");

        return(FAIL);
    }

    printf("Bye Bye.\n");

    return (SUCCESS);
}

/******************************************************************************/
