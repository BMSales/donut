#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>

#include "canvas.h"

int main()
{
    struct winsize w;
    // w.ws_row for rows
    // w.ws_col for collumns
    ioctl(STDIN_FILENO, TIOCGWINSZ, &w);

    //_canvas* canvas = Canvas_Init(50, 189);
    _canvas* canvas = Canvas_Init(w.ws_row, w.ws_col);

    Canvas_Draw(canvas);
    
    return(0);
}
