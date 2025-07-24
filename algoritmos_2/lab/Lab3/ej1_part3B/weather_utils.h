/** 
 *   @file weather_utils.h
 *   @brief Define methods to compare the weather properties
 */
#include <stdio.h>
#include "weather.h"
#include "weather_table.h"

/** 
 *   @brief Determines the month of maximus precipitation (rainfall) recorded per year
 *   @param[in] a table to determinate the month of maximus rainfall per year
 *   @param[out] output array to store the month of maximus rainfall per year
 */
void max_prec_year(WeatherTable a, int output[YEARS]);