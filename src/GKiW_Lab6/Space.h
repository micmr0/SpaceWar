#pragma once

// Space, czyli oteksturowana kula imituj�ca wszech�wiat.
class CSpace : public CSceneObject
{
public:
	CSpace(void);
	~CSpace(void);
	void Initialize(void);
	void Update(void);
	void Render(void);

protected:
	GLuint _displayListId;
	CTexture * _spaceTexture;
};

