#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "canvas.h"
#include "transform.h"

_canvas* Canvas_Init(int rows, int cols){
	_canvas* canvas = (_canvas*)calloc(1, sizeof(_canvas));

	canvas->rows = rows;
	canvas->cols = cols;
	canvas->matrix = (char**)calloc(rows, sizeof(char*));

	for(int i = 0; i < rows; i++){
		canvas->matrix[i] = (char*)calloc(cols, sizeof(char));
		for(int j = 0; j < cols; j++){
			canvas->matrix[i][j] = ' ';
		}
	}

	return canvas;
}

void Canvas_Reset(_canvas* canvas){
	for(int i = 0; i < canvas->rows; i++){
		for(int j = 0; j < canvas->cols; j++){
			canvas->matrix[i][j] = ' ';
		}
	}
}

void Shade_Pixel(_canvas* canvas, int x, int y, float luminance){
	if(luminance < 0.0){
		return;
	}

	int L = luminance * 8;

	char index[12] = {'.', ',', '-', '~', ':', ';', '=', '!', '*', '#', '$', '@'};

	canvas->matrix[y][x] = index[L];
}

void Canvas_Draw_Sphere(_canvas* canvas, float radius, float offset){
	_persProj* matrix = Pers_Proj_Init(30.0f, (float)canvas->rows, (float)canvas->cols, 1.0f, 1000.0f);
	float* output = NULL;

	float x, y, z;
	float luminance;

	int pos_x, pos_y;

	for(float phi = 0.0; phi < 360.0; phi += 0.5){
		
		for(float theta = 0.0; theta < 360.0; theta += 0.5){

			x = 2 * radius * cos(theta) * cos(phi);
			y = radius * sin(theta);
			z = -(radius * cos(theta)) * sin(phi) + offset;

			luminance = - sin(theta) - cos(theta) * sin(phi);

			output = Pers_Proj_Transform(matrix, x, y, z);

			pos_x = ((output[0] + 1.0) / 2.0) * canvas->cols;
			pos_y = ((output[1] + 1.0) / 2.0) * canvas->rows;
			//distance_z = output[2];

			if(pos_x < canvas->cols && pos_y < canvas->rows && pos_x >= 0.0 && pos_y >= 0.0){
				if(canvas->matrix[pos_y][pos_x] == ' '){
					Shade_Pixel(canvas, pos_x, pos_y, luminance);
				}
			}
			free(output);
		}
	}


	free(matrix);
}

void Canvas_Draw_Circle(_canvas* canvas, float radius, float offset, float phi){
	_persProj* matrix = Pers_Proj_Init(60.0f, (float)canvas->rows, (float)canvas->cols, 1.0f, 1000.0f);
	float* output = NULL;

	float x, y, z;
	float luminance;

	int pos_x, pos_y;
	
	for(float theta = 0.0; theta < 360.0; theta += 0.5){
		x = radius * cos(theta) * cos(phi);
		y = radius * sin(theta);
		z = -(radius * cos(theta)) * sin(phi) + offset;

		luminance = - sin(theta) - cos(theta) * sin(phi);

		output = Pers_Proj_Transform(matrix, x, y, z);

		pos_x = ((output[0] + 1.0) / 2.0) * canvas->cols;
		pos_y = ((output[1] + 1.0) / 2.0) * canvas->rows;
		//distance_z = output[2];

		if(pos_x < canvas->cols && pos_y < canvas->rows && pos_x >= 0.0 && pos_y >= 0.0){
			if(canvas->matrix[pos_y][pos_x] == ' '){
				Shade_Pixel(canvas, pos_x, pos_y, luminance);
			}
		}
	}
	free(matrix);
}

void Canvas_Draw_Donut(_canvas* canvas, float radius, float offset){
	_persProj* matrix = Pers_Proj_Init(60.0f, (float)canvas->rows, (float)canvas->cols, 1.0f, 1000.0f);
	float* output = NULL;

	float x, y, z;
	float luminance;
	float phi;

	int pos_x, pos_y;

	
	for(float theta = 0.0; theta < 360.0; theta += 0.5){
		x = (radius_2 + radius * cos(theta)) * cos(phi);
		y = -(radius_2 + radius * cos(theta)) * sin(phi) ;
		z = radius * sin(theta);

		luminance = ;

		output = Pers_Proj_Transform(matrix, x, y, z);

		pos_x = ((output[0] + 1.0) / 2.0) * canvas->cols;
		pos_y = ((output[1] + 1.0) / 2.0) * canvas->rows;
		//distance_z = output[2];

		if(pos_x < canvas->cols && pos_y < canvas->rows && pos_x >= 0.0 && pos_y >= 0.0){
			if(canvas->matrix[pos_y][pos_x] == ' '){
				Shade_Pixel(canvas, pos_x, pos_y, luminance);
			}
		}
	}
	free(matrix);
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
