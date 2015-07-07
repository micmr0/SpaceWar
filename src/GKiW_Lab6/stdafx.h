// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#define PI 3.14159265

#include "targetver.h"

#include <math.h>
#include <stdio.h>
#include <time.h>
#include <vector>

using namespace std;

#include <GL/freeglut.h>
#include <stdarg.h>
#include "Vec3.h"
#include "Bitmap.h"
#include "Texture.h"
#include "font.h"
#include "CollisionDetection.h"
#include "Collision.h"
#include "CollisionEllipsoid.h"
#include "CollisionPlane.h"
#include "CollisionPolygon.h"
#include "Player.h"
#include "SceneObject.h"
#include "Space.h"
#include "Spaceship.h"
#include "Enemy.h"
#include "Enemy2.h"
#include "Enemy3.h"
#include "Bullet.h"
#include "Bullet_enemy.h"
#include "Bullet_enemy2.h"
#include "Bullet_enemy3.h"
#include "Sun.h"
#include "Explosion.h"
#include "Explosion2.h"
#include "Explosion3.h"
#include <vector>
#include <math.h>
#include <windows.h>

#include "3DSLoader/model3DS.h"
#include "3DSLoader/textureBMP.h"
#include "3DSLoader/textureTGA.h"


#include "Scene.h"
#include "GKiW_Lab6.h"


#pragma region Zmienne globalne

	extern float T;

	extern int mouseX;
	extern int mouseY;

	extern bool captureMouse;
	extern bool free3DMovement;

	extern float mouseSensitivity;

	extern CScene * Scene;

	extern bool keystate[255];

#pragma endregion
