#include "ConsoleDemo.h"

bool isAllUpper(const std::string& str) {
    for (char c : str) {
        if (c < 'A' || c > 'Z')
            return false;
    }
    return true;
}

bool checkInputCorrectness(const std::string& str) {
    return str.length() == 3 && isAllUpper(str);
}

void checkResult(const std::vector<Route>& resultRoute) {
    if (!resultRoute.empty()) {
        for (const auto& route : resultRoute) {
            const auto& cities = route.getCities();

            for (size_t i = 0; i < cities.size(); ++i) {
                std::cout << cities[i];
                if (i < cities.size() - 1)
                    std::cout << ",";
            }
            std::cout << "," << route.getTotalPrice() << std::endl;
        }
    }
    else std::cout << "No routes" << std::endl;
}

void runConsoleDemo(const RouteService& routeService) {
    std::vector<Flight> flights = routeService.getFlights();

    std::cout << "Flights: " << std::endl;
    for (const auto& flight : flights) {
        std::cout << "  " << flight.getOrigin() << ","
            << flight.getDestination() << ","
            << flight.getPrice() << std::endl;
    }

    std::string origin, destination;

    std::cout << "Origin: ";
    std::cin >> origin;
    while (!checkInputCorrectness(origin)) {
        std::cout << "Origin: ";
        std::cin >> origin;
    }

    std::cout << "Destination: ";
    std::cin >> destination;
    while (!checkInputCorrectness(destination)) {
        std::cout << "Destination: ";
        std::cin >> destination;
    }
    std::cout << std::endl;

    // Subtask 1 function
    Route routes;
    std::vector<Route> resultRoute = routes.findPossibleRoutes(flights, origin, destination);

    checkResult(resultRoute);
}