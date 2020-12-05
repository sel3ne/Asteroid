#include <SFML/Graphics.hpp>
#include <cmath>
#include <fstream>
#include <iostream>
#include <list>
#include <memory>
#include <random>
#include <string>
#include <tuple>

#include "asteroid.h"
#include "explosion.h"
#include "globalStuff.h"
#include "heart.h"
#include "lifebar.h"
#include "player.h"
#include "shoot.h"

void render_title_bar(sf::RenderWindow& window) {
  sf::RectangleShape rectangle(sf::Vector2f(window_size_x, 40));
  rectangle.setPosition(0, 0);
  rectangle.setFillColor(sf::Color::Black);
  rectangle.setOutlineColor(sf::Color::Blue);
  rectangle.setOutlineThickness(2);
  sf::Font font;
  font.loadFromFile("cour.ttf");
  sf::Text scoreTx;
  scoreTx.setCharacterSize(20);
  scoreTx.setFont(font);
  scoreTx.setStyle(sf::Text::Bold);
  scoreTx.setFillColor(sf::Color::White);
  scoreTx.setPosition(10, 10);
  std::string textToDisplay =
      ("Score: " + std::to_string(score) + ", Level: " + std::to_string(level) +
       ", Total Score: " + std::to_string(totalScore) +
       ", Best Score so far: " + std::to_string(bestScore));
  scoreTx.setString(textToDisplay);
  window.draw(rectangle);
  window.draw(scoreTx);
}

void render_foot_bar(sf::RenderWindow& window) {
  sf::RectangleShape rectangle(sf::Vector2f(window_size_x, 40));
  rectangle.setPosition(0, window_size_y - 100);
  rectangle.setFillColor(sf::Color::Black);
  rectangle.setOutlineColor(sf::Color::Blue);
  rectangle.setOutlineThickness(2);
  sf::Font font;
  font.loadFromFile("cour.ttf");
  sf::Text scoreTx;
  scoreTx.setCharacterSize(20);
  scoreTx.setFont(font);
  scoreTx.setStyle(sf::Text::Bold);
  scoreTx.setFillColor(sf::Color::White);
  scoreTx.setPosition(10, window_size_y - 90);
  std::string textToDisplay = ("To restart press Enter");
  scoreTx.setString(textToDisplay);
  window.draw(rectangle);
  window.draw(scoreTx);
}

bool collision_check(Asteroid aster, Player play) {
  float asterX = aster.x() + aster.size() * 0.5;
  float asterY = aster.y() + aster.size() * 0.5;
  float asterRadius = aster.size() * 0.5;
  float playX = play.x() + play.size() * cos(play.angel()) * 0.33 / 2;
  float playY = play.y() + play.size() * sin(play.angel()) * 0.33 / 2;
  float playRadius = play.size() * 0.33;

  float distanceSq = pow((asterX - playX), 2) + pow((asterY - playY), 2);
  float maxDistanceSq = pow((asterRadius + playRadius), 2);
  if (distanceSq > maxDistanceSq) {
    return false;
  }
  return true;
}

bool been_hit_check(Asteroid aster, Shoot shoot) {
  float asterX = aster.x() + aster.size() * 0.5;
  float asterY = aster.y() + aster.size() * 0.5;
  float asterRadius = aster.size() * 0.5;
  float shootX = shoot.x() + shoot.size() * 0.5;
  float shootY = shoot.y() + shoot.size() * 0.5;
  float shootRadius = shoot.size() * 0.5;
  float distanceSq = pow(asterX - shootX, 2) + pow(asterY - shootY, 2);
  float maxDistanceSq = pow(asterRadius + shootRadius, 2);
  if (distanceSq > maxDistanceSq) {
    return false;
  }
  return true;
}

void tokenize(std::string& str, char delim, std::vector<std::string>& out) {
  size_t start;
  size_t end = 0;

  while ((start = str.find_first_not_of(delim, end)) != std::string::npos) {
    end = str.find(delim, start);
    out.push_back(str.substr(start, end - start));
  }
}

