#include "imgui.h"
#include "imgui-SFML.h"
#include "ResourceManager.h"
#include "SpriteComponent.h"	
#include "Parser.h"
#include "AnimationSystem.h"
#include "AnimationComponent.h"
#include "ImguiWindows.h"
#include "AssetStorage.h"
#include "RenderingSystem.h"
#include "Game.h"
#include "Texture.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <iostream>
#include <list>
#include <memory>

typedef sf::IntRect IntRect;
/*typedef sf::Sprite Sprite;
template <typename T>
using Vector2 = sf::Vector2<T>; //Vector<2> is equivalent to sf::Vector2<T>
typedef sf::Texture Texture;*/

//ResourceManager resManager;
//std::vector<CAnimatedSprite*>sprites;
//ImguiWindows imguiWindows;
//Parser parser;
AnimationSystem as;

int main()
{
	//Game game;
	Game::assets = std::make_unique<AssetStorage>();
	Game::animationSystem = std::make_unique<AnimationSystem>();
	Game::renderingSystem = std::make_unique<RenderingSystem>();
	Game::imguiWin = std::make_unique<ImguiWindows>();
	Game::window = std::make_unique<sf::RenderWindow>(sf::VideoMode(720, 640), "");

	Game::window->setVerticalSyncEnabled(true);
	ImGui::SFML::Init(*Game::window);

	sf::Color bgColor;

	float color[3] = { 0.f, 0.f, 0.f };

	//resManager.addTexture("marioluigi", "../res/marioluigi.png");
	//parser.parseSpriteFile("../res/data/sprites.json");
	Game::assets->load("../res/marioluigi.png", AssetStorage::TEXTURES);
	Game::assets->load("../res/data/littlemario.animations.json", AssetStorage::ANIMATIONS);
	Game::assets->load("../res/data/level1.sprites.json", AssetStorage::SPRITES);

	auto spLittleMario = std::make_shared<AnimationComponent>("littlemario_walk");
	Game::animationSystem->add(std::move(spLittleMario));
	//Game::renderingSystem->add()

	char windowTitle[255] = "ImGui + SFML = <3";
	char test[255] = "test test";

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
		
		//as.update();
		//imguiWindows.animationEditor();

		Game::window->clear(bgColor); // fill background with color
		
		Game::animationSystem->update();
		Game::renderingSystem->update();
		//as.update();
		//as.draw(window);
		
		ImGui::SFML::Render(*Game::window);
		Game::window->display();
	}
	

	ImGui::SFML::Shutdown();
}