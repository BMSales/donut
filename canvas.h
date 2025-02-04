#pragma once

typedef struct _canvas{
	int rows;
	int cols;
	char** matrix;
	float** z_buffer;
}_canvas;

_canvas* Canvas_Init(int, int);
void Canvas_Destroy(_canvas*);
/*void Canvas_Draw_Sphere(_canvas*, float, float);*/
/*void Canvas_Draw_Circle(_canvas*, float, float, float);*/
void Canvas_Draw_Donut(_canvas*, float, float, float, float);
void Canvas_Display(_canvas*);
