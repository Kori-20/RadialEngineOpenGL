#include "Rock1.h"
#include "Aid/MathTools.h"

float posChange = 0;

Rock1::Rock1()
{
	transform->SetPosition(660, 400);
	
	sprite = &AddComponent<SpriteComponent>("Assets/SAster96.bmp", 96.f/480, 96.f/480, 1);
	sprite->numberOfCollums = 5;
	sprite->numberOfRows = 5;

	overlapBox = &AddComponent<BoxCollision>();
	overlapBox->SetBoxDimenssions(Vector2D(30, 30));
	overlapBox->SetFilterMasking(GameObjectMask);
	overlapBox->SetFilterCollision(GameObjectF);
	overlapBox->_sensor = false;

	myRb = &AddComponent<RigidBody>();
	myRb->SetCollider(overlapBox);
	myRb->afectedByGravity = false;
	myRb->bodyType = EBodyType::KinematicB;
	SetLayer(15);
}

Rock1::~Rock1()
{

}

void Rock1::Update(float deltaTime)
{
	GameObject::Update(deltaTime);
	myRb->Move(Vector2D(-0.1f, 0), rockSpeed);

	float currentRotation = transform->GetRotation();
	transform->SetRotation(currentRotation + rotationSpeed);
}

