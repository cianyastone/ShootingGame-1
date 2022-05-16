#ifndef C2DSPRITE_H
#define C2DSPRITE_H

#include "../header/Angel.h"
#include "CShape.h"

typedef Angel::vec4  color4;
typedef Angel::vec4  point4;

#define QUAD_NUM 6		// 2 faces, 2 triangles/face 
#define Square_Size 100

class C2DSprite : public CShape
{
private:
	GLuint _textureBufferID;
	vec2 _velocity;
	GLfloat _rotation;

protected:
	float _fscale = 1;
	vec2 _position;
	float _fBT[3] = { 0 };
	mat4 _mxBS;							//for bullet scale

public:

	C2DSprite();
	C2DSprite(vec2 position);
	~C2DSprite();

	vec4  _OriginalLL, _OriginalTR;  // sprite 在 local 座標的左下與右上兩個頂點座標
	vec4  _LL, _TR;  // sprite 在世界座標的左上與右下兩個頂點座標
	vec4  _DefaultColor;
	bool  _bPushed;
	float _fBulletSpeed;

	void setTRSMatrix(mat4 &mat);
	void update(float dt);
	void update();
	void setDefaultColor(vec4 vColor);
	bool getButtonStatus(){ return _bPushed; }
	bool onTouches(const vec2 &tp);
	vec2 addVector2(vec2 v1, vec2 v2);

	GLuint getShaderHandle() { return _uiProgram; }

	void draw();
	void drawW();

	void setRotation(GLfloat rotation);
	GLfloat getRotaion();

	void setPosition(vec2 newPosition);
	vec2 getPosition();

	void setVelocity(vec2 newVector);
	vec2 getVelocity();


};




#endif