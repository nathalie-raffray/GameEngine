#include "Game.h"
#include "SystemRegistry.h"
#include "Entity.h"
#include "EventManager.h"
#include "ActionSystem.h"
#include "Level.h"
#include "AssetStorage.h"
#include "ImguiWindows.h"

void Game::init(const std::string& level, bool enable_imgui_editors)
{
	Level::pushLevel({level});
	ActionSystem::init("../res/data/inputconfig.json");
	//ComponentFactory::init();

	debug_mode = enable_imgui_editors;

	if (debug_mode)
	{
		imguiWin->init();
	}
}

void Game::update(float dt)
{
	if (debug_mode)
	{
		imguiWin->update();
	}
	
	system_registry->update(dt);
	//entity_registry->update(); //should i update this? since by deleting entities it will fuck up the entityhandles of all entities after the erased one
	EventManager::process_events(); //when systems are deleted, their listeners are removed from event manager
}
