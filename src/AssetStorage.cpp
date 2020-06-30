#include "AssetStorage.h"

#include <fstream>

#include "json_serialization.h"


//----------------------------------------------------------------------------------------------

AssetStorage::AssetStorage(const std::string& filePath)
{
	json js;
	std::ifstream i(filePath);
	i >> js;

	//table_of_contents = js.get<ToC>();

	for (auto& j : js)
	{
		for (auto& jj : j.items())
		{
			table_of_contents.emplace(jj.key(), jj.value());
		}
	}
}


//----------------------------------------------------------------------------------------------


void AssetStorage::remove(const AssetId& id)
{
	if (assets.count(id) == 0) return;
	assets.erase(id);
}

//----------------------------------------------------------------------------------------------



