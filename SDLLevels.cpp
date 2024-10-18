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
	GameController::Instance().RunGame();
	return 0;
}