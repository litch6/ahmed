#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

class gameobject : public sf::Drawable,public sf::Transformable {
public:
	virtual ~gameobject() = default;
	virtual sf::FloatRect bounds() = 0;
	virtual void setdir(char& nd) = 0;
	virtual void update(vector<int>map, sf::Vector2u block, sf::Vector2u size) = 0;
	virtual void setfalling(bool& c) = 0;
	virtual void setpostion(sf::Vector2f p) = 0;
	virtual void kill() = 0;
	virtual bool getstate() = 0;
	sf::Clock mclock;
};

class enemy : public gameobject {
protected:
	sf::Texture t;
	bool isalive = true, moving = true, falling = true;
	sf::Vector2f postion;
	float speed = 2, velocityY = 0, g = 1;
	char dir = 'R';
	sf::Sprite sprite;
public:
	enemy(std::filesystem::path& p) : sprite(t)  {
		t.loadFromFile(p);
		sprite.setPosition(postion);
	}
	virtual void setpostion(sf::Vector2f p)override {
		sprite.setPosition(p);
	}
	virtual void setdir(char& nd)override {
			this->dir = nd;
	}
	virtual void setfalling(bool& c) {
		this->falling = c;
	}
	virtual void kill() override {
		isalive = false;
		mclock.restart();
	}
	bool getstate()override {
		return this->isalive;
	}
	virtual sf::FloatRect bounds()override{
		return sprite.getGlobalBounds();
	}

};

class Item : public gameobject {
protected:
	sf::Texture t;
	sf::Sprite sprite;
	bool active = true, moving = true, falling;
	sf::Clock livespan;
	sf::Vector2f postion;
	float speed = 2, velocityY = 0, g = 1;
	char dir = 'R';
public:
	Item(std::filesystem::path& p) :sprite(t) {
		t.loadFromFile(p);
		sprite.setPosition(postion);
	}
	void activ() {
		livespan.restart();
		active = true;
	}
	sf::FloatRect bounds() override  {
		return sprite.getGlobalBounds();
	}
	virtual void setpostion(sf::Vector2f p)override {
		sprite.setPosition(p);
	}
	virtual void setdir(char& nd)override {
		this->dir = nd;
	}
	virtual void setfalling(bool& c) {
		this->falling = c;
	}
	bool getstate()override {
		return this->active;
	}
};
