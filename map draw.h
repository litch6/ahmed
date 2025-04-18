#pragma once
#include <SFML/Graphics.hpp>

class Tilemap :public sf::Drawable, public sf::Transformable {
private:
	sf::Texture t;
	sf::VertexArray map;
public:
	bool load(const std::filesystem::path& p, sf::Vector2u block, int* tiles, unsigned int w, unsigned int h) {
		if (!t.loadFromFile(p)) return false;
		map.setPrimitiveType(sf::PrimitiveType::Triangles);
		map.resize(w * h * 6);
		for (unsigned int i = 0; i < w; i++) {
			for (unsigned int j = 0; j < h; j++) {
				const int tn = tiles[i + (j * w)];
				if (tn == -1) continue;
				const int tx = tn % (t.getSize().x / block.x);
				const int ty = tn / (t.getSize().x / block.x);
				sf::Vertex* triangles = &map[(i + j * w) * 6];
				triangles[0].position = sf::Vector2f(i * block.x, j * block.y);
				triangles[1].position = sf::Vector2f((i + 1) * block.x, j * block.y);
				triangles[2].position = sf::Vector2f(i * block.x, (j + 1) * block.y);
				triangles[3].position = sf::Vector2f(i * block.x, (j + 1) * block.y);
				triangles[4].position = sf::Vector2f((i + 1) * block.x, j * block.y);
				triangles[5].position = sf::Vector2f((i + 1) * block.x, (j + 1) * block.y);
				triangles[0].texCoords = sf::Vector2f(tx * block.x, ty * block.y);
				triangles[1].texCoords = sf::Vector2f((tx + 1) * block.x, ty * block.y);
				triangles[2].texCoords = sf::Vector2f(tx * block.x, (ty + 1) * block.y);
				triangles[3].texCoords = sf::Vector2f(tx * block.x, (ty + 1) * block.y);
				triangles[4].texCoords = sf::Vector2f((tx + 1) * block.x, ty * block.y);
				triangles[5].texCoords = sf::Vector2f((tx + 1) * block.x, (ty + 1) * block.y);
			}
		}
		return true;
	}
private:
	void draw(sf::RenderTarget& ta, sf::RenderStates st)const override {
		st.transform *= getTransform();
		st.texture = &t;
		ta.draw(map, st);
	}
};
