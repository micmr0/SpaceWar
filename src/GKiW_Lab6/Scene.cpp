#include "StdAfx.h"

// Konstruktor.
CScene::CScene(void)
{
	x_hours=0;
	x_minutes=0;
	x_seconds=0;
	x_milliseconds=0;
	totaltime=0, count_down_time_in_secs=60, time_left=0;

	Bullet_active = false;
	Bullet_enemy_active = false;
	Enemy_active = false;
	Bullet_enemy2_active = false;
	Bullet_enemy3_active = false;
	Enemy2_active = false;
	Enemy3_active = false;
	Explosion_active = false;
	Explosion2_active = false;
	Explosion3_active = false;
	score = 0;
	zmiana = 0;
	end = false;
	del = true;
	zmienna2 = 4;
}

// Destruktor - sprz¹tamy po sobie.
CScene::~CScene(void)
{
	if (Space != NULL) {
		delete Space;
	}
	if (Stars != NULL) {
		delete Stars;
	}
	if (Spaceship != NULL) {
		delete Spaceship;
	}
	if (Bullet != NULL) {
		delete Bullet;
	}

	if (Enemy != NULL) {
		delete Enemy;
	}

	if (Enemy2 != NULL) {
		delete Enemy2;
	}

	if (Enemy3 != NULL) {
		delete Enemy3;
	}

	if(Bullet_enemy != NULL) {
		delete Bullet_enemy;
	}

	if (Bullet_enemy2 != NULL) {
		delete Bullet_enemy2;
	}

	if (Bullet_enemy3 != NULL) {
		delete Bullet_enemy3;
	}

	if (Explosion != NULL) {
		delete Explosion;
	}

	if (Explosion2 != NULL) {
		delete Explosion2;
	}

	if (Explosion3 != NULL) {
		delete Explosion3;
	}
}

void output(int x, int y, int z, int font, char *string)
{
	int len, i;
	glPushMatrix();
	float m6_amb[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float m6_dif[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float m6_spe[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT, m6_amb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, m6_dif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, m6_spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_TEXTURE);

	glLoadIdentity();
	glTranslatef(x, y, -10.0f);
	glRasterPos3f(x, y, -10.0f);

	len = (int)strlen(string);
	for (i = 0; i < len; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[i]);
	}

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE);
	glPopMatrix();
}

void wait(int seconds)
{
	clock_t endwait;
	endwait = clock() + seconds * CLOCKS_PER_SEC;
	while (clock() < endwait) {}
}

// Inicjalizacja sceny.
void CScene::Initialize(void) {
	
	#pragma region Ustawienia

		// Ustawienie wszelkiego rodzaju rzeczy, które s¹ charakterystyczne dla tej konkretnej sceny.

		glEnable(GL_LIGHT0);

		Player.pos.x = 0.0f;
		Player.pos.y = 0.3f;
		Player.pos.z = 0.0f;

		Player.dir.x = 0.0f;
		Player.dir.y = 0.0f;
		Player.dir.z = -1.0f;

		Player.speed = .5f;
		
	#pragma endregion

	#pragma region Zawartosc sceny
	
		// Scena zawieraæ bêdzie Space...
		Space = new CSpace();
		Space->Initialize();

		//i statek...
		Spaceship = new CSpaceship();
		Spaceship->Initialize();
		
		// i gwizady...
		Stars = new CStars();
		Stars->Initialize();

		//i slonce...
		Sun = new CSun();
		Sun->Initialize();

		//lecacy pocisk
		Bullet = new CBullet();
		Bullet_enemy = new CBullet_Enemy();

		srand(time(NULL));

		Enemy = new CEnemy();
		Enemy->Initialize();
		Enemy_active = true;

		Enemy->Position.x = -10 + (rand() % 20);
		Enemy->Position.y = -12 + (rand() % 10);
		Enemy->Position.z = -160 + (rand() % 10);

		Enemy2 = new CEnemy2();
		Enemy2->Initialize();
		Enemy2_active = true;

		Enemy2->Position.x = -14 + (rand() % 50);
		Enemy2->Position.y = -10 + (rand() % 10);
		Enemy2->Position.z = -140 + (rand() % 10);

		Enemy3 = new CEnemy3();
		Enemy3->Initialize();
		Enemy3_active = true;

		Enemy3->Position.x = -15 + (rand() % 30);
		Enemy3->Position.y = -10 + (rand() % 10);
		Enemy3->Position.z = -140 + (rand() % 10);

		Explosion = new CExplosion();
		Explosion->Initialize();

		x_startTime = clock();  // start clock
}


