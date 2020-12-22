#ifndef SCENELIGHTASSIGNMENT_H
#define SCENELIGHTASSIGNMENT_H

#include "Scene.h"
#include "Camera.h"
#include "Camera2.h"
#include "Light.h"
#include "Utility.h"
#include "Mesh.h"
#include "Mtx44.h"
#include "Application.h"
#include "MeshBuilder.h"
#include "MatrixStack.h"

class SceneLightAssignment : public Scene
{
	enum GEOMETRY_TYPE
	{
		GEO_AXES,
		GEO_FRUSTRUM,
		GEO_CIRCLE,
		GEO_QUARTERSPHERE,
		GEO_SPHERE,
		GEO_LIGHTBALL,
		GEO_QUAD,
		NUM_GEOMETRY,
	};

	enum UNIFORM_TYPE
	{
		U_MVP = 0,
		U_MODELVIEW,
		U_MODELVIEW_INVERSE_TRANSPOSE,
		U_MATERIAL_AMBIENT,
		U_MATERIAL_DIFFUSE,
		U_MATERIAL_SPECULAR,
		U_MATERIAL_SHININESS,
		U_LIGHT0_POSITION,
		U_LIGHT0_COLOR,
		U_LIGHT0_POWER,
		U_LIGHT0_KC,
		U_LIGHT0_KL,
		U_LIGHT0_KQ,
		U_LIGHT0_TYPE,
		U_LIGHT0_SPOTDIRECTION,
		U_LIGHT0_COSCUTOFF,
		U_LIGHT0_COSINNER,
		U_LIGHT0_EXPONENT,
		U_LIGHTENABLED,
		U_NUMLIGHTS,
		U_TOTAL,
	};

public:
	SceneLightAssignment();
	~SceneLightAssignment();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

private:
	unsigned m_vertexArrayID;
	Mesh *meshList[NUM_GEOMETRY];

	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];

	float rotateAngle;

	Camera2 camera;

	MS modelStack, viewStack, projectionStack;

	Light light[1];

	void RenderMesh(Mesh* mesh, bool enableLight);

	float headAngle;
	float leftUpperArmAngle;
	float rightUpperArmAngle;
	float leftLowerArmAngle;
	float rightLowerArmAngle;
	float leftUpperLegAngle;
	float rightUpperLegAngle;
	float leftLowerLegAngle;
	float rightLowerLegAngle;
};

#endif