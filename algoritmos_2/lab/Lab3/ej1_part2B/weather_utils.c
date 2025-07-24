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
 void max_per_year(WeatherTable a, int output[YEARS]){
    int maxT = a[0][0][0]._max_temp;
    for (unsigned int year = 0u; year < YEARS; ++year) {
        maxT = a[year][0][0]._max_temp; // Reiniciamos en cada año para poder chequear mejor las comparaciones
        for (month_t month = january; month <= december; ++month) {
            for (unsigned int day = 0u; day < DAYS; ++day) {
                if(a[year][month][day]._max_temp > maxT){
                    maxT = a[year][month][day]._max_temp;
                }
            }
        }
        output[year] = maxT;
    }
 }


