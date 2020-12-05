#ifndef LIFEBAR
#define LIFEBAR

#include <SFML/Graphics.hpp>
#include <cmath>
#include <random>

#include "globalStuff.h"

class Lifebar {
 public:
  Lifebar(int lifepoint) {
    lifepoint_ = lifepoint;

    size_ = 20;

    texture_ = new sf::Texture;
    texture_->loadFromFile("heart.png");
  }

  void render(sf::RenderWindow& window) {
    sf::Vector2u texSize = texture_->getSize();

    for (int i = 0; i < lifepoint_; i++) {
      sf::Sprite sprite;
      sprite.setTexture(*texture_);
      sprite.setPosition(window_size_x - (i + 1) * size_ - (i + 1) * 10, 10);
      sprite.setScale(size_ / (float)texSize.x, size_ / (float)texSize.y);
      window.draw(sprite);
    }
  }

  void setLifePoints(int lifepoint) { lifepoint_ = lifepoint; }

  void removeLife() { lifepoint_ = lifepoint_ - 1; }

  void addLife(int i) { lifepoint_ = lifepoint_ + i; }

  int lifepoint() { return lifepoint_; }

 private:
  int lifepoint_;
  float size_;
  sf::Texture* texture_;
};

#endif
