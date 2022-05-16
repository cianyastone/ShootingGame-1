#include "CCQuad.h"

CCQuad::CCQuad()
{
	_iNumVtx = QUAD_NUM;
	_pPoints = new vec4[QUAD_NUM];

	_pPoints[0] = vec4(-0.5f, 0.5f, 0.0f, 1.0f);
	_pPoints[1] = vec4(0.5f, 0.5f, 0.0f, 1.0f);
	_pPoints[2] = vec4(0.5f, -0.5f, 0.0f, 1.0f);
	_pPoints[3] = vec4(-0.5f, 0.5f, 0.0f, 1.0f);
	_pPoints[4] = vec4(0.5f, -0.5f, 0.0f, 1.0f);
	_pPoints[5] = vec4(-0.5f, -0.5f, 0.0f, 1.0f);

	_pNormals = new vec3[QUAD_NUM];
	_pNormals[0] = vec3(1.0f, 1.0f, 1.0f);  // (r, g, b, a)
	_pNormals[1] = vec3(1.0f, 0.0f, 0.0f);
	_pNormals[2] = vec3(0.0f, 1.0f, 0.0f);
	_pNormals[3] = vec3(1.0f, 1.0f, 1.0f);
	_pNormals[4] = vec3(0.0f, 1.0f, 0.0f);
	_pNormals[5] = vec3(0.0f, 0.0f, 1.0f);

	// Create and initialize a buffer object 
	createBufferObject();
	_bProjUpdated = false;
}

