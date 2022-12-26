#pragma once
#include <SFML/Graphics.hpp>
#include "Player.hpp"

namespace ia {

		Player::Player(X_Y pos_player, X_Y size, double speed, X_Y window_size, int player_num) {
			m_pos_player = pos_player;
			m_size = size;
			m_speed = speed;
			m_player_num = player_num;
			m_window_size = window_size;
			m_rect = new sf::RectangleShape(sf::Vector2f(m_size.x, m_size.y));
			if (player_num == 1)
				m_rect->setOrigin(m_size.x, 0);

			m_rect->setFillColor(sf::Color::Magenta);
			m_rect->setPosition(m_pos_player.x, m_pos_player.y);
		}
		void Player::move_player() {
			if ((((sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) && m_player_num == 1) || ((sf::Keyboard::isKeyPressed(sf::Keyboard::W)) && m_player_num == 2)) && (m_pos_player.y > 0)) {
				m_pos_player.y -= m_speed;
				m_rect->setPosition(m_pos_player.x, m_pos_player.y);

			}
			if ((((sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) && m_player_num == 1) || ((sf::Keyboard::isKeyPressed(sf::Keyboard::S)) && m_player_num == 2)) && (m_pos_player.y + m_size.y < m_window_size.y)) {
				m_pos_player.y += m_speed;
				m_rect->setPosition(m_pos_player.x, m_pos_player.y);

			}
		}

		sf::RectangleShape* Player::return_player() { return m_rect; }

		float Player::get_pos_y() {
			return m_pos_player.y;
		}
		Player::~Player() {};
	};