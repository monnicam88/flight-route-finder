#pragma once
#include <iostream>
#include <string>
#include <limits>

#include "RouteService.h"
#include "Route.h"

bool isAllUpper(const std::string& str);
bool checkInputCorrectness(const std::string& str);
void checkResult(const std::vector<Route>& resultRoute);
void runConsoleDemo(const RouteService& routeService);
