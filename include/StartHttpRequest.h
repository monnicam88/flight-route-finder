#pragma once
#include "RouteService.h"
#include "Route.h"

#include "httplib.h"
#include "json.hpp"

using json = nlohmann::ordered_json;

void startHttpServer(const RouteService& routeService);
