#pragma once
#include <cmath>
#include <SFML/Graphics.hpp>
#include "Ball.hpp"
#include <iostream>

namespace ia {

	float check_angle(float angle, bool left) {
		if (angle > 360)
			angle -= 360;
		if ((angle > 250) && left)
			return 250;
		if ((110 > angle) && left)
			return 110;
		if ((180 < angle && angle < 290) && !left)
			return 300;
		if ((180 > angle >= 70) && !left)
			return 70;
		return angle;
	}


	float len_vector(X_Y vec) {
		return sqrt(pow(vec.x, 2) + pow(vec.y, 2));
	}

	float scalar_mult_vector(X_Y vec1, X_Y vec2) {
		return vec1.x * vec2.x + vec1.y * vec2.y;
	}
	float angle_2vector(X_Y vec1, X_Y vec2) {
		return acos(scalar_mult_vector(vec1, vec2) / (len_vector(vec1) * len_vector(vec2))) / acos(-1) * 180.0;
	}

	X_Y create_vector(float angle) {
		X_Y coords;
		coords.x = cosf(angle * acos(-1) / 180.0);
		coords.y = sinf(angle * acos(-1) / 180.0);
		return coords;
	}

		Ball::Ball(X_Y pos_ball, float radius, float angle, X_Y platform_size, X_Y window_size, float speed) {
			m_pos_ball = pos_ball;
			m_radius = radius;
			m_angle = -angle;
			m_window_size = window_size;
			m_platform_size = platform_size;
			m_temp = create_vector(m_angle);
			m_speed = speed;
			m_move_vector = { m_temp.x, m_temp.y };
			m_circle = new sf::CircleShape(radius);
			m_circle->setOrigin(radius, radius);
			m_circle->setFillColor(sf::Color::Red);

		};

		X_Y Ball::get_pos() {
			return m_pos_ball;
		}

		void Ball::up_speed(float speed) {
			if (m_speed != 0)
				m_speed = speed;
		}

		

		void Ball::collision(std::vector <float> y_platforms) {
			if ((m_pos_ball.x - m_radius) <= 0)
				m_move_vector.x = -m_move_vector.x;

			if ((m_pos_ball.y - m_radius) <= 0)
				m_move_vector.y = -m_move_vector.y;

			if ((m_pos_ball.y + m_radius) >= m_window_size.y)
				m_move_vector.y = -m_move_vector.y;
			if (m_pos_ball.x + m_radius >= m_window_size.x) {
				if (m_speed !=0)
					m_score1 += 1;
				m_speed = 0;
				
			}
			if (m_pos_ball.x - m_radius <= 1) {
				if (m_speed != 0)
					m_score2 += 1;
				m_speed = 0;
				
			}
			float y_platform;
			for (int i = 0; i < y_platforms.size(); i++) {
				y_platform = y_platforms[i];
				if (((m_pos_ball.x + m_radius) >= m_window_size.x - 20 - m_platform_size.x) && i == 0) {
					if (((m_pos_ball.y) > y_platform + m_platform_size.y * 0.25) && ((m_pos_ball.y) < (y_platform + m_platform_size.y * 0.75))) {
						m_move_vector.x = -m_move_vector.x;
					}
					if (((m_pos_ball.y) > y_platform) && ((m_pos_ball.y) < (y_platform + m_platform_size.y * 0.25))) {
						m_temp = create_vector(190);
						m_move_vector = { -m_move_vector.x, -m_move_vector.y };
						if (m_move_vector.y > m_temp.y) {
							m_move_vector = create_vector(check_angle(190 + angle_2vector(m_temp, m_move_vector), true));
						}
						else {
							m_move_vector = create_vector(check_angle(190 - angle_2vector(m_temp, m_move_vector), true));
						}
					}
					if (((m_pos_ball.y) > y_platform + m_platform_size.y * 0.75) && ((m_pos_ball.y) < (y_platform + m_platform_size.y))) {
						m_temp = create_vector(170);
						m_move_vector = { -m_move_vector.x, -m_move_vector.y };
						if (m_move_vector.y > m_temp.y) {
							m_move_vector = create_vector(check_angle(170 + angle_2vector(m_temp, m_move_vector), true));
						}
						else {
							m_move_vector = create_vector(check_angle(170 - angle_2vector(m_temp, m_move_vector), true));
						}
					}
				}
				if (20 + m_platform_size.x >= (m_pos_ball.x - m_radius) && i == 1) {
					if (((m_pos_ball.y) > y_platform + m_platform_size.y * 0.25) && ((m_pos_ball.y) < (y_platform + m_platform_size.y * 0.75))) {
						m_move_vector.x = -m_move_vector.x;
					}
					if (((m_pos_ball.y) > y_platform) && ((m_pos_ball.y) < (y_platform + m_platform_size.y * 0.25))) {
						m_temp = create_vector(350);
						m_move_vector = { -m_move_vector.x, -m_move_vector.y };
						if (m_move_vector.y > m_temp.y) {
							m_move_vector = create_vector(check_angle(350 - angle_2vector(m_temp, m_move_vector), false));
						}
						else {
							m_move_vector = create_vector(check_angle(350 + angle_2vector(m_temp, m_move_vector), false));
						}
					}
					if (((m_pos_ball.y) > y_platform + m_platform_size.y * 0.75) && ((m_pos_ball.y) < (y_platform + m_platform_size.y))) {
						m_temp = create_vector(10);
						m_move_vector = { -m_move_vector.x, -m_move_vector.y };
						if (m_move_vector.y > m_temp.y) {
							m_move_vector = create_vector(check_angle(10 - angle_2vector(m_temp, m_move_vector), false));
						}
						else {
							m_move_vector = create_vector(check_angle(10 + angle_2vector(m_temp, m_move_vector), false));
						}
					}
				}
			}
		}

		sf::CircleShape* Ball::return_circle() {
			return m_circle;
		}
		void Ball::set_speed(int speed) {
			m_speed = speed;
			m_pos_ball = { m_window_size.x / 2 , m_window_size.y / 2 };
		}

		void Ball::move() {
			m_pos_ball.x += m_move_vector.x * m_speed;
			m_pos_ball.y += m_move_vector.y * m_speed;
			m_circle->setPosition(m_pos_ball.x, m_pos_ball.y);
		}

		Ball::~Ball() {};
	}