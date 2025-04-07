#include "Flight.h"

Flight::Flight() : price(0) {}

Flight::Flight(const std::string& origin, const std::string& destination, uint32_t price)
    : origin(origin), destination(destination), price(price) {}

std::string Flight::getOrigin() const {
    return origin;
}

std::string Flight::getDestination() const {
    return destination;
}

uint32_t Flight::getPrice() const {
    return price;
}