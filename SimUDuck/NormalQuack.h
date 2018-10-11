#pragma once
#include "IQuackBehaviour.h"
class NormalQuack : public IQuackBehaviour
{
public:
	NormalQuack();
	~NormalQuack();

	void Quack();
};

