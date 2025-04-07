#include <iostream>
#include <string>
#include <limits>

#include "StartHttpRequest.h"
#include "ConsoleDemo.h"
#include "Flight.h"

int main() {
    RouteService routeService;

    if (!routeService.loadFlightsFromFile("flights-network_rows-55.txt")) {
        std::cerr << "Error loading flights from file" << std::endl;
        return 1;
    }

    // For Subtask 1
    //runConsoleDemo(routeService);

    // For Subtasks 2 and 3
    startHttpServer(routeService);

    return 0;
}
