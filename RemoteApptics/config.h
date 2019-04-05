#ifndef CONFIG_H
#define CONFIG_H

#include <iostream>
#include <inttypes.h>

#define SUCCESS 1
#define FAIL 2

#define MAX_LOG_LINE 1000
#define LOG_FILE "/var/www/html/log.txt"

#define CONTROLLER_PORT 24000

#define SPI_ENTITY_SIZE 108
#define SPI_TRANSFER_SIZE 120
#define SPI_DATA_SIZE 116
#define CONTROL_DATA_GARBAGE_SIZE 38
#define GPS_STRING_SIZE 86

#define SFP_DATA_SIZE 24

#define ETHERNET_TRANSFER_SIZE 292
#define ETHERNET_ENTITY_SIZE 288
#define STREAM_DATA_SIZE 280
#define SENSOR_DATA_SIZE 17

#define FORWARD 1
#define BACKWARD 2
#define STOP 0


#endif // CONFIG_H
