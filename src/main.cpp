#include <iostream>
#include <vector>

enum class GasType { Air, Nitrox, Helium };

// Define gas-specific values using template specialization
// In Bühlmann's algorithm, a and b are coefficients that depend on the specific
// gas mixture being breathed. They affect the rate at which nitrogen and other
// inert gases are absorbed and released by the body's tissues. Different gases
// have different values for a and b due to their varying physiological effects.
// a: Represents the "a-value" for a specific gas mixture. It influences the
// rate of gas absorption by tissues. b: Represents the "b-value" for a specific
// gas mixture. It influences the rate of gas elimination from tissues.
template <GasType Gas> struct GasValues {};

// Define values for Air
template <> struct GasValues<GasType::Air> {
  static constexpr uint64_t a = 10000ULL;
  static constexpr uint64_t b = 10000ULL;
};
template <> struct GasValues<GasType::Nitrox> {
  static constexpr uint64_t a = 12599ULL;
  static constexpr uint64_t b = 8624ULL;
};

template <> struct GasValues<GasType::Helium> {
  static constexpr uint64_t a = 8618ULL;
  static constexpr uint64_t b = 11430ULL;
};

template <GasType Gas> class BuhlmannZHL16C {
private:
  const uint64_t M =
      8333ULL; // Represents the value 1/120 (minutes to seconds conversion)
  const uint64_t RG =
      5000ULL; // Represents the value 1/200 (cm to meters conversion)

  // Define half-time values for the tissue compartments
  std::vector<uint64_t> halfTimes = {200, 500, 1000, 2000, 4000, 8000};
  // Half-time values correspond to theoretical tissue compartments in the human
  // body. They represent the time required for a compartment to reach half
  // saturation or desaturation. The values are in seconds and represent tissue
  // compartments with half-times of 2, 5, 10, 20, 40, and 80 minutes
  // respectively.

public:
  // Constructor initializes half-times vector
  BuhlmannZHL16C()
      : halfTimes{200ULL, 500ULL, 1000ULL, 2000ULL, 4000ULL, 8000ULL} {
    // No additional code needed here
  }

  uint64_t calculateNDL(uint64_t depth) {
    auto maxNDL = UINT64_MAX; // Initialize with a large value

    for (size_t i = 0; i < halfTimes.size(); ++i) {

      // Calculate the NDL based on Bühlmann formula
      uint64_t NDL = ((GasValues<Gas>::a * depth * RG) / halfTimes[i]) - M;

      // Update max NDL if a lower value is found
      if (NDL < maxNDL) {
        maxNDL = NDL;
      }
    }

    return maxNDL;
  }

  uint16_t calculatePressureGroup(uint64_t depth, uint64_t time) {
    uint16_t group = 0;

    // Loop through the half-times
    for (size_t i = 0; i < halfTimes.size(); ++i) {

      auto gradient = (depth * RG / halfTimes[i]) - (depth * RG / time);

      // Check if gradient meets criteria for pressure group change
      if (gradient <= (GasValues<Gas>::a * time)) {
        group = i;
        break;
      }
    }

    return group;
  }
};

int main() {
  BuhlmannZHL16C<GasType::Nitrox> model;

  auto depth = 3000ULL; // Depth in centimeters
  auto time = 3600ULL;  // Time in seconds

  auto pressureGroup = model.calculatePressureGroup(depth, time);

  auto ndl = model.calculateNDL(depth);

  std::cout << "Initial Pressure Group: " << pressureGroup << std::endl;
  std::cout << "No-Decompression Limit: " << ndl << std::endl;

  return 0;
}
