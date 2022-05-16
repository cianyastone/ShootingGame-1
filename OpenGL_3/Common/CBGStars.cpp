#include <time.h>
#include "CBGStars.h"

CBGStars::CBGStars()
{
	srand((unsigned)time(NULL));
	_fSpeed = 5.f;	//�]�w���ʳt��

	//���͹��骫��
	for (int i = 0; i < STAR_NUM; i++) {
		_pStars[i] = new CQuad;
		_pStars[i]->setShader();
		_pStars[i]->setColor(vec4(0.7f, 0.7f, 0.7f, 1));	//gray

		_fStT[i][0] = -HALF_SCREEN_X + (rand() % (HALF_SCREEN_X * 2) + (rand() % 10) * 0.1);	//x�y��
		_fStT[i][1] = -HALF_SCREEN_Y + (rand() % (HALF_SCREEN_Y * 2) + (rand() % 10) * 0.1);	//y�y��
		_fStT[i][2] = -5;																	//z�y��
		_mxStT = Translate(_fStT[i][0], _fStT[i][1], _fStT[i][2]);
		_fStarScale = 0.1f;	//�Y��
		_mxStS = Scale(_fStarScale, _fStarScale, _fStarScale);
		_pStars[i]->setTRSMatrix(_mxStT * _mxStS);
	}
}

CBGStars::~CBGStars()
{
	for (int i = 0; i < STAR_NUM; i++) delete _pStars[i];
}

//---------------------------------------------------------

void CBGStars::UpdateMatrix(float delta)
{
	for (int i = 0; i < STAR_NUM; i++) {
		_fStT[i][1] -= delta * _fSpeed;	//y�y��
		_mxStT = Translate(_fStT[i][0], _fStT[i][1], _fStT[i][2]);
		_pStars[i]->setTRSMatrix(_mxStT * _mxStS);

		if (_fStT[i][1] < -HALF_SCREEN_Y) {
			_fStT[i][0] = -HALF_SCREEN_X + (rand() % (HALF_SCREEN_X * 2) + (rand() % 10) * 0.1);	//x�y��
			_fStT[i][1] = HALF_SCREEN_Y + 1;	//�W��}�l
		}
	}
}
void CBGStars::GL_Draw()
{
	for (int i = 0; i < STAR_NUM; i++) _pStars[i]->draw();
}
void CBGStars::SetViewMatrix(mat4 mvx)
{
	for (int i = 0; i < STAR_NUM; i++) _pStars[i]->setViewMatrix(mvx);
}
void CBGStars::SetProjectionMatrix(mat4 mpx)
{
	for (int i = 0; i < STAR_NUM; i++) _pStars[i]->setProjectionMatrix(mpx);
}