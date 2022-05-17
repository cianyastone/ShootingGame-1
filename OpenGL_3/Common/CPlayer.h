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
	/*CBulletShoot*_pBHead, *_pBTail, *_pBGet;
	CBulletShoot*_pBHead_shoot, *_pBGet_shoot;*/	//�l�u�o�g��

	//BoundingBox
	BoundingBox _boundingBox;

public:
	CPlayer();
	~CPlayer();
	void update(float dt);
	GLuint getShaderHandle() { return _uiProgram; }
	std::vector<CBulletShoot*>* bulletArray;

								//�g�X�l�u
	void GL_SetTranslatMatrix(mat4& mat);				//��s��m
	mat4 GL_getTranslatMatrix();
	float GetPlayerScale();
	float GetPlayerY();
	int _iBulletAmount;
	void setBoundingBox(BoundingBox boundingBox);
	BoundingBox getBoundingBox();

	void CreateBulletList();							//�إߤl�u��C
	void DeleteBulletList();							//�R���l�u��C
	void ShootBullet(float delta, float passive_x, int bullet_time);		//�o�g�l�u
	void NextBullet(float);								//�U�@���l�u
	void SetBulletPassiveMove(mat4&);					//�l�u���H�ƹ�

	void drawBullet();
	void setBullet();
	void UpdateMatrix(float delta);
	void GL_draw();
	void draw();
	void drawW();
	mat4 GetTRSMatrix();
};


#endif