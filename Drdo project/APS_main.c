/**
 * **************** ANTENNA POSITIONING SYSTEMS (APS) PROGRAM **********************
 * Program to calculate Azimuth and Elevation Look Angle for a ground SATCOM Antenna
 * that has to communicate with a given Geo-stationary Satellite then Position the
 * Antenna in 2-axis (Azimuth & Elevation) by driving two Stepper Motors in each axis
 * It takes only one input: Satellite Longitude in Degrees (+ve for East, -ve for West)
 * Reads GPS Coordinates of the site (Ground Station) itself from any GPS module
 * connected to UART1 of Beaglebone. Then performs calculation and positioning.
 ***********************************************************************************/
/**
 * This File: APS_main.c
 */
#include <math.h>
#include <stdlib.h>
#include "consoleUtils.h"
#include "APS_uart.h"
#include "stepper_gpio.h"
#include "stepper_functions.h"

#define AZ_MOTOR    SM1     //Stepper Motor1 is Azimuth Motor
#define EL_MOTOR    SM2     //Stepper Motor2 is Elevation Motor

float Az,El; //Antenna Azimuth & Elevation
float sat_long, site_long, site_lat; //satellite longitude, site longitude, site latitude
char rxBuff[20];
extern void ExtractLatLong(float *latitude, float *longitude);//Function to extract coordinates from $GPGGA sentence
extern int GetGPS(void);//Function to Read $GPGGA NMEA sentence from GPS module over UART1

/***** A Function to calculate Azimuth and Elevation Look Angles **********/
void CalAzimuthElevation(void)
{
    float G,L;
    G= (sat_long-site_long)*M_PI/180;
    L= site_lat*M_PI/180;
    Az= 180 + (atanf((tanf(G))/sinf(L)))*180/M_PI;
    El= (atanf((cosf(G)*cosf(L)-0.1512)/(sqrtf(1-powf((cosf(G)*cosf(L)),2.0)))))*180/M_PI;
}
/***** main function ********/
void main(void)
{
    int num_of_steps;
    ConfigConsoleUart();
    ConfigGPSUart();
    ConfigSMGPIOs();
    InitStepperMotors(0x01,0x01);
    ConsoleUtilsPrintf("\nAntenna Look Angle Calculator cum Positioner program running...\n");
    while(1)
    {
        ConsoleUtilsPrintf("\nEnter the Geo-stationary Satellite's Longitude: ");
        ConsoleUARTGetString(rxBuff);
        sat_long= atof(rxBuff);
        while(GetGPS());
        ExtractLatLong(&site_lat,&site_long);
        ConsoleUtilsPrintf("\nSite latitude= %f Deg\n",site_lat);
        ConsoleUtilsPrintf("\nSite longitude= %f Deg\n",site_long);
        CalAzimuthElevation();
        ConsoleUtilsPrintf("\nAntenna Azimuth= %f Deg\n",Az);
        ConsoleUtilsPrintf("Antenna Elevation= %f Deg\n",El);
        ConsoleUtilsPrintf("\nNow Positioning Antenna in Azimuth direction...\n");
        if(Az>180.0)
        {
            num_of_steps= DegreesToSteps(360.0-Az);
            ConsoleUtilsPrintf("Moving Az-motor %d steps counter clockwise...\n",num_of_steps);
            StepCCW(AZ_MOTOR,num_of_steps);
        }
        else
        {
            num_of_steps= DegreesToSteps(Az);
            ConsoleUtilsPrintf("Moving Az-motor %d steps clockwise...\n",num_of_steps);
            StepCW(AZ_MOTOR,num_of_steps);
        }
        ConsoleUtilsPrintf("\nNow Positioning Antenna in Elevation direction...\n");
        num_of_steps= DegreesToSteps(El);
        ConsoleUtilsPrintf("Moving El-motor %d steps clockwise...\n",num_of_steps);
        StepCW(EL_MOTOR,num_of_steps);
        ConsoleUtilsPrintf("\nPositioning done!\n");
    }

}
