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

void Canvas_Draw_Sphere(_canvas* canvas, float x, float y, float z){
	_persProj* matrix = Pers_Proj_Init(120.0f, (float)canvas->rows, (float)canvas->cols, 1.0f, 1000.0f);
	float* output = NULL;
	int pos_x, pos_y;

	output = Pers_Proj_Transform(matrix, x, y, z);

	pos_x = ((output[0] + 1.0) / 2.0) * canvas->cols;
	pos_y = ((output[1] + 1.0) / 2.0) * canvas->rows;

	if(pos_x < canvas->cols && pos_y < canvas->rows && pos_x >= 0 && pos_y >= 0){
		canvas->matrix[pos_y][pos_x] = '.';
	}

	free(output);
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
}
