#include <iostream>
#include <vector>

enum class GasType {
    Air,
    Nitrox,
    Helium
};

// Define gas-specific values using template specialization
// In Bühlmann's algorithm, a and b are coefficients that depend on the specific gas mixture being breathed.
// They affect the rate at which nitrogen and other inert gases are absorbed and released by the body's tissues.
// Different gases have different values for a and b due to their varying physiological effects.
// a: Represents the "a-value" for a specific gas mixture. It influences the rate of gas absorption by tissues.
// b: Represents the "b-value" for a specific gas mixture. It influences the rate of gas elimination from tissues.
template<GasType Gas>
struct GasValues {};

// Define values for Air
template<>
struct GasValues<GasType::Air> {
    static constexpr int a = 10000;
    static constexpr int b = 10000;
};

template<>
struct GasValues<GasType::Nitrox> {
    static constexpr int a = 12599;
    static constexpr int b = 8624;
};

template<>
struct GasValues<GasType::Helium> {
    static constexpr int a = 8618;
    static constexpr int b = 11430;
};

template<typename T, GasType Gas>
class BuhlmannZHL16C {
private:
    const int M = 8333;  // Represents the value 1/120 (minutes to seconds conversion)
    const int RG = 5000; // Represents the value 1/200 (cm to meters conversion)

    // Define half-time values for the tissue compartments
    std::vector<int> halfTimes = {200, 500, 1000, 2000, 4000, 8000};
    // Half-time values correspond to theoretical tissue compartments in the human body.
    // They represent the time required for a compartment to reach half saturation or desaturation.
    // The values are in seconds and represent tissue compartments with half-times of 2, 5, 10, 20, 40, and 80 minutes respectively.

public:
    // Constructor initializes half-times vector
    BuhlmannZHL16C() {
        // No additional code needed here
    }

    template<typename U>
    char calculatePressureGroup(int depth, int time) {
        char initialPressureGroup = 'A';

        int a = GasValues<Gas>::a;
        int b = GasValues<Gas>::b;

        // Loop through the half-times
        for (size_t i = 0; i < halfTimes.size(); ++i) {
            int halfTime = halfTimes[i];

            int gradient = (depth * RG / halfTime) - (depth * RG / time);

            // Check if gradient meets criteria for pressure group change
            if (gradient <= (a * time)) {
                initialPressureGroup = 'A' + i;
                break;
            }
        }

        return initialPressureGroup;
    }
};

int main() {
    BuhlmannZHL16C<int, GasType::Nitrox> model;

    int depth = 3000; // Depth in centimeters
    int time = 1800;  // Time in seconds

    char pressureGroup = model.calculatePressureGroup(depth, time);

    std::cout << "Initial Pressure Group: " << pressureGroup << std::endl;

    return 0;
}
