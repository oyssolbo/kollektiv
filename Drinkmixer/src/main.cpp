/**
 * @brief Short script for programming a 'sprit dispenser' to give the 
 *  desired amount of alcohol
 * 
 *  This project is currently written using stupid Arduino-code.
 *  If somebody are suicidal enough in the future, this should be 
 *  written using proper embedded.
 * 
 *  Project currently runs on Arduino Nano ATmega168
 * 
 *  Last edited: 
 *    Date: 22.10.21 
 *    Name: Øystein Solbø
 *    Abstract: Initial development
 */
#ifndef _USE_MATH_DEFINES
  #define _USE_MATH_DEFINES
#endif // _USE_MATH_DEFINES

#include <Arduino.h>
#include <math.h>
#include <float.h>

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
/**
 * NOTE: 
 *  Only change this variable!
 *  This variable defines the number of centiliters that it will
 *  deliver for each.
 * 
 * WARNING:
 *  Cannot guarantee that one will receive the exact number. There
 *  are some uncertainties in the calculations
 * 
 *  If this is set to an illogical value, it will be defaulted to 
 *  4 in the function @p check_valid_settings()
 */
#define NUM_CL 4
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////


// Constants for the alcohol-dispencer - measured or estimated
#define MAX_CL              10    // The maximum volume the dispencer will 
                                  // dish out per drink
#define NUM_CL_PER_ROTATION 0.4f  // Measure this more accurately
#define ANG_VEL             1     // Measure/estimate this more accurately
#define SWITCH_VOLTAGE      3.3f  // Measure the output from the switch                      

// Pins
#define SWITCH_PIN          10    // Random pin. Change later
#define MOTOR_PIN           11    // Random pin. Change later
#define LED_PIN             12    // Random pin. Change later


// Private functions
void setup_embedded();
float calculate_rotation_time();
int calculate_num_rotations(float num_cl);
bool check_valid_settings(float& num_cl);

/**
 * @brief Main function for checking the input. If the input has received
 *  the correct number of signals, the system will trigger an
 *  electrical signal to the motor to stop.
 */
int main()
{
  float num_cl;
  if(! check_valid_settings(num_cl))
  {
    // Some of the logic is either invalid or possibly errornous to default...
    return 1;
  }
  int max_rotations = calculate_num_rotations(num_cl);
  int num_rotations = 0;

  float rotation_time_ms = calculate_rotation_time();
  int half_rotation_time_ms = floor(rotation_time_ms / 2.0);

  // Setting up embedded and set the light high for debugging
  setup_embedded(); 
  digitalWrite(LED_PIN, HIGH);

  while(true)
  {
    // TODO: Check that 
    if(analogRead(SWITCH_PIN))
    {
      digitalWrite(LED_PIN, LOW);

      // Sleep 1/2 cycle to check if the signal is still high
      delay(half_rotation_time_ms);
      digitalWrite(LED_PIN, HIGH);

      if(analogRead(SWITCH_PIN))
      {
        // Impossible that it has rotated
        // Must be stationary on the switch
        num_rotations = 0;
        continue;
      }

      num_rotations++;
      if(num_rotations >= max_rotations)
      {
        // Send signal to the dispencer that max
        num_rotations = 0;
        digitalWrite(MOTOR_PIN, HIGH);
        delay(100);
        digitalWrite(MOTOR_PIN, LOW);
      }
    }
  }
  return 0;
}


/**
 * @brief Setup the pins using Arduino-library
 */
void setup_embedded()
{
  pinMode(LED_PIN, OUTPUT);  
  pinMode(MOTOR_PIN, OUTPUT);
  pinMode(SWITCH_PIN, INPUT); 
}


/**
 * @brief Check that the selected values are logically valid. For example
 *  that @p NUM_CL > 0, and @p NUM_CL <= @p MAX_CL
 * 
 * @param num_cl [out] Returns the volume that we can guarantee is feasable
 * 
 * @return true   If all settings valid or able to correct incorrect settings
 * @return false  If some combination of settings are infeasable 
 */
bool check_valid_settings(float& num_cl)
{
  num_cl = 0;
  if(NUM_CL_PER_ROTATION <= 0 || MAX_CL <= 0)
  {
    return false;
  }
  if(NUM_CL <= 0)
  {
    num_cl = (4.0f <= MAX_CL) ? 4.0f : MAX_CL;
  }
  else if(NUM_CL <= MAX_CL)
  {
    num_cl = NUM_CL;
  }
  else
  {
    num_cl = MAX_CL;
  }
  return true;
}


/**
 * @brief Calculate the time the motor uses to take one rotation
 */
float calculate_rotation_time()
{
  return 1.0 / ((float)ANG_VEL);
}

/**
 * @brief Calculate number of rotations to fill the desired amount
 *  of alcohol
 * 
 * @param num_cl The total amount to fill 
 * 
 * @warning The code will floor the number of iterations. For example
 *  if it is required with 3.2 rotations to fill up, it will only return
 *  3. If this is a major problem; deal with it or fix both the code and
 *  the mechanical structure yourself ;) 
 */
int calculate_num_rotations(float num_cl)
{
  return floor(num_cl / NUM_CL_PER_ROTATION);
}

