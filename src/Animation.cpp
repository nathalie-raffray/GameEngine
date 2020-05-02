#include "Animation.h"
#include "AssetStorage.h"
#include "Game.h"
#include "AnimationFrame.h"
#include "Sprite.h"

void to_json(json& j, const Animation& p)
{
	switch (p.mode)
	{
	case Animation::loop:
		j["mode"] = "loop";
		break;
	case Animation::one_time:
		j["mode"] = "one time";
		break;
	case Animation::ping_pong_backward:
		j["mode"] = "ping pong";
		break;
	case Animation::ping_pong_forward:
		j["mode"] = "ping pong";
		break;
	}

	std::size_t numFrames = p.frames.size();
	for (std::size_t i = 0; i < numFrames; i++)
	{
		j["sprites"]["screenOffset"][0] = p.frames[i].screenOffsetX;
		j["sprites"]["screenOffset"][1] = p.frames[i].screenOffsetY;
		j["sprites"][i] = *Game::assets->getSprite(p.frames[i].spriteId);
		j["sprites"][i]["duration"] = p.frames[i].duration;
	}
	//j["scale"] = 
}

void from_json(const json& j, Animation& p)
{
	std::string mode = j["mode"].get<std::string>();
	if (mode.compare("loop") == 0) p.mode = Animation::loop;
	if (mode.compare("one time") == 0) p.mode = Animation::one_time;
	if (mode.compare("ping pong") == 0) p.mode = Animation::ping_pong_forward;

	for (auto& jsprite : j["sprites"])
	{
		p.frames.emplace_back(jsprite["spriteId"].get<std::string>(), 
							  jsprite["screenOffset"][0].get<int>(), 
							  jsprite["screenOffset"][1].get<int>(),
							  jsprite["duration"].get<float>());
	}

}

