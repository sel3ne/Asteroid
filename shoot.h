#ifndef SHOOT
#define SHOOT

#include <SFML/Graphics.hpp>
#include <cmath>

#include "globalStuff.h"

class Shoot {
 public:
  Shoot(float x, float y, float angel) {
    x_ = x;
    y_ = y;
    speed_ = -500;
    size_ = 2;
    angel_ = angel;
    outsideOfScreen_ = false;
    hitSomething_ = false;
  }

  void render(sf::RenderWindow& window) {
    sf::CircleShape circle(size_);
    circle.setOrigin(size_, size_);
    circle.setPosition(x_, y_);
    circle.setFillColor(sf::Color::White);
    window.draw(circle);
  }

  void update(float time) {
    x_ = x_ + cos(angel_) * time * speed_;
    y_ = y_ + sin(angel_) * time * speed_;
    if (x_ > window_size_x) {
      outsideOfScreen_ = true;
    }
    if (x_ < 0) {
      outsideOfScreen_ = true;
    }
    if (y_ > window_size_y) {
      outsideOfScreen_ = true;
    }
    if (y_ < 0) {
      outsideOfScreen_ = true;
    }
  }

  float x() { return x_; }
  float y() { return y_; }
  float size() { return size_; }

  void setHitSomething(bool hit) { hitSomething_ = hit || hitSomething_; }
  bool hitSomething() { return hitSomething_; }

  bool outsideOfScreen() { return outsideOfScreen_; }

 private:
  float x_;
  float y_;
  float speed_;
  float size_;
  float angel_;
  bool outsideOfScreen_;
  bool hitSomething_;
};

#endif
