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
void max_prec_year(WeatherTable a, int output[YEARS]){
    
    unsigned int res_temp, prec_temp, month_c;
    
    for (unsigned int year = 0u; year < YEARS; ++year) {
        res_temp = 0;
        month_c = 1;
        for (month_t month = january; month <= december; ++month) {
            prec_temp = 0;
            for (unsigned int day = 0u; day < DAYS; ++day) {
                prec_temp = prec_temp + a[year][month][day]._rainfall;
            }
            if(prec_temp > res_temp){
                output[year] = month_c;
                res_temp = prec_temp;
            }
            month_c++;
        }
        
    }
 }


