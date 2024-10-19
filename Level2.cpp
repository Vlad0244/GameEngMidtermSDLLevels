#include "Level2.h"
#include "GameController.h"
#include "Renderer.h"
#include "SpriteSheet.h"
#include "TTFont.h"
#include "Timing.h"
#include "Warrior.h"
#include "Rock.h"

Level2::Level2()
{
	m_mapSizeX = 0;
	m_mapSizeY = 0;
	m_units.clear();
	finished = false;
	warriorSheet = nullptr;
	rockSheet = nullptr;
	loadStatus = "No";
}

Level2::~Level2()
{
	m_units.clear();
}

void Level2::Serialize(std::ostream& _stream)
{
	_stream.write(reinterpret_cast<char*>(&m_mapSizeX), sizeof(m_mapSizeX));
	_stream.write(reinterpret_cast<char*>(&m_mapSizeY), sizeof(m_mapSizeY));

	int numberOfUnits = m_units.size();
	_stream.write(reinterpret_cast<char*>(&numberOfUnits), sizeof(numberOfUnits));
	for (int count = 0; count < numberOfUnits; count++)
	{
		SerializePointer(_stream, m_units[count]);
	}
	warriorSheet->Serialize(_stream);
	rockSheet->Serialize(_stream);
	Resource::Serialize(_stream);
}

void Level2::Deserialize(std::istream& _stream)
{
	_stream.read(reinterpret_cast<char*>(&m_mapSizeX), sizeof(m_mapSizeX));
	_stream.read(reinterpret_cast<char*>(&m_mapSizeY), sizeof(m_mapSizeY));

	int numberOfUnits;
	_stream.read(reinterpret_cast<char*>(&numberOfUnits), sizeof(numberOfUnits));
	for (int count = 0; count < numberOfUnits; count++)
	{
		Unit* unit;
		DeserializePointer(_stream, unit);
		m_units.push_back(unit);
	}
	warriorSheet->Deserialize(_stream);
	rockSheet->Deserialize(_stream);
	Resource::Deserialize(_stream);
}

void Level2::AssignNonDefaultValues()
{
	m_mapSizeX = 1280;
	m_mapSizeY = 720;
	finished = false;
	for (int count = 0; count < 10; count++)
	{
		Warrior* warrior = Warrior::Pool->GetResource();
		warrior->AssignNonDefaultValues();
		Point posPoint = Point(0, 10 + 100 * count);
		warrior->AssignValues(posPoint, (rand() % (MAXSPEED2 - MINSPEED2 + 1) + MINSPEED2), 1);
		m_units.push_back(warrior);
	}

	for (int count = 0; count < 10; count++)
	{
		Rock* rock = Rock::Pool->GetResource();
		rock->AssignNonDefaultValues();
		Point posPoint2 = Point(50 + 100 * count, 0);
		rock->AssignValues(posPoint2, (rand() % (MAXSPEED2 - MINSPEED2 + 1) + MINSPEED2), 0);
		m_units.push_back(rock);
	}

	Resource::AssignNonDefaultValues();
}

void Level2::Update(TTFont* ttfont)
{
	Renderer* r = &Renderer::Instance();
	Timing* t = &Timing::Instance();

	r->SetDrawColor(Color(0, 128, 0, 255));
	r->ClearScreen();


	float minDeltaTime = 1.0f / MINSPEED2;
	if (t->GetDeltaTime() < minDeltaTime * 1000) // Convert to milliseconds
	{
		SDL_Delay((Uint32)((minDeltaTime * 1000) - t->GetDeltaTime())); // Delay to maintain minimum frame time
	}

	float deltaTime = t->GetDeltaTime();

	for (Unit* unit : m_units)
	{
		Warrior* warrior = dynamic_cast<Warrior*>(unit);

		if (warrior)
		{
			unsigned int X1 = static_cast<unsigned int>(warrior->GetPoint().X + (deltaTime * warrior->GetSpeed()));
			unsigned int Y1 = warrior->GetPoint().Y;

			cout << "Distance: " << X1 - warrior->GetPoint().X << " Speed: " << warrior->GetSpeed() << endl;
			warrior->SetPoint(Point{ X1, Y1 });

			Rect src = warriorSheet->Update(EN_AN_RUN, deltaTime);
			Rect dist = Rect(X1, Y1, 69 * 1.8 + X1, 44 * 1.8 + Y1);

			r->RenderTexture(warriorSheet, src, dist);

			if (warrior->GetPoint().X >= m_mapSizeX)
			{
				finished = true;
			}
		}

		Rock* rock = dynamic_cast<Rock*>(unit);

		if (rock)
		{
			unsigned int X1 = rock->GetPoint().X;
			unsigned int Y1 = static_cast<unsigned int>(rock->GetPoint().Y + (deltaTime * rock->GetSpeed()));

			cout << "Distance: " << Y1 - rock->GetPoint().Y << " Speed: " << rock->GetSpeed() << endl;
			rock->SetPoint(Point{ X1, Y1 });

			Rect src = rockSheet->Update(EN_AN_IDLE, deltaTime);
			Rect dist = Rect(X1, Y1, 20 * 1 + X1, 20 * 1 + Y1);

			r->RenderTexture(rockSheet, src, dist);
		}
	}

	std::string s = "Time: " + to_string(t->GetCurrentTimeT());
	ttfont->Write(r->GetRenderer(), s.c_str(), SDL_Color{ 0, 0, 255 }, SDL_Point{ 300, 0 });

	std::string fps = "Frames Per Second: " + std::to_string(t->GetFPS());
	ttfont->Write(r->GetRenderer(), fps.c_str(), SDL_Color{ 0, 0, 255 }, SDL_Point{ 0, 0 });

	std::string loaded = "Auto Saved: " + loadStatus;
	ttfont->Write(r->GetRenderer(), loaded.c_str(), SDL_Color{ 0, 0, 255 }, SDL_Point{ 500, 0 });

	int time = t->GetCurrentTimeT();
	if (time == 5)
	{
		loadLevel();
		loadStatus = "Yes";
	}
}

boolean Level2::isFinished()
{
	return finished;
}

void Level2::loadLevel()
{
	ofstream writeStream(LEVELFILE2, ios::out | ios::binary);
	ifstream readStream(LEVELFILE2, ios::in | ios::binary);

	Serialize(writeStream);
	Deserialize(readStream);
}

void Level2::startLevel(SpriteSheet* _sheetWarrior, SpriteSheet* _sheetRock)
{
	Renderer* r = &Renderer::Instance();

	r->Initialize(m_mapSizeX, m_mapSizeY);
	warriorSheet = _sheetWarrior;
	rockSheet = _sheetRock;
}

