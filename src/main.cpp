#include "imgui.h"
#include "imgui-SFML.h"
#include "ResourceManager.h"
#include "SpriteComponent.h"	
#include "Parser.h"
#include "AnimationSystem.h"
#include "ImguiWindows.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <iostream>
#include <list>


ResourceManager resManager;
//std::vector<CAnimatedSprite*>sprites;
ImguiWindows imguiWindows;
Parser parser;
AnimationSystem as;

int main()
{
	
	sf::RenderWindow window(sf::VideoMode(720, 640), "");
	window.setVerticalSyncEnabled(true);
	ImGui::SFML::Init(window);

	sf::Color bgColor;

	float color[3] = { 0.f, 0.f, 0.f };

	resManager.addTexture("marioluigi", "../res/marioluigi.png");
	parser.parseSpriteFile("../res/data/sprites.json");

	char windowTitle[255] = "ImGui + SFML = <3";
	char test[255] = "test test";

	window.setTitle(windowTitle);
	window.resetGLStates(); // call it if you only draw ImGui. Otherwise not needed.
	sf::Clock deltaClock;
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			ImGui::SFML::ProcessEvent(event);

			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		ImGui::SFML::Update(window, deltaClock.restart());
		
		as.update();
		imguiWindows.animationEditor();

		window.clear(bgColor); // fill background with color
		
		//as.update();
		as.draw(window);
		
		ImGui::SFML::Render(window);
		window.display();
	}
	

	ImGui::SFML::Shutdown();
}