class leaderboardPosition {
 public:
  leaderboardPosition(int highscore, std::string name) {
    highscore_ = highscore;
    name_ = name;
  }

  int highscore() { return highscore_; }
  std::string name() { return name_; }

  // unintuitiv operator, since the higher the score, the lower the placement
  bool operator<(leaderboardPosition B) {
    if (this->highscore() < B.highscore()) return false;
    return true;
  }

 private:
  int highscore_;
  std::string name_;
};

std::list<leaderboardPosition> scorebord() {
  std::string line;
  std::ifstream myfile("example.txt");
  char d = '_';
  std::list<leaderboardPosition> leaderbord = {};
  if (myfile.is_open()) {
    while (getline(myfile, line)) {
      std::vector<std::string> lineAsVector;
      tokenize(line, d, lineAsVector);

      int highscore = 0;
      std::string name = "";
      int i = 0;
      for (auto element : lineAsVector) {
        if (i == 0) {
          name = element;
        }
        if (i == 1) {
          highscore = std::stoi(element);
        }
        i = i + 1;
      }
      leaderbord.push_back(leaderboardPosition(highscore, name));
    }
    myfile.close();
  }

  else
    std::cout << "Unable to open file";

  return leaderbord;
}

void render_scoreboard(sf::RenderWindow& window,
                       std::list<leaderboardPosition> leaderbord) {
  sf::Font font;
  font.loadFromFile("cour.ttf");
  std::list<sf::Text> scores;
  int i = 0;
  for (auto singlePlayer : leaderbord) {
    sf::Text scoreTx;
    scoreTx.setCharacterSize(20);
    scoreTx.setFont(font);
    scoreTx.setStyle(sf::Text::Bold);
    scoreTx.setFillColor(sf::Color::White);
    scoreTx.setPosition(10, 110 + i * 30);
    std::string textToDisplay =
        (std::to_string(i + 1) + ". " + singlePlayer.name() + " with " +
         std::to_string(singlePlayer.highscore()) + " points!");
    scoreTx.setString(textToDisplay);
    scores.push_back(scoreTx);
    i = i + 1;
  }
  sf::RectangleShape rectangle(sf::Vector2f(window_size_x, i * 30 + 20));
  rectangle.setPosition(0, 100);
  rectangle.setFillColor(sf::Color::Black);
  rectangle.setOutlineColor(sf::Color::Blue);
  rectangle.setOutlineThickness(2);
  window.draw(rectangle);
  for (auto text : scores) {
    window.draw(text);
  }

  return;
}

std::list<leaderboardPosition> refresh_scoreboard(
    std::list<leaderboardPosition> leaderbord, int highscore,
    std::string name) {
  leaderbord.push_back(leaderboardPosition(highscore, name));
  leaderbord.sort();
  if (leaderbord.size() > 5) {
    leaderbord.pop_back();
  }
  return leaderbord;
}

void save_scoreboard(std::list<leaderboardPosition> leaderbord) {
  std::ofstream MyFile("example.txt");

  for (auto player : leaderbord) {
    MyFile << player.name() << "_" << player.highscore() << std::endl;
  }

  MyFile.close();
}

