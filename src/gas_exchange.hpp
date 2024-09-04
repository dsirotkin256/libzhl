#pragma once

#include "pressure.hpp"

/*
Alveolar gas equation
*/

pressure alv(const pressure &amb, const pressure &H2O_vapour, const double_t rq,
             const double_t inspired_gas_frac) {
  return {(amb.to_ata() - H2O_vapour.to_ata() +
           ((1 - rq) / rq) * CO2_PRESSURE.to_ata()) *
              inspired_gas_frac,
          pressure_unit::ATA};
}

/*
    Haldane equation
*/
pressure haldane(const pressure &alv, const pressure &pt0, const double_t k,
                 const double_t t) {
  return {alv.to_ata() + (pt0.to_ata() - alv.to_ata()) * exp(-k * t),
          pressure_unit::ATA};
}

/*
     Schreiner equation
*/

pressure schreiner(const pressure &alv0, const pressure &pt0, const double_t R,
                   const double_t k, const double_t t) {
  return {alv0.to_ata() + R * (t - 1 / k) -
              (alv0.to_ata() - pt0.to_ata() - R / k) * exp(-k * t),
          pressure_unit::ATA};
}

double_t sat_lim_A(const double_t t1) {
  return pressure{2, pressure_unit::ATA}.to_ata() / pow(t1 / 2, 1 / 3);
}

double_t sat_lim_B(const double_t t1) { return 1.005 - 1 / sqrt(t1 / 2); }
