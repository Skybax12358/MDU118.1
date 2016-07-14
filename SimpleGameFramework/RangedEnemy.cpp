#include "stdafx.h"
#include "RangedEnemy.h"


RangedEnemy::RangedEnemy()
{
	type = egotRangedEnemy;
	name = "RangedEnemy";
}


RangedEnemy::~RangedEnemy()
{
}

void RangedEnemy::Render(Gdiplus::Graphics& canvas, const CRect& clientRect)
{
	// Save the current transformation of the scene
	Gdiplus::Matrix transform;
	canvas.GetTransform(&transform);

	canvas.TranslateTransform((float)location.X, (float)location.Y);

	///// ALL OF THE RENDERING CODE GOES HERE
	GameFrameworkInstance.DrawRectangle(canvas, AABBi(Vector2i(-5, -5), Vector2i(5, 5)), true, Gdiplus::Color::Red);

	// Restore the transformation of the scene
	canvas.SetTransform(&transform);
}

void RangedEnemy::WriteToCSV(std::ofstream& os)
{
	// save the base data first
	GameObject::WriteToCSV(os);
	
		// save our own data
	os << attackDamage << ","
		<< attackRange << ","
		<< startingHealth << ","
		<< maxHealth << ","
		<< std::endl;
}

void RangedEnemy::WriteToBinary(std::ofstream& os)
{
	// save the base data first
	GameObject::WriteToBinary(os);
	
	// save our own data here
	os.write(reinterpret_cast<const char*>(&attackDamage), sizeof(attackDamage));
	os.write(reinterpret_cast<const char*>(&attackRange), sizeof(attackRange));
	os.write(reinterpret_cast<const char*>(&startingHealth), sizeof(startingHealth));
	os.write(reinterpret_cast<const char*>(&maxHealth), sizeof(maxHealth));
	
}

void RangedEnemy::ReadFromBinary(std::ifstream& is)
{
	// load the base data first
	GameObject::ReadFromBinary(is);

	// load our own data here
	is.read(reinterpret_cast<char*>(&attackDamage), sizeof(attackDamage));
	is.read(reinterpret_cast<char*>(&attackRange), sizeof(attackRange));
	is.read(reinterpret_cast<char*>(&startingHealth), sizeof(startingHealth));
	is.read(reinterpret_cast<char*>(&maxHealth), sizeof(maxHealth));

}

void RangedEnemy::ReadFromCSV(std::ifstream& is)
{
	// load the base data first
	GameObject::ReadFromCSV(is);

	// load our own data here
	is >> attackDamage
		>> attackRange
		>> maxHealth
		>> startingHealth;
}

