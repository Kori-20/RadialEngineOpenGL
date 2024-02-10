#include "ParalaxBackground.h"

ParalaxBackground::ParalaxBackground()
{
	paralLayerFront = &AddComponent<SpriteComponent>("Assets/bck2.bmp", 1, 3, 2);
	transform->SetPosition(1500, 1200);
	transform->SetRotation(90);
	Logger::Info(std::to_string(transform->GetPosition().x));
}

ParalaxBackground::~ParalaxBackground()
{
	
}

void ParalaxBackground::Update(float deltaTime)
{
	GameObject::Update(deltaTime);
	Logger::Info(std::to_string(transform->GetPosition().x));

	transform->SetPosition(transform->GetPosition().x - deltaTime * parallaxSpeed, transform->GetPosition().y);

	if (transform->GetPosition().x <= -1500)
	{
		transform->SetPosition(1500, transform->GetPosition().y);
	}
}
