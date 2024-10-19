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


	SpriteSheet::Pool = new ObjectPool<SpriteSheet>();
	SpriteAnim::Pool = new ObjectPool<SpriteAnim>();
	SpriteSheet* sheetWarrior = SpriteSheet::Pool->GetResource();
	sheetWarrior->Load("Assets/Textures/Warrior.tga");
	sheetWarrior->SetSize(17, 6, 69, 44);
	sheetWarrior->AddAnimation(EN_AN_IDLE, 0, 6, 1.0f);
	sheetWarrior->AddAnimation(EN_AN_RUN, 6, 8, 1.0f);
	sheetWarrior->AddAnimation(EN_AN_DEATH, 26, 11, 1.0f);

	SpriteSheet* sheetRock = SpriteSheet::Pool->GetResource();
	sheetRock->Load("Assets/Textures/Rock.tga");
	sheetRock->SetSize(1, 4, 20, 20);
	sheetRock->AddAnimation(EN_AN_IDLE, 0, 4, 1.0f);

	r->Initialize(1920, 1080);

	level1->startLevel(sheetWarrior, nullptr);
	level2->startLevel(sheetWarrior, sheetRock);
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