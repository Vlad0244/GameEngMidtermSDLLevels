#include "GameController.h"
#include "Renderer.h"
#include "SpriteSheet.h"
#include "TTFont.h"
#include "Timing.h"
#include "Level1.h"
#include "Level2.h"

GameController::GameController()
{
	m_sdlEvent = { };
}

GameController::~GameController()
{
}

void GameController::RunGame()
{
	// Level 1 logic
	/*Level1* level1 = new Level1();
	Renderer* r = &Renderer::Instance();
	Timing* t = &Timing::Instance();
	

	TTFont* font = new TTFont();
	font->Initialize(20);


	SpriteSheet::Pool = new ObjectPool<SpriteSheet>();
	SpriteAnim::Pool = new ObjectPool<SpriteAnim>();
	SpriteSheet* sheetWarrior = SpriteSheet::Pool->GetResource();
	sheetWarrior->Load("Assets/Textures/Warrior.tga");
	sheetWarrior->SetSize(17, 6, 69, 44);
	sheetWarrior->AddAnimation(EN_AN_IDLE, 0, 6, 2.0f);
	sheetWarrior->AddAnimation(EN_AN_RUN, 6, 8, 2.0f);

	SpriteSheet* sheetRock = SpriteSheet::Pool->GetResource();
	sheetRock->Load("Assets/Textures/Rock.tga");
	sheetRock->SetSize(1, 4, 20, 20);
	sheetRock->AddAnimation(EN_AN_IDLE, 0, 1, 6.0f);

	
	level1->AssignNonDefaultValues();
	level1->startLevel(sheetWarrior, nullptr);

	while (!level1->isFinished())
	{
		t->Tick();
		SDL_PollEvent(&m_sdlEvent);
		if (m_sdlEvent.type == SDL_QUIT)
			break;

		level1->Update(font);
		
		SDL_RenderPresent(r->GetRenderer());
	}

	delete SpriteAnim::Pool;
	delete SpriteSheet::Pool;
	delete level1;

	font->Shutdown();
	r->Shutdown();*/

	// Level 2 logic
	/*Level2* level2 = new Level2();
	Renderer* r2 = &Renderer::Instance();
	Timing* t2 = &Timing::Instance();


	TTFont* font2 = new TTFont();
	font2->Initialize(20);


	SpriteSheet::Pool = new ObjectPool<SpriteSheet>();
	SpriteAnim::Pool = new ObjectPool<SpriteAnim>();
	SpriteSheet* sheetWarrior2 = SpriteSheet::Pool->GetResource();
	sheetWarrior2->Load("Assets/Textures/Warrior.tga");
	sheetWarrior2->SetSize(17, 6, 69, 44);
	sheetWarrior2->AddAnimation(EN_AN_IDLE, 0, 6, 2.0f);
	sheetWarrior2->AddAnimation(EN_AN_RUN, 6, 8, 2.0f);
	sheetWarrior2->AddAnimation(EN_AN_DEATH, 26, 11, 2.0f);

	SpriteSheet* sheetRock2 = SpriteSheet::Pool->GetResource();
	sheetRock2->Load("Assets/Textures/Rock.tga");
	sheetRock2->SetSize(1, 4, 20, 20);
	sheetRock2->AddAnimation(EN_AN_IDLE, 0, 0, 6.0f);


	level2->AssignNonDefaultValues();
	level2->startLevel(sheetWarrior2, sheetRock2);

	while (!level2->isFinished())
	{
		t2->Tick();
		SDL_PollEvent(&m_sdlEvent);
		if (m_sdlEvent.type == SDL_QUIT)
			break;

		level2->Update(font2);

		SDL_RenderPresent(r2->GetRenderer());
	}

	delete SpriteAnim::Pool;
	delete SpriteSheet::Pool;
	delete level2;

	font2->Shutdown();
	r2->Shutdown();*/

	// TEMP LOGIC
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
	sheetWarrior->AddAnimation(EN_AN_IDLE, 0, 6, 2.0f);
	sheetWarrior->AddAnimation(EN_AN_RUN, 6, 8, 2.0f);

	SpriteSheet* sheetRock = SpriteSheet::Pool->GetResource();
	sheetRock->Load("Assets/Textures/Rock.tga");
	sheetRock->SetSize(1, 4, 20, 20);
	sheetRock->AddAnimation(EN_AN_IDLE, 0, 1, 6.0f);

	r->Initialize(1920, 1080);

	level1->startLevel(sheetWarrior, nullptr);
	level2->startLevel(sheetWarrior, sheetRock);

	while (true && !level2->isFinished())
	{
		t->Tick();

		SDL_PollEvent(&m_sdlEvent);
		if (m_sdlEvent.type == SDL_QUIT)
			break;

		if (!level1->isFinished())
		{
			level1->Update(font);
		}
		else
		{
			level2->Update(font);
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