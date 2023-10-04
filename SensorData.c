#include "SensorData.h"
#include "Utils.h"

#define MIN_EPOCH_TIMESTAMP 1644484800 // 9:00am EST
#define MAX_EPOCH_TIMESTAMP 1644488400 // 10:00am EST
#define MIN_TEMPERATURE 23.0
#define MAX_TEMPERATURE 40.0
#define MIN_HUMIDITY 60.0
#define MAX_HUMIDITY 80.0
#define MIN_STATION_PRESSURE 1050.0
#define MAX_STATION_PRESSURE 1170.0
#define MIN_WIND_SPEED 0.0
#define MAX_WIND_SPEED 10.0


void GenerateRandomSensorData(struct TS_SENSOR_DATA* pSensorData, int numDataPoints)
{
    for (int i = 0; i < numDataPoints; ++i) {
        pSensorData[i].epochTimestamp = GenerateRandomInt(MIN_EPOCH_TIMESTAMP, MAX_EPOCH_TIMESTAMP);
        pSensorData[i].temperature = GenerateRandomFloat(MIN_TEMPERATURE, MAX_TEMPERATURE);
        pSensorData[i].humidity = GenerateRandomFloat(MIN_HUMIDITY, MAX_HUMIDITY);
        pSensorData[i].stationPressure = GenerateRandomFloat(MIN_STATION_PRESSURE, MAX_STATION_PRESSURE);
        pSensorData[i].windSpeed = GenerateRandomFloat(MIN_WIND_SPEED, MAX_WIND_SPEED);
    }
}