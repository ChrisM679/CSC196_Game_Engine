#include "Math/Math.h"
#include "Core/Random.h"
#include <iostream>

#define NAME "Chris"

using namespace viper;

int main() 
{
	//const float deg = viper::math::radToDeg(math::pi);
	//math::clamp(1, 3, 5);

	std::cout << NAME << std::endl;
	std::cout << "Hello World!" << std::endl;
	std::cout << math::pi << std::endl;

	for (int i = 0; i < 10; i++) { 
		std::cout << random::getRandomFloat() << std::endl;
	}
}