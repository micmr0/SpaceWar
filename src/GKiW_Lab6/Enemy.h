#pragma once

class CEnemy : public CSceneObject
{
public:
	CEnemy();
	~CEnemy(void);
	void Initialize(void);
	void Update(void);
	void Render(void);

	bool kolizja;
	int ruch;
	int stan;

protected:
	GLuint _displayListEnemy;
};