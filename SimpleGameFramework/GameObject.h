#pragma once

#include "Vector.h"
#include <list>
#include <iostream>
#include <fstream>
#include <string>
#include "GameFramework.h"

enum GameObjectType {
	egotBase,
	

	egotRangedEnemy,

	egotNumGameObjectTypes
};

class GameObject; // forward declare GameObject
typedef std::list<GameObject*> GameObjects;

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	virtual void WriteToCSV(std::ofstream& os);
	virtual void ReadFromCSV(std::ifstream& is);

	static GameObjects ReadObjectsFromCSV(std::ifstream& is);

	virtual void WriteToBinary(std::ofstream& os);
	virtual void ReadFromBinary(std::ifstream& is);

	static GameObjects ReadObjectsFromBinary(std::ifstream& is);

	virtual void Render(Gdiplus::Graphics& canvas, const CRect& clientRect);

	bool operator == (const GameObject& rhs) const
	{
		// TODO: add in comparison of the children
		return (type == rhs.type) &&
			   (name == rhs.name) &&
			   (location == rhs.location);
	}
	bool operator != (const GameObject& rhs) const
	{
		return !(*this == rhs);
	}

protected:
	GameObjectType type;
	std::string name;

public:
	Vector2i location;
	GameObjects children;
};

