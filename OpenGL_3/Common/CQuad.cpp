#include "CQuad.h"
// Example 4 開始
// 面同 Example 3 朝上(Y軸)
// 每一個 Vertex 增加 Normal ，改成繼曾自 CShape，一併處理相關的設定需求


CQuad::CQuad()
{
	_iNumVtx = QUAD_NUM;
	_pPoints = NULL; _pNormals = NULL; _pTex = NULL;

	_pPoints  = new vec4[_iNumVtx];
	_pNormals = new vec3[_iNumVtx];

	_pPoints[0] = vec4( -0.2f, 0.2f,  0.0f, 1.0f);
	_pPoints[1] = vec4(  0.2f, 0.2f,  0.0f, 1.0f);
	_pPoints[2] = vec4(  0.2f, -0.2f, 0.0f, 1.0f);
	_pPoints[3] = vec4( -0.2f, 0.2f,  0.0f, 1.0f);
	_pPoints[4] = vec4(  0.2f, -0.2f, 0.0f, 1.0f);
	_pPoints[5] = vec4( -0.2f, -0.2f, 0.0f, 1.0f);

	_pNormals[0] = vec3(  0, 1.0f, 0);  // Normal Vector 的 W 為 0
	_pNormals[1] = vec3(  0, 1.0f, 0);
	_pNormals[2] = vec3(  0, 1.0f, 0);
	_pNormals[3] = vec3(  0, 1.0f, 0);
	_pNormals[4] = vec3(  0, 1.0f, 0);
	_pNormals[5] = vec3(  0, 1.0f, 0);

	// Set shader's name
	setShaderName("vsVtxNormal.glsl", "fsVtxNormal.glsl");

	// Create and initialize a buffer object 
	createBufferObject();

	// 預設為 -1.0f, 由 Normal 決定顏色
	_fColor[0] = -1.0f; _fColor[1] = -1.0f; _fColor[2] = -1.0f; _fColor[3] = 1;
}

void CQuad::GL_SetTranslatMatrix(mat4& mat)
{
	_mxBT = mat;
	_fBT[0] = _mxBT._m[0][3];
	_fBT[1] = _mxBT._m[1][3];
}

mat4 CQuad::GetTRSMatrix()
{
	return(_mxBT);
}

void CQuad::update(float dt)
{
}

void CQuad::draw()
{
	drawingSetShader();
	glDrawArrays( GL_TRIANGLES, 0, QUAD_NUM );
}

void CQuad::drawW()
{
	drawingWithoutSetShader();
	glDrawArrays( GL_TRIANGLES, 0, QUAD_NUM );
}
