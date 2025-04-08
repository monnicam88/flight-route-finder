#include <algorithm>
#include "Route.h"

Route::Route() : totalPrice(0) {}

Route::Route(const std::vector<std::string>& cities, uint32_t totalPrice)
    : cities(cities), totalPrice(totalPrice) {}

std::vector<std::string> Route::getCities() const {
    return cities;
}

uint32_t Route::getTotalPrice() const {
    return totalPrice;
}

bool Route::operator<(const Route& other) const {
    return totalPrice < other.totalPrice;
}

std::vector<Route> Route::findPossibleRoutes(
    const std::vector<Flight>& flights,
    const std::string& origin,
    const std::string& destination,
    uint32_t maxFlights
) 
{
    std::vector<Route> routes;
    std::vector<std::string> visited;
    std::vector<std::string> currentPath;

    visited.push_back(origin);
    currentPath.push_back(origin);

    findRoutesRecursive(flights, origin, destination, visited, currentPath, 0, routes, maxFlights, 0);

    std::sort(routes.begin(), routes.end(),
        [](const Route& a, const Route& b) {
            if (a.getTotalPrice() == b.getTotalPrice()) 
                 return a.getCities().size() < b.getCities().size();
            return a.getTotalPrice() < b.getTotalPrice();
        });

    return routes;
}

void Route::findRoutesRecursive(
    const std::vector<Flight>& flights,
    const std::string& currentCity,
    const std::string& destination,
    std::vector<std::string>& visited,
    std::vector<std::string>& currentPath,
    uint32_t currentPrice,
    std::vector<Route>& routes,
    uint32_t maxFlights,
    uint32_t flightsTaken
) {
    if (currentCity == destination) {
        // maxFlight option not used
        if (!maxFlights)
            routes.push_back(Route(currentPath, currentPrice));
        // maxFlight option is used
        if (maxFlights && flightsTaken == maxFlights)
            routes.push_back(Route(currentPath, currentPrice));
        return;
    }

    if (maxFlights && flightsTaken >= maxFlights)
        return;

    for (const Flight& flight : flights) {
        if (flight.getOrigin() == currentCity) {
            std::string nextCity = flight.getDestination();

            if (std::find(visited.begin(), visited.end(), nextCity) != visited.end())
                continue;

            visited.push_back(nextCity);
            currentPath.push_back(nextCity);

            findRoutesRecursive(
                flights,
                nextCity,
                destination,
                visited,
                currentPath,
                currentPrice + flight.getPrice(),
                routes,
                maxFlights,
                flightsTaken + 1
            );

            visited.pop_back();
            currentPath.pop_back();
        }
    }
}
