#pragma once
#include "stdafx.h"

static const int number = 500;
static const float far_plane = -30.f;
static const float near_plane = 6.0f;
static const float gap = 2.0f;
static const float field_width = 50.0f;
static const float field_height = 30.0f;
static const float radiaus = 50.0f;
static const float speed = .03f;

static const float g_alpha = 0.3f;
static float g_red = 0.0f;
static float g_speed = speed;
static const float g_speed_inc = 0.0f;

static float** g_xyz = new float*[number];
static float** g_colors = new float*[number];

class CStars : public CSceneObject
{
public:
	CStars(void);
	~CStars(void);
	void Initialize(void);
	void Update(void);
	void Render(void);
};

