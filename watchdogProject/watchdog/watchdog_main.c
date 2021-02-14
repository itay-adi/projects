#include <stdio.h> /*printf*/
#include <unistd.h> /*sleep*/

#include "watchdog.h"

/******************************************************************************/

enum status
{
    SUCCESS = 0,
    FAIL = 1
};

sig_atomic_t has_program_ended;

/******************************************************************************/

int main(int argc, char **argv)
{
    watch_dog_t *wd_handler = NULL;

    printf("Starting the watchdog: %d", getpid());

    wd_handler = MMI(argc, argv);

    if(!wd_handler)
    {
        printf("MMI failed\n");

        return(FAIL);
    }

    while(0 == has_program_ended)
    {
        sleep(1);
    }

    if(1 == DNR(wd_handler))
    {
        printf("DNR failed.\n");

        return(FAIL);
    }

    printf("watchdog ended.\n");

    return (SUCCESS);
}

/******************************************************************************/
