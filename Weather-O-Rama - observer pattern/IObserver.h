#pragma once
#include <memory>
//#include "ISubject.h"

//forward declaration
class ISubject;

class IObserver
{
public:
	IObserver(std::weak_ptr<ISubject> subject);
	virtual void Update(double temp, double humi, double pres) = 0;
protected:
	std::weak_ptr<ISubject> _subject;
};