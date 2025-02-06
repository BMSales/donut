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
    _shape* torus = Shape_Create_Torus(3*360*90, 10, 20);

    float center_x = 0.0;
    float center_y = 0.0;
    float center_z = 150.0;

    float angle_x = 0.01;
    float angle_y = 0.03;
    float angle_z = 0.02;

    while(1){
	Shape_Rotate_XYZ(torus, angle_x, angle_y, angle_z);
	Canvas_Draw_Shape(canvas, torus, center_x, center_y, center_z);
	Canvas_Display(canvas);
	usleep(16*1000);
	system("clear");
    }
    /*usleep(16*1000);*/
    //system("clear");

    return 0;
}
