#include "Warrior.h"
#include "Renderer.h"
#include "BasicStructs.h"
#include "SpriteSheet.h"

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
	SpriteSheet::Pool = new ObjectPool<SpriteSheet>();
	SpriteAnim::Pool = new ObjectPool<SpriteAnim>();
	SpriteSheet* sheetWarrior = SpriteSheet::Pool->GetResource();
	sheetWarrior->Load("Assets/Textures/Warrior.tga");
	sheetWarrior->SetSize(17, 6, 69, 44);
	sheetWarrior->AddAnimation(EN_AN_IDLE, 0, 6, 1.0f);
	sheetWarrior->AddAnimation(EN_AN_RUN, 6, 8, 1.0f);
	sheetWarrior->AddAnimation(EN_AN_DEATH, 26, 11, 1.0f);
	cout << "Warrior with Pos: X: " << posPoint.X << " Y: " << posPoint.Y << " is being created " << endl;
	posPoint = _posPoint;
	speed = _speed;
	direction = _direction;
	SetIsHit(false);
	warriorSheet = sheetWarrior;
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