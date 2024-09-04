#pragma once
#include "constants.hpp"
#include <iostream>

enum class pressure_unit { PA, ATA };

struct pressure {
  pressure_t _value;
  pressure_unit _unit;
  pressure(const pressure_t value, const pressure_unit unit)
      : _value{value}, _unit{unit} {}

  pressure_t to_pascal() const {
    return _unit == pressure_unit::ATA ? _value * STANDARD_ATMOSPHERIC_PA
                                       : _value;
  }

  pressure_t to_ata() const {
    return _unit == pressure_unit::PA ? _value / STANDARD_ATMOSPHERIC_PA
                                      : _value;
  }

  pressure_t operator()(const pressure_unit unit) const {
    return unit == pressure_unit::ATA ? to_ata() : to_pascal();
  }

  pressure_t operator()() const { return _value; }

  friend pressure operator+(const pressure &lhs, const pressure &rhs) {
    return {lhs.to_pascal() + rhs.to_pascal(), pressure_unit::PA};
  }

  friend pressure operator/(const pressure &lhs, const pressure &rhs) {
    return {lhs.to_pascal() / rhs.to_pascal(), pressure_unit::PA};
  }

  friend pressure operator*(const pressure &lhs, const pressure &rhs) {
    return {lhs.to_pascal() * rhs.to_pascal(), pressure_unit::PA};
  }

  friend auto operator<=>(const pressure &lhs, const pressure &rhs) {
    if (lhs.to_pascal() < rhs.to_pascal())
      return std::strong_ordering::less;
    if (lhs.to_pascal() > rhs.to_pascal())
      return std::strong_ordering::greater;
    return std::strong_ordering::equal;
  }

  friend std::ostream &operator<<(std::ostream &os, const pressure &p) {
    return os << p._value << (p._unit == pressure_unit::PA ? " Pa" : " ATA");
  }

  /*
      Based on the Dalton's Law we can backsolve partial pressure for a given
     gas composition from the gas mixture:

      P_total = Pi_1 + Pi_2 + ... + Pi_n;

      Where:
      - P_total is the total pressure of the gas mixture
      - Pi is the partial pressure of the i-th gas in the mixture
  */

  pressure partial_pressure(const volume_t gasVol) const {
    return pressure{gasVol * _value, _unit};
  }
};

const pressure STANDARD_ATMOSPHERIC_PRESSURE{STANDARD_ATMOSPHERIC_PA,
                                             pressure_unit::PA};

const pressure PPO2_MIN_LIMIT_PRESSURE{PPO2_MIN_LIMIT_PA, pressure_unit::PA};
const pressure PPO2_MAX_LIMIT_PRESSURE{PPO2_MAX_LIMIT_PA, pressure_unit::PA};
const pressure PPN2_MIN_LIMIT_PRESSURE{PPN2_MIN_LIMIT_PA, pressure_unit::PA};
const pressure PPN2_MAX_LIMIT_PRESSURE{PPN2_MAX_LIMIT_PA, pressure_unit::PA};
const pressure PPHE_MIN_LIMIT_PRESSURE{PPHE_MIN_LIMIT_PA, pressure_unit::PA};

const pressure CO2_PRESSURE{PPCO2_MAX_LIMIT_PA, pressure_unit::PA};