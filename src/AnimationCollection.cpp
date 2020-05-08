#include "AnimationCollection.h"
#include "Animation.h"
#include "AnimationFrame.h"

Animation* AnimationCollection::getAnimation(const AnimationId& id) 
{
	if (animations.count(id) == 0) return nullptr;
	else return animations[id].get();
}


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

