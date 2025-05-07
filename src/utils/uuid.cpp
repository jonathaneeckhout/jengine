#include <random>
#include <sstream>
#include <iomanip>

#include "jengine/utils/uuid.hpp"

std::string generate_uuid()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 15);
    std::uniform_int_distribution<> dis2(8, 11); // for variant bits

    std::stringstream ss;
    int i;
    ss << std::hex;
    for (i = 0; i < 8; i++)
        ss << dis(gen);
    ss << "-";
    for (i = 0; i < 4; i++)
        ss << dis(gen);
    ss << "-4"; // UUID version 4
    for (i = 0; i < 3; i++)
        ss << dis(gen);
    ss << "-";
    ss << dis2(gen); // variant bits 8, 9, A, or B
    for (i = 0; i < 3; i++)
        ss << dis(gen);
    ss << "-";
    for (i = 0; i < 12; i++)
        ss << dis(gen);
    return ss.str();
}