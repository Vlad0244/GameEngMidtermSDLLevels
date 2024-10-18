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

void Warrior::AssignValues(Point posPoint, int speed, int direction)
{
	posPoint = posPoint;
	speed = speed;
	direction = direction;
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