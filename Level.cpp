#include "Level.h"
#include "GameController.h"
#include "Renderer.h"
#include "SpriteSheet.h"
#include "TTFont.h"
#include "Timing.h"
#include "Warrior.h"

Level::Level()
{
	Unit::Pool = new ObjectPool<Unit>();
	Warrior::Pool = new ObjectPool<Warrior>();
	AssetController::Instance().Initialize(10000000); // Allocate 10MB
	m_mapSizeX = 0;
	m_mapSizeY = 0;
	m_units.clear();
}

Level::~Level()
{
	m_units.clear();
	delete Unit::Pool;
	delete Warrior::Pool;
	AssetController::Instance().Clear(); // Free 10MB
}

void Level::AssignNonDefaultValues()
{
	m_mapSizeX = 128;
	m_mapSizeY = 256;
	for (int count = 0; count < 5; count++)
	{
		Unit* unit = Unit::Pool->GetResource();
		unit->AssignNonDefaultValues();
		m_units.push_back(unit);
	}

	Resource::AssignNonDefaultValues();
}

void Level::Update(TTFont* ttfont)
{
}

boolean Level::isFinished()
{
	return boolean();
}

void Level::loadLevel()
{
}

void Level::startLevel(SpriteSheet* sheet)
{
}

void Level::Serialize(std::ostream& _stream)
{
	_stream.write(reinterpret_cast<char*>(&m_mapSizeX), sizeof(m_mapSizeX));
	_stream.write(reinterpret_cast<char*>(&m_mapSizeY), sizeof(m_mapSizeY));

	int numberOfUnits = m_units.size();
	_stream.write(reinterpret_cast<char*>(&numberOfUnits), sizeof(numberOfUnits));
	for (int count = 0; count < numberOfUnits; count++)
	{
		SerializePointer(_stream, m_units[count]);
	}
	Resource::Serialize(_stream);
}

void Level::Deserialize(std::istream& _stream)
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
	Resource::Deserialize(_stream);
}

void Level::ToString()
{
	cout << "LEVEL" << endl;
	cout << "MapSizeX: " << m_mapSizeX << endl;
	cout << "MapSizeY: " << m_mapSizeY << endl;
	for (int count = 0; count < m_units.size(); count++)
	{
		m_units[count]->ToString();
	}
	Resource::ToString();
}