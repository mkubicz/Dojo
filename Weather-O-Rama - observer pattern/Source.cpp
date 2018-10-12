#include <iostream>
#include "WeatherData.h"
#include "ForecastDisplay.h"
#include "CurrentConditionsDisplay.h"
#include "StatisticsDisplay.h"

void main()
{
	std::shared_ptr<WeatherData> wd = std::make_shared<WeatherData>();
	std::weak_ptr<WeatherData> wd_weak(wd);
	auto ccd = std::make_shared<CurrentConditionsDisplay>(wd_weak);
	auto fcd = std::make_shared<ForecastDisplay>(wd_weak);
	auto scd = std::make_shared<StatisticsDisplay>(wd_weak);

	wd->RegisterObserver(std::weak_ptr<IObserver>(ccd));
	wd->RegisterObserver(std::weak_ptr<IObserver>(fcd));

	wd->SetMeasurements(10.0, 60.30, 1005.0);

	wd->RegisterObserver(std::weak_ptr<IObserver>(scd));

	wd->SetMeasurements(23.0, 40.32, 999.0);

	wd->RemoveObserver(std::weak_ptr<IObserver>(ccd));

	wd->SetMeasurements(-5.0, 80.32, 994.0);

	wd->RegisterObserver(std::weak_ptr<IObserver>(ccd));

	wd->SetMeasurements(15.0, 60.00, 1031.0);


	system("PAUSE");
}
