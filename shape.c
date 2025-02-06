#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "shape.h"

#define M_PI 3.14159265358979323846

_shape* Shape_Init(){
	return (_shape*)calloc(1, sizeof(_shape));
}

void Point_Rotate_X(float* point, float cos_radians, float sin_radians){
	float y, z, norm_y, norm_z;

	y = point[1];
	z = point[2];

	norm_y = point[4];
	norm_z = point[5];

	point[1] = y * cos_radians - z * sin_radians;
	point[2] = y * sin_radians + z * cos_radians;

	point[4] = norm_y * cos_radians - norm_z * sin_radians;
	point[5] = norm_y * sin_radians + norm_z * cos_radians;
}

void Point_Rotate_Y(float* point, float cos_radians, float sin_radians){
	float x, z, norm_x, norm_z;

	x = point[0];
	z = point[2];

	norm_x = point[3];
	norm_z = point[5];

	point[0] = x * cos_radians + z * sin_radians;
	point[2] = -(x * sin_radians) + z * cos_radians;

	point[3] = norm_x * cos_radians + norm_z * sin_radians;
	point[5] = -(norm_x * sin_radians) + norm_z * cos_radians;
}

void Point_Rotate_Z(float* point, float cos_radians, float sin_radians){
	float x, y, norm_x, norm_y;

	x = point[0];
	y = point[1];
	norm_x = point[3];
	norm_y = point[4];

	point[0] = x * cos_radians - y * sin_radians;
	point[1] = x * sin_radians + y * cos_radians;

	point[3] = norm_x * cos_radians - norm_y * sin_radians;
	point[4] = norm_x * sin_radians + norm_y * cos_radians;
}

void Shape_Rotate_X(_shape* shape, float radians){
	float cos_radians, sin_radians;

	cos_radians = cos(radians);
	sin_radians = sin(radians);

	for(int i = 0; i < shape->number_of_points; i++){
		Point_Rotate_X(shape->point[i], cos_radians, sin_radians);
	}
}

void Shape_Rotate_Y(_shape* shape, float radians){
	float cos_radians, sin_radians;

	cos_radians = cos(radians);
	sin_radians = sin(radians);

	for(int i = 0; i < shape->number_of_points; i++){
		Point_Rotate_Y(shape->point[i], cos_radians, sin_radians);
	}
}

void Shape_Rotate_Z(_shape* shape, float radians){
	float cos_radians, sin_radians;

	cos_radians = cos(radians);
	sin_radians = sin(radians);

	for(int i = 0; i < shape->number_of_points; i++){
		Point_Rotate_Z(shape->point[i], cos_radians, sin_radians);
	}
}

void Shape_Rotate_XYZ(_shape* shape, float angle_x, float angle_y, float angle_z){
	float cos_x, sin_x;
	float cos_y, sin_y;
	float cos_z, sin_z;

	cos_x = cos(angle_x);
	sin_x = sin(angle_x);

	cos_y = cos(angle_y);
	sin_y = sin(angle_y);

	cos_z = cos(angle_z);
	sin_z = sin(angle_z);

	for(int i = 0; i < shape->number_of_points; i++){
		Point_Rotate_X(shape->point[i], cos_x, sin_x);
		Point_Rotate_Y(shape->point[i], cos_y, sin_y);
		Point_Rotate_Z(shape->point[i], cos_z, sin_z);
	}
}
_shape* Shape_Create_Sphere(int point_limit, float radius){
	_shape* sphere = Shape_Init();
	float theta;
	float phi = M_PI * (sqrt(5.0) - 1.0);
	float x, y, z;
	float radius_draw;

	sphere->point = (float**)calloc(point_limit, sizeof(float*));
	for(int i = 0; i < point_limit; i++){
		sphere->point[i] = (float*)calloc(6, sizeof(float));
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

		sphere->point[i][3] = x;
		sphere->point[i][4] = y;
		sphere->point[i][5] = z;

		sphere->number_of_points++;
	}

	return sphere;
}

_shape* Shape_Create_Torus(int point_limit, float radius_1, float radius_2){
	_shape* torus = Shape_Init();

	float phi_step_size = (360.0f / sqrt(4.0 * (float)point_limit)) * M_PI/180.0f;
	float theta_step_size = 4.0 * phi_step_size;

	float x, z, norm_x, norm_z;
	float cos_phi, sin_phi;
	int index = 0;

	torus->point = (float**)calloc(point_limit, sizeof(float*));
	for(int i = 0; i < point_limit; i++){
		torus->point[i] = (float*)calloc(6, sizeof(float));
	}

	for(float phi = 0.0; phi < 2 * M_PI; phi += phi_step_size){
		cos_phi = cos(phi);
		sin_phi = sin(phi);
		for(float theta = 0.0; theta < 2 * M_PI && index < point_limit; theta += theta_step_size){
			x = radius_2 + radius_1 * cos(theta);
			z = radius_1 * sin(theta);
			norm_x = cos(theta);
			norm_z = sin(theta);

			torus->point[index][0] = x;
			torus->point[index][2] = z;

			torus->point[index][3] = norm_x;
			torus->point[index][5] = norm_z;

			Point_Rotate_Z(torus->point[index], cos_phi, sin_phi);

			index++;
			torus->number_of_points++;
		}
	}

	return torus;
}
