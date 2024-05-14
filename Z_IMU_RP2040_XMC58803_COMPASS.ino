/*
original library example notes:
 * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT License (MIT)
 * @author      [dexian.huang](952838602@qq.com)
*/
/* ************************************************************************************** */

/*
zarvan's custom implementation notes:

Zarvan Movdawalla
Version 0.1
QMC5883 , RP2040
CF + AHRS 
DUAL CORE COMPATIBLE

STRICTLY not for commercial use. 
STRICTLY not for safety-critical/unsafe/hazardous applications.

Licensed under: MIT

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

*/


#include <DFRobot_QMC5883.h>

DFRobot_QMC5883 compass(&Wire, QMC5883_ADDRESS);

void setup()
{
  Serial.begin(9600);
  while (!compass.begin())
  {
    Serial.println("Could not find a valid 5883 sensor, check wiring!");
    delay(500);
  }

    Serial.println("Initialize QMC5883");
     compass.setRange(QMC5883_RANGE_2GA);
    // Serial.print("compass range is:");
    // Serial.println(compass.getRange());

     compass.setMeasurementMode(QMC5883_CONTINOUS);
    // Serial.print("compass measurement mode is:");
    // Serial.println(compass.getMeasurementMode());

     compass.setDataRate(QMC5883_DATARATE_200HZ);
    // Serial.print("compass data rate is:");
    // Serial.println(compass.getDataRate());

     compass.setSamples(QMC5883_SAMPLES_8);
    // Serial.print("compass samples is:");
    // Serial.println(compass.getSamples());
  

  delay(1000);
}
void loop()
{
  float declinationAngle = (0.0 + (0.0 / 60.0)) / (180 / PI);
  compass.setDeclinationAngle(declinationAngle);
  sVector_t mag = compass.readRaw();
  compass.getHeadingDegrees();
  Serial.print("X:");
  Serial.print(mag.XAxis);
  Serial.print(" Y:");
  Serial.print(mag.YAxis);
  Serial.print(" Z:");
  Serial.println(mag.ZAxis);
  Serial.print("Degress = ");
  Serial.println(mag.HeadingDegress);
  delay(100);
}
