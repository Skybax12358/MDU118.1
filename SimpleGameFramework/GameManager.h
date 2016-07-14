#pragma once

#include "GameFramework.h"
#include "GameObject.h"
#include "Vector.h"
#include <iostream>
using namespace std;

class GameManager
{
public:
	static GameManager& Instance();

	/** BeginPlay is called when the game first launches. It is only called once per launch. */
	void BeginPlay();

	/** EndPlay is called when the game is closing down. It is only called once and only on exit. */
	void EndPlay();

	/**
	 * Update is called every frame. Update is always called before render
	 *
	 * @param deltaTime The time in seconds since Update was last called.
	 */
	void Update(double deltaTime);

	/**
	 * Render is called every frame after Update is called. All drawing must happen in render.
	 *
	 * @param [in,out] canvas The canvas.
	 * @param clientRect	  The rectangle representing the drawable area.
	 */
	void Render(Gdiplus::Graphics& canvas, const CRect& clientRect);
	void OnSpaceDown();

private:
	GameManager();
	~GameManager();

private:
	GameObjects Everything;

public:
	int CurrentState;
};

/**
 * Retrieves the GameManagerInstance for the game.
 *
 * @return The game manager instance
 */
#define GameManagerInstance (GameManager::Instance())
