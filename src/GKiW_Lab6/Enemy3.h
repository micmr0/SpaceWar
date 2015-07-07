#pragma once

class CEnemy3 : public CSceneObject
{
public:
	CEnemy3();
	~CEnemy3(void);
	void Initialize(void);
	void Update(void);
	void Render(void);

protected:
	GLuint _displayListEnemy;
};