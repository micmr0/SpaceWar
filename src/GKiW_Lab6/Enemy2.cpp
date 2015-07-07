#include "StdAfx.h"
#include "Enemy2.h"
#include "Scene.h"
CEnemy2::CEnemy2() : CSceneObject()
{
}


CEnemy2::~CEnemy2(void)
{
}

void CEnemy2::Initialize(void)
{

	_displayListEnemy = glGenLists(1);

	glNewList(_displayListEnemy, GL_COMPILE);
	float m0_amb[] = { 0, 0, 0, 0 };
	float m0_dif[] = { 1, 1, 1, 1.0f };
	float m0_spe[] = { 0, 0, 0, 0.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT, m0_amb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, m0_dif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, m0_spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glRotatef(180, 0.0f, 1.0f, 0.0f);
	model3DS* enemy;
	enemy = new model3DS("model/statek2.3DS", 0.35f);
	glEnable(GL_TEXTURE_2D);
	glFrontFace(GL_CCW);
	//glDisable(GL_DEPTH_TEST);
	enemy->draw();
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_TEXTURE_2D);

	glEndList();

}

void CEnemy2::Update(void)
{
	Rotation.x = (mouseSensitivity * (glutGet(GLUT_WINDOW_HEIGHT) / 2 - mouseY));
	Rotation.y = -(-mouseSensitivity * (glutGet(GLUT_WINDOW_WIDTH) / 2 - mouseX));

	if (Position.z < 20)
	{
		Position.z += 0.4 + (rand() % 14) / 15;
	}

}

void CEnemy2::Render(void)
{
	glPushMatrix();
	glTranslatef(Position.x, Position.y, Position.z);
	glRotatef(Rotation.x, 1.0f, 0.0f, 0.0f);
	glRotatef(Rotation.y, 0.0f, 1.0f, 0.0f);
	glRotatef(Rotation.z, 0.0f, 0.0f, 1.0f);

	glCallList(_displayListEnemy);

	glPopMatrix();
}
