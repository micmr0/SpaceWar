#pragma once

//static const float	slowdown = 2.0f;				// Slow Down Particles
//static const float	xspeed;						// Base X Speed (To Allow Keyboard Direction Of Tail)
//static const float	yspeed;						// Base Y Speed (To Allow Keyboard Direction Of Tail)
//static const float	zoom = -50.0f;

class CSpaceship : public CSceneObject
{
public:
	CSpaceship(void);
	~CSpaceship(void);
	void Initialize(void);
	void Update(void);
	void Render(void);
	vec3 v[4];
#define	MAX_PARTICLES	100

	// Used To Zoom Out

	//GLuint	loop;						// Misc Loop Variable
	//GLuint	col;						// Current Color Selection
	//GLuint	delay;

	//typedef struct						// Create A Structure For Particle
	//{
	//	bool	active;					// Active (Yes/No)
	//	float	life;					// Particle Life
	//	float	fade;					// Fade Speed
	//	float	x;						// X Position
	//	float	y;						// Y Position
	//	float	z;						// Z Position
	//	float	xi;						// X Direction
	//	float	yi;						// Y Direction
	//	float	zi;						// Z Direction
	//	float	xg;						// X Gravity
	//	float	yg;						// Y Gravity
	//	float	zg;						// Z Gravity
	//}
	//particles;							// Particles Structure

	//particles particle[MAX_PARTICLES];

protected:
	GLuint _displayListId;
};

