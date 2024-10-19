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
	finished = false;
	warriorSheet = nullptr;
}

Level1::~Level1()
{
	m_units.clear();
}

void Level1::Serialize(std::ostream& _stream)
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
	Resource::Serialize(_stream);
}

void Level1::Deserialize(std::istream& _stream)
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
	Resource::Deserialize(_stream);
}

void Level1::AssignNonDefaultValues()
{
	m_mapSizeX = 1920;
	m_mapSizeY = 1080;
	finished = false;
	for (int count = 0; count < 10; count++)
	{
		Warrior* warrior = Warrior::Pool->GetResource();
		warrior->AssignNonDefaultValues();
		Point posPoint = Point(0, 10 + 100 * count);
		warrior->AssignValues(posPoint, (rand() % (MAXSPEED1 - MINSPEED1 + 1) + MINSPEED1), 1);
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


	float minDeltaTime = 1.0f / MINSPEED1;
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
	}

	std::string s = "Time: " + to_string(t->GetCurrentTimeT());
	ttfont->Write(r->GetRenderer(), s.c_str(), SDL_Color{ 0, 255, 0 }, SDL_Point{ 700, 0 });

	std::string fps = "Frames Per Second: " + std::to_string(t->GetFPS());
	ttfont->Write(r->GetRenderer(), fps.c_str(), SDL_Color{ 0, 0, 255 }, SDL_Point{ 0, 0 });


	int currentTime = t->GetCurrentTimeT();
	loadLevel(currentTime);
	
}

boolean Level1::isFinished()
{
	return finished;
}

void Level1::loadLevel(int currentTime)
{
	if (currentTime % 5 == 0)
	{
		ofstream writeStream(LEVELFILE1, ios::out | ios::binary);
		ifstream readStream(LEVELFILE1, ios::in | ios::binary);

		Serialize(writeStream);
		Deserialize(readStream);
	}
	
}

void Level1::startLevel(SpriteSheet* _sheetWarrior)
{
	warriorSheet = _sheetWarrior;
}

