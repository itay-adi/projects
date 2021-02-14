#ifndef ILRD_WD_H
#define ILRD_WD_H

#include <signal.h> /* sig_atomic_t */

typedef struct watchdog watch_dog_t;

watch_dog_t *MMI(int argc, char *argv[]);

int DNR(watch_dog_t *wd);

#endif /* ILRD_WD_H */