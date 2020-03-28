#include "Stream.h"
#include <string>
#include <sstream>
#include <fmt/format.h>



#define _USE_MATH_DEFINES
#include <cmath>

#define M_PI 3.14159265358979323846

namespace ps {

	Stream::Stream(){}

	const void Stream::PrintStep(size_t num)
	{

		std::ofstream csv(P::csv_folder + "gas.csv." + std::to_string(num));

		std::stringstream output;
		output << "x,y,z,burn";




		for (auto& particle : all_list) {
			//output += fmt::format("\n{},{},{}", particle._x(), particle._y(), particle.m_burn_counter);
			output << '\n' << particle._x() << ',' << particle._y() << ',' << particle._z() << ',' << particle.m_burn_counter;
		}

		csv << output.rdbuf();;
		csv.close();


	}

	void Stream::Fill() {

		double particles_double;
		int particles_at_step;

		std::random_device xy_rd;
		std::uniform_real_distribution<double> xy_dist;

		std::random_device z_rd;
		std::uniform_real_distribution<double> z_dist;

		double a, r, x, y, z, speed;

		for (int k = P::stream_radius_2; k > 0; --k)
		{
			xy_dist = std::uniform_real_distribution<double>(k - 1, k);

			particles_double = (P::stream_radius_2 - k + 1.0) / P::stream_radius * 3;
			particles_at_step = round(particles_double * particles_double);

			for (int i = 0; i < particles_at_step; ++i)
			{
				a = xy_dist(xy_rd) * 2 * M_PI;
				r = sqrt(xy_dist(xy_rd));

				x = r * cos(a);
				y = r * sin(a);

				speed = P::speed_distribution(x, y);
				z_dist = std::uniform_real_distribution<double>(0, speed);
				z = z_dist(z_rd);

				all_list.emplace_back(x, y, z, speed);

			}

		}

	}



	void Stream::BurnParticles()
	{
		unsigned segment_index; //walk over all segments

		for (auto& particle_i : all_list)
		{ //walk over all particles in segment
			if (particle_i.getState() == Particle::State::OK)
			{ //if particle doesn't burn
				//segment_index = GetSegmentIndex(particle_i);

				//if (particle_i._x() >= burn_from[segment_index])
				{ //if particle being close to burn line
					for (auto& burn_i : all_burn)
					{ //walk over all burning particles in current segment
						if (/*(*burn_i).m_burn_counter > 1 && */particle_i.Cross(*burn_i))
						{ //if particle cross with burning particle
							BurnParticle(particle_i);
							break;
						}
					}
				}
			}
			particle_i.Step();
		}
	}
	void Stream::MoveParticles()
	{
		for (auto& particle_i : all_list) {
			particle_i.Move();
		}
	}


	void Stream::ClearBurnList() {

		auto burn_it = all_burn.begin();
		auto died_it = burn_it;
		while (burn_it != all_burn.end()) {
			if ((*burn_it)->getState() == ps::Particle::State::DIED) {
				died_it = burn_it;
				++burn_it;
				all_burn.erase(died_it);
			}
			else ++burn_it;
		}


		all_burn.splice(all_burn.end(), all_will_burn);


	}

	void Stream::ClearParticleList() {

		auto particle_it = all_list.begin();
		auto died_it = particle_it;
		while (particle_it != all_list.end()) {
			if ((*particle_it).getState() == ps::Particle::State::DIED) {
				died_it = particle_it;
				++particle_it;
				all_list.erase(died_it);
			}
			else ++particle_it;
		}

	}



	/*unsigned Stream::GetSegmentIndex(Particle& p)
	{
		return floor((p._y() - P::area_beg) / P::area_size * P::segment_count);
	}*/


	void Stream::Lighter() {
		int i = 0, limit = P::light_count;
		for (auto& particle_i : all_list) {
			BurnParticle(particle_i);
			if (++i == limit) break;
		}

	}


	void Stream::BurnParticle(Particle& particle) {

		particle.setBurn();

		all_will_burn.push_back(&particle);

	}



	void Stream::Step() {

		//all_will_burn.clear();

		//UpdateBurnFrom();

		BurnParticles();

		ClearBurnList();

		ClearParticleList();

		MoveParticles();

	}

}