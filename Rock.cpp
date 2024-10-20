#include "Rock.h"
#include "Renderer.h"
#include "BasicStructs.h"
#include "SpriteSheet.h"

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
	SpriteSheet* sheetRock = SpriteSheet::Pool->GetResource();
	sheetRock->Load("Assets/Textures/Rock.tga");
	sheetRock->SetSize(1, 4, 20, 20);
	sheetRock->AddAnimation(EN_AN_IDLE, 0, 4, 1.0f);
	posPoint = _posPoint;
	speed = _speed;
	direction = _direction;
	rockSheet = sheetRock;
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
