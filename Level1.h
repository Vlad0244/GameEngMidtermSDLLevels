#pragma once
#include "Level.h"
#include "SpriteAnim.h"
#include "SpriteSheet.h"
#include "ObjectPool.h"

const int MINSPEED = 80;
const int MAXSPEED = 100;
const string LEVELFILE = "Level1.bin";
class Level1 : public Level
{
public:
	// Constructors/Destructors
	Level1();
	virtual ~Level1();

	// Methods
	void Serialize(std::ostream& _stream) override;
	void Deserialize(std::istream& _stream) override;
	void AssignNonDefaultValues() override;
	void Update(TTFont* ttfont) override;
	boolean isFinished() override;
	void loadLevel() override;
	void startLevel(SpriteSheet* sheetWarrior, SpriteSheet* emptySheet) override;

private:
	// Members
	SpriteSheet* warriorSheet;
	int m_mapSizeX;
	int m_mapSizeY;
	bool finished;
	vector<Unit*> m_units;
	string loadStatus;
};

