#pragma once

class CExplosion2 : public CSceneObject
{
public:
	CExplosion2();
	~CExplosion2(void);
	void Initialize(void);
	void Update(void);
	void Render(void);
	float z;

protected:
	GLuint _displayListId;
};