#include"CityMap.h"

int main() {

    auto cityMap = CityMap();

    cityMap.initCitiesFromFileToMap("data.txt");

    while (true) {
        std::string cityName;
        double radius;
        int distanceCalc;

        std::cout << "Please enter selected city name (with line break after it) or 0 to exit:\n";
        std::getline(std::cin, cityName);

        if (cityName == "0")
            break;

        std::cout << "Enter search radius: ";
        std::cin >> radius;

        // std::cout << "Enter distance calculation option (0: Euclidean, 1: Chebyshev, 2: Manhattan): ";
        std::cout << "Please enter the wanted norm (0 – L2, Euclidean distance, 1 – Linf, Chebyshev distance, 2 – L1, Manhattan distance):\n" ;
        std::cin >> distanceCalc;

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        try {
            cityMap.closeCities(cityName, radius, distanceCalc);
        }
        catch (const std::runtime_error& e) {
            //std::cerr << "Error: City not found." << std::endl;
            std::cerr << "ERROR: " << cityName << " isn't found in the city list. Please try again. "<< std::endl;
        }
        catch (const std::invalid_argument& e) {
            std::cerr << "ERROR: " << e.what() << std::endl;
        }
    }

    return 0;
}


