#pragma once

class CEnemy2 : public CSceneObject
{
public:
	CEnemy2();
	~CEnemy2(void);
	void Initialize(void);
	void Update(void);
	void Render(void);

protected:
	GLuint _displayListEnemy;
};