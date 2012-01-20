#pragma once

#include <stdlib.h>
#include <math.h>

#include "Renderer.h"
#include "Input.h"
#include "Physics.h"
#include "Sound.h"


class AI
{
public:
	AI(void);
	~AI(void);
	void shutdown();
	void initialize(Renderer* renderer, Input* input);
	void simulate(float milliseconds);

private:
	string getFPSString(float milliseconds);

	Renderer* renderer;
	Input* input;
	Physics* physics;
	int count;
	int fps;
};
