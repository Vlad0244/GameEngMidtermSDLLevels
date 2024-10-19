#include "Rock.h"
#include "Renderer.h"
#include "BasicStructs.h"

ObjectPool<Rock>* Rock::Pool = nullptr;

Rock::~Rock()
{
}

void Rock::AssignNonDefaultValues()
{

	Resource::AssignNonDefaultValues();
}

void Rock::AssignValues(Point _posPoint, float _speed, int _direction)
{
	posPoint = _posPoint;
	speed = _speed;
	direction = _direction;
}

void Rock::Serialize(std::ostream& _stream)
{
	Resource::Serialize(_stream);
}

void Rock::Deserialize(std::istream& _stream)
{
	Resource::Deserialize(_stream);
}

void Rock::ToString()
{
	cout << "ROCK" << endl;
	Resource::ToString();
}
