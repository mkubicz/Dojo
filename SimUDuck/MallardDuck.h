#pragma once
#include "IDuck.h"
class MallardDuck :
	public IDuck
{
public:
	MallardDuck();
	~MallardDuck();

	void Display();
};

