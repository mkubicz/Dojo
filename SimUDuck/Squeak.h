#pragma once
#include "IQuackBehaviour.h"
class Squeak :
	public IQuackBehaviour
{
public:
	Squeak();
	~Squeak();

	void Quack();
};

