#include <stdlib.h>
#include <stdio.h>

#include "canvas.h"

_canvas* Canvas_Init(int rows, int cols){
	_canvas* canvas = (_canvas*)calloc(1, sizeof(_canvas));

	canvas->rows = rows;
	canvas->cols = cols;
	canvas->matrix = (char**)calloc(rows, sizeof(char*));

	for(int i = 0; i < rows; i++){
		canvas->matrix[i] = (char*)calloc(cols, sizeof(char));
		for(int j = 0; j < cols; j++){
			canvas->matrix[i][j] = '.';
		}
	}

	return canvas;
}

void Canvas_Update(_canvas* canvas, int row, int col){
	canvas->matrix[row][col] = ' ';
}


void Canvas_Draw(_canvas* canvas){
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