// Aktualizacja œwiata gry.
void CScene::Update(void) {

	#pragma region Ruch kamery

	#pragma region znajdowanie pozycji myszy w œwiecie opengl

	GLint viewport[4];                  // Where The Viewport Values Will Be Stored
	glGetIntegerv(GL_VIEWPORT, viewport);           // Retrieves The Viewport Values (X, Y, Width, Height)
	GLdouble modelview[16];                 // Where The 16 Doubles Of The Modelview Matrix Are To Be Stored
	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
	GLdouble projection[16];                // Where The 16 Doubles Of The Projection Matrix Are To Be Stored
	glGetDoublev(GL_PROJECTION_MATRIX, projection);     // Retrieve The Projection Matrix

	GLfloat winX, winY, winZ; // Holds Our X, Y and Z Coordinates
	GLdouble posX, posY, posZ;

	winX = (float)mouseX;                  // Holds The Mouse X Coordinate
	winY = (float)mouseY;                  // Holds The Mouse Y Coordinate

	winY = (float)viewport[3] - winY;           // Subtract The Current Mouse Y Coordinate From The Screen Height.

	glReadPixels(winX, winY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);
	// Hold The Final Values

	gluUnProject(winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);

	positionX = &posX;
	positionY = &posY;
	positionZ = &posZ;

	#pragma endregion
	
	if (captureMouse) {
		if (posZ > -60)
		{
			Player.velRY = Player.velRY;
		}
		else
			Player.velRY = (-mouseSensitivity * (glutGet(GLUT_WINDOW_WIDTH) / 2 - mouseX))*0.15;
		if (posY > 80 || posY < -80)
		{
			Player.velRX = Player.velRX;
		}
		else
			Player.velRX = (mouseSensitivity * (glutGet(GLUT_WINDOW_HEIGHT) / 2 - mouseY))*0.15;
		//glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);

	//std:cout << posX << "   " << posY << "   " << posZ << endl;
	}

		/*if (keystate['a']) {
			Player.velS = -Player.speed;
		}
		if (keystate['d']) {
			Player.velS = Player.speed;
		}
		if (keystate['q']) {
			Player.velRY = -Player.speed;
		}
		if (keystate['e']) {
			Player.velRY = Player.speed;
		}
		if (keystate['f']) {
			Player.velRX = -Player.speed;
		}
		if (keystate['c']) {
			Player.velRX = Player.speed;
		}*/

		float T = acos(Player.dir.y);
		float G = atan2(Player.dir.z, Player.dir.x);
		T -= Player.velRX * .03f;
		G += Player.velRY * .03f;
		Player.dir.x = sin(T) * cos(G);
		Player.dir.y = cos(T);
		Player.dir.z = sin(T) * sin(G);

		vec3 per;
		per.x = -Player.dir.z;
		per.y = 0;
		per.z = Player.dir.x;

		vec3 nextPlayerPos = Player.pos;

		nextPlayerPos.x += Player.dir.x * Player.velM * .1f;
		if (free3DMovement) {
			nextPlayerPos.y += Player.dir.y * Player.velM * .1f;
		}
		else {
			// Niby-grawitacja
			nextPlayerPos.y -= .1f;
		}
		nextPlayerPos.z += Player.dir.z * Player.velM * .1f;

		nextPlayerPos.x += per.x * Player.velS * .1f;
		if (free3DMovement) {
			nextPlayerPos.y += Player.dir.y * Player.velM * .1f;
		}
		nextPlayerPos.z += per.z * Player.velS * .1f;
		
		// Uniemo¿liwiamy zejœcie gracza poni¿ej poziomu terenu
		nextPlayerPos.y = __max(0.3f, nextPlayerPos.y);

		// Zmieniamy pozycjê gracza o wyliczony wczeœniej wektor przemieszczenia, uwzglêdniaj¹c przy tym kolizje ze œwiatem
		// "Objects" powinno byæ wektorem tylko tych obiektów, z którymi chcemy sprawdziæ kolizjê. Dobrze by³oby
		// wprowadziæ wczeœniejsz¹ fazê detekcji kolizji w oparciu np. o AABB i zawêziæ liczbê elementów Objects.
		//Player.pos = CCollisionDetection::GetPositionAfterWorldCollisions(Player.pos, nextPlayerPos, Player, Objects);

		Player.velRX /= 1.2;
		Player.velRY /= 1.2;
		Player.velM /= 1.2;
		Player.velS /= 1.2;

	#pragma endregion

	#pragma region Aktualizacja obiektow sceny

		Space->Update();

		Spaceship->Update();

		if (Bullet_active)
		{
			Bullet->Update();
		}

		#pragma region Enemy

		if (Enemy_active && Bullet_enemy_active)
		{
			Bullet_enemy->Update();
		}

		if (Enemy_active)
		{
			Enemy->Update();
		};
		
		if (Enemy_active && Bullet_active)
		{
			GLdouble distance[3];

			distance[0] = abs(abs(Bullet->Position.x) - abs(Enemy->Position.x));
			distance[1] = abs(abs(Bullet->Position.y) - abs(Enemy->Position.y));
			distance[2] = abs(abs(Bullet->Position.z) - abs(Enemy->Position.z));

			if (distance[0] < 0.5 && distance[1] < 0.5 && distance[2] < 0.5)
			{
				score++;
				Explosion = new CExplosion();
				Explosion->Initialize();

				Explosion->Position.x = Enemy->Position.x;
				Explosion->Position.y = Enemy->Position.y;
				Explosion->Position.z = Enemy->Position.z;

				delete Enemy;
				Enemy_active = false;
				delete Bullet;
				Bullet_active = false;

				Explosion_active = true;

			};
		}


		if (Enemy_active && Bullet_enemy_active)
		{
			GLdouble distance[3];

			distance[0] = abs(abs(Spaceship->Position.x)-abs(Bullet_enemy->Position.x));
			distance[1] = abs(abs(Spaceship->Position.y)-abs(Bullet_enemy->Position.y));
			distance[2] = abs(abs(Spaceship->Position.z)-abs(Bullet_enemy->Position.z));

			if (distance[0] < 2.2 && distance[1] < 2.2 && distance[2] < 0.05)
			{
				for (int i = 0; i < 60; i++)
				{
					Spaceship->Position.y += 0.05;
				}
				//Enemy_active = false;
				delete Bullet_enemy;
				Bullet_enemy_active = false;
			};
		}

		if (Enemy_active)
		{
			if (Enemy->Position.z > 5)
			{
				delete Enemy;
				Enemy_active = false;
				Bullet_enemy_active = false;

				Enemy = new CEnemy();
				Enemy->Initialize();
				Enemy_active = true;

				Enemy->Position.x = -15 + (rand() % 20);
				Enemy->Position.y = -10 + (rand() % 15);
				Enemy->Position.z = -160 + (rand() % 10);
			}
		}

		#pragma endregion

		#pragma region Enemy2

		if (Enemy2_active && Bullet_enemy2_active)
		{
			Bullet_enemy2->Update();
		}

		if (Enemy2_active)
		{
			Enemy2->Update();
		};

		if (Enemy2_active && Bullet_active)
		{
			GLdouble distance[3];

			distance[0] = abs(abs(Bullet->Position.x) - abs(Enemy2->Position.x));
			distance[1] = abs(abs(Bullet->Position.y) - abs(Enemy2->Position.y));
			distance[2] = abs(abs(Bullet->Position.z) - abs(Enemy2->Position.z));

			if (distance[0] < 0.5 && distance[1] < 0.5 && distance[2] < 0.5)
			{
				score++;
				Explosion2 = new CExplosion2();
				Explosion2->Initialize();

				Explosion2->Position.x = Enemy2->Position.x;
				Explosion2->Position.y = Enemy2->Position.y;
				Explosion2->Position.z = Enemy2->Position.z;

				delete Enemy2;
				Enemy2_active = false;
				delete Bullet;
				Bullet_active = false;

				Explosion2_active = true;

			};
		}


		if (Enemy2_active && Bullet_enemy2_active)
		{
			GLdouble distance[3];

			distance[0] = abs(abs(Spaceship->Position.x) - abs(Bullet_enemy2->Position.x));
			distance[1] = abs(abs(Spaceship->Position.y) - abs(Bullet_enemy2->Position.y));
			distance[2] = abs(abs(Spaceship->Position.z) - abs(Bullet_enemy2->Position.z));

			if (distance[0] < 2.2 && distance[1] < 2.2 && distance[2] < 0.05)
			{
				for (int i = 0; i < 60; i++)
				{
					Spaceship->Position.y += 0.05;
				}
				//Enemy_active = false;
				delete Bullet_enemy2;
				Bullet_enemy2_active = false;
			};
		}

		if (Enemy2_active)
		{
			if (Enemy2->Position.z > 5)
			{
				delete Enemy2;
				Enemy2_active = false;
				Bullet_enemy2_active = false;

				Enemy2 = new CEnemy2();
				Enemy2->Initialize();
				Enemy2_active = true;

				Enemy2->Position.x = -10 + (rand() % 20);
				Enemy2->Position.y = -8 + (rand() % 10);
				Enemy2->Position.z = -140 + (rand() % 10);
			}
		}

	#pragma endregion


	#pragma region Enemy3

		if (Enemy3_active && Bullet_enemy3_active)
		{
			Bullet_enemy3->Update();
		}

		if (Enemy3_active)
		{
			Enemy3->Update();
		};

		if (Enemy3_active && Bullet_active)
		{
			GLdouble distance[3];

			distance[0] = abs(abs(Bullet->Position.x) - abs(Enemy3->Position.x));
			distance[1] = abs(abs(Bullet->Position.y) - abs(Enemy3->Position.y));
			distance[2] = abs(abs(Bullet->Position.z) - abs(Enemy3->Position.z));

			if (distance[0] < 0.5 && distance[1] < 0.5 && distance[2] < 0.5)
			{
				score++;
				Explosion3 = new CExplosion3();
				Explosion3->Initialize();

				Explosion3->Position.x = Enemy3->Position.x;
				Explosion3->Position.y = Enemy3->Position.y;
				Explosion3->Position.z = Enemy3->Position.z;

				delete Enemy3;
				Enemy3_active = false;
				delete Bullet;
				Bullet_active = false;

				Explosion3_active = true;

			};
		}


		if (Enemy3_active && Bullet_enemy3_active)
		{
			GLdouble distance[3];

			distance[0] = abs(abs(Spaceship->Position.x) - abs(Bullet_enemy3->Position.x));
			distance[1] = abs(abs(Spaceship->Position.y) - abs(Bullet_enemy3->Position.y));
			distance[2] = abs(abs(Spaceship->Position.z) - abs(Bullet_enemy3->Position.z));

			if (distance[0] < 2.2 && distance[1] < 2.2 && distance[2] < 0.05)
			{
				for (int i = 0; i < 60; i++)
				{
					Spaceship->Position.y += 0.05;
				}
				//Enemy_active = false;
				delete Bullet_enemy3;
				Bullet_enemy3_active = false;
			};
		}

		if (Enemy3_active)
		{
			if (Enemy3->Position.z > 5)
			{
				delete Enemy3;
				Enemy3_active = false;
				Bullet_enemy3_active = false;

				Enemy3 = new CEnemy3();
				Enemy3->Initialize();
				Enemy3_active = true;

				Enemy3->Position.x = -10 + (rand() % 20);
				Enemy3->Position.y = -8 + (rand() % 10);
				Enemy3->Position.z = -120 + (rand() % 10);
			}
		}

#pragma endregion

		if (Explosion_active)
		{
			Explosion->Update();
		}


		if (Explosion2_active)
		{
			Explosion2->Update();
		}

		if (Explosion3_active)
		{
			Explosion3->Update();
		}

	#pragma endregion

		
		time_left = count_down_time_in_secs - x_seconds;   // update timer

		
			x_countTime = clock(); // update timer difference
			x_milliseconds = x_countTime - x_startTime;
			x_seconds = (x_milliseconds / (CLOCKS_PER_SEC)) - (x_minutes * 60);
			x_minutes = (x_milliseconds / (CLOCKS_PER_SEC)) / 60;
			x_hours = x_minutes / 60;

			time_left = count_down_time_in_secs - x_seconds; // subtract to get difference 

			//printf("\nPozostalo %d sekund do konca ( %d ) calosci", time_left, count_down_time_in_secs);

			

	
}

