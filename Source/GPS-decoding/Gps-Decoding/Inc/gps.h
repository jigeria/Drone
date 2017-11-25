#ifndef _GPS_H
#define _GPS_H

#include "stm32f4xx_hal.h"
#include "usart.h"
#include "gpio.h"
#include "math.h"
#include "string.h"

#define RECEIVE_BUFF_SIZE 8
#define GPS_BUFF_SIZE 1024
#define NAV_POSLLH_SIZE 36
#define NAV_POSLLH_LENGTH 28
#define NAV_VELNED_SIZE 44
#define NAV_VELNED_LENGTH 36

#define PI 3.141592653589

#define STD_LONGITUDE_DEGREES 127
#define STD_LONGITUDE_MINUTE 24
#define STD_LONGITUDE_SECOND 51

#define STD_LATITUDE_DEGREES 36
#define STD_LATITUDE_MINUTE 19
#define STD_LATITUDE_SECOND 10

#define LATITUDE_DEGREES_DISTANCE 111
#define LATITUDE_MINUTE_DISTANCE 1.85
#define LATITUDE_SECOND_DISTANCE 30.8


typedef union _GPS_POSLLH_UNION
{
	uint8_t       buff[4];
	float         data;
	int           data_int;

}PosllhUnion;

typedef union _GPS_VELNED_UNION
{
	uint8_t       buff[4];
	float         data;
	int           data_int;

}VelnedUnion;

typedef struct _GPS_COMMON
{
  uint8_t	data_dma_receive_buff[RECEIVE_BUFF_SIZE];
  uint8_t       packet_rx_data_buff[GPS_BUFF_SIZE];
  uint8_t	rx_data_buff[GPS_BUFF_SIZE];

  uint8_t	CK_A;
  uint8_t	CK_B;

  int           packet_complete_flag;
  int           check_sum_complete_flag;
  int           rx_buff_idx;
  int           start_packet_idx;
  int           read_rx_pause;
  int           buff_idx;

  int	      Gps_data_buff[9];

}GpsCommon;

typedef struct _GPS_POSLLH
{
  float         time;
  float         ellipsoid;
  float         mean_sealevel;
  
  int           longitude_degrees;
  int           longitude_minute;
  float         longitude_second;
  
  int           latitude_degrees;
  int           latitude_minute;
  float         latitude_second;
  
  float         longitude_degrees_distance;
  float         longitude_minute_distance;
  float         longitude_second_distance;
  
  int           longitude_minute_gap;
  int           longitude_degrees_gap;
  float         longitude_second_gap;
  
  int           latitude_degrees_gap;
  int           latitude_minute_gap;
  float         latitude_second_gap;
  
  float         longitude_distance;
  float         latitude_distance;
  
  float         distance;
  
}GpsPosllh;

typedef struct _GPS_VELNED
{
  float         vel_N;
  float         vel_E;
  float         vel_D;

  float         speed;
  float         gSpeed;         //ground speed
  float         heading;

  float         sAcc;           //speed accuracy estimate
  float         cAcc;           //course/heading accuracy estimate

}GpsVelned;

extern		GpsCommon gps_posllh;
extern		GpsCommon gps_velned;
extern		GpsPosllh posllh_data;
extern		GpsVelned velned_data;
extern          PosllhUnion posllh_union;
extern		VelnedUnion velned_union;

int             calculate_gps_check_sum(struct GpsCommon gps_protocol, int NAV_SIZE);
void            gps_init();
void            decode_gps_posllh_packet();
void		decode_gps_velned_packet();
void            check_gps_packet(struct GpsCommon gps_protocol);

#endif