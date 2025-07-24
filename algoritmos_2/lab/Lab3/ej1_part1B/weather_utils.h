/** 
 *   @file weather_utils.h
 *   @brief Define methods to compare the weather properties
 */
#include <stdio.h>
#include "weather.h"
#include "weather_table.h"

/** 
 *   @brief Determines the minimum temperature recorded
 *   @details
 *   Weather file line must contain:
 *   <int> <int> <int> <unsigned int> <unsigned int> <unsigned int>
 *   @param[in] a table to determinate min temp
 */
int min_History(WeatherTable a);