#pragma once
#include <SFML/Graphics/RenderWindow.hpp>

#include <memory>

class AssetStorage;
class ImguiWindows;
class AnimationSystem;
class RenderingSystem;
class EntityRegistry;
class SystemRegistry;

class Game {
public:
	static bool paused;
	static std::unique_ptr<AssetStorage> assets;
	static std::unique_ptr<ImguiWindows> imguiWin;
	static std::unique_ptr<AnimationSystem> animationSystem;
	static std::unique_ptr<RenderingSystem> renderingSystem;
	static std::unique_ptr<sf::RenderWindow> window;
	static std::unique_ptr<EntityRegistry> entity_registry;
	static std::unique_ptr<SystemRegistry> system_registry;

	static void update(float dt);
};