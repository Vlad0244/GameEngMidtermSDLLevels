#include "GameController.h"
#include "Renderer.h"
#include "SpriteSheet.h"
#include "TTFont.h"
#include "Timing.h"

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
	r->Initialize(800, 600);

	TTFont* font = new TTFont();
	font->Initialize(20);

	Point ws = r->GetWindowSize();

	SpriteSheet::Pool = new ObjectPool<SpriteSheet>();
	SpriteAnim::Pool = new ObjectPool<SpriteAnim>();
	SpriteSheet* sheetWarrior = SpriteSheet::Pool->GetResource();
	sheetWarrior->Load("Assets/Textures/Warrior.tga");
	sheetWarrior->SetSize(17, 6, 69, 44);
	sheetWarrior->AddAnimation(EN_AN_IDLE, 0, 6, 6.0f);
	sheetWarrior->AddAnimation(EN_AN_RUN, 6, 8, 6.0f);

	SpriteSheet* sheetRock = SpriteSheet::Pool->GetResource();
	sheetRock->Load("Assets/Textures/Rock.tga");
	sheetRock->SetSize(1, 4, 20, 20);
	sheetRock->AddAnimation(EN_AN_IDLE, 0, 1, 6.0f);

	unsigned int xTest = 5;
	unsigned int yTest = 5;

	while (m_sdlEvent.type != SDL_QUIT)
	{
		t->Tick();
		//xTest = xTest + 1;
		//yTest = yTest + 1;
		SDL_PollEvent(&m_sdlEvent);
		//r->SetDrawColor(Color(255, 255, 255, 255));
		//r->ClearScreen();
		//r->RenderTexture(sheetWarrior, sheetWarrior->Update(EN_AN_IDLE, t->GetDeltaTime()), Rect(0, 0, 69 * 3, 44 * 3));
		//r->RenderTexture(sheetWarrior, sheetWarrior->Update(EN_AN_RUN, t->GetDeltaTime()), Rect(xTest, 150, xTest + 69 * 1.8, 150 + 44 * 1.8));

		//r->RenderTexture(sheetRock, sheetRock->Update(EN_AN_IDLE, t->GetDeltaTime()), Rect(400, yTest, 400 + 20 * 1, yTest + 20 * 1));


		//std::string s = "Frame number: " + std::to_string(sheetWarrior->GetCurrentClip(EN_AN_IDLE)) + ", Time: " + to_string(t->GetCurrentTime());
		//font->Write(r->GetRenderer(), s.c_str(), SDL_Color{ 0, 255, 0 }, SDL_Point{ 250, 50 });

		//s = "Frame number: " + std::to_string(sheetWarrior->GetCurrentClip(EN_AN_RUN));
		//font->Write(r->GetRenderer(), s.c_str(), SDL_Color{ 0, 255, 0 }, SDL_Point{ 250, 200 });

		//std::string fps = "Frames Per Second: " + std::to_string(t->GetFPS());
		//font->Write(r->GetRenderer(), fps.c_str(), SDL_Color{ 0, 0, 255 }, SDL_Point{ 0, 0 });

		SDL_RenderPresent(r->GetRenderer());
	}

	delete SpriteAnim::Pool;
	delete SpriteSheet::Pool;

	font->Shutdown();
	r->Shutdown();
}