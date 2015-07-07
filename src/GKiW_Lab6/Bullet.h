#pragma once
#include "stdafx.h"

class CBullet : public CSceneObject
{
public:
	CBullet(void);
	~CBullet(void);
	void Initialize(void);
	void Update(void);
	void Render(void);

	vec3 pos;
	vec3 dir;



protected:
	GLuint _displayListId;
	
};

