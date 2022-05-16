#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H
#include "../header/Angel.h"
#include "CShape.h"
#include <iostream>


typedef struct {
	int top;
	int bottom;
	int left;
	int right;
}BoundingBox;

BoundingBox makeBoundingBox(int top, int bottom, int left, int right);


#endif