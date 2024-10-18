#include "Level1.h"
#include "GameController.h"
#include "Renderer.h"
#include "SpriteSheet.h"
#include "TTFont.h"
#include "Timing.h"
#include "Warrior.h"

Level1::Level1()
{
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
		warrior->AssignValues(posPoint, (rand() % 21 + 80), 1);
		m_units.push_back(warrior);
	}

	Resource::AssignNonDefaultValues();
}

void Level1::Update(TTFont* ttfont)
{
	Renderer* r = &Renderer::Instance();
	Timing* t = &Timing::Instance();

	r->SetDrawColor(Color(128, 128, 128, 255));
	r->ClearScreen();
	float deltaTime = t->GetDeltaTime();
	for (Unit* unit : m_units)
	{
		Warrior* warrior = dynamic_cast<Warrior*>(unit);

		if (warrior)
		{
			unsigned int X1 = warrior->GetPoint().X + (deltaTime * warrior->GetSpeed());
			unsigned int Y1 = warrior->GetPoint().Y;
			warrior->SetPoint(Point{ X1, Y1 });

			r->RenderTexture(warriorSheet, warriorSheet->Update(EN_AN_RUN, deltaTime),
				Rect(X1, Y1, 69 * 1.8 + X1, 44 * 1.8 + Y1));
			cout << "Delta Time: " << deltaTime << ", Warrior Position: X=" << X1 << ", Y=" << Y1 << endl;
		}
	}
	


	std::string s = "Time: " + to_string(t->GetCurrentTime());
	ttfont->Write(r->GetRenderer(), s.c_str(), SDL_Color{ 0, 255, 0 }, SDL_Point{ 700, 0 });

	std::string fps = "Frames Per Second: " + std::to_string(t->GetFPS());
	ttfont->Write(r->GetRenderer(), fps.c_str(), SDL_Color{ 0, 0, 255 }, SDL_Point{ 0, 0 });
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
	Renderer* r = &Renderer::Instance();

	r->Initialize(m_mapSizeX, m_mapSizeY);
	warriorSheet = _sheetWarrior;
}

