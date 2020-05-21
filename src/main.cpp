#include "Game.h"

/* REGISTRIES */
#include "EntityRegistry.h" 
#include "SystemRegistry.h" 

/* SYSTEMS */
#include "GoombaController.h"
#include "AnimationSystem.h"
#include "RenderingSystem.h"
#include "CollisionSystem.h"

/* DEBUG */
#include "ImguiWindows.h"

/* EVENTS */
#include "EventManager.h"

/* ASSET STORAGE */
#include "AssetStorage.h"

/* IMGUI && SFML */
#include "imgui.h"
#include "imgui-SFML.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

/* STL */
#include <iostream>
#include <list>
#include <memory>
#include <vector>

using IntRect = sf::IntRect;

bool								Game::paused			= false;
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

	Game::system_registry->add<AnimationSystem>();
	Game::system_registry->add<RenderingSystem>();
	Game::system_registry->add<GoombaController>();
	Game::system_registry->add<CollisionSystem>();

	auto entity = Game::entity_registry->create();
	entity->add<AnimationComponent>();
	auto component1 = entity->get<AnimationComponent>();
	component1->animation_collection_id = "littlemario";
	component1->currentAnimation = "littlemario_walk";

	auto goomba1 = Game::entity_registry->create();
	goomba1->add<ColliderComponent>();

	auto goomba2 = Game::entity_registry->create();
	goomba2->add<ColliderComponent>();


	Game::imguiWin->add(entity);
	Game::imguiWin->animationInit();

	Game::system_registry->addEntityToSystems(entity);
	Game::system_registry->addEntityToSystems(goomba1);
	Game::system_registry->addEntityToSystems(goomba2);

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

		Game::update(0);

		Game::imguiWin->animationEditor();
		
		ImGui::SFML::Render(*Game::window);
		Game::window->display();
	}
	

	ImGui::SFML::Shutdown();
}