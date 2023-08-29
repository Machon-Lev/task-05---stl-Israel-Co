#include "..\include\CityMap.h"

// #include "citiesMap.h"
#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <vector>


void CityMap::insert(std::string cityName, double x, double y)
{
	Coordinate newCity = { x, y };

	this->cityMap.insert({ cityName,newCity });
}


double calculateEuclideanDistance(double x0, double y0, double x1, double y1) {
	return std::sqrt((x0 - x1) * (x0 - x1) + (y0 - y1) * (y0 - y1));
}

double calculateChebyshevDistance(double x0, double y0, double x1, double y1) {
	return std::max(std::abs(x0 - x1), std::abs(y0 - y1));
}

double calculateManhattanDistance(double x0, double y0, double x1, double y1) {
	return std::abs(x0 - x1) + std::abs(y0 - y1);
}


void CityMap::initDistanceFunctions()
{
	this->distanceFunctions = {
	  {0, calculateEuclideanDistance},
	  {1, calculateChebyshevDistance},
	  {2, calculateManhattanDistance}
	};
}

void CityMap::initCitiesFromFileToMap(std::string filename)
{
	std::ifstream file(filename);
	std::string line;
	std::string cityName;
	double x, y;

	while (std::getline(file, line)) {
		cityName = line;

		if (!std::getline(file, line)) {
			throw std::runtime_error("Invalid data format in file: " + filename);
		}

		std::istringstream iss(line);
		std::string xCoord, yCoord;
		if (!(std::getline(iss, xCoord, '-') && std::getline(iss, yCoord))) {
			throw std::runtime_error("Invalid data format in file: " + filename);
		}

		std::istringstream xIss(xCoord);
		std::istringstream yIss(yCoord);
		if (!(xIss >> x) || !(yIss >> y)) {
			throw std::runtime_error("Invalid data format in file: " + filename);
		}

		this->insert(cityName, x, y);
	}
}

bool inSquare(double x0, double y0, double x1, double y1, double radius) {
	return   std::max(std::abs(x0 - x1), std::abs(y0 - y1)) <= radius;
}

void CityMap::closeCities(std::string cityName, double radius, int distanceCalc) const
{
	auto chosenCity = this->cityMap.find(cityName);

	if (chosenCity == this->cityMap.end()) {
		throw std::runtime_error("City not found in the map");
	}

	if (this->distanceFunctions.find(distanceCalc) == this->distanceFunctions.end()) {
		throw std::runtime_error("invalide distance calc function");
	}


	int northCity = 0;

	std::vector<std::pair<std::string, Coordinate>> closeCity;

	std::copy_if(this->cityMap.begin(), this->cityMap.end(), std::back_inserter(closeCity),
		[=, &northCity](const std::pair<std::string, Coordinate> city) {


			if (city.first != chosenCity->first &&
				inSquare(chosenCity->second.x, chosenCity->second.y, city.second.x, city.second.y, radius) &&
				this->distanceFunctions.at(distanceCalc)(chosenCity->second.x, chosenCity->second.y,
					city.second.x, city.second.y) < radius)
			{
				if (chosenCity->second.y > city.second.y)
					++northCity;

				return true;
			}
			return false;
		});

	std::sort(closeCity.begin(), closeCity.end(), [=](const auto& city1, const auto& city2) {
		return this->distanceFunctions.at(distanceCalc)(chosenCity->second.x, chosenCity->second.y,
			city1.second.x, city1.second.y) <
			this->distanceFunctions.at(distanceCalc)(chosenCity->second.x, chosenCity->second.y,
				city2.second.x, city2.second.y);
		});

	std::cout << "Search result:" << std::endl;
	std::cout << closeCity.size() << " city/cities found in the given radius." << std::endl;
	std::cout << northCity << " cities are to the north of the selected city." << std::endl;
	std::cout << "City list:" << std::endl;

	std::transform(closeCity.begin(), closeCity.end(), std::ostream_iterator<std::string>(std::cout, "\n"),
		[](const auto& element) { return element.first; });
}
