#pragma once
#include "ECS/GameObject.h"
#include "OpenGL/SpriteComponent.h"

class ParalaxBackground : public GameObject
{
public:

	ParalaxBackground();
	~ParalaxBackground();

	void Update(float deltaTime) override;

private:
	SpriteComponent* paralLayerFront;

	float parallaxSpeed = 30;
};

