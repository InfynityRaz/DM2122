#include "Scene2.h"
#include "GL\glew.h"

#include "shader.hpp"


Scene2::Scene2()
{
	rotateDirection = 0;
	scaleDirection = 0;
}

Scene2::~Scene2()
{
}

void Scene2::Init()
{
	rotateAngle = 30;
	translateX = 1;
 	scaleAll = 3;

	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	glGenBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
	glGenBuffers(NUM_GEOMETRY, &m_colorBuffer[0]);

	static const GLfloat vertex_buffer_data[] = 
	{
		-0.5, 0.5, 0,
		0.5, 0.5, 0,
		-0.5, -0.5, 0,
		0.5, 0.5, 0,
		-0.5, -0.5, 0,
		0.5, -0.5, 0,
	};

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_1]);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data, GL_STATIC_DRAW);

	static const GLfloat color_buffer_data[] =
	{
		1, 0, 0,
		1, 0, 0,
		1, 0, 0,
		1, 0, 0,
		1, 0, 0,
		1, 0, 0,
	};

	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data), color_buffer_data, GL_STATIC_DRAW);

	m_programID = LoadShaders("Shader//TransformVertexShader.vertexshader", "Shader//SimpleFragmentShader.fragmentshader");
	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");

	glUseProgram(m_programID);

	glEnable(GL_DEPTH_TEST);
}

void Scene2::Update(double dt)
{
	if (rotateDirection == 0)
		rotateAngle += (float)(100 * dt);
	else
		rotateAngle -= (float)(100 * dt);
	if (rotateAngle >= 60)
		rotateDirection = 1;
	else if (rotateAngle <= 30)
		rotateDirection = 0;
	translateX += (float)(10 * dt);
	if (translateX >= 20)
		translateX = -15;
	if (scaleDirection == 0)
		scaleAll += (float)(2 * dt);
	else
		scaleAll -= (float)(2 * dt);
	if (scaleAll >= 9)
		scaleDirection = 1;
	else if (scaleAll <= 3)
		scaleDirection = 0;
}

void Scene2::Render()
{
	Mtx44 translate, rotate, scale;
	Mtx44 model;
	Mtx44 view;
	Mtx44 projection;
	Mtx44 MVP;

	translate.SetToIdentity();
	rotate.SetToIdentity();
	scale.SetToIdentity();
	model.SetToIdentity();
	view.SetToIdentity();
	projection.SetToOrtho(-10, 10, -10, 10, -10, 10);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	translate.SetToTranslation(-5, 5, 0);
	scale.SetToScale(3, 3, 3);
	rotate.SetToRotation(rotateAngle, 0, 0, 1);
	model = rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_1]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_1]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	translate.SetToTranslation(translateX, 5, 0);
	scale.SetToScale(3, 3, 3);
	rotate.SetToRotation(130, 0, 0, 1);
	model = translate * rotate;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_1]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_1]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0); 
	glDrawArrays(GL_TRIANGLES, 0, 6);

	translate.SetToTranslation(-5, -2, 0);
	scale.SetToScale(scaleAll, scaleAll, scaleAll);
	rotate.SetToRotation(130, 0, 0, 1);
	model = translate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_1]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_1]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(1);

	glDisableVertexAttribArray(0);
}

void Scene2::Exit()
{
	glDeleteBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
	glDeleteBuffers(NUM_GEOMETRY, &m_colorBuffer[0]);
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}
