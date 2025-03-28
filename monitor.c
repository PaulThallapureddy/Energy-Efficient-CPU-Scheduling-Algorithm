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
void display_metrics(SystemMetrics metrics) {
    erase();
    
    mvprintw(1, 1, "SYSTEM MONITOR DASHBOARD");
    mvprintw(3, 1, "CPU Usage:    %.1f%%", metrics.cpu_usage);
    mvprintw(4, 1, "Frequency:    %.0f MHz", metrics.frequency);
    mvprintw(5, 1, "Temperature:  %.1f°C", metrics.temperature);
    mvprintw(6, 1, "Power Draw:   %.2f W", metrics.power);
    
    mvprintw(8, 1, "Performance State:");
    if (metrics.frequency > 2500.0) {
        attron(COLOR_PAIR(1));
        mvprintw(9, 1, "HIGH PERFORMANCE");
        attroff(COLOR_PAIR(1));
    } else if (metrics.frequency > 1800.0) {
        attron(COLOR_PAIR(3));
        mvprintw(9, 1, "BALANCED");
        attroff(COLOR_PAIR(3));
    } else {
        attron(COLOR_PAIR(2));
        mvprintw(9, 1, "POWER SAVING");
        attroff(COLOR_PAIR(2));
    }
    
    refresh();
}

int main() {
    srand(time(NULL));
    initialize_ncurses();
    
    while (1) {
        SystemMetrics metrics = generate_metrics();
        display_metrics(metrics);
        usleep(500000); // Update twice per second
    }
    
    endwin();
    return 0;
}