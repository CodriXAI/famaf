/** 
 *   @file weather_utils.h
 *   @brief Define methods to compare the weather properties
 */
 #include <stdio.h>
 #include "weather_utils.h"
 #include "weather.h"
 #include "weather_table.h"

 /** 
  *   @brief Determines the minimum temperature recorded
  *   @details
  *   Weather file line must contain:
  *   <int> <int> <int> <unsigned int> <unsigned int> <unsigned int>
  *   @param[in] a table to determinate min temp
  */
int min_History(WeatherTable a){
    int minT = a[0][0][0]._min_temp;
    for (unsigned int year = 0u; year < YEARS; ++year) {
        for (month_t month = january; month <= december; ++month) {
            for (unsigned int day = 0u; day < DAYS; ++day) {
                if(a[year][month][day]._min_temp < minT){
                    minT = a[year][month][day]._min_temp;
                }
            }
        }
    }
    return minT;
}