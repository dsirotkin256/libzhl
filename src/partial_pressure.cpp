#include "constants.hpp"
#include "pressure.hpp"
#include <algorithm>
#include <format>
#include <iostream>
#include <string_view>

struct gas_mixture {
  pressure _ambient;
  volume_t _O2;
  volume_t _N2;
  volume_t _He;

  /*
      Mixture calibration:
      - Compensate N2 and O2 with He based on safety constraints
   */
  explicit gas_mixture(const pressure &ambient)
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
};
template <>
struct std::formatter<gas_mixture> : std::formatter<std::string_view> {
  template <typename Context>
  auto format(const gas_mixture &m, Context &ctx) const {
    return formatter<std::string_view>::format(
        std::format("VO2 {}, VN2 {}, VHe {}", m._O2, m._N2, m._He), ctx);
  }
};

int main() {
  const pressure vapour{0.0627, pressure_unit::ATA};

  for (int p = 1; p <= 10; ++p) {
    const pressure amb{pressure_t(p), pressure_unit::ATA};

    const gas_mixture trimix(amb);
    const auto ppO2 = amb.partial_pressure(trimix._O2);
    const auto ppN2 = amb.partial_pressure(trimix._N2);
    const auto ppHe = amb.partial_pressure(trimix._He);
    std::cout << std::format("{}\n{}\nPPO2 {}, PPN2 {}, PPHe {}\n\n", amb,
                             trimix, ppO2, ppN2, ppHe);
  }

  return 0;
}