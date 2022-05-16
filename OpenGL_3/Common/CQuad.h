#pragma once
#ifndef CQUAD_H
#define CQUAD_H
#include "../header/Angel.h"
#include "CShape.h"

typedef Angel::vec4  color4;
typedef Angel::vec4  point4;

#define QUAD_NUM 6		// 2 faces, 2 triangles/face 

class CQuad : public CShape
{ 
private:

	float _fBT[3] = { 1 };					//for player translation / scale
	mat4 _mxBT, _mxBS, _mxBR;

public:
	CQuad();
	~CQuad(){};
	void update(float dt);
	GLuint getShaderHandle() { return _uiProgram;} 

	void GL_SetTranslatMatrix(mat4& mat);
	mat4 GetTRSMatrix();
	void draw();
	void drawW();
};




#endif