#pragma once
#include <SFML/Graphics.hpp>
#include "Ball.hpp"

namespace ia {

	class Player
	{
	private:
		X_Y m_pos_player;
		X_Y m_window_size;
		X_Y m_size;
		double m_speed;
		sf::RectangleShape *m_rect;
		int m_player_num;

	public:
		Player(X_Y pos_player, X_Y size, double speed, X_Y window_size, int player_num);
		void move_player();

		sf::RectangleShape* return_player();

		float get_pos_y();
		~Player();
	};
}