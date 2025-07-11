#ifndef SCHEDULER_H
#define SCHEDULER_H

#define MAX_TASKS 10

typedef void (*task_fn)(void);

typedef struct {
    task_fn fn;
    unsigned int interval_ms;
    unsigned int elapsed_ms;
    unsigned char priority;
    unsigned char active;
    const char* name;
} Task;

void scheduler_init();
int scheduler_add(task_fn fn, unsigned int interval, unsigned char priority, const char* name);
void scheduler_remove(int id);
void scheduler_enable(int id);
void scheduler_disable(int id);
void scheduler_tick();
void scheduler_run();

#endif
