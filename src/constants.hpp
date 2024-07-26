#pragma once
#include <cstdint>

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
const volume_t MAX_VOLUME_RATIO = 1;