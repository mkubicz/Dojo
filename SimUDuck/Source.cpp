#include <iostream>
#include "MallardDuck.h"
#include "RubberDuck.h"
#include "FlyWithWings.h"
#include "FlyNoWay.h"

int main()
{
	MallardDuck md;
	RubberDuck rd;

	md.Display();
	md.PerformFly();
	md.PerformQuack();

	rd.Display();
	rd.PerformFly();
	rd.PerformQuack();

	rd.SetFlyBehaviour(std::make_unique<FlyWithWings>());
	rd.PerformFly();

	auto newfly = std::make_unique<FlyNoWay>();
	rd.SetFlyBehaviour(std::move(newfly));
	rd.PerformFly();

	system("PAUSE");
}