#include "IObserver.h"

IObserver::IObserver(std::weak_ptr<ISubject> subject)
	: _subject(subject)
{
}
