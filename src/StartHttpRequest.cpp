#include <iostream>
#include <string>

#include "StartHttpRequest.h"

void startHttpServer(const RouteService& routeService) {
    httplib::Server server;

    server.Post("/routes", [&routeService](const httplib::Request& req, httplib::Response& res) {
        json requestBody;

        try {
            requestBody = json::parse(req.body);
        }
        catch (const std::exception&) {
            res.set_content("{\"message\": \"Unable to parse request body!\"}", "application/json");
            res.status = 400;
            return;
        }

        std::string origin, destination;

        if (!requestBody.contains("origin")) {
            res.set_content("{\"message\": \"Missing origin input!\"}", "application/json");
            res.status = 400;
            return;
        }
        if (!requestBody["origin"].is_string()) {
            res.set_content("{\"message\": \"The input for origin is not in the correct format!\"}", "application/json");
            res.status = 400;
            return;
        }
        origin = requestBody["origin"].get<std::string>();

        if (!requestBody.contains("destination")) {
            res.set_content("{\"message\": \"Missing destination input!\"}", "application/json");
            res.status = 400;
            return;
        }
        if (!requestBody["destination"].is_string()) {
            res.set_content("{\"message\": \"The input for destination is not in the correct format!\"}", "application/json");
            res.status = 400;
            return;
        }
        destination = requestBody["destination"].get<std::string>();

        if (origin == destination) {
            res.set_content("{\"message\": \"The origin and destination cannot be the same!\"}", "application/json");
            return;
        }

        // [SOLVED] TODO: Future optimization to remove "isMaxFlightsUsed" flag... 
        // See the "Issues" section -> Closed issues
        uint32_t maxFlights = 0;
        if (requestBody.contains("maxFlights")) {
            if (!requestBody["maxFlights"].is_number_unsigned() || requestBody["maxFlights"] == 0) {
                res.set_content("{\"message\": \"The input for maxFlights is not in the correct format!\"}", "application/json");
                res.status = 400;
                return;
            }

            uint64_t maxFlightsCheck = requestBody["maxFlights"].get<uint64_t>();

            if (maxFlightsCheck > std::numeric_limits<uint32_t>::max()) {
                res.set_content("{\"message\": \"You have gone over the maximum amount for the maxFlight filter!\"}", "application/json");
                res.status = 400;
                return;
            }

            maxFlights = static_cast<uint32_t>(maxFlightsCheck);
        }

        std::vector<Route> routeList = routeService.findRoutes(origin, destination, maxFlights);

        if (routeList.empty()) {
            res.set_content("{\"message\": \"There are no routes!\"}", "application/json");
            return;
        }

        json response = json::array();
        for (const Route& route : routeList) {
            json routeJson = {
                {"route", route.getCities()},
                {"price", route.getTotalPrice()}
            };
            response.push_back(routeJson);
        }

        res.set_content(response.dump(), "application/json");
        });

    std::cout << "HTTP server started on http://localhost:8080" << std::endl;
    std::cout << "Press Ctrl+C to stop the server" << std::endl;
    server.listen("localhost", 8080);
}
