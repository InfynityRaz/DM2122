#ifndef MESH_BUILDER_H
#define MESH_BUILDER_H

#include "Mesh.h"
#include "Vertex.h"
#include "MyMath.h"
#include <vector>

/******************************************************************************/
/*!
		Class MeshBuilder:
\brief	Provides methods to generate mesh of different shapes
*/
/******************************************************************************/
class MeshBuilder
{
public:
	static Mesh* GenerateAxes(const std::string &meshName, float lengthX, float lengthY, float lengthZ);
	static Mesh* GenerateQuad(const std::string& meshName, Color color, float length = 1.f);
	static Mesh* GenerateCube(const std::string &meshName, Color color, float length = 1.f);
	static Mesh* GenerateCircle(const std::string& meshName, Color color, unsigned numSlice, float radius);
	static Mesh* GenerateSphere(const std::string& meshName, Color color, unsigned numStack, unsigned numSlice, float radius);
	static Mesh* GenerateFrustrum(const std::string& meshName, Color color, unsigned numSlice, float topRadius, float bottomRadius, float height);
	static Mesh* GenerateQuarterSphere(const std::string& meshName, Color color, unsigned numStack, unsigned numSlice, float radius);
};

#endif