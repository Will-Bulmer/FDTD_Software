#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <cmath>
#include <string>

using json = nlohmann::json;

namespace Constants {
    constexpr double PI = 3.14159265358979323846;
    constexpr double EPS_0 = 8.8541878128e-12;
    constexpr double C_0 = 299792458.0;
    constexpr double MU_0 = 1.25663706212e-6;
    constexpr double IMP = 376.730313668;
    constexpr double CURL_COEFF = EPS_0 * MU_0;
    constexpr double UPDATE_COEFF = 1.0 / CURL_COEFF;
}

// Load JSON from file
json loadConfig(const std::string& filename) {
    std::ifstream file(filename);  // Open the File
    json config;    // Declare JSON Object
    file >> config;     // Reads the JSON File
    return config;
}

// Compute the time step based on the provided dimension and grid resolutions
double computeTimeStep(const std::string& dimension, double ds, double ref_index = 1.0) {
    using namespace Constants;

    // Assumed dx = dy = dz = ds
    double oneD_dt = (ds * ref_index) / (4.0 * C_0);
    double twoD_dt = (ref_index / (4.0 * C_0)) * (1.0 / sqrt((1.0 / pow(ds, 2.0)) + (1.0 / pow(ds, 2.0))));
    double threeD_dt = (ref_index / (4.0 * C_0)) * (1.0 / sqrt((1.0 / pow(ds, 2.0)) + (1.0 / pow(ds, 2.0)) + (1.0 / pow(ds, 2.0))));

    if (dimension == "1D") return oneD_dt;
    if (dimension == "2D") return twoD_dt;
    if (dimension == "3D") return threeD_dt;

    throw std::runtime_error("Unexpected dimension value: " + dimension);
}





