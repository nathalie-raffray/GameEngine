#include "AnimationCollection.h"
#include "Game.h"
#include "AssetStorage.h"

#include <fstream>

//----------------------------------------------------------------------------------------------

Animation* AnimationCollection::getAnimation(const AnimationId& id) 
{
	if (animations.count(id) == 0) return nullptr;
	else return animations[id].get();
}

//----------------------------------------------------------------------------------------------

bool AnimationCollection::load(const std::string& filePath)
{
	json js;
	std::ifstream i(filePath);
	i >> js;

	auto uAC = std::make_unique<AnimationCollection>();

	for (json& j : js["animations"])
	{
		auto uA = std::make_unique<Animation>();

		*uA = j;

		uAC->animations.emplace(j["animationId"].get<std::string>(), std::move(uA));
	}

	Game::assets->assets.emplace(js["animationCollectionId"], std::move(uAC));

	return true;
}

//----------------------------------------------------------------------------------------------

/*void from_json(const json& j, AnimationCollection& ac)
{
	//for (json& ja : j["animations"])
	//{
	//	auto uA = std::make_unique<Animation>();

		//loadSprites(j["sprites"]);

		//*uA = j;

		//animations.emplace(j["animationId"].get<std::string>(), std::move(uA));

		//Game::imguiWin->addAssociatedAnimation(filePath, animations.find(j["animationId"].get<std::string>())->first); //only necessary for ImGui animation editor
	//}
}*/

void to_json(json& j, const AnimationCollection& ac)
{
	j["loadType"] = "animations";
	int i = 0;
	for (auto& animation : ac.animations)
	{
		j["animations"][i] = *animation.second;
		j["animations"][i]["animationId"] = animation.first;
		i++;
	}
}

