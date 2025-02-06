#pragma once

typedef struct _shape{
	float** point;
	int number_of_points;
}_shape;

void Point_Rotate_X(float*, float);
void Point_Rotate_Y(float*, float);
void Point_Rotate_Z(float*, float);

void Point_Offset(float*, float, float, float);

_shape* Shape_Create_Sphere(int, float);
_shape* Shape_Create_Torus(int, float, float);
