#pragma once
#include <SFML/Graphics/RenderWindow.hpp>

#include <memory>

class AssetStorage;
class ImguiWindows;
class AnimationSystem;
class RenderingSystem;

class Game {
public:
	static bool paused;

	static std::unique_ptr<AssetStorage> assets;
	static std::unique_ptr<ImguiWindows> imguiWin;
	static std::unique_ptr<AnimationSystem> animationSystem;
	static std::unique_ptr<RenderingSystem> renderingSystem;
	static std::unique_ptr<sf::RenderWindow> window;

};