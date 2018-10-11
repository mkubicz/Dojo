#include "WeatherData.h"
#include "IObserver.h"

void WeatherData::RegisterObserver(std::weak_ptr<IObserver> ob)
{
	_observers.push_back(ob);
}

void WeatherData::RemoveObserver(std::weak_ptr<IObserver> ob)
{
	//idk czy to bêdzie dzia³aæ
	//_observers.remove(std::weak_ptr<IObserver>(ob));
	_observers.remove_if(
		[ob_toremove = ob](std::weak_ptr<IObserver> ob) 
		{
			if (!ob_toremove.expired() && !ob.expired())
				return ob_toremove.lock().get() == ob.lock().get();

			return false;
		}
	);
}

double WeatherData::GetTemperature()
{
	return _temp;
}

double WeatherData::GetHumidity()
{
	return _humi;
}

double WeatherData::GetPressure()
{
	return _pres;
}

void WeatherData::SetMeasurements(double temp, double humi, double pres)
{
	_temp = temp;
	_humi = humi;
	_pres = pres;
	MeasurementsChanged();
}

void WeatherData::MeasurementsChanged()
{
	NotifyObservers();
}

void WeatherData::NotifyObservers()
{
	for (auto obwp : _observers)
	{
		if (!obwp.expired())
		{
			auto obsp = obwp.lock();
			obsp->Update(_temp, _humi, _pres);
		}
		else
		{
			//_observers.remove(obwp);
		}
	}
}
