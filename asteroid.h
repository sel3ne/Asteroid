#ifndef ASTEROID
#define ASTEROID

#include <SFML/Graphics.hpp>
#include <cmath>

#include "globalStuff.h"

float RandomFloat(float beg, float end);

class Asteroid {
 public:
  Asteroid(float x, float y, float size, float speed) {
    x_ = x;
    y_ = y;
    size_ = size;
    direction_ = RandomFloat(0, 2 * 3.141);
    texture_ = new sf::Texture;
    texture_->loadFromFile("asteroid.png");
    speed_ = speed;
    beenHit_ = false;
  }

  void render(sf::RenderWindow& window) {
    sf::Vector2u texSize = texture_->getSize();
    sf::Sprite sprite;
    sprite.setTexture(*texture_);
    sprite.setPosition(x_, y_);
    sprite.setScale(size_ / (float)texSize.x, size_ / (float)texSize.y);
    window.draw(sprite);
  }

  void renderDebug(sf::RenderWindow& window) {
    sf::CircleShape circle(3);
    circle.setPosition(x_, y_);
    circle.setFillColor(sf::Color(250, 150, 100));
    window.draw(circle);
  }

  void renderCollision(sf::RenderWindow& window) {
    sf::CircleShape circle(size_ / 2);
    circle.setOrigin(size_ / 2, size_ / 2);
    circle.setPosition(x_ + size_ / 2, y_ + size_ / 2);
    circle.setFillColor(sf::Color(250, 150, 100, 100));
    window.draw(circle);
  }

  float x() { return x_; }
  float y() { return y_; }
  float size() { return size_; }
  void setBeenHit(bool shootDown) { beenHit_ = shootDown; };
  bool beenHit() { return beenHit_; }

  void update(float time) {
    float x_change = cos(direction_) * speed_ * time;
    float y_change = sin(direction_) * speed_ * time;
    x_ = x_ + x_change;
    y_ = y_ + y_change;
    sf::Vector2u texSize = texture_->getSize();
    if (x_ - size_ > window_size_x) {
      x_ = x_ - window_size_x - 2 * size_;
    }
    if (x_ + size_ < 0) {
      x_ = x_ + window_size_x + 2 * size_;
    }
    if (y_ - size_ > window_size_y) {
      y_ = y_ - window_size_y - 2 * size_;
    }
    if (y_ + size_ < 0) {
      y_ = y_ + window_size_y + 2 * size_;
    }
  }

 private:
  float x_;
  float y_;
  float size_;
  float direction_;
  float speed_;
  bool beenHit_;
  sf::Texture* texture_;
};

#endif
