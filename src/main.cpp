#include "imgui.h"
#include "imgui-SFML.h"

#include "SpriteComponent.h"	
#include "Parser.h"
#include "AnimationSystem.h"
#include "AnimationComponent.h"
#include "ImguiWindows.h"
#include "AssetStorage.h"
#include "Sprite.h"
#include "RenderingSystem.h"
#include "Game.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <iostream>
#include <list>
#include <memory>

using IntRect = sf::IntRect;

bool								Game::paused = false;
std::unique_ptr<AssetStorage>		Game::assets = std::make_unique<AssetStorage>();
std::unique_ptr<AnimationSystem>    Game::animationSystem = std::make_unique<AnimationSystem>();
std::unique_ptr<RenderingSystem>    Game::renderingSystem = std::make_unique<RenderingSystem>();
std::unique_ptr<ImguiWindows>	    Game::imguiWin = std::make_unique<ImguiWindows>();
std::unique_ptr<sf::RenderWindow>   Game::window = std::make_unique<sf::RenderWindow>(sf::VideoMode(720, 640), "");

int main()
{
	//Game game;
	Game::window->setVerticalSyncEnabled(true);

	ImGui::SFML::Init(*Game::window);

	sf::Color bgColor;

	float color[3] = { 0.f, 0.f, 0.f };

	Game::assets->load("../res/data/textures.json", AssetStorage::TEXTURES);
	Game::assets->load("../res/data/littlemario.animations.json", AssetStorage::ANIMATIONS);
	Game::assets->load("../res/data/level1.sprites.json", AssetStorage::SPRITES);

	ImguiWindows imguiEditors;
	imguiEditors.animationInit();

	char windowTitle[255] = "ImGui + SFML = <3";

	Game::window->setTitle(windowTitle);
	Game::window->resetGLStates(); // call it if you only draw ImGui. Otherwise not needed.
	sf::Clock deltaClock;
	while (Game::window->isOpen()) {
		sf::Event event;
		while (Game::window->pollEvent(event)) {
			ImGui::SFML::ProcessEvent(event);

			if (event.type == sf::Event::Closed) {
				Game::window->close();
			}
		}

		ImGui::SFML::Update(*Game::window, deltaClock.restart());

		Game::window->clear(bgColor); // fill background with color

		Game::animationSystem->update();
		Game::renderingSystem->update();

		imguiEditors.animationEditor();
		
		ImGui::SFML::Render(*Game::window);
		Game::window->display();
	}
	

	ImGui::SFML::Shutdown();
}