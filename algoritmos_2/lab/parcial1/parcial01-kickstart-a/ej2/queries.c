/*
  @file queries.c
  @brief Consultas sobre tablas de datos climáticos.
*/

#include "queries.h"

/**
 * @brief Total de lluvias de un año dado.
 *
 * @param a Tabla de datos climáticos.
 * @param year Año, entre FST_YEAR (1980) y LST_YEAR (2016).
 */
int year_rainfall(WeatherTable a, int year) {
  int sum = 0;
  for(unsigned int k_month = 0u; k_month < 12u;k_month++){
    for(unsigned int k_day = 0u; k_day < 28u;k_day++){
      sum = sum + a[year-FST_YEAR][k_month][k_day]._rainfall;
    }
  }

  return sum;
}
