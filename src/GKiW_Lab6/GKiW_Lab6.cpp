#include "stdafx.h"

#pragma region Zmienne globalne

	int mouseX = 0;
	int mouseY = 0;

	bool captureMouse = true;
	bool free3DMovement = false;

	float mouseSensitivity = .05f;

	CScene * Scene;

	bool keystate[255];

	float Spaceship_velRX, Spaceship_velRY;

	

#pragma endregion



int main(int argc, char* argv[])
{
	glutInit(&argc, argv);

	glutInitWindowPosition(100, 100);
	glutInitWindowSize(640, 360);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	glutCreateWindow("GKiW: Lab 6");
	
	glutDisplayFunc(OnRender);
	glutReshapeFunc(OnReshape);
	glutKeyboardFunc(OnKeyPress);
	glutKeyboardUpFunc(OnKeyUp);
	glutPassiveMotionFunc(OnMouseMove);
	glutMotionFunc(OnMouseMove);
	glutMouseFunc(mouseClick);

	glutTimerFunc(17, OnTimer, 0);

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	glEnable(GL_NORMALIZE);

	glEnable(GL_LIGHTING);
	float gl_amb[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, gl_amb);
	
	mouseX = glutGet(GLUT_WINDOW_WIDTH) / 2;
	mouseY = glutGet(GLUT_WINDOW_HEIGHT) / 2;
	//glutWarpPointer(mouseX, mouseY);
	glutSetCursor(GLUT_CURSOR_DESTROY);
	
	// Inicjalizacja sceny.
	Scene = new CScene();
	Scene->Initialize();
	

	glutMainLoop();

	printf("\n\n\nTime's out\n\n\n");


	return 0;
}

#pragma region Obsluga wejscia

	void OnKeyPress(unsigned char key, int x, int y) {
		if (!keystate[key]) {
			keystate[key] = true;
			OnKeyDown(key, x, y);
		}
	}

	void OnKeyDown(unsigned char key, int x, int y) {
		if (key == 27) {
			glutLeaveMainLoop();
		}
		if (key == 'm' || key == 'M') {
			if (captureMouse) {
				captureMouse = false;
				glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
			}
			else {
				captureMouse = true;
				glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);
				glutSetCursor(GLUT_CURSOR_DESTROY);
			}
		}

	}

	void OnKeyUp(unsigned char key, int x, int y) {
		keystate[key] = false;
	}

	void OnMouseMove(int x, int y) {
		mouseX = x;
		mouseY = y;
	}

	void mouseClick(int button, int state, int x, int y)
	{
		if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN))
		{
			Scene->Bullet = new CBullet();
			Scene->Bullet_active = true;
			Scene->Bullet->Initialize();
			Scene->Bullet->dir.x = Scene->Player.dir.x;
			Scene->Bullet->dir.y = Scene->Player.dir.y;
			Scene->Bullet->dir.z = Scene->Player.dir.z;

		}

		if (1)
		{
			Spaceship_velRX = Scene->Spaceship->Position.y;
			Spaceship_velRY = Scene->Spaceship->Position.x;

			float T = acos(Scene->Spaceship->Position.y);
			float G = atan2(Scene->Spaceship->Position.z, Scene->Spaceship->Position.x);
			T -= Spaceship_velRX * .03f;
			G += Spaceship_velRY * .03f;

			Scene->Bullet_enemy = new CBullet_Enemy();
			Scene->Bullet_enemy_active = true;
			Scene->Bullet_enemy->Initialize();

			Scene->Bullet_enemy2 = new CBullet_Enemy2();
			Scene->Bullet_enemy2_active = true;
			Scene->Bullet_enemy2->Initialize();

			Scene->Bullet_enemy3 = new CBullet_Enemy3();
			Scene->Bullet_enemy3_active = true;
			Scene->Bullet_enemy3->Initialize();
			
			Scene->Bullet_enemy->dir.x = sin(T) * cos(G)*0.1;
			Scene->Bullet_enemy->dir.y = cos(T)*0.1;
			Scene->Bullet_enemy->dir.z = sin(T) * sin(G)*0.1;

			Scene->Bullet_enemy2->dir.x = sin(T) * cos(G)*0.1;
			Scene->Bullet_enemy2->dir.y = cos(T)*0.1;
			Scene->Bullet_enemy2->dir.z = sin(T) * sin(G)*0.1;

			Scene->Bullet_enemy3->dir.x = sin(T) * cos(G)*0.1;
			Scene->Bullet_enemy3->dir.y = cos(T)*0.1;
			Scene->Bullet_enemy3->dir.z = sin(T) * sin(G)*0.1;

		}
	}


#pragma endregion

void OnTimer(int id) {
	glutTimerFunc(17, OnTimer, 0);
	// Aktualizacj� �wiata przenie�li�my do obiektu klasy CScene
	// (lub dziedzicz�cej po niej, gdy scen b�dzie kilka):
	Scene->Update();
}

void OnRender() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Rysowanie w�a�ciwej sceny przenie�li�my do obiektu klasy CScene
	// (lub dziedzicz�cej po niej, gdy scen b�dzie kilka):
	Scene->Render();
	glutSwapBuffers();

	glFlush();
	glutPostRedisplay();

}

void OnReshape(int width, int height) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, width, height);
	gluPerspective(50.0f, (float) width / height, .01f, 100.0f);
}
