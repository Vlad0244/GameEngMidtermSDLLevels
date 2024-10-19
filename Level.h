#ifndef LEVEL_H
#define LEVEL_H

#include "Unit.h"
#include "TTFont.h"
#include "SpriteAnim.h"
#include "SpriteSheet.h"
#include "ObjectPool.h"

class Level : public Resource
{
public:
	// Constructors/Destructors
	Level();
	virtual ~Level();

	// Methods
	void Serialize(std::ostream& _stream) override;
	void Deserialize(std::istream& _stream) override;
	void ToString() override;
	virtual void AssignNonDefaultValues() override;
	virtual void Update(TTFont* ttfont);
	virtual boolean isFinished();
	virtual void loadLevel();
	virtual void startLevel(SpriteSheet* sheet, SpriteSheet* sheet2);

private:
	// Members
	int m_mapSizeX;
	int m_mapSizeY;
	vector<Unit*> m_units;
};

#endif // LEVEL_H
