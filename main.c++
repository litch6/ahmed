#include "Mario.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include "MapDraw.h"
#include <vector>
#include "enemy.h"
#include "oop.h"

using namespace std;


int main() {
	sf::RenderWindow Game(sf::VideoMode({ 800,600 }), "Mario", sf::Style::Close | sf::Style::Resize);
	std::filesystem::path p = ("Mario.png");
	std::filesystem::path mt = ("OverWorld.png");
	std::filesystem::path ep = ("Enemies.png");
	std::filesystem::path items = ("Items.png");
	sf::RectangleShape back;
	back.setFillColor(sf::Color::Cyan);
	back.setSize({ 50 * 16,15 * 16 });
	vector<unique_ptr<gameobject>> objects;
	objects.push_back(make_unique<goomba>(ep, sf::Vector2f({ 10,70 })));
	objects.push_back(make_unique<goomba>(ep, sf::Vector2f({ 400,70 })));
	std::vector<int> mariomap = {
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 3, 3, 3, 3, 3, 3, 3, 3, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 3, 3, 3, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0,
		-1, 4, -1, -1, 3, 3, 4, 3, 3, 3, -1, -1, -1, 1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0,
		-1, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1, -1, -1, -1, -1, -1, -1, -1, -1, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0,
		-1, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1, -1, -1, -1, -1, -1, -1, -1, -1, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0,0
	};
	sf::View v1({ 120,100 }, { 400,400 });
	Tilemap map;
	if (!map.load(mt, sf::Vector2u({ 16,16 }), mariomap.data(), 50, 15))return 1;
	Game.setFramerateLimit(60);
	Mario m(p);
	mashrom ms(items, sf::Vector2f({ 90,144 }));
	while (Game.isOpen())
	{
		while (const std::optional ev = Game.pollEvent()) {
			if (ev->is<sf::Event::Closed>())Game.close();
			if (auto key = ev->getIf<sf::Event::KeyPressed>()) {
			}
			if (ev->is<sf::Event::KeyReleased>()) {
				if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) &&
					!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
					m.ismoving = false;
				}
				if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
				}
			}
		}
		if (m.isalive && !m.freez) {
			for (auto it = objects.begin(); it != objects.end(); ) {
				auto& ob = *it;
				ob.get()->update(mariomap, sf::Vector2u({ 16,16 }), sf::Vector2u({ 50,15 }));
				m.ecollision(ob.get());
				if (!ob->getstate() && ob->mclock.getElapsedTime().asMilliseconds() >= 500) {
					it = objects.erase(it);
				}
				else it++;
			}
			ms.collision(m);
		}
		ms.update(mariomap, sf::Vector2u({ 16,16 }), sf::Vector2u({ 50,15 }));
		m.update(v1, mariomap, sf::Vector2u({ 16,16 }), sf::Vector2u({ 50,15 }));
		Game.setView(v1);
		Game.clear();
		Game.draw(back);
		Game.draw(map);
		for (auto& ob : objects) {
			Game.draw(*ob);
		}
		Game.draw(ms);
		Game.draw(m);
		Game.display();

	}
}
