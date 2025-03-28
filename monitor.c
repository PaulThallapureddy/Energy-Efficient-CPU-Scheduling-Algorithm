#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <ncurses.h>

typedef struct {
    double cpu_usage;
    double frequency;
    double temperature;
    double power;
} SystemMetrics;

void initialize_ncurses() {
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
}

SystemMetrics generate_metrics() {
    SystemMetrics metrics;
    metrics.cpu_usage = 20.0 + (double)rand() / RAND_MAX * 80.0;
    
    if (metrics.cpu_usage > 70.0) {
        metrics.frequency = 3000.0;
        metrics.temperature = 70.0 + (double)rand() / RAND_MAX * 15.0;
    } else {
        metrics.frequency = 1200.0;
        metrics.temperature = 45.0 + (double)rand() / RAND_MAX * 15.0;
    }
    
    metrics.power = 5.0 + metrics.cpu_usage * 0.15;
    return metrics;
}