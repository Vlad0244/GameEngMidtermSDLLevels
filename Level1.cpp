#include "Level1.h"
#include "GameController.h"
#include "Renderer.h"
#include "SpriteSheet.h"
#include "TTFont.h"
#include "Timing.h"
#include "Warrior.h"

Level1::Level1()
{
	AssetController::Instance().Initialize(10000000); // Allocate 10MB
	Unit::Pool = new ObjectPool<Unit>();

	m_mapSizeX = 0;
	m_mapSizeY = 0;
	m_units.clear();
}

Level1::~Level1()
{
	m_units.clear();
	delete Unit::Pool;
	AssetController::Instance().Clear(); // Free 10MB
}

void Level1::AssignNonDefaultValues()
{
	m_mapSizeX = 1920;
	m_mapSizeY = 1080;
	for (int count = 0; count < 10; count++)
	{
		Warrior* warrior = Warrior::Pool->GetResource();
		warrior->AssignNonDefaultValues();
		Point posPoint = Point(0, 10 + 100 * count);
		warrior->AssignValues(posPoint, rand() % 21 + 80, 1);
		m_units.push_back(warrior);
	}

	Resource::AssignNonDefaultValues();
}

void Level1::Update(float deltaTime, TTFont* ttfont)
{
	Renderer* r = &Renderer::Instance();
	Timing* t = &Timing::Instance();
	r->SetDrawColor(Color(128, 128, 128, 255));
	r->ClearScreen();

	for (Unit* unit : m_units)
	{
		int X1 = dynamic_cast<Warrior*>(unit)->GetPoint().X + (t->GetDeltaTime() * dynamic_cast<Warrior*>(unit)->GetSpeed());
		int Y1 = dynamic_cast<Warrior*>(unit)->GetPoint().Y;

		r->RenderTexture(warriorSheet, warriorSheet->Update(EN_AN_IDLE, t->GetDeltaTime()), 
			Rect(X1, Y1, 69 * 1.8 + X1, 44 * 1.8 + Y1));
	}


	std::string s = "Frame number: " + std::to_string(warriorSheet->GetCurrentClip(EN_AN_IDLE)) + ", Time: " + to_string(t->GetCurrentTime());
	ttfont->Write(r->GetRenderer(), s.c_str(), SDL_Color{ 0, 255, 0 }, SDL_Point{ 100, 0 });

	std::string fps = "Frames Per Second: " + std::to_string(t->GetFPS());
	ttfont->Write(r->GetRenderer(), fps.c_str(), SDL_Color{ 0, 0, 255 }, SDL_Point{ 0, 0 });

	SDL_RenderPresent(r->GetRenderer());
}

boolean Level1::isFinished()
{
	return boolean();
}

void Level1::loadLevel()
{
}

void Level1::startLevel(SpriteSheet* _sheetWarrior)
{
	warriorSheet = _sheetWarrior;
}

