#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <chrono>
#include <thread>
#include <string>
#include "Ball.hpp"
#include "Player.hpp"
#include <string> 



int main()
{

	ia::X_Y window_size = { 800, 600 };
	ia::X_Y player_size = { 20,120 };
	bool flag_stop = false;
	ia::X_Y ball_pos = { window_size.x / 2, window_size.y / 2 };
	float speed = 3;
	int count_player = 2;
	std::vector <float> players;
	float radius = 15;

	ia::X_Y rec_pos1 = { window_size.x - 20,  window_size.y / 2-50 };
	ia::X_Y rec_pos2 = { 20,  window_size.y / 2-50 };

	ia::Ball ball(ball_pos, 15, 180, player_size, window_size, speed);

	ia::Player player1(rec_pos1, player_size, 6, window_size, 1);
	ia::Player player2(rec_pos2, player_size, 6, window_size, 2);
	players.push_back(player1.get_pos_y());
	players.push_back(player2.get_pos_y());
	sf::RenderWindow window(sf::VideoMode(window_size.x, window_size.y), "Pong!");
	sf::Clock timer;

	while (window.isOpen())
	{
		sf::Time dt;
		dt = timer.getElapsedTime();
		if (dt.asSeconds()>=15) {
			ball.up_speed(speed);
			dt = timer.restart();
			speed += 0.5;
		}
		players.clear();
		players.push_back(player1.get_pos_y());
		players.push_back(player2.get_pos_y());
		sf::Event event;
		ball.move();
		ball.collision(players);
		player1.move_player();
		player2.move_player();

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
				speed = 3;
				ball.set_speed(speed);
				ball.return_circle()->setPosition(ball_pos.x, ball_pos.y);
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				return 0;

		}
		window.clear(sf::Color(245, 230, 220));
		window.draw(*player1.return_player());
		window.draw(*player2.return_player());
		window.draw(*ball.return_circle());
		window.display();
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
	return 0;
}
