An automation which keeps a critical code segment from crashing, according to the user's demand

Files:

1. client.c: Conceptualize the client which call the wd functionality in order to watch his process
2. watchdog.h: the watchdog API
3. watchdog_main.c: The wd process itself which keep the user's process alive
4. watchdog_service.c: The ed functinality
