#pragma once
#include "Unit.h"
#include "BasicStructs.h"
#include "SpriteSheet.h"

class Warrior : public Unit
{
public:
	// Constructors/Destructors
	Warrior() : posPoint(0, 0) {}
	virtual ~Warrior();

	// Methods
	void Serialize(std::ostream& _stream) override;
	void Deserialize(std::istream& _stream) override;
	void ToString() override;
	void AssignNonDefaultValues() override;
	void AssignValues(Point posPoint, float speed, int direction);
	void SetPoint(Point _posPoint) { posPoint = _posPoint; }
	int GetSpeed() { return speed; }
	Point GetPoint() { return posPoint; }
	boolean GetIsHit() { return isHit; }
	void SetIsHit(boolean _hit) { isHit = _hit; }
	SpriteSheet* GetSpriteSheet() { return warriorSheet; }
	// Members 
	static ObjectPool<Warrior>* Pool;

private:
	// Members
	SpriteSheet* warriorSheet;
	boolean direction;
	float speed;
	Point posPoint;
	boolean isHit;
};

