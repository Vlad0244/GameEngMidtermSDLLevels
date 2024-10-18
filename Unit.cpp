#include "Unit.h"

ObjectPool<Unit>* Unit::Pool = nullptr;

Unit::Unit()
{}

Unit::~Unit()
{
}

void Unit::AssignNonDefaultValues()
{
	Resource::AssignNonDefaultValues();
}

void Unit::Serialize(std::ostream& _stream)
{
	Resource::Serialize(_stream);
}

void Unit::Deserialize(std::istream& _stream)
{
	Resource::Deserialize(_stream);
}

void Unit::ToString()
{
	cout << "UNIT" << endl;
	Resource::ToString();
}