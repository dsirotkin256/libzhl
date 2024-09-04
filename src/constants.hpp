#pragma once

#include <cmath>
#include <cstdint>

/*
    Partial Pressures Guidelines with extra safety margin
    US Navy Diving Manual (Revision 7, 2020)
*/

using volume_t = double_t;
using pressure_t = double_t;
const pressure_t PPO2_MIN_LIMIT_PA = 21278;
const pressure_t PPO2_MAX_LIMIT_PA = 141855;
const pressure_t PPN2_MIN_LIMIT_PA = 0;
const pressure_t PPN2_MAX_LIMIT_PA = 354638;
const pressure_t PPHE_MIN_LIMIT_PA = 0;
const pressure_t PPCO2_MIN_LIMIT_PA = 0;
const pressure_t PPCO2_MAX_LIMIT_PA = 5340;
const pressure_t STANDARD_ATMOSPHERIC_PA = 101325;
const volume_t MAX_VOLUME_RATIO = 1;

/*
    Buhlmann model constants
*/
const double M0 = 1.6;      // initial M-value
const double tau0 = 2.0;    // initial half-time
const double GF_LOW = 0.3;  // low gradient factor
const double GF_HIGH = 0.8; // high gradient factor

/*
    Thermal conductivity at 1 ATA
*/

const double_t O2_TC = 264;
const double_t CO2_TC = 164;
const double_t N2_TC = 259;
const double_t AR_TC = 177;
const double_t NE_TC = 489;
const double_t HE_TC = 1500;
const double_t H2_TC = 1810;
