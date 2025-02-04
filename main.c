#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include <sys/ioctl.h>

#include "canvas.h"

int main(){

    // retrieves the terminal's dimensions
    struct winsize window;
    // w.ws_row for rows
    // w.ws_col for collumns
    ioctl(STDIN_FILENO, TIOCGWINSZ, &window);

    _canvas* canvas = Canvas_Init(window.ws_row, window.ws_col);

    float radius = 10.0;
    float offset = 150.0;
    float angle_a = 0.0;
    float angle_b = 0.0;

    while(1){
	Canvas_Draw_Donut(canvas, radius, offset, angle_a, angle_b);
	Canvas_Display(canvas);
	usleep(16*1000);
	system("clear");
	//offset += 0.2;
	angle_a += 0.02;
	angle_b += 0.02;
    }

}
