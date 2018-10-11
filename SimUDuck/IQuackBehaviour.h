#pragma once

class IQuackBehaviour
{
public:
	IQuackBehaviour();
	virtual ~IQuackBehaviour() = default;

	virtual void Quack() = 0;
};

