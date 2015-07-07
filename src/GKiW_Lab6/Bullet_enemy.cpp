#include "StdAfx.h"
#include "Bullet_enemy.h"

CBullet_Enemy::CBullet_Enemy(void) : CSceneObject()
{
	dir.x = Scene->Spaceship->Position.x;
	dir.y = Scene->Spaceship->Position.y;
	dir.z = Scene->Spaceship->Position.z;
}

CBullet_Enemy::~CBullet_Enemy(void)
{

}

void CBullet_Enemy::Initialize(void)
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

	glTranslatef(Scene->Enemy->Position.x, Scene->Enemy->Position.y, Scene->Enemy->Position.z);
	glutSolidSphere(0.04, 10, 10);
	glPopMatrix();

	glEndList();

	Position.x = Scene->Enemy->Position.x;
	Position.y = Scene->Enemy->Position.y;
	Position.z = Scene->Enemy->Position.z;

}

void CBullet_Enemy::Update(void)
{
	Position.x += (dir.x)*1.5;
	Position.y += (dir.y)*1.5;
	Position.z -= (dir.z)*1.5;

	dir.Normalize();
}

void CBullet_Enemy::Render(void)
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
