#pragma once
#include <random>
typedef std::uniform_int_distribution<int> u_int_dist;
class Random
{
private:
	//static u_int_dist distribution;
public:

	template <typename T>
	static T FromRange(T min, T max) {
		static std::default_random_engine generator((uint32_t)time(NULL));
		u_int_dist dist(min, max);
		return (dist(generator));
	}
};

