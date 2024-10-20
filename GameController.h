#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include "StandardIncludes.h"

enum GameState { LEVEL1, LEVEL2, QUIT };

class GameController : public Singleton<GameController>
{
public:
	// Constructors/Destructors
	GameController();
	virtual ~GameController();

	// Methods
	void RunGame();

private:
	// Members
	GameState state;
	SDL_Event m_sdlEvent;
};

#endif // GAME_CONTROLLER_H
