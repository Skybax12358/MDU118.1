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
	enemies.push_back(objectPtr1);

	{
		std::ofstream binaryLevel("level.bin");

		// write out the number of enemies
		size_t numEnemies = enemies.size();
		binaryLevel.write(reinterpret_cast<const char*>(&numEnemies), sizeof(numEnemies));

		// save all of the enemies
		for (GameObject* objectPtr : enemies)
		{
			objectPtr->WriteToBinary(binaryLevel);
		}

		binaryLevel.close();
	}

	{
		std::ofstream csvLevel("level.csv");

		// write out the number of enemies
		csvLevel << enemies.size() << std::endl;

		// save all of the enemies
		for (GameObject* objectPtr : enemies)
		{
			objectPtr->WriteToCSV(csvLevel);
		}

		csvLevel.close();
	}

	// free up all of the game objects
	for (GameObject* objectPtr : enemies)
	{
		delete objectPtr;
	}

	{
		std::ifstream binaryLevel("level.bin");

		enemies = GameObject::ReadObjectsFromBinary(binaryLevel);

		binaryLevel.close();
	}

	// free up all of the game objects
	for (GameObject* objectPtr : enemies)
	{
		delete objectPtr;
	}

	{
		std::ifstream csvLevel("level.csv");

		enemies = GameObject::ReadObjectsFromCSV(csvLevel);

		csvLevel.close();
	}
}

void GameManager::EndPlay()
{
	// free up all of the game objects
	for (GameObject* objectPtr : enemies)
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

	/*
	canvas.ScaleTransform(0.5f, 0.5f);
	canvas.RotateTransform(30.0f);
	canvas.TranslateTransform(200.0f, 200.0f);
	
	// Render method demonstration (You can remove all of this code)
	GameFrameworkInstance.DrawLine(canvas, Vector2i(200, 200), Vector2i(400, 200), Gdiplus::Color::White);

	GameFrameworkInstance.DrawRectangle(canvas, AABBi(Vector2i(10, 110), Vector2i(100, 200)), false, Gdiplus::Color::White);
	GameFrameworkInstance.DrawRectangle(canvas, AABBi(Vector2i(200, 110), Vector2i(300, 200)), true, Gdiplus::Color::White);

	canvas.SetTransform(&transform);

	GameFrameworkInstance.DrawCircle(canvas, Vector2i(200, 200), 50, false, Gdiplus::Color::White);
	GameFrameworkInstance.DrawCircle(canvas, Vector2i(400, 200), 50, true, Gdiplus::Color::White);

	GameFrameworkInstance.DrawText(canvas, Vector2i(10, 300), 12, "Arial", "Hello World!", Gdiplus::Color::White);

	// Load the image file Untitled.png from the Images folder. Give it the unique name of Image1
	ImageWrapper* image1 = GameFrameworkInstance.GetLoadedImage(Image1);
	GameFrameworkInstance.DrawImage(canvas, Vector2i(400, 400), image1);
	*/

	// tell all of the game objects to render
	for (GameObject* gameObjectPtr : enemies)
	{
		gameObjectPtr->Render(canvas, clientRect);
	}

	// Restore the transformation of the scene
	canvas.SetTransform(&transform);
}



/*
1. Only make changes in GameManager.cpp
2. You can't delete more than 5 lines the code.
3. You only get 2 minutes to break the code.
*/