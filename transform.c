#include <stdlib.h>
#include <math.h>

#include "transform.h"

#define M_PI 3.14159265358979323846

_persProj* Pers_Proj_Init(float fov_angle, float screen_height, float screen_width, float z_near, float z_far){
	_persProj* matrix = (_persProj*)calloc(1, sizeof(_persProj));

	float aspect_ratio = screen_width/screen_height;
	float z_range = z_near - z_far;
	float tan_half_fov = tanf((fov_angle * M_PI/180.0f)/2);

	matrix->matrix[0][0] = 1.0f / (tan_half_fov * aspect_ratio);
	matrix->matrix[1][1] = 1.0f / tan_half_fov;

	matrix->matrix[2][2] = (- z_near - z_far)/z_range;
	matrix->matrix[2][3] = 2.0f * z_far * z_near/z_range;

	matrix->matrix[3][2] = 1.0f;

	return matrix;
}

float* Pers_Proj_Transform(_persProj* matrix, float x, float y, float z){
	float* output = (float*)calloc(2, sizeof(float));
	float z_thing = 0.0;

	output[0] = x * matrix->matrix[0][0];
	output[1] = y * matrix->matrix[1][1];
	z_thing = z * matrix->matrix[2][2] + matrix->matrix[2][3];

	output[0] /= z_thing;
	output[1] /= z_thing;

	return output;
}
