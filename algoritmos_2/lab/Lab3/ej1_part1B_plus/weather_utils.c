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
    char meses[12][4] = {
        "Ene",
        "Feb",
        "Mar",
        "Abr",
        "May",
        "Jun",
        "Jul",
        "Ago",
        "Sep",
        "Oct",
        "Nov",
        "Dic"
    };
    int minT = a[0][0][0]._min_temp;
    date dateMin;
    for (unsigned int year = 0u; year < YEARS; ++year) {
        for (month_t month = january; month <= december; ++month) {
            for (unsigned int day = 0u; day < DAYS; ++day) {
                if(a[year][month][day]._min_temp < minT){
                    minT = a[year][month][day]._min_temp;
                    dateMin.year = year;
                    dateMin.month = month;
                    dateMin.day = day;
                }
            }
        }
    }
    printf("Fecha donde se registró la mínima temperatura en Córdoba: \n");
    printf("%d / %s / %d \n", dateMin.day+1,meses[dateMin.month],dateMin.year+1980);
    return minT;
}