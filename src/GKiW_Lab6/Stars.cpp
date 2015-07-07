#include "StdAfx.h"
#include "Stars.h"


CStars::CStars(void) : CSceneObject()
{
}

CStars::~CStars(void)
{
}

void CStars::Initialize(void)
{
	srand(time(NULL));


	for (int i = 0; i < number; i++) // losowanie gwiazd
	{
		g_xyz[i] = new float [3];
		g_xyz[i][0] = ((float)rand() / RAND_MAX - .5f) * field_width;
		g_xyz[i][1] = ((float)rand() / RAND_MAX - .5f) * field_height;
		g_xyz[i][2] = ((float)rand() / RAND_MAX) *(near_plane - far_plane + gap) + far_plane;

		g_colors[i] = new float [3];
		g_colors[i][0] = (float)rand() / RAND_MAX;
		g_colors[i][1] = (float)rand() / RAND_MAX;
		g_colors[i][2] = (float)rand() / RAND_MAX;
	}
}

void CStars::Update(void)
{

}

void CStars::Render(void)
{
	static float inc = 0.0f;
	inc += 0.001f;

	g_speed += g_speed_inc;
	for (int i = 0; i < number; i++)
	{
		glPushMatrix();
		glRotatef(50 * cos(inc), 0.0f, 0.0f, 1.0f);
		float m0_amb[] = { 1,1,1, 1.0f };
		float m0_dif[] = { 1, 1, 1, 1.0f };
		float m0_spe[] = { g_colors[i][0], g_colors[i][1], g_colors[i][2], 1.0f };
		glMaterialfv(GL_FRONT, GL_AMBIENT, m0_amb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, m0_dif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, m0_spe);
		glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);

		float l0_amb[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		float l0_dif[] = { 1, 1, 1, 1 };
		float l0_spe[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		float l0_pos[] = { g_xyz[i][0], g_xyz[i][1], g_xyz[i][2], 1 };
		glLightfv(GL_LIGHT0, GL_AMBIENT, l0_amb);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, l0_dif);
		glLightfv(GL_LIGHT0, GL_SPECULAR, l0_spe);
		glLightfv(GL_LIGHT0, GL_POSITION, l0_pos);

		glTranslatef(g_xyz[i][0], g_xyz[i][1], g_xyz[i][2]);
		glutSolidSphere(.010f, 10, 10);
		glPopMatrix();

		// zwiekszanie z
		g_xyz[i][2] += g_speed;

		// sprawdzanie czy sa poza polem zasiegu
		if (g_xyz[i][2] > near_plane + gap)
		{
			float d;
			if ((d = sqrt(g_xyz[i][0] * g_xyz[i][0] + g_xyz[i][1] * g_xyz[i][1])) < radiaus)
			{
				g_red += (radiaus - d) / radiaus;
				if (g_red > 2.5f) g_red = 2.5f;
			}

			g_xyz[i][0] = ((float)rand() / RAND_MAX - .5f) * field_width;
			g_xyz[i][1] = ((float)rand() / RAND_MAX - .5f) * field_height;
			g_xyz[i][2] = far_plane;
		}
		else if (g_xyz[i][2] < far_plane)
		{
			g_xyz[i][0] = ((float)rand() / RAND_MAX - .5f) * field_width;
			g_xyz[i][1] = ((float)rand() / RAND_MAX - .5f) * field_height;
			g_xyz[i][2] = near_plane;
		}

	}

}
