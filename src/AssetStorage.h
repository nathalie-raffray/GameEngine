#pragma once
#include <string>
#include <unordered_map>
#include <memory>
#include <iostream>

using AssetId = std::string;

#include "Asset.h"

using AssetMap = std::unordered_map<AssetId, std::unique_ptr<Asset>>;

class AssetStorage
{
public:
	AssetMap assets;

public:
	friend class ImguiWindows;

	//load a table of contents into asset storage to initialize it
	AssetStorage(const std::string& filePath);

	template<typename T> T* get(const AssetId& id);

	void remove(const AssetId& id);

private:
	std::unordered_map<AssetId, std::string> table_of_contents;

};

//----------------------------------------------------------------------------------------------

template<typename T>
inline T* AssetStorage::get(const AssetId& id)
{
	if (assets.count(id) == 0)
	{
		if (table_of_contents.count(id) == 0)
		{
			std::cout << "Could not load asset with id: " << id << std::endl;
			return nullptr;
		}
		T::load(table_of_contents[id]);
	}
	return dynamic_cast<T*>(assets[id].get()); 
}

//----------------------------------------------------------------------------------------------
