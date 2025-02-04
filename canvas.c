#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "canvas.h"
#include "transform.h"

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
			canvas->z_buffer[i][j] = 0.0;
		}
	}

	return canvas;
}

void Canvas_Destroy(_canvas* canvas){
	for(int i = 0; i < canvas->rows; i++){
		free(canvas->matrix[i]);
		free(canvas->z_buffer[i]);
	}
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

void Shade_Pixel(_canvas* canvas, int x, int y, float one_over_z, float luminance){
	if(luminance > 0){
		if(one_over_z > canvas->z_buffer[y][x]){
			canvas->z_buffer[y][x] = one_over_z;
			int L = luminance * 8;
			char index[12] = ".,-~;:=!*#$@";
			canvas->matrix[y][x] = index[L];
		}
	}
}

/*void Canvas_Draw_Sphere(_canvas* canvas, float radius, float offset){*/
/*	_persProj* matrix = Pers_Proj_Init(30.0f, (float)canvas->rows, (float)canvas->cols, 1.0f, 1000.0f);*/
/*	float* output = NULL;*/
/**/
/*	float x, y, z;*/
/*	float luminance;*/
/**/
/*	int pos_x, pos_y;*/
/**/
/*	for(float phi = 0.0; phi < 360.0; phi += 0.5){*/
/**/
/*		for(float theta = 0.0; theta < 360.0; theta += 0.5){*/
/**/
/*			x = 2 * radius * cos(theta) * cos(phi);*/
/*			y = radius * sin(theta);*/
/*			z = -(radius * cos(theta)) * sin(phi) + offset;*/
/**/
/*			luminance = - sin(theta) - cos(theta) * sin(phi);*/
/**/
/*			output = Pers_Proj_Transform(matrix, x, y, z);*/
/**/
/*			pos_x = ((output[0] + 1.0) / 2.0) * canvas->cols;*/
/*			pos_y = ((output[1] + 1.0) / 2.0) * canvas->rows;*/
/**/
/*			if(pos_x < canvas->cols && pos_y < canvas->rows && pos_x >= 0.0 && pos_y >= 0.0){*/
/*				if(canvas->matrix[pos_y][pos_x] == ' '){*/
/*					Shade_Pixel(canvas, pos_x, pos_y, luminance);*/
/*				}*/
/*			}*/
/*			free(output);*/
/*		}*/
/*	}*/
/**/
/*	free(matrix);*/
/*}*/
/**/

void Canvas_Draw_Circle(_canvas* canvas, float radius, float offset, float phi){
	_persProj* matrix = Pers_Proj_Init(30.0f, (float)canvas->rows, (float)canvas->cols, 1.0f, 1000.0f);
	float* output = NULL;

	float x, y, z;
	float one_over_z;
	float luminance;

	int pos_x, pos_y;

	for(float theta = 0.0; theta < 2 * M_PI; theta += 0.07){
		x = radius * cos(theta) * cos(phi);
		y = radius * sin(theta);
		z = -(radius * cos(theta)) * sin(phi) + offset;

		luminance = - sin(theta) - cos(theta) * sin(phi);

		output = Pers_Proj_Transform(matrix, x, y, z);

		pos_x = ((output[0] + 1.0) / 2.0) * canvas->cols;
		pos_y = ((output[1] + 1.0) / 2.0) * canvas->rows;
		one_over_z = 1/z;

		if(pos_x < canvas->cols && pos_y < canvas->rows && pos_x >= 0.0 && pos_y >= 0.0){
			if(canvas->matrix[pos_y][pos_x] == ' '){
				Shade_Pixel(canvas, pos_x, pos_y, one_over_z, luminance);
			}
		}
	}
	free(matrix);
}


void Canvas_Draw_Donut(_canvas* canvas, float radius, float offset, float angle_a, float angle_b){
	_persProj* matrix = Pers_Proj_Init(30.0f, (float)canvas->rows, (float)canvas->cols, 1.0f, 1000.0f);
	float* output = NULL;

	float x, y, z;
	float one_over_z;
	float helper_1, helper_2;
	float luminance;
	float radius_2 = 2.0 * radius;

	float cos_a = cos(angle_a);
	float sin_a = sin(angle_a);
	float cos_b = cos(angle_b);
	float sin_b = sin(angle_b);

	float sin_theta, cos_theta;
	float sin_phi, cos_phi;

	int pos_x, pos_y;

	for(float phi = 0.0; phi < 2.0 * M_PI; phi += 0.02){
		cos_phi = cos(phi);
		sin_phi = sin(phi);
		for(float theta = 0.0; theta < 2 * M_PI; theta += 0.07){
			cos_theta = cos(theta);
			sin_theta = sin(theta);

			helper_1 = radius_2 + radius * cos_theta;
			helper_2 = radius * sin_theta;
			
			x = helper_1 * cos_phi * cos_a + helper_2 * sin_a;
			y = -helper_1 * sin_phi * cos_b - helper_1 * cos_phi * sin_a * sin_b + helper_2 * cos_a * sin_b;
			z = helper_1 * sin_phi * sin_b - helper_1 * cos_phi * sin_a * cos_b + helper_2 * cos_a * cos_b + offset;

			luminance = cos_theta * sin_phi * cos_b + cos_theta * cos_phi * sin_a * sin_b - sin_theta * cos_a * sin_b - 
				cos_theta * sin_phi * sin_b + cos_theta * cos_phi * sin_a * cos_b - sin_theta * cos_a * cos_b;

			output = Pers_Proj_Transform(matrix, x, y, z);

			pos_x = ((output[0] + 1.0) / 2.0) * canvas->cols;
			pos_y = ((output[1] + 1.0) / 2.0) * canvas->rows;
			one_over_z = 1/z;

			/*printf("x: %f\n", x);*/
			/*printf("y: %f\n", y);*/
			/*printf("z: %f\n", z);*/
			/*printf("one_over_z: %f\n\n", one_over_z);*/

			if(pos_x < canvas->cols && pos_y < canvas->rows && pos_x >= 0.0 && pos_y >= 0.0){
				//canvas->matrix[pos_y][pos_x] = '.';
				Shade_Pixel(canvas, pos_x, pos_y, one_over_z, luminance);
			}
			free(output);
		}
	}

	/*for(int i = 0; i < canvas->rows; i++){*/
	/*	for(int j = 0; j < canvas->cols; j++){*/
	/*		printf("%f ", canvas->z_buffer[i][j]);*/
	/*	}*/
	/*	printf("\n");*/
	/*}*/

	free(matrix);
	/*exit(-1);*/
}

void Canvas_Display(_canvas* canvas){
	/*printf("rows: %d\n", canvas->rows);*/
	/*printf("cols: %d\n", canvas->cols);*/
	/*printf("\"%c\"\n", canvas->matrix[0][0]);*/

	for(int i = 0; i < canvas->rows; i++){
		for(int j = 0; j < canvas->cols; j++){
			printf("%c", canvas->matrix[i][j]);
		}
		printf("\n");
	}
	Canvas_Reset(canvas);
}
