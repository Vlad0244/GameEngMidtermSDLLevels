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
	//warriorSheet->Serialize(_stream);
	//rockSheet->Serialize(_stream);
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
	//warriorSheet->Deserialize(_stream);
	//rockSheet->Deserialize(_stream);
	Resource::Deserialize(_stream);
}

void Level2::AssignNonDefaultValues()
{
	m_mapSizeX = 1920;
	m_mapSizeY = 1080;
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
	//for (int i = 0; i < m_units.size(); i ++)
	{
		Rock* rock = dynamic_cast<Rock*>(unit);

		if (rock)
		{
			float kof = rock->GetSpeed() / MAXSPEED2 * 6.0f;
			unsigned int X1 = rock->GetPoint().X;
			unsigned int Y1 = static_cast<unsigned int>(rock->GetPoint().Y + (deltaTime * rock->GetSpeed()));

			rock->SetPoint(Point{ X1, Y1 });

			Rect src = rock->GetSpriteSheet()->Update(EN_AN_IDLE, deltaTime, kof);
			Rect dist = Rect(X1, Y1, 20 * 1 + X1, 20 * 1 + Y1);

			r->RenderTexture(rock->GetSpriteSheet(), src, dist);

		}

		Warrior* warrior = dynamic_cast<Warrior*>(unit);

		if (warrior)
		{
			unsigned int X1 = static_cast<unsigned int>(warrior->GetPoint().X + (deltaTime * warrior->GetSpeed()));
			unsigned int Y1 = warrior->GetPoint().Y;
			cout << "Speed: " << warrior->GetSpeed() << " Max Speed: " << MAXSPEED2 << " " << (warrior->GetSpeed() / MAXSPEED2) * 6.0f;
			float kof = ((float)warrior->GetSpeed() / (float)MAXSPEED2) * 6.0f;

			cout << "Distance: " << X1 - warrior->GetPoint().X << " Speed: " << warrior->GetSpeed() << endl;
			warrior->SetPoint(Point{ X1, Y1 });

			if (warrior->GetPoint().X >= m_mapSizeX)
			{
				finishLevel();
			}

			if (!warrior->GetIsHit()) 
			{
				Rect src = warrior->GetSpriteSheet()->Update(EN_AN_RUN, deltaTime, kof);
				Rect dist = Rect(X1, Y1, 69 * 1.8 + X1, 44 * 1.8 + Y1);

				r->RenderTexture(warrior->GetSpriteSheet(), src, dist);


				for (auto it = m_units.begin(); it != m_units.end();)
				{

					Rock* rock = dynamic_cast<Rock*>(*it);

					if (rock)
					{

						boolean collision = checkCollision(warrior, rock);

						if (collision)
						{
							warrior->SetIsHit(true);
							it = m_units.erase(it);
							// a warr will only collide with one rock at a given frame. break out of iteration if collision occurs.
							break;
						}
						else
						{
							++it; // if no collision
						}
					}
					else
					{
						++it; // if not rock
					}
				}
			}
			
			else 
			{
				Rect src = warrior->GetSpriteSheet()->Update(EN_AN_DEATH, deltaTime, kof);

				Rect dist = Rect(X1, Y1, 69 * 1.8 + X1, 44 * 1.8 + Y1);
				r->RenderTexture(warrior->GetSpriteSheet(), src, dist);
				cout << "Current Clip Frame: " << warrior->GetSpriteSheet()->GetCurrentClip(EN_AN_DEATH) << endl;
				if (warrior->GetSpriteSheet()->GetCurrentClip(EN_AN_DEATH) >= 36)
				{
					cout << " We are deleting warrior" << endl;
					m_units.erase(find(m_units.begin(), m_units.end(), warrior));

				}
			}



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
	if (m_units.empty())
	{
		finishLevel();
	}
}

boolean Level2::checkCollision(Warrior* warr, Rock* rock) {
	Point warrPoint = warr->GetPoint();
	Point rockPoint = rock->GetPoint();

	Rect warrDist = Rect(warrPoint.X, warrPoint.Y, 69 * 1.8 + warrPoint.X, 44 * 1.8 + warrPoint.Y);
	Rect rockDist = Rect(rockPoint.X, rockPoint.Y, 20 * 1 + rockPoint.X, 20 * 1 + rockPoint.Y);

	int warrX1 = warrDist.X1;         
	int warrY1 = warrDist.Y1;         
	int warrX2 = warrDist.X2;         
	int warrY2 = warrDist.Y2;         

	int rockX1 = rockDist.X1;        
	int rockY1 = rockDist.Y1;        
	int rockX2 = rockDist.X2;        
	int rockY2 = rockDist.Y2;        

	return (warrX1 < rockX2 && warrX2 > rockX1 && warrY1 < rockY2 && warrY2 > rockY1);
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
	cout << "Level2 is started" << endl;
	warriorSheet = _sheetWarrior;
	rockSheet = _sheetRock;
}

void Level2::finishLevel()
{
	Timing* t = &Timing::Instance();
	t->Reset();
	finished = true;
}

