#include <curses.h>
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>


#define BUFF_SIZE 256


static long double get_cpu_util() {
    long double a[4], b[4], loadavg;
    
    FILE *stat = fopen("/proc/stat","r");
    fscanf(stat, "%*s %Lf %Lf %Lf %Lf", &a[0], &a[1], &a[2], &a[3]);
    fclose(stat);
    sleep(1);
    
    stat = fopen("/proc/stat","r");
    fscanf(stat, "%*s %Lf %Lf %Lf %Lf", &b[0], &b[1], &b[2], &b[3]);
    fclose(stat);
    
    loadavg = ((b[0]+b[1]+b[2]) - (a[0]+a[1]+a[2])) / ((b[0]+b[1]+b[2]+b[3]) - (a[0]+a[1]+a[2]+a[3]));
    
    return loadavg;
}


static void get_mem(int *avaiableRAM, int *totalRAM) {
    FILE *meminfo = fopen("/proc/meminfo", "rt");
    fscanf(meminfo, "%*s %d\n %*s %*s %*d %*s\n %*s %d", totalRAM, avaiableRAM);
    
    fclose(meminfo);
}


static void get_time(char *buf) {
    static time_t rawtime;
    
    time(&rawtime);
    strftime(buf, 32, "%a %d-%m %H:%M:%S", localtime(&rawtime));
}


int main() {
    initscr();
    start_color();
    
    curs_set(false);
    init_color(COLOR_BLACK, 0, 0, 0);
    
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    
    attron(COLOR_PAIR(1));
    bkgd(COLOR_PAIR(1));
    
    
    FILE *file;
    char buff[BUFF_SIZE];
    char time_buff[32];
    
    int totalRAM, avaiableRAM;
    
    while (true) {
        clear();
        move(0, 0);
        
        get_mem(&avaiableRAM, &totalRAM);
        get_time(time_buff);
        
        file = fopen("bs", "a+");
        while (fgets(buff, BUFF_SIZE, file))
            printw(buff, time_buff);
        
        fclose(file);
        
        printw("\n\tCPU Utilization: %.2Lf%%\n", get_cpu_util() * 100);
        // bitshifting instead of dividing by 1024
        printw("\tUsed RAM: %d MB \n\tTotal RAM: %d MB (%.2f%% used)\n", (totalRAM >> 10) - (avaiableRAM >> 10), (totalRAM >> 10), ((double) ((totalRAM >> 10) - (avaiableRAM >> 10)) / (totalRAM >> 10)) * 100);
        
        refresh();
    }
    
    return 0;
}
