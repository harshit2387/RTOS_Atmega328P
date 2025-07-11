#include "scheduler.h"
#include "uart.h"

static Task tasks[MAX_TASKS];

void scheduler_init() {
    for (int i = 0; i < MAX_TASKS; i++) {
        tasks[i].fn = 0;
    }
}

int scheduler_add(task_fn fn, unsigned int interval, unsigned char priority, const char* name) {
    for (int i = 0; i < MAX_TASKS; i++) {
        if (!tasks[i].fn) {
            tasks[i].fn = fn;
            tasks[i].interval_ms = interval;
            tasks[i].elapsed_ms = 0;
            tasks[i].priority = priority;
            tasks[i].active = 1;
            tasks[i].name = name;
            return i;
        }
    }
    return -1;
}

void scheduler_remove(int id) {
    if (id >= 0 && id < MAX_TASKS) tasks[id].fn = 0;
}

void scheduler_enable(int id) { tasks[id].active = 1; }
void scheduler_disable(int id) { tasks[id].active = 0; }

void scheduler_tick() {
    for (int i = 0; i < MAX_TASKS; i++) {
        if (tasks[i].fn && tasks[i].active)
            tasks[i].elapsed_ms++;
    }
}

void scheduler_run() {
    unsigned char top_priority = 0xFF;
    int chosen = -1;

    for (int i = 0; i < MAX_TASKS; i++) {
        if (tasks[i].fn && tasks[i].active && tasks[i].elapsed_ms >= tasks[i].interval_ms) {
            if (chosen == -1 || tasks[i].priority < top_priority) {
                chosen = i;
                top_priority = tasks[i].priority;
            }
        }
    }

    if (chosen != -1) {
        tasks[chosen].elapsed_ms = 0;
        uart_send_string("[RUN] ");
        uart_send_string(tasks[chosen].name);
        uart_send_string("\n");
        tasks[chosen].fn();
    }
}
