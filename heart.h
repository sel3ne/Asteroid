#ifndef HEART
#define HEART

#include <SFML/Graphics.hpp>
#include <cmath>
#include <random>

#include "asteroid.h"
#include "globalStuff.h"
#include "player.h"
#include "shoot.h"

class Heart {
 public:
  Heart(float x, float y, float size, float speed) {
    x_ = x;
    y_ = y;
    size_ = size;
    direction_ = RandomFloat(0, 2 * 3.141);
    texture_ = new sf::Texture;
    texture_->loadFromFile("heart.png");
    speed_ = speed;
    beenHit_ = false;
    beenDestroyed_ = false;
  }

  void collision_check_with_player(Player play) {
    float heartX = x() + size() * 0.5;
    float heartY = y() + size() * 0.5;
    float heartRadius = size() * 0.5;
    float playX = play.x() + play.size() * cos(play.angel()) * 0.33 / 2;
    float playY = play.y() + play.size() * sin(play.angel()) * 0.33 / 2;
    float playRadius = play.size() * 0.33;

    float distanceSq = pow((heartX - playX), 2) + pow((heartY - playY), 2);
    float maxDistanceSq = pow((heartRadius + playRadius), 2);
    if (distanceSq <= maxDistanceSq) {
      beenHit_ = true;
    }
  }

  bool been_hit_check_with_shoot(Shoot shoot) {
    float heartX = x() + size() * 0.5;
    float heartY = y() + size() * 0.5;
    float heartRadius = size() * 0.5;
    float shootX = shoot.x() + shoot.size() * 0.5;
    float shootY = shoot.y() + shoot.size() * 0.5;
    float shootRadius = shoot.size() * 0.5;
    float distanceSq = pow(heartX - shootX, 2) + pow(heartY - shootY, 2);
    float maxDistanceSq = pow(heartRadius + shootRadius, 2);
    if (distanceSq < maxDistanceSq) {
      beenDestroyed_ = true;
      return true;
    } else {
      return false;
    }
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
  bool beenDestroyed() { return beenDestroyed_; }

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
  bool beenDestroyed_;
  sf::Texture* texture_;
};

#endif
