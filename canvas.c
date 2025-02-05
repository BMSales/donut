#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "canvas.h"
#include "shape.h"

#define M_PI 3.14159265358979323846

_canvas* Canvas_Init(int rows, int cols){
	_canvas* canvas = (_canvas*)calloc(1, sizeof(_canvas));

	canvas->rows = rows;
	canvas->cols = cols;
	canvas->matrix = (char**)calloc(rows, sizeof(char*));
	canvas->z_buffer = (float**)calloc(rows, sizeof(float*));
	for(int i = 0; i < rows; i++){
		canvas->matrix[i] = (char*)calloc(cols, sizeof(char));
		canvas->z_buffer[i] = (float*)calloc(cols, sizeof(float));
		for(int j = 0; j < cols; j++){
			canvas->matrix[i][j] = ' ';
		}
	}

	canvas->fov_angle = 30.0f;
	canvas->z_near = 1.0f;
	canvas->z_far = 1000.0f;

	float aspect_ratio = (float)cols/(float)rows;
	float z_range = canvas->z_near - canvas->z_far;
	float tan_half_fov = tanf((canvas->fov_angle * M_PI/180.0f)/2.0f);

	canvas->pers_proj[0] = 1.0f / (tan_half_fov * aspect_ratio);
	canvas->pers_proj[1] = 1.0f / tan_half_fov;
	canvas->pers_proj[2] = (- canvas->z_near - canvas->z_far)/z_range;
	canvas->pers_proj[3] = 2.0f * canvas->z_far * canvas->z_near/z_range;

	return canvas;
}

void Canvas_Destroy(_canvas* canvas){
	for(int i = 0; i < canvas->rows; i++){
		free(canvas->matrix[i]);
		free(canvas->z_buffer[i]);
	}
	free(canvas->matrix);
	free(canvas->z_buffer);
	free(canvas);
}

void Canvas_Reset(_canvas* canvas){
	for(int i = 0; i < canvas->rows; i++){
		for(int j = 0; j < canvas->cols; j++){
			canvas->matrix[i][j] = ' ';
			canvas->z_buffer[i][j] = 0.0;
		}
	}
}

void Canvas_PersProj_Update(_canvas* canvas, float fov_angle, float z_near, float z_far){
	float aspect_ratio = (float)canvas->cols/(float)canvas->rows;
	float z_range = z_near - z_far;
	float tan_half_fov = tanf((fov_angle * M_PI/180.f)/2.0f);

	canvas->fov_angle = fov_angle;
	canvas->z_near = z_near;
	canvas->z_far = z_far;

	canvas->pers_proj[0] = 1.0f / (tan_half_fov * aspect_ratio);
	canvas->pers_proj[1] = 1.0f / tan_half_fov;
	canvas->pers_proj[2] = (- z_near - z_far)/z_range;
	canvas->pers_proj[3] = 2.0f * z_far * z_near/z_range;
}

void Canvas_Matrix_Update(_canvas* canvas, int rows, int cols){
	for(int i = 0; i < canvas->rows; i++){
		free(canvas->matrix[i]);
		free(canvas->z_buffer[i]);
	}
	free(canvas->matrix);
	free(canvas->z_buffer);

	canvas->matrix = (char**)calloc(rows, sizeof(char*));
	canvas->z_buffer = (float**)calloc(rows, sizeof(float*));

	for(int i = 0; i < rows; i++){
		canvas->matrix[i] = (char*)calloc(cols, sizeof(char));
		canvas->z_buffer[i] = (float*)calloc(cols, sizeof(float));
		for(int j = 0; j < cols; j++){
			canvas->matrix[i][j] = ' ';
		}
	}

	Canvas_PersProj_Update(canvas, canvas->fov_angle, canvas->z_near, canvas->z_far);
}

void Shade_Pixel(_canvas* canvas, float proj_x, float proj_y){
	int pos_x = ((proj_x + 1.0) / 2.0) * canvas->cols;
	int pos_y = ((proj_y + 1.0) / 2.0) * canvas->rows;

	if(pos_x < canvas->cols && pos_y < canvas->rows && pos_x >= 0.0 && pos_y >= 0.0){
		if(canvas->matrix[pos_y][pos_x] == ' '){
			canvas->matrix[pos_y][pos_x] = '.';
		}
	}
}

void Canvas_Draw_Point(_canvas* canvas, float x, float y, float z){
	float proj_x, proj_y, proj_z;

	proj_x = x * canvas->pers_proj[0];
	proj_y = y * canvas->pers_proj[1];
	proj_z = z * canvas->pers_proj[2] + canvas->pers_proj[3];

	proj_x /= proj_z;
	proj_y /= proj_z;

	Shade_Pixel(canvas, proj_x, proj_y);
}

void Canvas_Draw_Shape(_canvas* canvas, _shape* shape, float center_x, float center_y, float center_z){
	for(int i = 0; i < shape->number_of_points; i++){
		Point_Offset(shape->point[i], center_x, center_y, center_z);
		Canvas_Draw_Point(canvas, shape->point[i][0], shape->point[i][1], shape->point[i][2]);
	}
}

void Canvas_Display(_canvas* canvas){
	for(int i = 0; i < canvas->rows; i++){
		for(int j = 0; j < canvas->cols; j++){
			printf("%c", canvas->matrix[i][j]);
			canvas->matrix[i][j] = ' ';
		}
		printf("\n");
	}
}
