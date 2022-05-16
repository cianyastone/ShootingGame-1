#ifndef CBULLET_H
#define CBULLET_H
#include "../header/Angel.h"
#include "CShape.h"

typedef Angel::vec4  color4;
typedef Angel::vec4  point4;

#define QUAD_NUM 9		// 2 faces, 2 triangles/face 

class CBullet : public CShape
{
private:

public:
	CBullet();
	~CBullet() {};
	void update(float dt);
	GLuint getShaderHandle() { return _uiProgram; }

	void draw();
	void drawW();
};




#endif