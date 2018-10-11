#include "MallardDuck.h"
#include <iostream>
#include "FlyWithWings.h"
#include "NormalQuack.h"


MallardDuck::MallardDuck()
{
	_flyBehaviour = std::make_unique<FlyWithWings>();
	_quackBehaviour = std::make_unique<NormalQuack>();
}


MallardDuck::~MallardDuck()
{
}

void MallardDuck::Display()
{
	std::cout << "A mallard duck." << std::endl;
}
