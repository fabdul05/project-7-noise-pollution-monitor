#pragma once
#include <string>
#include <chrono>

struct Measurement {
    std::chrono::system_clock::time_point timestamp; 
    double decibels;                                 
    std::string location;                            
};
