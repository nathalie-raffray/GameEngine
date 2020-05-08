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
#include "Entity.h"
//#include "AnimationCollection.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <iostream>
#include <list>
#include <memory>
#include <vector>

using IntRect = sf::IntRect;

bool								Game::paused			= false;
std::unique_ptr<AnimationSystem>    Game::animationSystem   = std::make_unique<AnimationSystem>();
std::unique_ptr<RenderingSystem>    Game::renderingSystem   = std::make_unique<RenderingSystem>();
std::unique_ptr<ImguiWindows>	    Game::imguiWin			= std::make_unique<ImguiWindows>();
std::unique_ptr<AssetStorage>		Game::assets			= std::make_unique<AssetStorage>("../res/data/tableofcontents.json");
std::unique_ptr<sf::RenderWindow>   Game::window			= std::make_unique<sf::RenderWindow>(sf::VideoMode(720, 640), "");

template<typename ComponentType>
struct ComponentRegistry;

int main()
{
	Game::window->setVerticalSyncEnabled(true);

	ImGui::SFML::Init(*Game::window);

	sf::Color bgColor;

	float color[3] = { 0.f, 0.f, 0.f };

	//EntityHandle eh;
	//auto c = ComponentRegistry<AnimationComponent>::components;
	auto entity = std::make_unique<Entity>();
	entity->add<AnimationComponent>();
	auto component1 = entity->get<AnimationComponent>();
	component1->animation_collection_id = "littlemario";
	component1->currentAnimation = "littlemario_walk";

	entity->add<SpriteComponent>(std::move(SpriteComponent{ "littlemario", true }));
	auto component2 = entity->get<SpriteComponent>();
	component2->spriteId = "littlemario2";

	auto entity2 = std::make_unique<Entity>();
	entity2->add<AnimationComponent>();
	auto component3 = entity->get<AnimationComponent>();
	component3->animation_collection_id = "babymario";
	component3->currentAnimation = "babymario_walk";

	Game::imguiWin->animationInit();

	auto spLittleMario = std::make_shared<AnimationComponent>();
	spLittleMario->animation_collection_id = "littlemario";
	spLittleMario->currentAnimation = "littlemario_walk";

	Game::animationSystem->add(spLittleMario);
	Game::renderingSystem->add(spLittleMario);
	Game::imguiWin->add(spLittleMario);


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

		Game::imguiWin->animationEditor();
		
		ImGui::SFML::Render(*Game::window);
		Game::window->display();
	}
	

	ImGui::SFML::Shutdown();
}