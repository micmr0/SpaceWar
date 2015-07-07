#include "StdAfx.h"
#include "Bullet.h"

CBullet::CBullet(void) : CSceneObject()
{
	dir.x = 0;
	dir.y = 0;
	dir.z = -1;
}

CBullet::~CBullet(void)
{
}

void CBullet::Initialize(void)
{
	_displayListId = glGenLists(1);

	glNewList(_displayListId, GL_COMPILE);
	

	glPushMatrix();
	float m6_amb[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	float m6_dif[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	float m6_spe[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT, m6_amb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, m6_dif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, m6_spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	#pragma endregion
	glTranslatef(Scene->Spaceship->Position.x, Scene->Spaceship->Position.y, Scene->Spaceship->Position.z);
	glutSolidSphere(0.04, 10, 10);
	glPopMatrix();

	glEndList();

}

void CBullet::Update(void)
{
	Position.x += (dir.x)*1.9;
	Position.y += (dir.y)*1.9;
	Position.z += (dir.z)*1.9;
}

void CBullet::Render(void)
{
	glPushMatrix();
	glTranslatef(Position.x, Position.y, Position.z);
	glRotatef(Rotation.x, 1.0f, 0.0f, 0.0f);
	glRotatef(Rotation.y, 0.0f, 1.0f, 0.0f);
	glRotatef(Rotation.z, 0.0f, 0.0f, 1.0f);
	pos = vec3(Position.x, Position.y, Position.z);
	glCallList(_displayListId);

	glPopMatrix();
}
