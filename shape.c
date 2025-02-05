#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "shape.h"

#define M_PI 3.14159265358979323846

_shape* Shape_Init(){
	return (_shape*)calloc(1, sizeof(_shape));
}

void Point_Rotate_X(float* point, float radians){
     float y, z;

     y = point[1];
     z = point[2];

     point[1] = y * cos(radians) - z * sin(radians);
     point[2] = y * sin(radians) + z * cos(radians);
}

void Point_Rotate_Y(float* point, float radians){
     float x, z;

     x = point[0];
     z = point[2];

     point[0] = x * cos(radians) + z * sin(radians);
     point[2] = -(x * sin(radians)) + z * cos(radians);
}

void Point_Rotate_Z(float* point, float radians){
     float x, y;

     x = point[0];
     y = point[1];

     point[0] = x * cos(radians) - y * sin(radians);
     point[1] = x * sin(radians) + y * cos(radians);
}

void Point_Offset(float* point, float x_offset, float y_offset, float z_offset){
	point[0] += x_offset;
	point[1] += y_offset;
	point[2] += z_offset;
}

_shape* Shape_Create_Sphere(float radius){
	_shape* sphere = Shape_Init();
	float point_limit = 10000.0;
	float step_size = point_limit / 360.0;
	int index = 0;

	sphere->point = (float**)calloc(point_limit, sizeof(float*));
	for(int i = 0; i < point_limit; i++){
		sphere->point[i] = (float*)calloc(3, sizeof(float));
	}

	for(float phi = 0.0; phi < 2.0 * M_PI && index < point_limit; phi += 0.02){
		for(float theta = 0.0; theta < 2 * M_PI && index < point_limit; theta += 2 * M_PI/step_size){
			sphere->point[index][0] = radius * cos(theta);
			sphere->point[index][1] = radius * sin(theta);
			sphere->point[index][2] = 0.0;

			Point_Rotate_Y(sphere->point[index], phi);
			index++;
			sphere->number_of_points++;
		}
	}

	return sphere;
}
