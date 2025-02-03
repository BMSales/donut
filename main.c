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

    while(1){
	Canvas_Draw_Sphere(canvas, x, y, 50);
	Canvas_Display(canvas);
	usleep(16*1000);
	printf("\e[1:1H\e[2J");
    }

}
