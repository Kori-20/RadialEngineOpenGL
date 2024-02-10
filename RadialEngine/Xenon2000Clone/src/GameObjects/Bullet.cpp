#include "Bullet.h"
#include "../Managers/ScoreManager.h"
#include "Level/LevelManager.h"
#include "Enemies/TestEnemy.h"

Bullet::Bullet()
{
	bulletSprite = &AddComponent<SpriteComponent>("Assets/bullet.bmp",.1,.1, 1);
	bulletSprite->numberOfCollums = 1;
	bulletSprite->numberOfRows = 1;
	bulletSprite->isAnimated = false;

	bulletBox = &AddComponent<BoxCollision>(Vector2D(3,12));
	bulletBox->SetFilterMasking(AllyProjectileMask);
	bulletBox->SetFilterCollision(AllyProjectileF);

	bulletRb = &AddComponent<RigidBody>();
	bulletRb->afectedByGravity = false;
	bulletRb->SetCollider(bulletBox);	

	transform->SetRotation(90.f);
}

Bullet::~Bullet()
{

}

void Bullet::OnCollisionStart(GameObject* obj)
{

}

void Bullet::OnOverlapBegin(GameObject* obj)
{
	if (obj->HasTag(Enemy))
	{
		auto enemy = dynamic_cast<TestEnemy*>(obj);
		enemy->TakeDamage(pelletDamage);

		LevelManager::getInstance().GetCurrentLevel()->RemoveGameObject(this);

		Destroy();
	}
}

void Bullet::OnOverlapEnd(GameObject* obj)
{
	Logger::Warning("Bullet Overlap end");
}

void Bullet::Update(float deltaTime)
{
	GameObject::Update(deltaTime);
	bulletlifeTime += deltaTime;

	if (bulletlifeTime >= 4.f)
	{
		Destroy();
	}

	// Horizontal game
	if (goRight)
	{
		bulletRb->Move(Vector2D(pelletSpeed, bulletRb->GetVelocity().y), pelletSpeed);
	}
	else
	{
		bulletRb->Move(Vector2D(-pelletSpeed, bulletRb->GetVelocity().y), pelletSpeed);
	}

}
