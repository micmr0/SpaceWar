#include "StdAfx.h"

CExplosion2::CExplosion2() : CSceneObject()
{
	z = 0;
}


CExplosion2::~CExplosion2(void)
{
}

void CExplosion2::Initialize(void)
{

	_displayListId = glGenLists(1);

	glNewList(_displayListId, GL_COMPILE);
	float m0_amb[] = { 1, 0, 0, 1 };
	float m0_dif[] = { 1, 0, 0, 1.0f };
	float m0_spe[] = { 1, 0, 0, 1.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT, m0_amb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, m0_dif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, m0_spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	model3DS* Explosion;
	Explosion = new model3DS("model/Explosion.3DS", 0.2f);

	glEnable(GL_TEXTURE_2D);
	glFrontFace(GL_CCW);
	//glDisable(GL_DEPTH_TEST);
	Explosion->draw();

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_TEXTURE_2D);


	glEndList();


}

void CExplosion2::Update(void)
{
	z += 0.4;
}

void CExplosion2::Render(void)
{
	glPushMatrix();
	glTranslatef(Position.x, Position.y, Position.z);
	glRotatef(Rotation.x, 1.0f, 0.0f, 0.0f);
	glRotatef(Rotation.y, 0.0f, 1.0f, 0.0f);
	glRotatef(Rotation.z, 0.0f, 0.0f, 1.0f);
	glScalef(z, z, z);
	glCallList(_displayListId);

	glPopMatrix();
}
