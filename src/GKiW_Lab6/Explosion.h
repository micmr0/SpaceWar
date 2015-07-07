#pragma once

class CExplosion : public CSceneObject
{
public:
	CExplosion();
	~CExplosion(void);
	void Initialize(void);
	void Update(void);
	void Render(void);
	float z;

protected:
	GLuint _displayListId;
};