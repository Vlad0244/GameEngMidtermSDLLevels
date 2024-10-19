#pragma once
#include "Level.h"
#include "SpriteAnim.h"
#include "SpriteSheet.h"
#include "ObjectPool.h"

const int MINSPEED1 = 80;
const int MAXSPEED1 = 100;
const string LEVELFILE1 = "Level1.bin";
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
	void loadLevel(int currentTime);
	void startLevel(SpriteSheet* sheetWarrior) override;

private:
	// Members
	SpriteSheet* warriorSheet;
	int m_mapSizeX;
	int m_mapSizeY;
	bool finished;
	vector<Unit*> m_units;
};

