#pragma once
#include "Unit.h"
#include "BasicStructs.h"

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
	void AssignValues(Point posPoint, int speed, int direction);
	int GetSpeed() { return speed; }
	Point GetPoint() { return posPoint; }

	// Members 
	static ObjectPool<Warrior>* Pool;

private:
	// Members
	boolean direction;
	int speed;
	Point posPoint;

};

