#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/ioctl.h>

#include "canvas.h"

#define NANOSECOND_MULTIPLIER 1000000 // 1 millisecond = 1.000.000 nanoseconds

int main()
{
    struct timespec time;
    time.tv_sec = 0;
    time.tv_nsec = 16 * NANOSECOND_MULTIPLIER;

    struct winsize w;
    // w.ws_row for rows
    // w.ws_col for collumns
    ioctl(STDIN_FILENO, TIOCGWINSZ, &w);

    //_canvas* canvas = Canvas_Init(50, 189);
    _canvas* canvas = Canvas_Init(w.ws_row, w.ws_col);

    int i = 0;
    while(1){
	Canvas_Update(canvas, 10, i);
	Canvas_Draw(canvas);
	nanosleep(&time, NULL);
	system("clear");
	i = (i + 1) % w.ws_col;
    }
    
    return(0);
}
