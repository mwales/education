#include <iostream>

class IBuilding
{
public:
	IBuilding()
	{
		std::cout << "Created Building" << std::endl;
	}

	virtual ~IBuilding()
	{
		std::cout << "Destorying Building" << std::endl;
	}

	virtual void updateTemperature() = 0;

	virtual void debug() = 0;
};

class FloridaBuilding: public IBuilding
{
public:
	int theZipCode;

	int theArea;

	FloridaBuilding(int zip, int area)
	{
		theZipCode = zip;
		theArea = area;
		std::cout << "Created Florida Building at " << theZipCode << std::endl;
	}

	virtual ~FloridaBuilding()
	{
		std::cout << "Destoryed Florida Building at " << theZipCode << std::endl;
	}

	virtual void hurricanePrep()
	{
		std::cout << "Storm shutters up" << std::endl;
	}

	virtual void debug()
	{
		std::cout << "Debug Florida are = " << theArea << std::endl;
	}

};

class IWorkplace
{
public:
	IWorkplace()
	{
		std::cout << "Created Workplace" << std::endl;
	}

	virtual ~IWorkplace()
	{
		std::cout << "Destroyed workplace" << std::endl;
	}

	virtual void startBreakTime() = 0;

	virtual void debug() = 0;
};

class HourlyWorkplace: public IWorkplace
{
public:

	int theMinHours;

	int theMaxHours;

	HourlyWorkplace(int minHrs, int maxHrs)
	{
		theMinHours = minHrs;
		theMaxHours = maxHrs;
		std::cout << "Created Hourly Workplace" << theMinHours << " to " << theMaxHours << std::endl;
	}

	virtual ~HourlyWorkplace()
	{
		std::cout << "Destroyed hourly workplace" << std::endl;
	}

	virtual void startBreakTime() = 0;

	virtual void debug()
	{
		std::cout << "Debug Hourly Workplace" << theMinHours << " to " << theMaxHours << std::endl;
	}
};


class DrugStore: public FloridaBuilding, public HourlyWorkplace
{
public:
	DrugStore():
		FloridaBuilding(123, 234),
		HourlyWorkplace(20, 45)
	{
		std::cout << "Created drug store" << std::endl;
	}

	virtual ~DrugStore()
	{
		std::cout << "Destroying drug store" << std::endl;
	}

	virtual void updateTemperature()
	{
		std::cout << "Update Temp" << std::endl;
	}

	virtual void startBreakTime()
	{
		std::cout << "Start Break" << std::endl;
	}

	virtual void debug()
	{
		std::cout << "Do Drug Debug" << std::endl;
	}
};

void inspectWorkplace(IWorkplace* wp)
{
	std::cout << "Inspecting workplace" << std::endl;
	wp->debug();
}


void inspectBuilding(IBuilding* bldg)
{
	std::cout << "Inspecting building" << std::endl;
	bldg->debug();
}




int main(int argc, char** argv)
{
	DrugStore* walgreens = new DrugStore();

	walgreens->updateTemperature();
	walgreens->startBreakTime();
	walgreens->debug();

	inspectWorkplace(walgreens);
	inspectBuilding(walgreens);

	delete walgreens;

	return 0;
}

