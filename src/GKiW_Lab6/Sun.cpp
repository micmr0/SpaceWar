#include "StdAfx.h"
#include "Sun.h"


CSun::CSun(void) : CSceneObject()
{
}

CSun::~CSun(void)
{
}

void CSun::Initialize(void)
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
	_skyTexture = new CTexture("Resources\\slonce.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
	_skyTexture->Load();

	GLUquadricObj *slonce;
	slonce = gluNewQuadric();
	gluQuadricDrawStyle(slonce, GLU_FILL);
	gluQuadricNormals(slonce, GLU_SMOOTH);
	gluQuadricOrientation(slonce, GLU_OUTSIDE);
	gluQuadricTexture(slonce, GL_TRUE);

	glPushMatrix();
	float m5_amb[] = { 10.0f, 10.0f, 10.0f, 10.0f };
	float m5_dif[] = { 10.0f, 10.0f, 10.0f, 10.0f };
	float m5_spe[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT, m5_amb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, m5_dif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, m5_spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 100.0f);

	#pragma region Swiatlo
	float l0_amb[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	float l0_dif[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float l0_spe[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float l0_pos[] = { 60.0f, 2.5f, -60.0f, 1.0f };
	glLightfv(GL_LIGHT2, GL_AMBIENT, l0_amb);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, l0_dif);
	glLightfv(GL_LIGHT2, GL_SPECULAR, l0_spe);
	glLightfv(GL_LIGHT2, GL_POSITION, l0_pos);
	#pragma endregion

	glTranslatef(60.0f, 2.50f, -60.0f);
	gluSphere(slonce, 1.4f, 50, 50);
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	//glFrontFace(GL_CCW);
	glEnable(GL_LIGHTING);

	glEndList();
	
}

void CSun::Update(void)
{
}

void CSun::Render(void)
{
	glPushMatrix();
	glTranslatef(Position.x, Position.y, Position.z);
	glRotatef(Rotation.x, 1.0f, 0.0f, 0.0f);
	glRotatef(Rotation.y, 0.0f, 1.0f, 0.0f);
	glRotatef(Rotation.z, 0.0f, 0.0f, 1.0f);

	glCallList(_displayListId);

	glPopMatrix();

}
