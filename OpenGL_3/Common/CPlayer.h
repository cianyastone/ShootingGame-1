#ifndef CPLAYER_H
#define CPLAYER_H
#include "../header/Angel.h"
#include "CShape.h"
#include "CBulletShoot.h"
#include "BoundingBox.h"
#include "C2DSprite.h"

typedef Angel::vec4  color4;
typedef Angel::vec4  point4;

#define QUAD_NUM 9		// 2 faces, 2 triangles/face 
#define PLAYER_Y_AXIS -7.f
#define BULLET_NUM 10				//�l�u�ƶq

class CPlayer : public CShape
{
private:
	// Matrix 
	mat4 _mxView, _mxProjection;
	mat4 _mxMVFinal, _mxTRS;

	float _fPT[3] = { 1 };					//for player translation / scale
	int _MaskNum = 5;

	GLfloat _AngleSpeed;

	// �����O�_���x�}����s
	bool  _bUpdateMV;
	bool  _bUpdateProj;

	//���a
	float _fPlayerScale = 1;
	mat4 _mxPT, _mxPS, _mxBT, _mxMask[QUAD_NUM];

	//�l�u��C
	CBulletShoot*_lBHead, *_lBTail, *_lBGet;
	CBulletShoot*_lBHead_shoot, *_lBGet_shoot;	//�l�u�o�g��

	//BoundingBox
	BoundingBox _boundingBox;

public:
	CPlayer();
	~CPlayer() {};
	void update(float dt);
	GLuint getShaderHandle() { return _uiProgram; }
	std::vector<CBulletShoot*>* bulletArray;
								//�g�X�l�u
	void GL_SetTranslatMatrix(mat4& mat);				//��s��m
	vec2 GL_getTranslatVector();
	float GetPlayerScale();
	float GetPlayerY();
	int _iBulletAmount;
	void setBoundingBox(BoundingBox boundingBox);
	BoundingBox getBoundingBox();

	void drawBullet();
	void setBullet();
	void SetBulletPassiveMove(mat4& mat);
	void ShootBullet(float delta, float passive_x, int bullet_time);
	void NextBullet(float g_fPTx);
	void UpdateMatrix(float delta);
	void GL_draw();
	void draw();
	void drawW();
};


#endif