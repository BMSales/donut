#pragma once

typedef struct _canvas{
	int rows;
	int cols;
	char** matrix;
}_canvas;

_canvas* Canvas_Init(int, int);
void Canvas_Draw(_canvas*);
