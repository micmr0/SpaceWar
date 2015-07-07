#pragma once
#include "Stars.h"

// Scena - Jest to podstawowy element organizuj¹cy hierarchiê obiektów w grze.
// Z za³o¿enia, w danym momencie powinna istnieæ tylko jedna scena.
// W sytuacji gdy scen mo¿e byæ wiêcej, dobrze jest utworzyæ klasy dziedzicz¹ce po tej.
class CScene
{
public:
	
	CSpace * Space; // Space - wszechswiat.
	CStars * Stars;
	CSun * Sun;
	CSpaceship * Spaceship;
	CEnemy * Enemy;
	CEnemy2 * Enemy2;
	CEnemy3 * Enemy3;
	CBullet * Bullet;
	CBullet_Enemy * Bullet_enemy;
	CBullet_Enemy2 * Bullet_enemy2;
	CBullet_Enemy3 * Bullet_enemy3;
	CExplosion * Explosion;
	CExplosion2 * Explosion2;
	CExplosion3 * Explosion3;
	CPlayer Player; // Stan gracza.

	char wyn[32];
	char czas[32];
	int score;
	int zmiana;


	GLdouble* positionX;
	GLdouble* positionY;
	GLdouble* positionZ;

	bool Bullet_active;
	bool Bullet_enemy_active;
	bool Enemy_active;
	bool Bullet_enemy2_active;
	bool Bullet_enemy3_active;
	bool Enemy2_active;
	bool Enemy3_active;
	bool Explosion_active;
	bool Explosion2_active;
	bool Explosion3_active;
	bool end;
	bool del;
	int zmienna2;

	unsigned int x_hours;
	unsigned int x_minutes;
	unsigned int x_seconds;
	unsigned int x_milliseconds;
	unsigned int totaltime, count_down_time_in_secs, time_left;


	clock_t x_startTime, x_countTime;
	//count_down_time_in_secs = 10;  // 1 minute is 60, 1 hour is 3600

	CScene(void); // Konstruktor.
	~CScene(void); // Destruktor.
	void Initialize(void); // Inicjalizacja (wywo³ywana raz).
	void Update(void); // Aktualizacja œwiata.
	void Render(void); // Rysowanie ca³ej sceny.

};

