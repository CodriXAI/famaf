/** 
 *   @file weather_utils.h
 *   @brief Define methods to compare the weather properties
 */
#include <stdio.h>
#include "weather.h"
#include "weather_table.h"

/** 
 *   @brief Determines the maximus temperature recorded per year
 *   @param[in] a table to determinate max temp per year
 *   @param[out] output array to store temperatures per year
 */
void max_per_year(WeatherTable a, int output[YEARS]);