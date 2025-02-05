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

/*void Shape_Display_Points(_shape* shape){*/
/*	for(int i = 0; i < shape->number_of_points; i++){*/
/*	}*/
/*}*/

_shape* Shape_Create_Sphere(int point_limit, float radius){
	_shape* sphere = Shape_Init();
	float theta;
	float phi = M_PI * (sqrt(5.0) - 1.0);
	float x, y, z;
	float radius_draw;

	sphere->point = (float**)calloc(point_limit, sizeof(float*));
	for(int i = 0; i < point_limit; i++){
		sphere->point[i] = (float*)calloc(3, sizeof(float));
	}

	//drawn using the fibonacci sphere algorithm
	for(int i = 0; i < point_limit; i++){
		y = 1.0 - ((float)i / ((float)point_limit - 1.0)) * 2.0;
		radius_draw = sqrt(1.0 - y * y);

		theta = phi * i;

		x = cos(theta) * radius_draw;
		z = sin(theta) * radius_draw;

		sphere->point[i][0] = x * radius;
		sphere->point[i][1] = y * radius;
		sphere->point[i][2] = z * radius;

		sphere->number_of_points++;
	}

	return sphere;
}
