#include "imgui.h"
#include "imgui-SFML.h"


#include "SpriteComponent.h"	
#include "Parser.h"
#include "AnimationComponent.h"
#include "AssetStorage.h"
#include "Sprite.h"
#include "Game.h"

#include "EntityRegistry.h" 
#include "SystemRegistry.h" 
#include "AnimationSystem.h"
#include "RenderingSystem.h"
#include "ImguiWindows.h"


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
//class EntityRegistry;

bool								Game::paused			= false;
std::unique_ptr<AnimationSystem>    Game::animationSystem   = std::make_unique<AnimationSystem>();
std::unique_ptr<RenderingSystem>    Game::renderingSystem   = std::make_unique<RenderingSystem>();
std::unique_ptr<ImguiWindows>	    Game::imguiWin			= std::make_unique<ImguiWindows>();
std::unique_ptr<AssetStorage>		Game::assets			= std::make_unique<AssetStorage>("../res/data/tableofcontents.json");
std::unique_ptr<sf::RenderWindow>   Game::window			= std::make_unique<sf::RenderWindow>(sf::VideoMode(720, 640), "");
std::unique_ptr<EntityRegistry>		Game::entity_registry   = std::make_unique<EntityRegistry>();
std::unique_ptr<SystemRegistry>		Game::system_registry   = std::make_unique<SystemRegistry>();


int main()
{
	Game::window->setVerticalSyncEnabled(true);

	ImGui::SFML::Init(*Game::window);

	sf::Color bgColor;

	float color[3] = { 0.f, 0.f, 0.f };
/*
	Entity entity;
	entity.add<AnimationComponent>();
	auto component1 = entity.get<AnimationComponent>();
	component1->animation_collection_id = "littlemario";
	component1->currentAnimation = "littlemario_walk";

	Game::entity_registry->add(std::move(entity));

	Entity entity2;
	entity2.add<AnimationComponent>();
	auto component2 = entity2.get<AnimationComponent>();
	component2->animation_collection_id = "littlemario";
	component2->currentAnimation = "littlemario_swim";

	Game::entity_registry->add(std::move(entity2));
	*/
	/*auto entity2 = std::make_unique<Entity>();
	entity2->add<AnimationComponent>();
	auto component3 = entity->get<AnimationComponent>();
	component3->animation_collection_id = "babymario";
	component3->currentAnimation = "babymario_walk";*/

	Game::imguiWin->animationInit();

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

		//Game::update(0);

		//Game::imguiWin->animationEditor();
		
		ImGui::SFML::Render(*Game::window);
		Game::window->display();
	}
	

	ImGui::SFML::Shutdown();
}