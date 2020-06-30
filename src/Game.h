#pragma once
#include <SFML/Graphics/RenderWindow.hpp>

#include <memory>

class AssetStorage;
class ImguiWindows;
class EntityRegistry;
class SystemRegistry;
class Level;

class Game {
public:
	static bool paused;
	static std::unique_ptr<AssetStorage> assets;
	static std::unique_ptr<ImguiWindows> imguiWin;
	static std::unique_ptr<sf::RenderWindow> window;
	//static std::unique_ptr<EntityRegistry> entity_registry;
	//static std::unique_ptr<SystemRegistry> system_registry;
	static Level* current_level;
	static EntityRegistry* entity_registry;
	static SystemRegistry* system_registry;

	static void init(const std::string& level);

	static void update(float dt);
};