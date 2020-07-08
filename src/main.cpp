/* LEVEL */
#include "Level.h"

/* DEBUG */
#include "ImguiWindows.h"

/* ASSET STORAGE */
#include "AssetStorage.h"

/* IMGUI && SFML */
#include "imgui.h"
#include "imgui-SFML.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

/* STL */
#include <iostream>
#include <list>
#include <memory>
#include <vector>

using IntRect = sf::IntRect;

/* declare and initialize static Game variables*/
bool Game::paused = false;
bool Game::debug_mode = false;
std::unique_ptr<ImguiWindows> Game::imguiWin = std::make_unique<ImguiWindows>("../res/data/tableofcontents.json");
std::unique_ptr<AssetStorage> Game::assets = std::make_unique<AssetStorage>("../res/data/tableofcontents.json");
std::unique_ptr<sf::RenderWindow> Game::window = std::make_unique<sf::RenderWindow>(sf::VideoMode(720, 640), "");
EntityRegistryHandle Game::entity_registry{};
SystemRegistryHandle Game::system_registry{};
LevelHandle Game::current_level{};

//----------------------------------------------------------------------------------------------

int main()
{
	Game::window->setVerticalSyncEnabled(true);

	ImGui::SFML::Init(*Game::window);

	sf::Color bgColor;

	float color[3] = { 0.f, 0.f, 0.f };

	Game::init("level1", true);

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
		
		//Game::imguiWin->entityEditor();
		Game::update(deltaClock.restart().asSeconds());
		//Game::imguiWin->animationEditor();
		
		ImGui::SFML::Render(*Game::window);
		Game::window->display();
	}
	ImGui::SFML::Shutdown();
}

//----------------------------------------------------------------------------------------------
