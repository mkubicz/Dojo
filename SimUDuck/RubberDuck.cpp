#include "RubberDuck.h"
#include <iostream>
#include "FlyNoWay.h"
#include "Squeak.h"

RubberDuck::RubberDuck()
{
	_flyBehaviour = std::make_unique<FlyNoWay>();
	_quackBehaviour = std::make_unique<Squeak>();
}


RubberDuck::~RubberDuck()
{
}

void RubberDuck::Display()
{
	std::cout << "I'm a rubber ducky!" << std::endl;
}
