#include <parameters.h>


int main() {
    try {
        // Load configuration
        const auto config = loadConfig("grid_config.json"); // Automatically deduce type at compile-time

        // Extract grid resolution from config
        double lambda_min = config["GRID_RESOLUTION"]["lambdaMin"];
        std::string dimension = config["PARAMETER_SETTINGS"]["dimension"] + "D";

        // Compute grid resolutions
        double ds = lambda_min / 20.0;
        double dt = computeTimeStep(dimension, ds);

        std::cout << "Time step for " << dimension << ": " << dt << std::endl;
    } 
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}