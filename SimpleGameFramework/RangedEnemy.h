#pragma once
#include "GameObject.h"
class RangedEnemy :
	public GameObject
{
public:
	RangedEnemy();
	virtual ~RangedEnemy();

	virtual void WriteToCSV(std::ofstream& os);
	virtual void ReadFromCSV(std::ifstream& is);

	virtual void WriteToBinary(std::ofstream& os);
	virtual void ReadFromBinary(std::ifstream& is);

	//basic integers
public:
	int startingHealth = 20;
	int maxHealth = 50;
	int attackRange = 250;
	int attackDamage = 10;
};

