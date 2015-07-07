#include "StdAfx.h"
#include "Space.h"


CSpace::CSpace(void) : CSceneObject()
{
}


CSpace::~CSpace(void)
{
}

void CSpace::Initialize(void)
{
	

	_displayListId = glGenLists(1);

	glNewList(_displayListId, GL_COMPILE);
	

	glPushAttrib(GL_ENABLE_BIT);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	//glFrontFace(GL_CW);
	// Ustawienie sposobu teksturowania - GL_MODULATE sprawia, ¿e œwiat³o ma wp³yw na teksturê; GL_DECAL i GL_REPLACE rysuj¹ teksturê tak jak jest
	
	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	_spaceTexture = new CTexture("Resources\\kosmos.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
	_spaceTexture->Load();

	GLUquadricObj *sphere;
	sphere = gluNewQuadric();
	gluQuadricDrawStyle(sphere, GLU_FILL);
	gluQuadricNormals(sphere, GLU_SMOOTH);
	gluQuadricOrientation(sphere, GLU_INSIDE);
	gluQuadricTexture(sphere, GL_TRUE);

	// Wybór tekstury korzystaj¹c z jej id
	//glBindTexture(GL_TEXTURE_2D, _skyTexture->GetId());

	glPushMatrix();

	glRotatef(100, 1.0f, 0.0f, 0.0f);
	gluSphere(sphere, 30.0f, 80, 80);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	//glFrontFace(GL_CCW);
	glEnable(GL_LIGHTING);
	glEndList();

}

void CSpace::Update(void)
{
	//Rotation.y -= 0.015f;
}

void CSpace::Render(void)
{
	glPushMatrix();

	glTranslatef(Position.x, Position.y, Position.z);
	glRotatef(Rotation.x, 1.0f, 0.0f, 0.0f);
	glRotatef(Rotation.y, 0.0f, 1.0f, 0.0f);
	glRotatef(Rotation.z, 0.0f, 0.0f, 1.0f);

	//glEnable(GL_TEXTURE_2D);
	//glBindTexture(GL_TEXTURE_2D, _skyTexture->GetId());
	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	glCallList(_displayListId);

	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}
