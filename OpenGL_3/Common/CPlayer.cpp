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

	//CreateBulletList();
	_AngleSpeed = 0;
}

CPlayer::~CPlayer()
{
	//DeleteBulletList();
}

void CPlayer::GL_SetTranslatMatrix(mat4& mat)
{
	_mxPT = mat;
	_fPT[0] = _mxPT._m[0][3];
	_fPT[1] = _mxPT._m[1][3];
}

mat4 CPlayer::GL_getTranslatMatrix()
{
	return _mxPT;
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

mat4 CPlayer::GetTRSMatrix()
{
	return(_mxPT);
}

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
	//_pBGet = _pBHead;
	//while (_pBGet != nullptr) {
	//	_pBGet->GL_draw();
	//	_pBGet = _pBGet->link;
	//}
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
		_mxBT = (*spriteIterator)->GetTranslateMatrix();
	}

	std::vector<std::vector<CBulletShoot*>::iterator> deleteArray;
	for (std::vector<CBulletShoot*>::iterator spriteIterator = bulletArray->begin();
		spriteIterator != bulletArray->end(); spriteIterator++)
	{
		if ((*spriteIterator)->GetBulletPosition() > 7.0f)
		{
			deleteArray.push_back(spriteIterator);
		}
	}

	for (std::vector<std::vector<CBulletShoot*>::iterator>::iterator deleteIterator = deleteArray.begin();
		deleteIterator != deleteArray.end(); deleteIterator++)
	{
		bulletArray->erase(*deleteIterator);
	}
}
//
//void CPlayer::CreateBulletList()	//�إߤl�u��C
//{
//	//first node
//	_pBHead = new CBulletShoot;
//	_pBHead->link = nullptr;
//	_pBTail = _pBHead;
//	_pBHead_shoot = _pBHead;	//�l�u�o�g��
//	_iBulletAmount++;				//�l�u�ƶq����
//
//	//the rest of nodes
//	for (int i = 0; i < BULLET_NUM - 1; i++) {
//		if ((_pBGet = new CBulletShoot) == NULL) {
//			printf("�O���餣��\n"); exit(0);
//		}
//		_pBGet->link = nullptr;
//		_pBTail->link = _pBGet;
//		_pBTail = _pBGet;
//		_iBulletAmount++;	//�l�u�ƶq����
//	}
//}
//
//void CPlayer::DeleteBulletList()	//�R���l�u��C
//{
//	_pBGet = _pBHead;
//	while (_pBHead != nullptr) {
//		_pBHead = _pBHead->link;
//		delete _pBGet;
//		_pBGet = _pBHead;
//	}
//	_iBulletAmount = 0;	//�l�u�ƶq�k�s
//}
//
//void CPlayer::SetBulletPassiveMove(mat4& mat)
//{
//	_pBGet = _pBHead;	//�l�u��C
//	while (_pBGet != nullptr) {
//		if (_pBGet->_bisShoot == false) { //�l�u�|���g�X
//			_pBGet->GL_SetTRSMatrix(mat);
//		}
//		_pBGet = _pBGet->link;
//	}
//}
//
//void CPlayer::ShootBullet(float delta, float passive_x)
//{
//	_pBGet_shoot = _pBHead_shoot;
//	_pBGet_shoot->shootBullet(delta, passive_x);
//	_mxBT = _pBGet_shoot->GetTranslateMatrix();	//��s�l�u��m
//	_pBGet_shoot->_bisShoot = true;		//�l�u�g�X
//}
//
//void CPlayer::NextBullet(float g_fPTx)
//{
//	_iBulletAmount--; //�l�u�ƶq����
//	_pBHead_shoot = _pBHead_shoot->link;
//	_pBGet_shoot->_bisShoot = false;
//
//	if (_iBulletAmount == 0) {	//�S���l�u
//		_pBHead_shoot = _pBHead;
//		_pBGet_shoot = _pBHead_shoot;
//		while (_pBGet_shoot != nullptr) {
//			_pBGet_shoot->ResetBullet(g_fPTx); //�l�u�k��
//			_pBGet_shoot = _pBGet_shoot->link;
//			_iBulletAmount++; //�l�u�ƶq����
//		}
//	}
//}


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


