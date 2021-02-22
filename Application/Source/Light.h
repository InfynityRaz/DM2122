#ifndef LIGHT_H
#define LIGHT_H

#include "Vertex.h"

struct Light
{
	enum LIGHT_TYPE
	{
		LIGHT_POINT = 0,
		LIGHT_DIRECTIONAL,
		LIGHT_SPOT
	};
	Position position;
	Color color;
	float power;
	float kC, kL, kQ;
	LIGHT_TYPE type;
	Vector3 spotDirection;
	float cosCutoff;
	float cosInner;
	float exponent;

	Light() {}
};

#endif