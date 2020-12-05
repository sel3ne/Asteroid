#ifndef PLAYER
#define PLAYER

#include <SFML/Graphics.hpp>
#include <cmath>

#include "globalStuff.h"

class Player {
 public:
  Player(float x, float y) {
    x_ = x;
    y_ = y;
    texture_ = new sf::Texture;
    texture_->loadFromFile("space_ship.png");
    speed_ = 0;
    size_ = 100;
    angel_ = 3.141 / 2;
    name_ = "Amani";
  }

  void render(sf::RenderWindow& window) {
    sf::Vector2u texSize = texture_->getSize();
    sf::Sprite sprite;
    sprite.setOrigin(texSize.x / 2., texSize.y / 2.);
    sprite.setTexture(*texture_);
    sprite.setPosition(x_, y_);
    sprite.setScale(size_ / (float)texSize.x, size_ / (float)texSize.y);
    sprite.setRotation(angel_ * 360 / (2 * 3.141) - 90);
    window.draw(sprite);
  }

  void renderDebug(sf::RenderWindow& window) {
    sf::CircleShape circle(5);
    circle.setOrigin(5, 5);
    circle.setPosition(x_, y_);
    circle.setFillColor(sf::Color(250, 150, 100));
    window.draw(circle);
  }

  void renderCollision(sf::RenderWindow& window) {
    sf::CircleShape circle(0.33 * size_);
    circle.setOrigin(0.33 * size_, 0.33 * size_);
    circle.setPosition(x_ + size_ * cos(angel_) * 0.33 / 2,
                       y_ + size_ * sin(angel_) * 0.33 / 2);
    circle.setFillColor(sf::Color(250, 150, 250, 50));
    window.draw(circle);
  }

  float x() { return x_; }
  float y() { return y_; }
  float angel() { return angel_; }

  void set_speed(float speed) { speed_ = speed; }
  void change_angel(float angel) { angel_ = angel_ + angel; }
  float size() { return size_; }

  void update(float time) {
    x_ = x_ + cos(angel_) * time * speed_;
    y_ = y_ + sin(angel_) * time * speed_;
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
  float speed_;
  float angel_;
  float size_;
  sf::Texture* texture_;
  std::string name_;
};

#endif
