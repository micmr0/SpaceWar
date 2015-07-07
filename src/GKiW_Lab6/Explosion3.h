#pragma once

class CExplosion3 : public CSceneObject
{
public:
	CExplosion3();
	~CExplosion3(void);
	void Initialize(void);
	void Update(void);
	void Render(void);
	float z;

protected:
	GLuint _displayListId;
};