#include "GameController.h"
#include "Renderer.h"
#include "SpriteSheet.h"
#include "TTFont.h"
#include "Timing.h"
#include "Level1.h"
#include "Level2.h"

GameController::GameController()
{
	state = LEVEL1;
	m_sdlEvent = { };
}

GameController::~GameController()
{
}

void GameController::RunGame()
{
	Level1* level1 = new Level1();
	Level2* level2 = new Level2();
	level1->AssignNonDefaultValues();
	level2->AssignNonDefaultValues();

	Renderer* r = &Renderer::Instance();
	Timing* t = &Timing::Instance();


	TTFont* font = new TTFont();
	font->Initialize(20);






	r->Initialize(1920, 1080);

	//level1->startLevel(sheetWarrior, nullptr);
	//level2->startLevel(sheetWarrior, sheetRock);
	bool run = true;

	while (run)
	{
		t->Tick();
		SDL_PollEvent(&m_sdlEvent);
		if (m_sdlEvent.type == SDL_QUIT)
			state = QUIT;

		switch (state)
		{
		case GameState::LEVEL1:
			{
				level1->Update(font);
				if (level1->isFinished())
				{
					state = LEVEL2;
				}
				break;
			}
		case GameState::LEVEL2:
			{
				level2->Update(font);
				if (level2->isFinished())
				{
					state = QUIT;
				}
				break;
			}
		case GameState::QUIT:
		{
			run = false;
			break;
		}
		}

		SDL_RenderPresent(r->GetRenderer());
	}

	delete SpriteAnim::Pool;
	delete SpriteSheet::Pool;
	delete level1;
	delete level2;

	font->Shutdown();
	r->Shutdown();
}