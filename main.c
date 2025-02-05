#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include <sys/ioctl.h>

#include "canvas.h"
#include "shape.h"

int main(){
    srand(clock());

    // retrieves the terminal's dimensions
    struct winsize window;
    // w.ws_row for rows
    // w.ws_col for collumns
    ioctl(STDIN_FILENO, TIOCGWINSZ, &window);

    _canvas* canvas = Canvas_Init(window.ws_row, window.ws_col);
    printf("I got here\n");
    _shape* sphere = Shape_Create_Sphere(100.0);

    float center_x = 0.0;
    float center_y = 0.0;
    float center_z = 0.0;

    while(1){
	Canvas_Draw_Shape(canvas, sphere, center_x, center_y, center_z);
	Canvas_Display(canvas);
	usleep(16*1000);
	system("clear");
	center_z += 0.05;
    }
    /*usleep(16*1000);*/
    //system("clear");

    return 0;
}
