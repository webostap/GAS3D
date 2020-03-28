#include <iostream>
#include <fstream>
#include <ctime> 
#include "Stream.h"



int main() {

	//std::cout << P::particles_sum;
	//return 0;

	//remove all files from csv directory
	bool gas_out = 0, line_out = 0;

	for (size_t i = 0; std::remove((P::csv_folder + "gas.csv." + std::to_string(i)).c_str()) == 0; ++i);


	ps::Stream main_swarm = ps::Stream();
	//main_swarm.Test(10);

	//auto first_partile = main_swarm.m_particle_list.begin();
	//double point;

	double start_time = clock();
	for (size_t i = 0; i < P::steps; i++)
	{

		if (i == P::burn_at_step) {
			main_swarm.Lighter();
		}



		main_swarm.Step();

		main_swarm.Fill();






		//if (i % 10 == 0)
			//if (i >= P::burn_at_step)
		{
			//main_swarm.PrintStep(i - P::burn_at_step);
			//main_swarm.PrintStep(i / 10);
			main_swarm.PrintStep(i);
		}



		std::cout << i << ")\t" << main_swarm.all_list.size() << '\n';
	}

	std::cout << (clock() - start_time) / 1000 << "s";
}
