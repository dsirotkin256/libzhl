#pragma once
#include <cstdint>
#include <cmath>

using volume_t = double_t;
using pressure_t = double_t;

/* 
    Partial Pressures Guidelines with extra safety margin 
    US Navy Diving Manual (Revision 7, 2020)
*/
const pressure_t PPO2_MIN_LIMIT_PA = 21278;
const pressure_t PPO2_MAX_LIMIT_PA = 141855;
const pressure_t PPN2_MIN_LIMIT_PA = 0; 
const pressure_t PPN2_MAX_LIMIT_PA = 354638;
const pressure_t PPHE_MIN_LIMIT_PA = 0;
const pressure_t STANDARD_ATMOSPHERIC_PA = 101325;
const pressure_t CO2_PRESSURE_PA = 5340;
const volume_t MAX_VOLUME_RATIO = 1;

const double M0 = 1.6; // initial M-value
const double tau0 = 2.0; // initial half-time
const double GF_LOW = 0.3; // low gradient factor
const double GF_HIGH = 0.8; // high gradient factor