#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <math.h>

typedef struct {
    int task_id;
    double workload;
    int priority;
} Task;

typedef enum {
    POWERSAVE,
    BALANCED,
    PERFORMANCE
} PowerMode;

typedef struct {
    PowerMode current_mode;
    double frequency;
    double power_limit;
} CpuState;

void initialize_cpu(CpuState* cpu) {
    cpu->current_mode = BALANCED;
    cpu->frequency = 2000.0;
    cpu->power_limit = 15.0;
}

void adjust_power_mode(CpuState* cpu, Task* task) {
    double required_freq = 1200.0 + (task->workload * 1800.0);
    
    if (required_freq > 2500.0) {
        cpu->current_mode = PERFORMANCE;
        cpu->frequency = 3000.0;
    } else if (required_freq > 1800.0) {
        cpu->current_mode = BALANCED;
        cpu->frequency = 2000.0;
    } else {
        cpu->current_mode = POWERSAVE;
        cpu->frequency = 1200.0;
    }
}

void execute_task(CpuState* cpu, Task* task) {
    printf("Executing Task %d (Workload: %.2f, Priority: %d)\n",
           task->task_id, task->workload, task->priority);
    printf("Switching to %s mode (%.0f MHz)\n",
           cpu->current_mode == PERFORMANCE ? "PERFORMANCE" :
           cpu->current_mode == BALANCED ? "BALANCED" : "POWERSAVE",
           cpu->frequency);
    
    double execution_time = task->workload * (3000.0 / cpu->frequency);
    sleep(execution_time);
}