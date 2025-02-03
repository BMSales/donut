#pragma once

typedef struct _persProj{
	float matrix[4][4];
}_persProj;

_persProj* Pers_Proj_Init(float fov_angle, float screen_height, float screen_width, float z_near, float z_far);
float* Pers_Proj_Transform(_persProj* matrix, float x, float y, float z);
