#pragma once
#include <SFML/Graphics.hpp>
#include "collision.h"
#include <vector>
#include <algorithm>
#include "oop.h"
#include <iostream>
#include "Mario.h"

using namespace std;

class goomba : public enemy {
private:
	Collision check;
	sf::IntRect moves[2], dead;
public:
	goomba(std::filesystem::path& p,sf::Vector2f spawn) : enemy(p) {
		postion = spawn;
		moves[0] = sf::IntRect({ 6,14 }, { 20,18 });
		moves[1] = sf::IntRect({ 38,14 }, { 20,18 });
		dead = sf::IntRect({ 70,14 }, { 22,18 });
		sprite.setTextureRect(moves[0]);
		sprite.setPosition(postion);
	}
	void animation() {
		if (isalive ) {
			if (mclock.getElapsedTime().asMilliseconds() >= 250) {
				static int f = 0;
				sprite.setTextureRect(moves[f++]);
				f = (f  % 2);
				mclock.restart();
			}
		}
		else
			sprite.setTextureRect(dead);
	}
	void update(vector<int>map,sf::Vector2u block,sf::Vector2u size)override{
		if (isalive) {
			check.hcollision( this, map, block, size);
			check.hfalling(this, map, block, size);
			if (falling) {
				velocityY += g;
				postion.y += velocityY;
			}
			move();
			sprite.setPosition(postion);
		}
		animation();
	}
	void move() {
		if (dir == 'R') {
			postion.x += speed;
		}
		else{
			postion.x -= speed;
		}
	}
	sf::FloatRect bounds()override {
		return sprite.getGlobalBounds();
	}
	void draw(sf::RenderTarget& t, sf::RenderStates)const override {
		t.draw(sprite);
	}
};

class mashrom : public Item {
private:
	Collision check;
	sf::IntRect idle;
public:
	mashrom(std::filesystem::path& p, sf::Vector2f spawn):Item(p) {
		idle = sf::IntRect({ 0,0 }, { 16,16 });
		postion = spawn;
		sprite.setTextureRect(idle);
		sprite.setPosition(postion);

	}
	void collision(Mario& m) {
		sf::FloatRect c1 = sprite.getGlobalBounds(), c2 = m.Marios.getGlobalBounds();
		char side = ' ';
		if(check.check(c1,c2,side))
		m.adult = true;
		m.freez=true;
		m.flash();
	}
	void kill()override {
		if (active && livespan.getElapsedTime().asSeconds() >= 10) {
			active = false;
		}
	}
	void move() {
		if (dir == 'R') {
			postion.x += speed;
		}
		else postion.x -= speed;
	}
	virtual void update(vector<int>map, sf::Vector2u block, sf::Vector2u size)override {
		if (active) {
			check.hfalling(this, map, block, size);
			check.hcollision(this, map, block, size);
			if (falling) {
				velocityY += g;
				postion.y += velocityY;
			}
			velocityY = 0;
			move();
			kill();
			sprite.setPosition(postion);
		}
	}
	void draw(sf::RenderTarget& t, sf::RenderStates y)const override {
		t.draw(sprite);
	}
};
