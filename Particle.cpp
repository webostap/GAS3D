#include "Particle.h"

namespace ps {
	Particle::Particle(double _x, double _y, double _z, double _speed) : x(_x), y(_y), z(_z), speed(_speed) {}

	const bool Particle::isBurn()
	{
		return m_state == State::BURN;
	}

	void Particle::setBurn() {
		m_state = State::BURN;
	}


	void Particle::Step() {

		/*if (m_z_cord >= P::max_x) {
			m_state = State::DIED;
			return;
		}*/


		if (m_state == State::BURN) ++m_burn_counter;

		if (m_burn_counter == P::burn_time) {
			m_state = State::DIED;
			return;
		}

		++m_steps;


	}
	void Particle::Move() {

		z += speed;

	}



	const double Particle::_x() {
		return x;
	}

	const double Particle::_y() {
		return y;
	}

	const double Particle::_z() {
		return z;
	}

	const Particle::State Particle::getState() {
		return m_state;
	}

	const double Particle::Distance(const Particle& p) {
		return (x - p.x)*(x - p.x) + (y - p.y)*(y - p.y) + (z - p.z)*(z - p.z);
	}

	const bool Particle::Cross(const Particle& p) {
		return Distance(p) < P::burn_radius_2;
	}
}
