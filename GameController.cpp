#include "GameController.h"
#include "Renderer.h"
#include "SpriteSheet.h"
#include "TTFont.h"
#include "Timing.h"
#include "Level1.h"

GameController::GameController()
{
	m_sdlEvent = { };
}

GameController::~GameController()
{
}

void GameController::RunGame()
{
	AssetController::Instance().Initialize(10000000); // Allocate 10MB
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

	Level1* level1 = new Level1();
	level1->AssignNonDefaultValues();
	level1->startLevel(sheetWarrior);

	while (m_sdlEvent.type != SDL_QUIT)
	{
		t->Tick();
		SDL_PollEvent(&m_sdlEvent);
		level1->Update(font);
		SDL_RenderPresent(r->GetRenderer());
	}

	delete SpriteAnim::Pool;
	delete SpriteSheet::Pool;

	font->Shutdown();
	r->Shutdown();
}