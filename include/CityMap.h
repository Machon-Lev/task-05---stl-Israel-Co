#pragma once
#include <map>
#include <functional>
#include "Coordinate.h"

typedef std::function<double(double, double, double, double)> DistanceFunction;
class CityMap {

private:
    std::map<std::string, Coordinate> cityMap;

    std::map<int, DistanceFunction> distanceFunctions;

    void insert(std::string cityName, double x, double y);

    void initDistanceFunctions();

public:

    CityMap() {
        this->initDistanceFunctions();
    }

    void initCitiesFromFileToMap(std::string filename);

    void closeCities(std::string cityName, double radius, int distanceCalc) const;


};