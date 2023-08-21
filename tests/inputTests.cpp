#define CATCH_CONFIG_MAIN  
#include "catch.hpp"
#include "../input/grid_config.json"  // Parser File
#include "../input/analysis.json"  // Parser File

TEST_CASE("Test JSON Parsing", "[JSON]") {
    SECTION("TESTING GRID VALUES") {
        json grid_params = read_json_file("grid_config.json");

        // DIMENSIONS
        std::vector<std::string> allowedDimensions = {"1D", "2D", "3D"};
        REQUIRE(std::find(allowedDimensions.begin(), allowedDimensions.end(), grid_params["PARAMETER_SETTINGS"]["dimension"].get<std::string>()) != allowedDimensions.end());

        // AXIS
        std::vector<std::string> allowedAxes = {"x", "y", "z", "xy", "xz", "yz", "yx", "zx", "zy"};
        REQUIRE(std::find(allowedAxes.begin(), allowedAxes.end(), grid_params["PARAMETER_SETTINGS"]["axis"].get<std::string>()) != allowedAxes.end());

        // FIELD PLOT
        std::vector<std::string> allowedFieldPlots = {"ex", "ey", "ez", "bx", "by", "bz", "E", "B"};
        REQUIRE(std::find(allowedFieldPlots.begin(), allowedFieldPlots.end(), grid_params["PARAMETER_SETTINGS"]["fieldPlot"].get<std::string>()) != allowedFieldPlots.end());

                // FIELD PLOT
        std::vector<std::string> allowedPointSource = {"ex", "ey", "ez", "bx", "by", "bz", "E", "B"};
        REQUIRE(std::find(allowedPointSource.begin(), allowedPointSource.end(), grid_params["PARAMETER_SETTINGS"]["pointSource"].get<std::string>()) != allowedPointSource.end());
        // BOUNDARY CONDITIONS
        std::vector<std::string> allowedBoundaryConditions = {"PML", "dirichlet", "Dirichlet"};
        REQUIRE(std::find(allowedBoundaryConditions.begin(), allowedBoundaryConditions.end(), grid_params["PARAMETER_SETTINGS"]["boundaryCondition"].get<std::string>()) != allowedBoundaryConditions.end());
    
        // PML LIMITS
        REQUIRE(source_params["PML"]["lowBoundary"][0].get<int>() < grid_params["GRID_SIZE"]["iMax"].get<int>() / 2); // Half of the grid size
        REQUIRE(source_params["PML"]["lowBoundary"][1].get<int>() < grid_params["GRID_SIZE"]["jMax"].get<int>() / 2);
        REQUIRE(source_params["PML"]["lowBoundary"][2].get<int>() < grid_params["GRID_SIZE"]["kMax"].get<int>() / 2);
        REQUIRE(source_params["PML"]["highBoundary"][0].get<int>() < grid_params["GRID_SIZE"]["iMax"].get<int>() / 2);
        REQUIRE(source_params["PML"]["highBoundary"][1].get<int>() < grid_params["GRID_SIZE"]["jMax"].get<int>() / 2);
        REQUIRE(source_params["PML"]["highBoundary"][2].get<int>() < grid_params["GRID_SIZE"]["kMax"].get<int>() / 2);

    }

    SECTION("TEST ANALYSIS VALUES") {
        json analysis_params = read_json_file("analysis_config.json");
        std::vector<std::string> alloweComparisonGraphs = {"zero_E", "mod_sinx", "mod_sinx_shift"};
        REQUIRE(std::find(allowedComparisonGraphs.begin(), allowedComparisonGraphs.end(), analysis_params["ANALYSIS"]["comparisonGraph"].get<std::string>()) != allowedComparisonGraphs.end());

    }
    SECTION("Test Reading Invalid JSON File") {
        REQUIRE_THROWS_AS(read_json_file("path_to_invalid.json"), json::parse_error);
    }

    SECTION("Test Reading Non-Existent JSON File") {
        REQUIRE_THROWS(read_json_file("non_existent_file.json"));
    }
}

TEST_CASE("Testing Parameter Setup", "[h]") {
        #include "../input/parameters.h"
           // Check if constants have not changed
        REQUIRE(source_params["Compile-Time Constants"]["PI"].get<double>() == Approx(3.14159265358979323846));
        REQUIRE(source_params["Compile-Time Constants"]["EPS_0"].get<double>() == Approx(8.8541878128e-12));
        REQUIRE(source_params["Compile-Time Constants"]["C_0"].get<double>() == Approx(299792458.0));
        REQUIRE(source_params["Compile-Time Constants"]["MU_0"].get<double>() == Approx(1.25663706212e-6));
        REQUIRE(source_params["Compile-Time Constants"]["IMP"].get<double>() == Approx(376.730313668));

}

