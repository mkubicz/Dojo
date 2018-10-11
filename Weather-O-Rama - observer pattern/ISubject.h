#pragma once
#include <memory>
//#include "IObserver.h"

//forward declaration
class IObserver;

class ISubject
{
public:
	virtual void RegisterObserver(std::weak_ptr<IObserver> ob) = 0;
	virtual void RemoveObserver(std::weak_ptr<IObserver> ob) = 0;
	virtual void NotifyObservers() = 0;

};