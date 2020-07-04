#pragma once
#include <SFML/Graphics/RenderWindow.hpp>

#include <memory>

class AssetStorage;
class ImguiWindows;
struct EntityRegistryHandle;
struct SystemRegistryHandle;
struct LevelHandle;
struct EntityHandle;

class Game {
public:
	static bool paused;
	static bool debug_mode;
	static std::unique_ptr<AssetStorage> assets;
	static std::unique_ptr<ImguiWindows> imguiWin;
	static std::unique_ptr<sf::RenderWindow> window;
	
	static LevelHandle current_level;
	static EntityRegistryHandle entity_registry;
	static SystemRegistryHandle system_registry;

	static void init(const std::string& level, bool enable_imgui_editors);

	static void update(float dt);
};