#include "AssetController.h"
#include "FileController.h"

StackAllocator* AssetController::Stack = nullptr;

AssetController::AssetController()
{
}

void AssetController::Initialize(int _stackSize)
{
	Stack = new StackAllocator();
	AssetController::Stack->AllocateStack(_stackSize);
	Asset::Pool = new ObjectPool<Asset>();
}

AssetController::~AssetController()
{
	Clear();
}

void AssetController::Clear()
{
	// Remove all asset objects from the object pool
	for (auto const& x : m_assets)
	{
		Asset::Pool->ReleaseResource(x.second);
	}
	if (Asset::Pool != nullptr)
	{
		delete Asset::Pool;
		Asset::Pool = nullptr;
	}
	Stack->ClearMemory();
	m_assets.clear();
	
}

Asset* AssetController::GetAsset(string _guid)
{
	// If asset has already been loaded, return loaded asset
	if (m_assets.count(_guid) != 0)
	{
		return m_assets[_guid];
	}

	// Otherwise, load the asset and return it
	Asset* asset = Asset::Pool->GetResource();
	asset->SetGUID(_guid);
	asset->SetDataSize(FileController::Instance().GetFileSize(_guid));
	asset->SetData(Stack->GetMemory(asset->GetDataSize()));
	FileController::Instance().ReadFile(_guid, asset->GetData(), asset->GetDataSize());

	// Add new asset to the map
	m_assets[_guid] = asset;

	return asset;
}