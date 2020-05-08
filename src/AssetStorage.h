#pragma once
#include <string>
#include <unordered_map>
#include <memory>

using AssetId = std::string;

struct Asset;

using AssetMap = std::unordered_map<AssetId, std::unique_ptr<Asset>>;
using ToC = std::unordered_map<AssetId, std::string>;

class AssetStorage
{
public:
	friend class ImguiWindows;

	//load a table of contents into asset storage to initalize it
	AssetStorage(const std::string& filePath);

	template<typename T> T* get(const AssetId& id);

	void remove(const AssetId& id);

private:
	AssetMap assets;
	ToC table_of_contents;

	void load(const AssetId& id);

};

//----------------------------------------------------------------------------------------------

template<typename T>
inline T* AssetStorage::get(const AssetId& id)
{
	if (assets.count(id) == 0)
	{
		load(id);
		if (assets.count(id) == 0) return nullptr;
	}
	return dynamic_cast<T*>(assets[id].get()); 
}

//----------------------------------------------------------------------------------------------
