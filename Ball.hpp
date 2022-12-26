#pragma once
#include <cmath>
#include <SFML/Graphics.hpp>

namespace ia {

	struct X_Y
	{
		float x;
		float y;
	};

	float check_angle(float angle, bool left);


	float len_vector(X_Y vec);

	float scalar_mult_vector(X_Y vec1, X_Y vec2);
	float angle_2vector(X_Y vec1, X_Y vec2);

	X_Y create_vector(float angle);

	class Ball
	{
	private:
		X_Y m_pos_ball = { 0, 0 };
		float m_radius = 0;
		float m_angle;
		float m_speed;
		X_Y m_move_vector;
		sf::CircleShape* m_circle;
		X_Y m_platform_size;
		X_Y m_window_size;
		X_Y m_temp;
		bool m_flag_stop = false;
		float m_score1 = 0;
		float m_score2 = 0;
	public:
		Ball(X_Y pos_ball, float radius, float angle, X_Y platform_size, X_Y window_size, float speed);

		X_Y get_pos();

		void up_speed(float speed);

		void set_speed(int speed);

		void collision(std::vector <float> y_platforms);
		sf::CircleShape* return_circle();

		void move();

		~Ball();
	};
}