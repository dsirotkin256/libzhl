#include "constants.hpp"
#include "gas_exchange.hpp"
#include "pressure.hpp"
#include <algorithm>
#include <iostream>

struct gas_mixture {
  pressure _ambient;
  volume_t _O2;
  volume_t _N2;
  volume_t _He;

  /*
      Mixture calibration:
      - Compensate N2 and O2 with He based on safety constraints
   */
  gas_mixture(const pressure &ambient)
      : _ambient{ambient},
        _O2{std::min(
                PPO2_MAX_LIMIT_PRESSURE.to_ata(),
                std::max(PPO2_MIN_LIMIT_PRESSURE.to_ata(),
                         PPO2_MIN_LIMIT_PRESSURE.to_ata() * ambient.to_ata())) /
            ambient.to_ata()},
        _N2{std::min(PPN2_MAX_LIMIT_PRESSURE.to_ata() / ambient.to_ata(),
                     MAX_VOLUME_RATIO - _O2)},
        _He{std::max(MAX_VOLUME_RATIO - _O2 - _N2,
                     PPHE_MIN_LIMIT_PRESSURE.to_ata())} {}

  friend std::ostream &operator<<(std::ostream &os,
                                  const gas_mixture &mixture) {
    return os << "VO2 " << mixture._O2 << ", "
              << "VN2 " << mixture._N2 << ", "
              << "VHe " << mixture._He;
  }
};

int main() {
  const pressure vapour{0.0627, pressure_unit::ATA};

  for (pressure_t p = 1; p <= 10; p += 0.5) {
    const pressure amb{pressure_t(p), pressure_unit::ATA};

    gas_mixture trimix(amb);

    std::cout << amb << '\n'
              << trimix << '\n'
              << "PPO2 " << amb.partial_pressure(trimix._O2) << ", "
              << "PPN2 " << amb.partial_pressure(trimix._N2) << ", "
              << "PPHe " << amb.partial_pressure(trimix._He) << "\n\n";
  }

  return 0;
}