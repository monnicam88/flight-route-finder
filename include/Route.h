#pragma once
#include <vector>
#include <string>
#include "Flight.h"

class Route {
private:
    std::vector<std::string> cities;
    uint32_t totalPrice;

public:
    Route();
    Route(const std::vector<std::string>& cities, uint32_t totalPrice);

    std::vector<std::string> getCities() const;
    uint32_t getTotalPrice() const;
    bool operator<(const Route& other) const;
    static std::vector<Route> findPossibleRoutes(
        const std::vector<Flight>& flights,
        const std::string& origin,
        const std::string& destination,
        uint32_t maxFlights = 0
    );

private:
/**
 * @brief Recursively finds all possible routes between two cities.
 *
 * This function performs a recursive search through the list of flights to find
 * all valid routes from the current city to the destination city. It takes into 
 * account the maximum number of allowed flights, if specified.
 * 
 * @param flights List of available flights.
 * @param currentCity The city from which the current search begins.
 * @param destination The target city to reach.
 * @param visited List of already visited cities to avoid cycles.
 * @param currentPath The current path being explored.
 * @param currentPrice Accumulated price of the current route.
 * @param routes Collection to store all valid found routes.
 * @param maxFlights Maximum number of allowed flights: 
 *                   - When it is 0 means maxFlights option is not used in the request
 *                   - When it is not 0 means maxFlights option is used in the request 
 *                     with certain value.
 * @param flightsTaken Number of flights taken so far in the current path.
 */
    static void findRoutesRecursive(
        const std::vector<Flight>& flights,
        const std::string& currentCity,
        const std::string& destination,
        std::vector<std::string>& visited,
        std::vector<std::string>& currentPath,
        uint32_t currentPrice,
        std::vector<Route>& routes,
        uint32_t maxFlights,
        uint32_t flightsTaken
    );
};
