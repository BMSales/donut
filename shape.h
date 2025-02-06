#pragma once

typedef struct _shape{
	float** point;
	int number_of_points;
}_shape;

void Point_Rotate_X(float*, float, float);
void Point_Rotate_Y(float*, float, float);
void Point_Rotate_Z(float*, float, float);

void Shape_Rotate_X(_shape*, float);
void Shape_Rotate_Y(_shape*, float);
void Shape_Rotate_Z(_shape*, float);

void Shape_Rotate_XYZ(_shape*, float, float, float);

_shape* Shape_Create_Sphere(int, float);
_shape* Shape_Create_Torus(int, float, float);
