#ifndef EXPLOSION
#define EXPLOSION

#include <SFML/Graphics.hpp>
#include <cmath>

#include "globalStuff.h"

class Explosion {
 public:
  Explosion(float x, float y, float angel, float speed) {
    x_ = x;
    y_ = y;
    speed_ = speed;
    angel_ = angel;
    alpha_ = 255;
    // size_ = 2;
    outsideOfScreen_ = false;
    invisibleExplosion_ = false;
  }

  void setColor(int r, int g, int b) {
    r_ = r;
    g_ = g;
    b_ = b;
  }

  void render(sf::RenderWindow& window) {
    sf::CircleShape circle(2);
    circle.setOrigin(2, 2);
    circle.setPosition(x_, y_);
    circle.setFillColor(color_);
    window.draw(circle);
  }

  void update(float time) {
    x_ = x_ + cos(angel_) * time * speed_;
    y_ = y_ + sin(angel_) * time * speed_;
    alpha_ = alpha_ - time * 100;
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
    if (alpha_ < 0) {
      alpha_ = 0;
      invisibleExplosion_ = true;
    }
    color_ = sf::Color(r_, g_, b_, alpha_);
  }

  float x() { return x_; }
  float y() { return y_; }

  bool outsideOfScreen() { return outsideOfScreen_; }
  bool invisibleExplosion() { return invisibleExplosion_; }

 private:
  float x_;
  float y_;
  float speed_;
  float angel_;
  int alpha_;
  int r_;
  int g_;
  int b_;
  bool outsideOfScreen_;
  bool invisibleExplosion_;
  sf::Color color_;
};

#endif
