/* Name: main.c
 * Author: HMTH(c) 
 */

#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>

#define NULL 0
#define wait 2000
#define numPts 200

const int interval = wait / numPts; //time between every data point based on the wait time and number of points
int values[numPts];     //array to contain all data points within the wait time
double rTop; 
double rBot;
double rValues[10];     //small array to average out last 10 R Values calculated
int count = 0;          //count for R Values array

void turn_on_red (bool _is_on) {
	//TODO: implement
}

void turn_on_ir (bool _is_on) {
	//TODO: implement
}

int read_photo_sensor () {
	//TODO: implement
	return 1;
}

int main(void)
{
	while (1) {
	  int minVal = 1023;  //minimum value taken
	  int maxVal = 0;     //maximum value taken
	  turn_on_red (true);  //Red on
	  turn_on_ir  (false); //IR off
	  for (int j = 0; j < numPts; j++) {
	    values[j] = read_photo_sensor();  //Read value of photodiode and assign to position j in values array
	    if (values[j] < minVal) {   //Assign current reading to minimum value if current reading is smaller than previous minimum
	      minVal = values[j];
	    }
	    else if (values[j] > maxVal) {  //Assign current reading to aximum value if current reading is largr than previous maximum
	      maxVal = values[j];
	    }
	    _delay_ms(interval);
	  }
	 
	  if (minVal == 0) { //To avoid all null values
	    minVal = 1;
	  }
	
	  double rTop = log((double)minVal / (double)maxVal); //Top portion of the R Value formula ln(Redmin/Redmax)
	
	  minVal = 1023; //Resetting min and max 
	  maxVal = 0;
	  turn_on_red (false); //Red off
	  turn_on_ir  (true);  //IR on
	  for (int j = 0; j < numPts; j++) {
	    values[j] = read_photo_sensor();
	    if (values[j] < minVal) {
	      minVal = values[j];
	    }
	    else if (values[j] > maxVal) {
	      maxVal = values[j];
	    }
	    _delay_ms(interval);
	  }
	
	  if (minVal == 0) { //To avoid all null values
	    minVal = 1;
	  }
	
	  double rBot = log((double)minVal / (double)maxVal); //Bottom portion of the R Value formula ln(IRmin/IRmax)
	  double rValue = rTop / rBot; //R Value formula
	  rValues[count] = rValue;     //Assign current R value to position count in array
	
	  if (rValues[9] != NULL) { //if the array is full
	    double rSum = 0;
	    for (int i = 0; i < 10; i++) {
	      rSum = rSum + rValues[i]; //Sum of all R Values in array for average
	    }
	    double rAvg = rSum / 10;    //Average of R Values
		
	   //SpO2 = rAvg*100 %	
	   // transmit new SpO2 value
	  }
	  else {                        //If array not full, display current R Value
		// transmit current rValue value
	  }
	
	  count++; //Increase count
	  count = count % 10; //To make sure count goes from 0 to 9 and back to 0 (circular array) 
	}
}
