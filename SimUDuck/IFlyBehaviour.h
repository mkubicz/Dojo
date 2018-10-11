#pragma once

class IFlyBehaviour
{
public:
	IFlyBehaviour();
	virtual ~IFlyBehaviour() = default;

	virtual void Fly() = 0;
};

