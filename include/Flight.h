#pragma once
#include <string>

class Flight {
private:
    std::string origin;
    std::string destination;
    uint32_t price;

public:
    Flight();
    Flight(const std::string& origin, const std::string& destination, uint32_t price);

    std::string getOrigin() const;
    std::string getDestination() const;
    uint32_t getPrice() const;
};