CCQuad::CCQuad(int objectID)
{
	switch (objectID)
	{
	case 0://bg
		_iNumVtx = 30;
		_pPoints = new vec4[_iNumVtx];

		_pPoints[0] = vec4(-1.1357f, -1.9671f, 0.0f, 1.0f);//1
		_pPoints[1] = vec4(0.0000f, -4.7354f, 0.0f, 1.0f);//2
		_pPoints[2] = vec4(1.1357f, -1.9671f, 0.0f, 1.0f);//3
		_pPoints[3] = vec4(1.1357f, -1.9671f, 0.0f, 1.0f);
		_pPoints[4] = vec4(4.1010f, -2.3677f, 0.0f, 1.0f);//4
		_pPoints[5] = vec4(2.2714f, 0.0000f, 0.0f, 1.0f);//5
		_pPoints[6] = vec4(-1.1357f, 1.9671f, 0.0f, 1.0f);//6
		_pPoints[7] = vec4(-4.1010f, 2.3677f, 0.0f, 1.0f);//7
		_pPoints[8] = vec4(-2.2714f, -0.0000f, 0.0f, 1.0f);//8
		_pPoints[9] = vec4(1.1357f, 1.9671f, 0.0f, 1.0f);//9
		_pPoints[10] = vec4(-0.0000f, 4.7354f, 0.0f, 1.0f);//10
		_pPoints[11] = vec4(-1.1357f, 1.9671f, 0.0f, 1.0f);//6
		_pPoints[12] = vec4(2.2714f, 0.0000f, 0.0f, 1.0f);//5
		_pPoints[13] = vec4(4.1010f, 2.3677f, 0.0f, 1.0f);//11
		_pPoints[14] = vec4(1.1357f, 1.9671f, 0.0f, 1.0f);//9
		_pPoints[15] = vec4(-2.2714f, -0.0000f, 0.0f, 1.0f);//8
		_pPoints[16] = vec4(-4.1010f, -2.3677f, 0.0f, 1.0f);//12
		_pPoints[17] = vec4(-1.1357f, -1.9671f, 0.0f, 1.0f);//1
		_pPoints[18] = vec4(-1.1357f, 1.9671f, 0.0f, 1.0f);//6
		_pPoints[19] = vec4(-2.2714f, -0.0000f, 0.0f, 1.0f);//8
		_pPoints[20] = vec4(-1.1357f, -1.9671f, 0.0f, 1.0f);//1
		_pPoints[21] = vec4(1.1357f, 1.9671f, 0.0f, 1.0f);//9
		_pPoints[22] = vec4(-1.1357f, 1.9671f, 0.0f, 1.0f);//6
		_pPoints[23] = vec4(-1.1357f, -1.9671f, 0.0f, 1.0f);//1
		_pPoints[24] = vec4(2.2714f, 0.0000f, 0.0f, 1.0f);//5
		_pPoints[25] = vec4(1.1357f, 1.9671f, 0.0f, 1.0f);//9
		_pPoints[26] = vec4(-1.1357f, -1.9671f, 0.0f, 1.0f);//1
		_pPoints[27] = vec4(1.1357f, -1.9671f, 0.0f, 1.0f);//3
		_pPoints[28] = vec4(2.2714f, 0.0000f, 0.0f, 1.0f);//5
		_pPoints[29] = vec4(-1.1357f, -1.9671f, 0.0f, 1.0f);//1
		_pNormals = new vec3[_iNumVtx];
		for (int i = 0; i < _iNumVtx; i++) _pNormals[i] = vec3(1.0f, 1.0f, 1.0f);
		break;
	case 1://bullet
		_iNumVtx = 18;
		_pPoints = new vec4[_iNumVtx];

		_pPoints[0] = vec4(-3.1458f, -3.1458f, 0.0f, 1.0f);//1
		_pPoints[1] = vec4(0.0000f, -4.4500f, 0.0f, 1.0f);//2
		_pPoints[2] = vec4(3.1458f, -3.1458f, 0.0f, 1.0f);//3
		_pPoints[3] = vec4(-4.4500f, -0.0000f, 0.0f, 1.0f);//4
		_pPoints[4] = vec4(-3.1458f, -3.1458f, 0.0f, 1.0f);//1
		_pPoints[5] = vec4(3.1458f, -3.1458f, 0.0f, 1.0f);//3
		_pPoints[6] = vec4(-3.1458f, 3.1458f, 0.0f, 1.0f);//5
		_pPoints[7] = vec4(-4.4500f, -0.0000f, 0.0f, 1.0f);//4
		_pPoints[8] = vec4(3.1458f, -3.1458f, 0.0f, 1.0f);//3
		_pPoints[9] = vec4(-0.0000f, 4.4500f, 0.0f, 1.0f);//6
		_pPoints[10] = vec4(-3.1458f, 3.1458f, 0.0f, 1.0f);//5
		_pPoints[11] = vec4(3.1458f, -3.1458f, 0.0f, 1.0f);//3
		_pPoints[12] = vec4(3.1458f, 3.1458f, 0.0f, 1.0f);//7
		_pPoints[13] = vec4(-0.0000f, 4.4500f, 0.0f, 1.0f);//6
		_pPoints[14] = vec4(3.1458f, -3.1458f, 0.0f, 1.0f);//3
		_pPoints[15] = vec4(4.4500f, 0.0000f, 0.0f, 1.0f);//8
		_pPoints[16] = vec4(3.1458f, 3.1458f, 0.0f, 1.0f);//7
		_pPoints[17] = vec4(3.1458f, -3.1458f, 0.0f, 1.0f);//3
		_pNormals = new vec3[_iNumVtx];
		for (int i = 0; i < _iNumVtx; i++) _pNormals[i] = vec3(1.0f, 1.0f, 1.0f);
		break;
	case 3://player
		_iNumVtx = 9;
		_pPoints = new vec4[_iNumVtx];

		_pPoints[0] = vec4(3.0462f, -2.3839f, 0.0f, 1.0f);
		_pPoints[1] = vec4(-0.0000f, 4.7240f, 0.0f, 1.0f);
		_pPoints[2] = vec4(-3.0462f, -2.3839f, 0.0f, 1.0f);
		_pPoints[3] = vec4(1.0154f, -2.3839f, 1.0f, 1.0f);
		_pPoints[4] = vec4(0.0000f, 4.7240f, 1.0f, 1.0f);
		_pPoints[5] = vec4(-1.0154f, -2.3839f, 1.0f, 1.0f);
		_pPoints[6] = vec4(-1.0154f, -2.3839f, 1.0f, 1.0f);
		_pPoints[7] = vec4(0.0000f, -4.4147f, 1.0f, 1.0f);
		_pPoints[8] = vec4(1.0154f, -2.3839f, 1.0f, 1.0f);
		_pNormals = new vec3[_iNumVtx];
		for (int i = 0; i < 3; i++) _pNormals[i] = vec3(0.9411f, 0.3294f, 0.309f);
		for (int i = 3; i < _iNumVtx; i++) _pNormals[i] = vec3(0.9529f, 0.9529f, 0.9529f);
		break;
	case 4://boss
		_iNumVtx = 57;
		_pPoints = new vec4[_iNumVtx];

		_pPoints[0] = vec4(1.3847f, 1.8627f, 0.0f, 1.0f);//14
		_pPoints[1] = vec4(1.3847f, -1.0603f, 0.0f, 1.0f);//15
		_pPoints[2] = vec4(3.8799f, 1.4451f, 0.0f, 1.0f);//16
		_pPoints[3] = vec4(3.8799f, 3.9505f, 0.0f, 1.0f);//17
		_pPoints[4] = vec4(1.3847f, 1.8627f, 0.0f, 1.0f);//14
		_pPoints[5] = vec4(3.8799f, 1.4451f, 0.0f, 1.0f);//16
		_pPoints[6] = vec4(4.5928f, 3.9505f, 0.0f, 1.0f);//18
		_pPoints[7] = vec4(3.8799f, 3.9505f, 0.0f, 1.0f);//17
		_pPoints[8] = vec4(3.8799f, 1.4451f, 0.0f, 1.0f);//16
		_pPoints[9] = vec4(4.5928f, -2.3130f, 0.0f, 1.0f);//19
		_pPoints[10] = vec4(4.5928f, 3.9505f, 0.0f, 1.0f);//18
		_pPoints[11] = vec4(3.8799f, 1.4451f, 0.0f, 1.0f);//16
		_pPoints[12] = vec4(4.5928f, -2.3130f, 0.0f, 1.0f);//19
		_pPoints[13] = vec4(3.8799f, 1.4451f, 0.0f, 1.0f);//16
		_pPoints[14] = vec4(3.8799f, -2.3130f, 0.0f, 1.0f);//20

		_pPoints[15] = vec4(-3.8738f, 1.4451f, 0.0f, 1.0f);//21
		_pPoints[16] = vec4(-1.3786f, -1.0603f, 0.0f, 1.0f);//22
		_pPoints[17] = vec4(-1.3786f, 1.8627f, 0.0f, 1.0f);//23
		_pPoints[18] = vec4(-3.8738f, 1.4451f, 0.0f, 1.0f);//21
		_pPoints[19] = vec4(-1.3786f, 1.8627f, 0.0f, 1.0f);//23
		_pPoints[20] = vec4(-3.8738f, 3.9505f, 0.0f, 1.0f);//24
		_pPoints[21] = vec4(-3.8738f, 1.4451f, 0.0f, 1.0f);//21
		_pPoints[22] = vec4(-3.8738f, 3.9505f, 0.0f, 1.0f);//24
		_pPoints[23] = vec4(-4.5867f, 3.9505f, 0.0f, 1.0f);//25
		_pPoints[24] = vec4(-3.8738f, 1.4451f, 0.0f, 1.0f);//21
		_pPoints[25] = vec4(-4.5867f, 3.9505f, 0.0f, 1.0f);//25
		_pPoints[26] = vec4(-4.5867f, -2.3130f, 0.0f, 1.0f);//26
		_pPoints[27] = vec4(-3.8738f, -2.3130f, 0.0f, 1.0f);//27
		_pPoints[28] = vec4(-3.8738f, 1.4451f, 0.0f, 1.0f);//21
		_pPoints[29] = vec4(-4.5867f, -2.3130f, 0.0f, 1.0f);//26

		_pPoints[30] = vec4(1.3794f, -1.8954f, 1.0f, 1.0f);//1
		_pPoints[31] = vec4(1.3794f, 2.6978f, 1.0f, 1.0f);//2
		_pPoints[32] = vec4(0.9209f, 2.6978f, 1.0f, 1.0f);//3
		_pPoints[33] = vec4(-1.3715f, -1.8954f, 1.0f, 1.0f);//4
		_pPoints[34] = vec4(0.0040f, -4.4008f, 1.0f, 1.0f);//5
		_pPoints[35] = vec4(1.3794f, -1.8954f, 1.0f, 1.0f);//1
		_pPoints[36] = vec4(-1.3715f, -1.8954f, 1.0f, 1.0f);//4
		_pPoints[37] = vec4(1.3794f, -1.8954f, 1.0f, 1.0f);//1
		_pPoints[38] = vec4(0.9209f, 2.6978f, 1.0f, 1.0f);//3
		_pPoints[39] = vec4(-0.9130f, 2.6978f, 1.0f, 1.0f);//6
		_pPoints[40] = vec4(-1.3715f, 2.6978f, 1.0f, 1.0f);//7
		_pPoints[41] = vec4(-1.3715f, -1.8954f, 1.0f, 1.0f);//4
		_pPoints[42] = vec4(-0.9130f, 2.6978f, 1.0f, 1.0f);//6
		_pPoints[43] = vec4(-1.3715f, -1.8954f, 1.0f, 1.0f);//4
		_pPoints[44] = vec4(0.9209f, 2.6978f, 1.0f, 1.0f);//3
		_pPoints[45] = vec4(-0.4545f, 3.5329f, 1.0f, 1.0f);//8
		_pPoints[46] = vec4(-0.9130f, 2.6978f, 1.0f, 1.0f);//6
		_pPoints[47] = vec4(0.9209f, 2.6978f, 1.0f, 1.0f);//3
		_pPoints[48] = vec4(0.4625f, 3.5329f, 1.0f, 1.0f);//9
		_pPoints[49] = vec4(-0.4545f, 3.5329f, 1.0f, 1.0f);//8
		_pPoints[50] = vec4(0.9209f, 2.6978f, 1.0f, 1.0f);//3

		_pPoints[51] = vec4(0.9209f, -0.6427f, 2.0f, 1.0f);//10
		_pPoints[52] = vec4(-0.9130f, -0.6427f, 2.0f, 1.0f);//11
		_pPoints[53] = vec4(-0.6838f, -1.8954f, 2.0f, 1.0f);//12
		_pPoints[54] = vec4(0.9209f, -0.6427f, 2.0f, 1.0f);//10
		_pPoints[55] = vec4(-0.6838f, -1.8954f, 2.0f, 1.0f);//12
		_pPoints[56] = vec4(0.6917f, -1.8954f, 2.0f, 1.0f);//13


		_pNormals = new vec3[_iNumVtx];
		for (int i = 0; i < 30; i++) _pNormals[i] = vec3(0.9529f, 0.9529f, 0.9529f);
		for (int i = 30; i < 51; i++) _pNormals[i] = vec3(0.9803f, 0.9803f, 0.9803f);
		for (int i = 51; i < _iNumVtx; i++) _pNormals[i] = vec3(0.2f, 0.6f, 0.5372f);
		break;
	}


	// Create and initialize a buffer object 
	createBufferObject();
	_bProjUpdated = false;
}


void CCQuad::draw()
{
	glUseProgram(_uiProgram);
	glBindVertexArray(_uiVao);
	if (_bViewUpdated) {
		_mxMVFinal = _mxView * _mxTRS;
		_bViewUpdated = false;
	}
	glUniformMatrix4fv(_uiModelView, 1, GL_TRUE, _mxMVFinal);

	if (_bProjUpdated) {
		glUniformMatrix4fv(_uiProjection, 1, GL_TRUE, _mxProjection);
		_bProjUpdated = false;
	}
	glDrawArrays(GL_TRIANGLES, 0, _iNumVtx);
}

void CCQuad::drawW()
{
	glBindVertexArray(_uiVao);

	if (_bViewUpdated) {
		_mxMVFinal = _mxView * _mxTRS;
		_bViewUpdated = false;
	}

	glUniformMatrix4fv(_uiModelView, 1, GL_TRUE, _mxMVFinal);
	if (_bProjUpdated) {
		glUniformMatrix4fv(_uiProjection, 1, GL_TRUE, _mxProjection);
		_bProjUpdated = false;
	}
	glDrawArrays(GL_TRIANGLES, 0, _iNumVtx);
}