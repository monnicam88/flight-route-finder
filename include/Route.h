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
