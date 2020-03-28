#pragma once
#include "Params.inl"


#define _USE_MATH_DEFINES
#include <cmath>

namespace ps {


	class Particle {

	public:


		enum class State { OK, BURN, DIED };

		Particle(double x, double y, double z, double speed);
		virtual ~Particle() {};

		//get coordinates
		const double _x();
		const double _y();
		const double _z();

		//get state
		const State getState();

		const bool isBurn();
		void setBurn();

		//void Step();
		void Step();
		void Move();
		const double Distance(const Particle&);
		const bool Cross(const Particle&);

		State m_state = State::OK;
		size_t m_burn_counter = 0;
		size_t m_steps = 0;

		double x, y, z, speed;

	};

} /* namespace ps */

