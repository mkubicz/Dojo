#include "IDuck.h"


IDuck::IDuck()
{
}

void IDuck::SetFlyBehaviour(std::unique_ptr<IFlyBehaviour>&& fb)
{
	_flyBehaviour.swap(fb);
	fb.release();
}

void IDuck::SetQuackBehaviour(std::unique_ptr<IQuackBehaviour>&& qb)
{
	_quackBehaviour.swap(qb);
	qb.release();
}

void IDuck::PerformFly()
{
	_flyBehaviour->Fly();
}

void IDuck::PerformQuack()
{
	_quackBehaviour->Quack();
}

