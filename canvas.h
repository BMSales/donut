#pragma once

#include "shape.h"

typedef struct _canvas{
	int rows;
	int cols;
	char** matrix;
	float** z_buffer;

	float pers_proj[4];
	float fov_angle;
	float z_near;
	float z_far;
	float light[3];
}_canvas;

_canvas* Canvas_Init(int, int);
void Canvas_Destroy(_canvas*);

void Canvas_PersProj_Update(_canvas*, float, float, float);
void Canvas_Matrix_Update(_canvas*, int, int);

void Canvas_Draw_Shape(_canvas*, _shape*, float, float, float);

void Canvas_Display(_canvas*);
