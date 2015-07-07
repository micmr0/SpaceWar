#include "StdAfx.h"
#include "Spaceship.h"
#include "Scene.h"
CSpaceship::CSpaceship(void) : CSceneObject()
{
}


CSpaceship::~CSpaceship(void)
{
	v[0] = vec3(Position.x + 1, Position.y + 1, Position.z);
	v[1] = vec3(Position.x - 1, Position.y + 1, Position.z);
	v[2] = vec3(Position.x - 1, Position.y - 1, Position.z);
	v[3] = vec3(Position.x + 1, Position.y - 1, Position.z);
}

void CSpaceship::Initialize(void)
{

	_displayListId = glGenLists(1);

	glNewList(_displayListId, GL_COMPILE);
	float m0_amb[] = { 0, 0, 0, 0 };
	float m0_dif[] = { 0, 0, 0, 0.0f };
	float m0_spe[] = { 0, 0, 0, 0.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT, m0_amb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, m0_dif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, m0_spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);

	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.0f);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 15.0f);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.5f);
	model3DS* spaceship;
	spaceship = new model3DS("model/statek.3DS", 0.35f);

	glEnable(GL_TEXTURE_2D);
	glFrontFace(GL_CCW);
	//glDisable(GL_DEPTH_TEST);
	spaceship->draw();
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_TEXTURE_2D);

	//for (loop = 0; loop<MAX_PARTICLES; loop++)				// Initials All The Textures
	//{
	//	particle[loop].active = true;								// Make All The Particles Active
	//	particle[loop].life = 1.0f;								// Give All The Particles Full Life
	//	particle[loop].fade = float(rand() % 100) / 1000.0f + 0.003f;	// Random Fade Speed
	//	particle[loop].xi = float((rand() % 50) - 26.0f)*10.0f;		// Random Speed On X Axis
	//	particle[loop].yi = float((rand() % 50) - 25.0f)*10.0f;		// Random Speed On Y Axis
	//	particle[loop].zi = float((rand() % 50) - 25.0f)*10.0f;		// Random Speed On Z Axis
	//	particle[loop].xg = 0.0f;									// Set Horizontal Pull To Zero
	//	particle[loop].yg = -0.8f;								// Set Vertical Pull Downward
	//	particle[loop].zg = 0.0f;									// Set Pull On Z Axis To Zero
	//}

	glEndList();

}

void CSpaceship::Update(void)
{
	Rotation.x = (mouseSensitivity * (glutGet(GLUT_WINDOW_HEIGHT) / 2 - mouseY));
	Rotation.y = -(-mouseSensitivity * (glutGet(GLUT_WINDOW_WIDTH) / 2 - mouseX));
}

void CSpaceship::Render(void)
{
	glPushMatrix();
	glTranslatef(Position.x, Position.y, Position.z);
	glRotatef(Rotation.x, 1.0f, 0.0f, 0.0f);
	glRotatef(Rotation.y, 0.0f, 1.0f, 0.0f);
	glRotatef(Rotation.z, 0.0f, 0.0f, 1.0f);
	glCallList(_displayListId);

	//_skyTexture->Load();

	//for (loop = 0; loop<MAX_PARTICLES; loop++)					// Loop Through All The Particles
	//{
	//	if (particle[loop].active)							// If The Particle Is Active
	//	{
	//		float x = particle[loop].x;						// Grab Our Particle X Position
	//		float y = particle[loop].y*(Position.y-1);						// Grab Our Particle Y Position
	//		float z = particle[loop].z;					// Particle Z Pos + Zoom

	//		glPushMatrix();
	//		float m5_amb[] = { 1.0f, 0.0f, 0.0f, 10.0f };
	//		float m5_dif[] = { 1.0f, 0.0f, 0.0f, 10.0f };
	//		float m5_spe[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	//		glMaterialfv(GL_FRONT, GL_AMBIENT, m5_amb);
	//		glMaterialfv(GL_FRONT, GL_DIFFUSE, m5_dif);
	//		glMaterialfv(GL_FRONT, GL_SPECULAR, m5_spe);
	//		glMaterialf(GL_FRONT, GL_SHININESS, 1.0f);

	//		#pragma region Swiatlo
	//		float l0_amb[] = { 1.0f, 0.0f, 1.2f, 1.0f };
	//		float l0_dif[] = { 0.0f, 0.0f, 1.0f, 1.0f };
	//		float l0_spe[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	//		glLightfv(GL_LIGHT2, GL_AMBIENT, l0_amb);
	//		glLightfv(GL_LIGHT2, GL_DIFFUSE, l0_dif);
	//		glLightfv(GL_LIGHT2, GL_SPECULAR, l0_spe);
	//		#pragma endregion

	//		glTranslatef(x, y, z);
	//		glutSolidSphere(0.02f, 5, 5);
	//		glPopMatrix();

	//		particle[loop].x += particle[loop].xi / (slowdown * 100);// Move On The X Axis By X Speed
	//		particle[loop].y += particle[loop].yi / (slowdown * 100);// Move On The Y Axis By Y Speed
	//		particle[loop].z += particle[loop].zi / (slowdown * 100);// Move On The Z Axis By Z Speed

	//		particle[loop].xi += particle[loop].xg;			// Take Pull On X Axis Into Account
	//		particle[loop].yi += particle[loop].yg;			// Take Pull On Y Axis Into Account
	//		particle[loop].zi += particle[loop].zg;			// Take Pull On Z Axis Into Account
	//		particle[loop].life -= particle[loop].fade;		// Reduce Particles Life By 'Fade'

	//		if (particle[loop].life<0.0f)					// If Particle Is Burned Out
	//		{
	//			particle[loop].life = 1.0f;					// Give It New Life
	//			particle[loop].fade = float(rand() % 1000) / 1000.0f + 0.003f;	// Random Fade Value
	//			particle[loop].x = 0.0f;						// Center On X Axis
	//			particle[loop].y = 0.0f;						// Center On Y Axis
	//			particle[loop].z = 0.0f;						// Center On Z Axis
	//			particle[loop].xi = xspeed + float((rand() % 30) - 32.0f);	// X Axis Speed And Direction
	//			particle[loop].yi = yspeed + float((rand() % 30) - 30.0f);	// Y Axis Speed And Direction
	//			particle[loop].zi = float((rand() % 20) - 30.0f);	// Z Axis Speed And Direction
	//		}

	//	}
	//}

	glPopMatrix();
}
