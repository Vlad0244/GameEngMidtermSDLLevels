#pragma once
#include "Level.h"
#include "SpriteAnim.h"
#include "SpriteSheet.h"
#include "ObjectPool.h"

const int MINSPEED2 = 80;
const int MAXSPEED2 = 100;
const string LEVELFILE2 = "Level2.bin";
class Level2 : public Level
{
public:
	// Constructors/Destructors
	Level2();
	virtual ~Level2();

	// Methods
	void Serialize(std::ostream& _stream) override;
	void Deserialize(std::istream& _stream) override;
	void AssignNonDefaultValues() override;
	void Update(TTFont* ttfont) override;
	boolean isFinished() override;
	void loadLevel() override;
	void startLevel(SpriteSheet* sheetWarrior, SpriteSheet* rockSheet) override;

private:
	// Members
	SpriteSheet* warriorSheet;
	SpriteSheet* rockSheet;
	int m_mapSizeX;
	int m_mapSizeY;
	bool finished;
	vector<Unit*> m_units;
	string loadStatus;
};

