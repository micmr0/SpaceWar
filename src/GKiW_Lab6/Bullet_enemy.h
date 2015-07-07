#pragma once
#include "stdafx.h"

class CBullet_Enemy : public CSceneObject
{
public:
	//CCollisionEllipsoid * collisionEllipsoid; // Elipsoida s³u¿¹ca do wykrywania kolizji.
	CBullet_Enemy(void);
	~CBullet_Enemy(void);
	void Initialize(void);
	void Update(void);
	void Render(void);

	vec3 pos;
	vec3 dir;



protected:
	GLuint _displayListId;

};
