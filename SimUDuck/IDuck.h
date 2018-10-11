#pragma once
#include <memory>
#include "IFlyBehaviour.h"
#include "IQuackBehaviour.h"

class IDuck
{
public:
	IDuck();
	virtual ~IDuck() = default; 

	//bierzemy rvalue referencje bo przecie¿ nie bêdziemy kopiowaæ unique pointerów
	//i rvalue ref sugeruje ¿e faktycznie przenosimy nasz argument do funkcji
	void SetFlyBehaviour(std::unique_ptr<IFlyBehaviour>&&fb);
	void SetQuackBehaviour(std::unique_ptr<IQuackBehaviour>&& qb);

	void PerformFly();
	void PerformQuack();
	virtual void Display() = 0;

protected:
	std::unique_ptr<IFlyBehaviour> _flyBehaviour;
	std::unique_ptr<IQuackBehaviour> _quackBehaviour;
};

