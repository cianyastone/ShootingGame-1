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
#define BULLET_NUM 10				//子彈數量

class CPlayer : public CShape
{
private:
	// Matrix 
	mat4 _mxView, _mxProjection;
	mat4 _mxMVFinal, _mxTRS;

	float _fPT[3] = { 1 };					//for player translation / scale
	int _MaskNum = 5;

	GLfloat _AngleSpeed;

	// 紀錄是否有矩陣的更新
	bool  _bUpdateMV;
	bool  _bUpdateProj;

	//玩家
	float _fPlayerScale = 1;
	mat4 _mxPT, _mxPS, _mxBT, _mxMask[QUAD_NUM];

	//子彈串列
	/*CBulletShoot*_pBHead, *_pBTail, *_pBGet;
	CBulletShoot*_pBHead_shoot, *_pBGet_shoot;*/	//子彈發射用

	//BoundingBox
	BoundingBox _boundingBox;

public:
	CPlayer();
	~CPlayer();
	void update(float dt);
	GLuint getShaderHandle() { return _uiProgram; }
	std::vector<CBulletShoot*>* bulletArray;

								//射出子彈
	void GL_SetTranslatMatrix(mat4& mat);				//更新位置
	mat4 GL_getTranslatMatrix();
	float GetPlayerScale();
	float GetPlayerY();
	int _iBulletAmount;
	void setBoundingBox(BoundingBox boundingBox);
	BoundingBox getBoundingBox();

	void CreateBulletList();							//建立子彈串列
	void DeleteBulletList();							//刪除子彈串列
	void ShootBullet(float delta, float passive_x, int bullet_time);		//發射子彈
	void NextBullet(float);								//下一顆子彈
	void SetBulletPassiveMove(mat4&);					//子彈跟隨滑鼠

	void drawBullet();
	void setBullet();
	void UpdateMatrix(float delta);
	void GL_draw();
	void draw();
	void drawW();
	mat4 GetTRSMatrix();
};


#endif