std::tuple<bool, bool> main_game_function(sf::RenderWindow& window,
                                          int levelOfGame) {
  sf::Clock clock;
  sf::Clock shootingClock;
  float shooting_time = 0;
  float shooting_timout = 0.1 - levelOfGame * 0.01;
  float player_speed = 300 + 10 * levelOfGame;
  float asteroid_speed = 100 + levelOfGame * 50;
  sf::Event event;
  Player player1(100, 100);
  int num_asteroid = 2 * levelOfGame;
  std::list<Asteroid> asteroids = {};
  std::list<Shoot> shoots = {};
  std::list<std::list<Explosion>> firework = {};
  std::list<Heart> hearts = {};
  int num_of_heart = 2 + (levelOfGame) / 2;
  float heart_speed = 50 + levelOfGame * 10;
  Lifebar lifebar(numberOfLife);
  for (int i = 0; i < num_of_heart; i++) {
    float pos_x = RandomFloat(500, window_size_x - 200);
    float pos_y = RandomFloat(500, window_size_y - 200);
    float size = RandomFloat(50, 100);
    hearts.push_back(Heart(pos_x, pos_y, size, heart_speed));
  }

  for (int i = 0; i < num_asteroid; i++) {
    float pos_x = RandomFloat(500, window_size_x - 200);
    float pos_y = RandomFloat(500, window_size_y - 200);
    float size = RandomFloat(20, 100);
    asteroids.push_back(Asteroid(pos_x, pos_y, size, asteroid_speed));
  }
  bool collision_happend = false;
  while (window.isOpen()) {
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window.close();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
      player1.set_speed(-player_speed);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
      player1.set_speed(player_speed);
    } else {
      player1.set_speed(0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
      player1.change_angel(-0.05);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
      player1.change_angel(0.05);
    }
    float elapsed_time = clock.restart().asSeconds();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
      shooting_time = shooting_time + shootingClock.restart().asSeconds();
      if (shooting_time > shooting_timout) {
        shooting_time = 0;
        float posX = player1.x() - player1.size() * 0.5 * cos(player1.angel());
        float posY = player1.y() - player1.size() * 0.5 * sin(player1.angel());
        float angel = player1.angel();
        shoots.push_back(Shoot(posX, posY, angel));
      }
    }

    for (Asteroid& asteroid : asteroids) {
      asteroid.update(elapsed_time);
      collision_happend =
          collision_happend || collision_check(asteroid, player1);
    }
    for (std::list<Shoot>::iterator shoot = shoots.begin();
         shoot != shoots.end(); ++shoot) {
      shoot->update(elapsed_time);
      for (Asteroid& aster : asteroids) {
        aster.setBeenHit(been_hit_check(aster, *shoot) || aster.beenHit());
        shoot->setHitSomething(been_hit_check(aster, *shoot));
      }
      for (Heart& heart : hearts) {
        heart.been_hit_check_with_shoot(*shoot);
        shoot->setHitSomething(heart.been_hit_check_with_shoot(*shoot));
      }
    }

    for (Heart& heart : hearts) {
      heart.update(elapsed_time);
      heart.collision_check_with_player(player1);
    }

    for (Heart& heart : hearts) {
      if (heart.beenHit() == true) {
        lifebar.addLife(1);
      }
    }

    for (Asteroid& asteroid : asteroids) {
      if (asteroid.beenHit() == true) {
        score = score + 1;
        totalScore = totalScore + 1;
        if (bestScore < totalScore) {
          bestScore = bestScore + 1;
        }
        if (score == num_asteroid) {
          return {false, true};
        }
      }
    }

    for (Asteroid& asteroid : asteroids) {
      std::list<Explosion> explosions = {};
      if (asteroid.beenHit() == true) {
        for (int i = 0; i < 360; i++) {
          int steps = 4 * i;
          int speed = 0;
          if (0 <= steps && steps < 360) {
            speed = 100;
          } else if (360 <= steps && steps < 720) {
            speed = 150;
          } else if (720 <= steps && steps < 1080) {
            speed = 200;
          } else if (1080 <= steps && steps < 1440) {
            speed = 250;
          }
          Explosion expo =
              Explosion(asteroid.x(), asteroid.y(), steps * 3.141 / 180, speed);
          expo.setColor(255, 255, 255);
          explosions.push_back(expo);
        }
        firework.push_back(explosions);
      }
    }

    for (Heart& heart : hearts) {
      std::list<Explosion> explosions = {};
      if (heart.beenDestroyed() == true) {
        for (int i = 0; i < 360; i++) {
          int steps = 4 * i;
          int speed = 0;
          if (0 <= steps && steps < 360) {
            speed = 100;
          } else if (360 <= steps && steps < 720) {
            speed = 150;
          } else if (720 <= steps && steps < 1080) {
            speed = 200;
          } else if (1080 <= steps && steps < 1440) {
            speed = 250;
          }
          Explosion expo =
              Explosion(heart.x(), heart.y(), steps * 3.141 / 180, speed);
          expo.setColor(255, 0, 0);
          explosions.push_back(expo);
        }
        firework.push_back(explosions);
      }
    }

    for (std::list<Explosion>& explosions : firework) {
      for (Explosion& explo : explosions) {
        explo.update(elapsed_time);
      }
    }

    asteroids.remove_if([](Asteroid aster) { return aster.beenHit() == true; });
    shoots.remove_if([](Shoot shoot) { return shoot.hitSomething() == true; });
    shoots.remove_if(
        [](Shoot shoot) { return shoot.outsideOfScreen() == true; });
    hearts.remove_if([](Heart heart) { return heart.beenHit() == true; });
    hearts.remove_if([](Heart heart) { return heart.beenDestroyed() == true; });

    player1.update(elapsed_time);

    // Rendering everything
    window.clear();

    for (Asteroid& asteroid : asteroids) {
      asteroid.render(window);
      // asteroid.renderDebug(window);
      // asteroid.renderCollision(window);
    }

    for (Heart& heart : hearts) {
      heart.render(window);
      // heart.renderDebug(window);
      // heart.renderCollision(window);
    }

    for (std::list<Explosion>& explosions : firework) {
      for (Explosion& explo : explosions) {
        explo.render(window);
      }
      explosions.remove_if(
          [](Explosion explo) { return explo.invisibleExplosion() == true; });
    }

    for (Shoot& shoot : shoots) {
      shoot.render(window);
    }
    player1.render(window);
    // player1.renderDebug(window);
    // player1.renderCollision(window);

    render_title_bar(window);
    lifebar.render(window);

    if (collision_happend) {
      if (lifebar.lifepoint() == 0) {
        return {true, false};
      } else {
        numberOfLife = numberOfLife - 1;
        lifebar.removeLife();
        return {false, false};
      }
    }

    window.display();
  }
  return {false, false};
}

