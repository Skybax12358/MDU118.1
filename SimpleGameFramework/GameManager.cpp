#include "stdafx.h"
#include "GameManager.h"

GameManager& GameManager::Instance()
{
	static GameManager instance;

	return instance;
}

GameManager::GameManager()
{
}

GameManager::~GameManager()
{
}

const char* Image1 = "Image1";

void GameManager::BeginPlay()
{
	////////////////////////////////////////////////////////////////////////////////
	// Begin example code

	// Load the image file Untitled.png from the Images folder. Give it the unique name of Image1
	GameFrameworkInstance.LoadImageResource(AppConfigInstance.GetResourcePath("Images/Untitled.png"), Image1);

	// End example code
	////////////////////////////////////////////////////////////////////////////////

	// Create a new game object and give it a random location
	GameObject* objectPtr1 = new GameObject();
	objectPtr1->location = Vector2i(GameFrameworkInstance.RandomIntBetween(100, 700),
									GameFrameworkInstance.RandomIntBetween(100, 500));

	// Add it to my list of enemies
	Everything.push_back(objectPtr1);

	{
		std::ofstream binaryLevel("level.bin");

		// write out the number of enemies
		size_t numEnemies = Everything.size();
		binaryLevel.write(reinterpret_cast<const char*>(&numEnemies), sizeof(numEnemies));

		// save all of the enemies
		for (GameObject* objectPtr : Everything)
		{
			objectPtr->WriteToBinary(binaryLevel);
		}

		binaryLevel.close();
	}

	{
		std::ofstream csvLevel("level.csv");

		// write out the number of enemies
		csvLevel << Everything.size() << std::endl;

		// save all of the enemies
		for (GameObject* objectPtr : Everything)
		{
			objectPtr->WriteToCSV(csvLevel);
		}

		csvLevel.close();
	}

	// free up all of the game objects
	for (GameObject* objectPtr : Everything)
	{
		delete objectPtr;
	}

	{
		std::ifstream binaryLevel("level.bin");

		Everything = GameObject::ReadObjectsFromBinary(binaryLevel);

		binaryLevel.close();
	}

	// free up all of the game objects
	for (GameObject* objectPtr : Everything)
	{
		delete objectPtr;
	}

	{
		std::ifstream csvLevel("level.csv");

		Everything = GameObject::ReadObjectsFromCSV(csvLevel);

		csvLevel.close();
	}
}

void GameManager::EndPlay()
{
	// free up all of the game objects
	for (GameObject* objectPtr : Everything)
	{
		delete objectPtr;
	}
}

void GameManager::Update(double deltaTime)
{

}

void GameManager::Render(Gdiplus::Graphics& canvas, const CRect& clientRect)
{
	// Save the current transformation of the scene
	Gdiplus::Matrix transform;
	canvas.GetTransform(&transform);

	// tell all of the game objects to render
	for (GameObject* gameObjectPtr : Everything)
	{
		gameObjectPtr->Render(canvas, clientRect);
	}

	// Restore the transformation of the scene
	canvas.SetTransform(&transform);
}

void GameManager::OnSpaceDown()
{
	// free up all of the game objects
	for (GameObject* objectPtr : Everything)
	{
  		
	}

	CurrentState++;
}