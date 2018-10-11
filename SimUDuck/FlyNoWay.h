#pragma once
#include "IFlyBehaviour.h"
class FlyNoWay : public IFlyBehaviour
{
public:
	FlyNoWay();
	~FlyNoWay();

	void Fly();
};

