#include "CBulletShoot.h"
#include "CQuad.h"
#include "CPlayer.h"

CPlayer* _pPlayer;				// ª±®a

CBulletShoot::CBulletShoot()
{
	//Bullet status
	_bisShoot = false;
	_fbulletSpeed = 5.0f;

	g_fPTy = _pPlayer->GetPlayerY();

	_pBBullet = new CQuad;
	_pBBullet->setShader();
	_pBBullet->setColor(vec4(1.0f, 1.0f, 0.7607f, 1));

	_fBT[1] = PLAYER_Y_AXIS;
	_mxBT = Translate(_fBT[0], _fBT[1], _fBT[2]);
	_fscale = 0.1;
	_mxBS = Scale(_fscale, _fscale, _fscale);
	_pBBullet->setTRSMatrix(_mxBT * _mxBS);
}

void CBulletShoot::GL_setTranslatMatrix(mat4& mat)
{
	_mxBT = mat;
	_fBT[0] = _mxBT._m[0][3];
	_fBT[1] = _mxBT._m[1][3];
	_mxBT = Translate(_fBT[0], _fBT[1], _fBT[2]);
	_pBBullet->setTRSMatrix(mat);
}

void CBulletShoot::GL_draw()
{
	_pBBullet->draw();
}

void CBulletShoot::shootBullet(float delta, float passive_x)
{
	if (!_bisShoot) {
		_fBT[0] = passive_x;
		_bisShoot = true;
	}
	_fBT[1] += delta * _fbulletSpeed;
	_mxBT = Translate(_fBT[0], _fBT[1], _fBT[2]);
	_pBBullet->setTRSMatrix(_mxBT * _mxBS);
}


void CBulletShoot::update(float dt)
{
}

void CBulletShoot::GL_SetTRSMatrix(mat4& mat)
{
	_fBT[0] = mat._m[0][3];
	_fBT[1] = mat._m[1][3];
	_mxBT = Translate(_fBT[0], _fBT[1], _fBT[2]);
	_pBBullet->setTRSMatrix(mat);
}


mat4 CBulletShoot::GetTRSMatrix()
{
	return(_pBBullet->GetTRSMatrix());
}

mat4 CBulletShoot::GetTranslateMatrix()
{
	return _mxBT;
}

float CBulletShoot::GetBulletPosition()
{
	float y;
	y = _mxBT._m[1][3];
	return y;
}

void CBulletShoot::ResetBullet(float fPTx)
{
	_fBT[0] = fPTx;
	_fBT[1] = PLAYER_Y_AXIS;
	_mxBT = Translate(_fBT[0], _fBT[1], _fBT[2]);
	_pBBullet->setTRSMatrix(_mxBT);
}