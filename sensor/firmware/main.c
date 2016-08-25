/* Name: main.c
 * Author: HMTH(c) 
 */

#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>

#include "common_tasks.h"

#define wait 2000
#define numPts 200

const int interval = wait / numPts; //time between every data point based on the wait time and number of points
int values[numPts];     //array to contain all data points within the wait time

void turn_on_red (bool _is_on) {
	//TODO: implement
}

void turn_on_ir (bool _is_on) {
	//TODO: implement
}

int read_photo_sensor (void) {
	//TODO: implement
	return 1;
}

void InitRF_SPI (void) {
	//Set SCK, MISO, CSN and CE as outport
	//TODO: implement
	//Set MOSI as input, connects to nRF MISO
	//TODO: implement
	//CSN high to start with, nothing to be sent to the nRF yet!
	//TODO: implement
	//CE low to start with, nothing to send/receive yet
	//TODO: implement
}

int main(void)
{
	while (1) {
	  int minREDVal = 1023;  //minimum value taken
	  int maxREDVal = 0;     //maximum value taken
	  turn_on_red (true);  //Red on
	  turn_on_ir  (false); //IR off
	  for (int j = 0; j < numPts; j++) {
	    values[j] = read_photo_sensor();  //Read value of photodiode and assign to position j in values array
	    if (values[j] < minREDVal) {   //Assign current reading to minimum value if current reading is smaller than previous minimum
	      minREDVal = values[j];
	    }
	    else if (values[j] > maxREDVal) {  //Assign current reading to aximum value if current reading is largr than previous maximum
	      maxREDVal = values[j];
	    }
	    _delay_ms(interval);
	  }
	 
	  if (minREDVal == 0) { //To avoid all null values
	    minREDVal = 1;
	  }
	
	  int minIRVal = 1023;  //minimum value taken
	  int maxIRVal = 0;     //maximum value taken
	  turn_on_red (false); //Red off
	  turn_on_ir  (true);  //IR on
	  for (int j = 0; j < numPts; j++) {
	    values[j] = read_photo_sensor();
	    if (values[j] < minIRVal) {
	      minIRVal = values[j];
	    }
	    else if (values[j] > maxIRVal) {
	      maxIRVal = values[j];
	    }
	    _delay_ms(interval);
	  }
	
	  if (minIRVal == 0) { //To avoid all null values
	    minIRVal = 1;
	  }
	// TODO: transmit 40 bits of {minREDVal, maxREDVal, minIRVal, maxIRVal}	
	}

	return 0; /* Not reach */
}