bool end_screen_function(sf::RenderWindow& window) {
  sf::Event event;
  sf::Texture* texture = new sf::Texture;
  texture->loadFromFile("Game_Over.png");
  sf::Vector2u texSize = texture->getSize();
  sf::Sprite sprite;
  sprite.setTexture(*texture);
  sprite.setPosition(0, 0);
  sprite.setScale(window_size_x / (float)texSize.x,
                  window_size_y / (float)texSize.y);
  window.draw(sprite);
  render_title_bar(window);
  render_foot_bar(window);
  std::list<leaderboardPosition> leaderbord = scorebord();
  leaderbord = refresh_scoreboard(leaderbord, totalScore, "Amani");
  render_scoreboard(window, leaderbord);
  save_scoreboard(leaderbord);
  while (window.isOpen()) {
    window.display();
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window.close();
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
        score = 0;
        level = startingLevel;
        totalScore = 0;
        numberOfLife = 3;
        return false;
      }
    }
  }
  return true;
}

int main() {
  std::unique_ptr<sf::RenderWindow> window = std::make_unique<sf::RenderWindow>(
      sf::VideoMode(window_size_x, window_size_y), "Asteroid - have fun");
  window->setFramerateLimit(60);
  sf::Clock totalClock;
  std::tuple<bool, bool> results;
  bool gameOver = false;
  bool levelFinished = false;

  while (!gameOver && window->isOpen()) {
    results = main_game_function(*window, level);
    gameOver = std::get<0>(results);
    levelFinished = std::get<1>(results);
    if (levelFinished == true) {
      level = level + 1;
      score = 0;
      levelFinished = false;
    } else if (gameOver == true) {
      gameOver = end_screen_function(*window);
    }
  }

  return 0;
}
