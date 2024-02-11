#include "EntityManager.h"

EntityManager::EntityManager()
{

}

EntityManager::~EntityManager()
{

}

void EntityManager::Init()
{
	for (auto& rE : entityGroup)
	{
		rE->Init();
	}
}

void EntityManager::Start()
{
	for (auto& rE : entityGroup)
	{
		rE->Start();
	}
}

void EntityManager::Update(float deltaTime)
{
	for (auto& entity : entityGroup) 
	{
		if (entity->IsMarkedForRemoval())
		{
			MarkForRemoval(entity);
		}
		else 
		{
			entity->Update(deltaTime);
		}
	}
	RemoveMarkedEntities();
}

void EntityManager::LateUpdate(float deltaTime)
{
	for (int i = 0; i < entityGroup.size(); i++)
	{
		
	}
}

void EntityManager::Draw(float deltaTime)
{

	// Sort the entities by layer before drawing
	std::stable_sort(entityGroup.begin(), entityGroup.end(), [](const GameObject* a, const GameObject* b)
	{
		return a->GetLayer() < b->GetLayer();
	});

	for (auto& rE : entityGroup)
	{
		rE->Draw(deltaTime);
	}
}

void EntityManager::AddEntity(GameObject* entity)
{
	entityGroup.push_back(entity);

	//Temporary ID System
	int newID = (entityGroup.size() - 1);
	entity->SetID(newID);
	Logger::Note("Obj created: " + std::to_string(newID));
}

void EntityManager::RemoveEntity(GameObject* entity)
{
	auto it = std::find(entityGroup.begin(), entityGroup.end(), entity);//find the entity
	if (it != entityGroup.end()) //if the entity is found
	{
		entityGroup.erase(it);//erase the entity

		//Temporary ID System
		int vacantID = entity->GetID();
		Logger::Warning("Obj removed: " + std::to_string(vacantID));
	}
	delete entity;//delete the entity 
}

void EntityManager::ClearEntities()
{
	entityGroup.clear();
}

void EntityManager::MarkForRemoval(GameObject* entity) 
{
	entity->MarkForRemoval();
}

void EntityManager::RemoveMarkedEntities() 
{
	// Define a lambda function that marks entities for removal and returns true if they should be deleted
	auto shouldDeleteAndRemove = [](GameObject* entity) 
	{
		if (entity->IsMarkedForRemoval()) 
		{
			int vacantID = entity->GetID();
			Logger::Warning("Obj removed: " + std::to_string(vacantID));
			entity->Destroy();
			delete entity; 
			return true; 
		}
		return false; // Return false to keep the entity in the vector
	};

	// Use the lambda function with std::remove_if to move the entities to be deleted to the end of the vector
	auto newEnd = std::remove_if(entityGroup.begin(), entityGroup.end(), shouldDeleteAndRemove);
	// Erase the entities marked for deletion from the vector
	entityGroup.erase(newEnd, entityGroup.end());
}

