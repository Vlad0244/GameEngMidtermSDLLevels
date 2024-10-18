#pragma once
#include "Level.h"
#include "SpriteAnim.h"
#include "SpriteSheet.h"
#include "ObjectPool.h"

class Level1 : public Level
{
public:
	// Constructors/Destructors
	Level1();
	virtual ~Level1();

	// Methods
	void AssignNonDefaultValues() override;
	void Update(float deltaTime, TTFont* ttfont) override;
	boolean isFinished() override;
	void loadLevel() override;
	void startLevel(SpriteSheet* sheetWarrior) override;

private:
	// Members
	SpriteSheet* warriorSheet;
	int m_mapSizeX;
	int m_mapSizeY;
	vector<Unit*> m_units;
};

