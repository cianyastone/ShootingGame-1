#include "CPlayer.h"
// Example 4 �}�l
// ���P Example 3 �¤W(Y�b)
// �C�@�� Vertex �W�[ Normal �A�令�~���� CShape�A�@�ֳB�z�������]�w�ݨD


CPlayer::CPlayer()
{
	_iNumVtx = QUAD_NUM;
	_pPoints = NULL; _pNormals = NULL; _pTex = NULL;

	_pPoints = new vec4[_iNumVtx];
	_pNormals = new vec3[_iNumVtx];

	_pPoints[0] = vec4(0.5f, 0.0f, 0.0, 1.0f);
	_pPoints[1] = vec4(0.75f, 0.5f, 0.0, 1.0f);
	_pPoints[2] = vec4(1.0f, 0.0f, 0.0, 1.0f);
	_pPoints[3] = vec4(0.0f, 1.2f, 0.0, 1.0f);
	_pPoints[4] = vec4(-0.6f, 0.0f, 0.0, 1.0f);
	_pPoints[5] = vec4(0.6f, 0.0f, 0.0, 1.0f);
	_pPoints[6] = vec4(-0.5f, 0.0f, 0.0, 1.0f);
	_pPoints[7] = vec4(-0.75f, 0.5f, 0.0, 1.0f);
	_pPoints[8] = vec4(-1.0f, 0.0f, 0.0, 1.0f);

	_pNormals[0] = vec3(0, 1.0f, 0);  // Normal Vector �� W �� 0
	_pNormals[1] = vec3(0, 1.0f, 0);
	_pNormals[2] = vec3(0, 1.0f, 0);
	_pNormals[3] = vec3(0, 1.0f, 0);
	_pNormals[4] = vec3(0, 1.0f, 0);
	_pNormals[5] = vec3(0, 1.0f, 0);
	_pNormals[6] = vec3(0, 1.0f, 0);
	_pNormals[7] = vec3(0, 1.0f, 0);
	_pNormals[8] = vec3(0, 1.0f, 0);

	// Set shader's name
	setShaderName("vsVtxNormal.glsl", "fsVtxNormal.glsl");

	// Create and initialize a buffer object 
	createBufferObject();

	// �w�]�� -1.0f, �� Normal �M�w�C��
	_fColor[0] = -1.0f; _fColor[1] = -1.0f; _fColor[2] = -1.0f; _fColor[3] = 1;

	bulletArray = new std::vector<CBulletShoot*>;


	_AngleSpeed = 0;
}

void CPlayer::GL_SetTranslatMatrix(mat4& mat)
{
	_mxPT = mat;
	_fPT[0] = _mxPT._m[0][3];
	_fPT[1] = _mxPT._m[1][3];
}

vec2 CPlayer::GL_getTranslatVector()
{
	vec2 vT;
	vT.x = _fPT[0];
	vT.y = _fPT[1];
	return vT;
}

float CPlayer::GetPlayerScale()
{
	_fPlayerScale = 0.5f;
	return _fPlayerScale;
}

float CPlayer::GetPlayerY()
{
	return PLAYER_Y_AXIS;
}

void CPlayer::setBoundingBox(BoundingBox boundingBox)
{
	_boundingBox = boundingBox;
}

BoundingBox CPlayer::getBoundingBox()
{
	return _boundingBox;
}

/*void CPlayer::drawBullet()
{
	_lBGet = _lBHead;
	while (_lBGet != nullptr) {
		_lBGet->drawbullet();
		_lBGet = _lBGet->List;
	}
}

void CPlayer::setBullet()
{
	
}

void CPlayer::SetBulletPassiveMove(mat4& mat)
{
	_lBGet = _lBHead;	//�l�u��C
	while (_lBGet != nullptr) {
		if (_lBGet->_bisShoot == false) { //�l�u�|���g�X
			_lBGet->setTRSMatrix(mat);
		}
		_lBGet = _lBGet->List;
	}
}


void CPlayer::ShootBullet(float delta, float passive_x)
{
	_lBGet_shoot = _lBHead_shoot;
	//_lBGet_shoot->shootBullet(delta, passive_x);
	_mxBT = _lBGet_shoot->GetTRSMatrix();	//��s�l�u��m
	_lBGet_shoot->_bisShoot = true;		//�l�u�g�X
}

void CPlayer::NextBullet(float g_fPTx)
{
	_iBulletAmount--; //�l�u�ƶq����
	_lBHead_shoot = _lBHead_shoot->List;
	_lBGet_shoot->_bisShoot = false;

	if (_iBulletAmount == 0) {	//�S���l�u
		_lBHead_shoot = _lBHead;
		_lBGet_shoot = _lBHead_shoot;
		while (_lBGet_shoot != nullptr) {
			_lBGet_shoot->ResetBullet(g_fPTx); //�l�u�k��
			_lBGet_shoot = _lBGet_shoot->List;
			_iBulletAmount++; //�l�u�ƶq����
		}
	}
}*/
void CPlayer::UpdateMatrix(float delta)
{
	mat4 mxMa[QUAD_NUM];

	_AngleSpeed += 150.f * delta;
}


void CPlayer::update(float dt)
{
}

void CPlayer::GL_draw()
{
	draw();
	for (std::vector<CBulletShoot*>::iterator spriteIterator = bulletArray->begin();
		spriteIterator != bulletArray->end(); spriteIterator++) {
		(*spriteIterator)->GL_draw();
	}
}

void CPlayer::ShootBullet(float delta, float passive_x, int bullet_time)
{
	static int updates = 0;
	if (updates >= bullet_time) {
		CBulletShoot* bullet = new CBulletShoot;
		bulletArray->push_back(bullet);
		updates = 0;
	}
	updates++;

	for (std::vector<CBulletShoot*>::iterator spriteIterator = bulletArray->begin();
	spriteIterator != bulletArray->end(); spriteIterator++) {
		(*spriteIterator)->shootBullet(delta, passive_x);
		_mxBT = (*spriteIterator)->GetTRSMatrix();
	}


}

void CPlayer::draw()
{
	drawingSetShader();
	glDrawArrays(GL_TRIANGLES, 0, QUAD_NUM);
}

void CPlayer::drawW()
{
	drawingWithoutSetShader();
	glDrawArrays(GL_TRIANGLES, 0, QUAD_NUM);
}
