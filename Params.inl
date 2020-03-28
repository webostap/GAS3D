#pragma once
#include <string>


#define _USE_MATH_DEFINES
#include <cmath>




namespace P {

	template <typename T>
	struct Interval {
		const T min, max, mid;
		Interval(T aMin, T aMax) : min(aMin), max(aMax), mid((aMax - aMin) / 2.) {}
	};


	const std::string csv_folder("C:/Users/prive/Desktop/csv3d/");

	const unsigned steps = 100;
	const unsigned burn_at_step = 5;
	const unsigned light_count = 5525;


	const double stream_radius = 5;
	const double stream_radius_2 = stream_radius* stream_radius;


	static double center_distance_2(const double x, const double y) {
		return x * x + y * y;
	}
	static double center_distance(const double x, const double y) {
		return sqrt(center_distance_2(x, y));
	}

	const double burn_radius = 0.25;
	const double base_speed =  25  / 100;

	/*static double speed_distribution(const double center_distance) {
		return 0.02 * (stream_radius - center_distance);
	}*/

	static double speed_distribution(const double x, const double y) {
		return 0.1 * (stream_radius - center_distance(x, y));
	}

	const double burn_radius_2 = burn_radius * burn_radius;
	const unsigned burn_time = 7;



}