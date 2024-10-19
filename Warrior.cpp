#include "Warrior.h"
#include "Renderer.h"
#include "BasicStructs.h"

ObjectPool<Warrior>* Warrior::Pool = nullptr;

Warrior::~Warrior()
{
}

void Warrior::AssignNonDefaultValues()
{

	Resource::AssignNonDefaultValues();
}

void Warrior::AssignValues(Point _posPoint, float _speed, int _direction)
{
	cout << "Warrior with Pos: X: " << posPoint.X << " Y: " << posPoint.Y << " is being created " << endl;
	posPoint = _posPoint;
	speed = _speed;
	direction = _direction;
	SetIsHit(false);
}

void Warrior::Serialize(std::ostream& _stream)
{
	Resource::Serialize(_stream);
}

void Warrior::Deserialize(std::istream& _stream)
{
	Resource::Deserialize(_stream);
}

void Warrior::ToString()
{
	cout << "WARRIOR" << endl;
	Resource::ToString();
}