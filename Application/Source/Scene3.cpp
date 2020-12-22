#include "Scene3.h"
#include "GL\glew.h"

#include "shader.hpp"


Scene3::Scene3()
{
}

Scene3::~Scene3()
{
}

void Scene3::Init()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	glGenBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
	glGenBuffers(NUM_GEOMETRY, &m_colorBuffer[0]);

	static const GLfloat vertex_buffer_data_1[] = 
	{
		0, 3, 0,

	};

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[TREE]);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data_1), vertex_buffer_data_1, GL_STATIC_DRAW);

	static const GLfloat color_buffer_data_1[] =
	{
		0, 0, 0,
		0, 0, 0,
		0, 0, 0,
	};

	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[TREE]);

	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data_1), color_buffer_data_1, GL_STATIC_DRAW);

	m_programID = LoadShaders("Shader//TransformVertexShader.vertexshader", "Shader//SimpleFragmentShader.fragmentshader");
	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");

	glUseProgram(m_programID);

	glEnable(GL_DEPTH_TEST);
}

void Scene3::Update(double dt)
{
	rotateAngle += (float)(1 * dt);
	translateX += (float)(1 * dt);
	scaleAll += (float)(1 * dt);
}

void Scene3::Render()
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

	model = rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[TREE]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[TREE]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 6);

	glDisableVertexAttribArray(1);

	glDisableVertexAttribArray(0);
}

void Scene3::Exit()
{
	glDeleteBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
	glDeleteBuffers(NUM_GEOMETRY, &m_colorBuffer[0]);
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}
