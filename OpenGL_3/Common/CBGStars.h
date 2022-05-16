#ifndef CBGSTARS_H
#define CBGSTARS_H
#include "../Header/Angel.h"
#include "CQuad.h"

#define STAR_NUM 30			//�I���P�P�ƶq
#define HALF_SCREEN_X 5
#define HALF_SCREEN_Y 7

class CBGStars
{
protected:
	// For Objects
	CQuad *_pStars[STAR_NUM];

	//TRS matrix
	float _fSpeed;						//stars moving speed
	float _fStT[STAR_NUM][3] = { 0 };	//�C���P�P�y��
	float _fStarScale = 1;
	mat4 _mxStT, _mxStS;				//for star translation / scale

public:

	CBGStars();
	~CBGStars();

	void UpdateMatrix(float);			//��s�B��
	void GL_Draw();
	void SetViewMatrix(mat4);
	void SetProjectionMatrix(mat4);

};
#endif