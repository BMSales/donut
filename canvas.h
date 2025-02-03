#pragma once

typedef struct _canvas{
	int rows;
	int cols;
	char** matrix;
}_canvas;

_canvas* Canvas_Init(int, int);
void Canvas_Draw_Sphere(_canvas*, float, float, float);
void Canvas_Display(_canvas*);
