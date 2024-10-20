#include <iostream>

#include "Unit.h"
#include "FileController.h"
#include "StackAllocator.h"
#include "ObjectPool.h"
#include "Resource.h"
#include "Asset.h"
#include "AssetController.h"
#include "GameController.h"

int main()
{
	srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
	GameController::Instance().RunGame();
	return 0;
}