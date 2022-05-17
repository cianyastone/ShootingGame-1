#ifndef CBULLETSHOOT_H
#define CBULLETSHOOT_H
#include "../header/Angel.h"
#include "CShape.h"
#include "CQuad.h"
#include <vector>

typedef Angel::vec4  color4;
typedef Angel::vec4  point4;

#define QUAD_NUM 6		// 2 faces, 2 triangles/face 

class CBulletShoot
{
private:

	float _fBT[3] = { 0 };					//for player translation / scale
	float g_fPTy;

	CQuad* _pBBullet;

	// 紀錄是否有矩陣的更新
	bool  _bUpdateMV;
	bool  _bUpdateProj;

	float _fPlayerScale = 1;
	float _fscale = 1;
	mat4 _mxBT, _mxBS, _mxBR;

	//子彈
	float _fbulletSpeed;					//Bullet Speed
	
public:
	CBulletShoot();
	~CBulletShoot() {};
	void update(float dt);
	//CBulletShoot* link;

	bool _bisShoot;							//Bullet Status
	void GL_setTranslatMatrix(mat4& mat);
	void GL_SetTRSMatrix(mat4& mat);
	void shootBullet(float delta, float passive_x);
	void ResetBullet(float fPTx);
	float GetBulletPosition();
	void GL_draw();
	mat4 GetTRSMatrix();
	mat4 GetTranslateMatrix();
};

#endif