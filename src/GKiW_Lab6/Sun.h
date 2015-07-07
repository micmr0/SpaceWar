#pragma once
#include "stdafx.h"

class CSun : public CSceneObject
{
public:
	CSun(void);
	~CSun(void);
	void Initialize(void);
	void Update(void);
	void Render(void);

protected:
	GLuint _displayListId;
	CTexture * _skyTexture;

};

