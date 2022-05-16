#ifndef CBULLETSHOOT_H
#define CBULLETSHOOT_H
#include "../header/Angel.h"
#include "CShape.h"
#include <vector>

typedef Angel::vec4  color4;
typedef Angel::vec4  point4;

#define QUAD_NUM 6		// 2 faces, 2 triangles/face 

class CBulletShoot
{
private:

	float _fBT[3] = { 1 };					//for player translation / scale
	float g_fPTy;

	// �����O�_���x�}����s
	bool  _bUpdateMV;
	bool  _bUpdateProj;

	float _fPlayerScale = 1;
	float _fscale = 1;
	mat4 _mxBT, _mxBS, _mxBR;

	//�l�u
	float _fbulletSpeed;					//Bullet Speed
	
public:
	CBulletShoot();
	~CBulletShoot() {};
	void update(float dt);

	bool _bisShoot;							//Bullet Status
	void GL_setTranslatMatrix(mat4& mat);
	void shootBullet(float delta, float passive_x);
	void ResetBullet(float fPTx);
	float GetBulletPosition();
	void GL_draw();
	mat4 GetTRSMatrix();
};

#endif