////////////////////////////////////////////////
////////////////////////////////////////////  
/*
Zarvan Movdawalla
Version 0.1
BMP280 , RP2040
BARO ALTIMETER
DUAL CORE COMPATIBLE

STRICTLY not for commercial use. 
STRICTLY not for safety-critical/unsafe/hazardous applications.

Licensed under: CC BY-NC-SA

Disclaimer: Software is provided as-is, we make absolutely no claim or warranty towards its safety and reliability. It is purely an evaluation tool for advanced computing applications with microcontrollers.
Users acknowledge and agree that the use of the Software involves inherent risks, including but not limited to the risk of hardware damage, injury, or loss of property. 
Users assume all risks associated with the use of ZarvanM's AHRS-PID algorithm and software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.






*///////////////////////////////////////////////
////////////////////////////////////////////////
#include <BMP280_DEV.h>                           // Include the BMP280_DEV.h library

float temperature, pressure, altitude, adjustment,corrected_alt=0;            // Create the temperature, pressure and altitude variables
BMP280_DEV bmp280;                                // Instantiate (create) a BMP280_DEV object and set-up for I2C operation (address 0x77)

void setup() 
{
  Serial.begin(115200);  
  while(!Serial)
  {

  }                         // Initialise the serial port
  bmp280.begin(0x76);                                 // Default initialisation, place the BMP280 into SLEEP_MODE 
  bmp280.setPresOversampling(OVERSAMPLING_X16);    // Set the pressure oversampling to X4
  bmp280.setTempOversampling(OVERSAMPLING_X16);    // Set the temperature oversampling to X1
  bmp280.setIIRFilter(IIR_FILTER_8);              // Set the IIR filter to setting 4
  bmp280.setTimeStandby(TIME_STANDBY_05MS);     // Set the standby time to 2 seconds
  bmp280.setSeaLevelPressure(1009);


delay(1000);


  bmp280.startForcedConversion();                 // Start BMP280 continuous conversion in NORMAL_MODE 
  delay(100);
  bmp280.getCurrentMeasurements(temperature, pressure, altitude);    // Check if the measurement is complete   
    adjustment = altitude;


    Serial.print(temperature);                    // Display the results    
    Serial.print(F("*C   "));
    Serial.print(pressure);    
    Serial.print(F("hPa   "));
    Serial.print(adjustment);
    Serial.println(F("m")); 
    delay(3500); 
  




}

void loop() 
{




  bmp280.startForcedConversion();                 // Start BMP280 continuous conversion in NORMAL_MODE 
  bmp280.getMeasurements(temperature, pressure, altitude);    // Check if the measurement is complete
  
    
    corrected_alt = altitude - adjustment;




    Serial.print(temperature);                    // Display the results    
    Serial.print(F("*C   "));
    Serial.print(pressure);    
    Serial.print(F("hPa   "));
    Serial.print(corrected_alt);
    Serial.println(F("m"));  
  
}