// Narysowanie sceny.
void CScene::Render(void) {

	#pragma region Kamera

		gluLookAt(
			Player.pos.x + Player.cam.x, Player.pos.y + Player.cam.y, Player.pos.z + Player.cam.z,
			Player.pos.x + Player.cam.x + Player.dir.x, Player.pos.y + Player.cam.y + Player.dir.y, Player.pos.z + Player.cam.z + Player.dir.z,
			0.0f, 1.0f, 0.0f
		);

	#pragma endregion

	#pragma region Space

		Space->Position = Player.pos;
		Space->Render();

	#pragma endregion


	#pragma region Stars

		Stars->Render();
		Sun->Render();

	#pragma endregion


	#pragma region Enemy

		if (Enemy_active)
		{
			Enemy->Render();
		};

		if (Enemy2_active)
		{
			Enemy2->Render();
		};

		if (Enemy3_active)
		{
			Enemy3->Render();
		};

		if (Bullet_active)
		{
			if ((Bullet->Position.x) < -140 || (Bullet->Position.y) < -140 || (Bullet->Position.z) < -140)
			{
				delete Bullet;
				Bullet_active = false;
			}
		};


		if (Enemy_active && Bullet_enemy_active)
		{
			if ((Bullet_enemy->Position.x) > 140 || (Bullet_enemy->Position.y) > 140 || (Bullet_enemy->Position.z) > 20)
			{
				delete Bullet_enemy;
				Bullet_enemy_active = false;
			}
		};

		if (Enemy2_active && Bullet_enemy2_active)
		{
			if ((Bullet_enemy2->Position.x) > 140 || (Bullet_enemy2->Position.y) > 140 || (Bullet_enemy2->Position.z) > 20)
			{
				delete Bullet_enemy2;
				Bullet_enemy2_active = false;
			}
		};

		if (Enemy3_active && Bullet_enemy3_active)
		{
			if ((Bullet_enemy3->Position.x) > 140 || (Bullet_enemy3->Position.y) > 140 || (Bullet_enemy3->Position.z) > 20)
			{
				delete Bullet_enemy3;
				Bullet_enemy3_active = false;
			}
		};

		if (Bullet_active)
		{
			Bullet->Render();
		}

		if (Enemy_active && Bullet_enemy_active)
		{
			Bullet_enemy->Render();
		}

		if (Enemy2_active && Bullet_enemy2_active)
		{
			Bullet_enemy2->Render();
		}

		if (Enemy3_active && Bullet_enemy3_active)
		{
			Bullet_enemy3->Render();
		}

		//cout << "Bullet:" << Bullet->Position.z << endl; cout << "Enemy:" << (Enemy->Position.z);

		//cout << "x" << Scene->Spaceship->Position.x << endl; cout << "y" << Scene->Spaceship->Position.y << endl << "z" << Scene->Spaceship->Position.z << endl;
	#pragma endregion


	#pragma region Spaceship

		Spaceship->Render();
		Spaceship->Position.x = Player.dir.x*4;
		Spaceship->Position.y = Player.dir.y*4;
		Spaceship->Position.z = Player.dir.z-3;

	#pragma endregion


	#pragma region explosion
		if (Explosion_active)
		{

			Explosion->Render();
		
		
			if (Explosion->z > 5)
			{
				delete Explosion;
				Explosion_active = false;

				Enemy = new CEnemy();
				Enemy->Initialize();
				Enemy_active = true;

				Enemy->Position.x = -10 + (rand() % 25);
				Enemy->Position.y = -10 + (rand() % 15);
				Enemy->Position.z = -140 + (rand() % 10);
			}
		
		}
	#pragma endregion

	#pragma region explosion2
		if (Explosion2_active)
		{

			Explosion2->Render();


			if (Explosion2->z > 5)
			{
				delete Explosion2;
				Explosion2_active = false;

				Enemy2 = new CEnemy2();
				Enemy2->Initialize();
				Enemy2_active = true;

				Enemy2->Position.x = -10 + (rand() % 25);
				Enemy2->Position.y = -10 + (rand() % 15);
				Enemy2->Position.z = -120 + (rand() % 10);
			}

		}
	#pragma endregion

	#pragma region explosion3
		if (Explosion3_active)
		{

			Explosion3->Render();


			if (Explosion3->z > 5)
			{
				delete Explosion3;
				Explosion3_active = false;

				Enemy3 = new CEnemy3();
				Enemy3->Initialize();
				Enemy3_active = true;

				Enemy3->Position.x = -10 + (rand() % 25);
				Enemy3->Position.y = -10 + (rand() % 10);
				Enemy3->Position.z = -140 + (rand() % 10);
			}

		}
	#pragma endregion

		//cout << Bullet->Position.z;
		
		output(4, 4, -1, 2, "Pozostaly czas:");
		sprintf(czas, "%i", time_left);
		output(6, 4, -1, 2, czas);


		output(4, 3, -1, 2, "Pokonani Wrogowie:");
		sprintf(wyn, "%i", score);
		output(6, 3, -1, 2, wyn);


		if ((score >= zmienna2))
		{
			count_down_time_in_secs += 30;
			output(2, 3, -1, 2, "+ 30 sekund premii");
			zmienna2 += 4;
		}

		if (time_left == 0)
		{
			Bullet_active = false;
			Bullet_enemy_active = false;
			Enemy_active = false;
			Bullet_enemy2_active = false;
			Bullet_enemy3_active = false;
			Enemy2_active = false;
			Enemy3_active = false;
			Explosion_active = false;
			Explosion2_active = false;
			Explosion3_active = false;
			end = true;



		};

		if (end)
		{
			glutSwapBuffers();
			glFlush();
			glutPostRedisplay();

			output(0, 0, -1, 2, "Koniec Gry. Twoj wynik to:");
			output(4, 0, -1, 2, wyn);
			output(0, -1, -1, 2, "Wcisnij ESC aby wyjsc");
		}

}

