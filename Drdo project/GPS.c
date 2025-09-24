/*
 * GPS.c
 *
 *  Created on: 06-Apr-2022
 *      Author: PK
 *
 */

#include "uartStdio.h"
#include "soc_AM335x.h"
#include "uart_irda_cir.h"
#include "hw_types.h"
#include <string.h>
#include <stdlib.h>
#include "consoleUtils.h"

static char gps_str[300];

#define GPS_UART                  SOC_UART_1_REGS
#define GPS_UART_LSR              0x14

void ExtractLatLong(float *latitude, float *longitude)
{
    char *p;
//-------Extraction of Latitude (in Degrees.fractional_degress)------------------------------------------
        p=gps_str;
        while(*p!=',')
            p++;
        p++;
        while(*p!=',')
            p++;
        p++;
        *latitude= ((*p-48)*10 + (*(p+1)-48));   //latitude degrees
        p+= 2;
        (*latitude)+= (atof(p))/60;//latitude minutes plus fractional minutes converted into degrees and summed up
//-------Extraction of Longitude (in Degrees.fractional_degress)------------------------------------------
        while(*p!=',')
            p++;
        p++;
        while(*p!=',')
            p++;
        p++;
        *longitude= ((*p-48)*100 + (*(p+1)-48)*10 + (*(p+2)-48));
        p+= 3;
        (*longitude)+= (atof(p))/60;

//-------Extraction of Altitude: Not needed here hence commented------------------------------------------
//
//        while(*p!='M')
//            p++;
//        *(p-1)= 0;//terminate by Null
//        p-=2;
//        while(*p!=',')
//            p--;
//        p++;
//        altitude=atof(p);
////        while(*(p++)!='.');
////        if(*p >'4')
////            m++;
////        altitude=m;

}

/*
 * This function reads GNGGA string from NMEA sentences
 */
int GetGPS(void)
{
    char rxByte=0;
    char *q;
    unsigned int m;
    unsigned char comma_count=0;
    char fixQuality;
    while(comma_count!=10)
    {

        m=0;
        q= gps_str;
        while(rxByte!= '$')
        {
            if(HWREG(GPS_UART + GPS_UART_LSR) & 0x1)    //Check RX FIFO status in LSR
            {
                rxByte = UARTCharGetNonBlocking(GPS_UART);
                //UARTprintf("%c",rxByte);
            }
            m++;
            if(m > 600000)
            {
                *gps_str=0;
                ConsoleUtilsPrintf("GPS UART timed out\n");
                return -3;
            }
        }
        *q= rxByte;
        q++;
        while(rxByte!=',')
        {
            if(HWREG(GPS_UART + GPS_UART_LSR) & 0x1)    //Check RX FIFO status in LSR
            {
                rxByte = UARTCharGetNonBlocking(GPS_UART);
                *q= rxByte;
                q++;
            }
        }
        comma_count++;
        if(!strncmp(gps_str,"$GPGGA",6))
        {
            while(comma_count!=10)
            {
                if(HWREG(GPS_UART + GPS_UART_LSR) & 0x1)    //Check RX FIFO status in LSR
                {
                    rxByte = UARTCharGetNonBlocking(GPS_UART);
                    *q= rxByte;
                    if(rxByte==',')
                        comma_count++;
                    if(*(q-2)=='E')
                        fixQuality=*q;
                    q++;
                }
            }
            rxByte = UARTCharGet(GPS_UART);
            if(rxByte!='M')
            {
                *gps_str=0;
                ConsoleUtilsPrintf("GPS string timed out\n");
                return -1;
            }
            *q= rxByte;
            q++; *q=0;
            ConsoleUtilsPrintf("\nGPS String: %s\n",gps_str);
            if((fixQuality == '1')||(fixQuality == '2'))
                //ExtractLatLong(gps_str);
                ConsoleUtilsPrintf("GPS fix found\n");
            else
            {
                //TFP->longitude=0; TFP->latitude=0;
                ConsoleUtilsPrintf("GPS fix not found\n");
                return -2;
            }
        }
        else
        {
            rxByte= 0;
            comma_count=0;
        }
    }
    return 0;
}
