#pragma once
#include "Unit.h"
#include "BasicStructs.h"

class Rock : public Unit
{
public:
	// Constructors/Destructors
	Rock() : posPoint(0, 0) {}
	virtual ~Rock();

	// Methods
	void Serialize(std::ostream& _stream) override;
	void Deserialize(std::istream& _stream) override;
	void ToString() override;
	void AssignNonDefaultValues() override;
	void AssignValues(Point posPoint, float speed, int direction);
	void SetPoint(Point _posPoint) { posPoint = _posPoint; }
	int GetSpeed() { return speed; }
	Point GetPoint() { return posPoint; }
	
	// Members 
	static ObjectPool<Rock>* Pool;

private:
	// Members
	boolean direction;
	float speed;
	Point posPoint;
};

