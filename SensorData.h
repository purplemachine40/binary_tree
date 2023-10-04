#pragma once

struct TS_SENSOR_DATA {
	int epochTimestamp;
	float temperature;
	float humidity;
	float stationPressure;
	float windSpeed;
};

void GenerateRandomSensorData(struct TS_SENSOR_DATA* pSensorData, int numDataPoints);