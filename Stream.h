#pragma once
#include "Params.inl"
#include "Particle.h"
#include <list>
#include <vector>
#include <fstream>
#include <sstream>
#include <random>



#define _USE_MATH_DEFINES
#include <cmath>

namespace ps {

	class Stream {

	public:

	public:
		Stream();

		void Step();

		void Fill();
		void Lighter();
		//void UpdateBurnFrom();
		void BurnParticles();
		void MoveParticles();
		void ClearBurnList();
		void ClearParticleList();

		void BurnParticle(Particle& p);

		//void StepParticle(unsigned index, std::list<Particle>::iterator&);

		const void PrintStep(size_t);



		//unsigned GetSegmentIndex(Particle& p);




		//private:


		std::list <Particle> all_list;
		std::list <Particle*> all_burn;
		std::list <Particle*> all_will_burn;


		//std::vector<std::list<Particle>::iterator> died_list;


	};


} /* namespace ps */

