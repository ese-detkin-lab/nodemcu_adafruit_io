/***************************************************************************
 * Created by: Kim Luong, 2021-11-29
 ***************************************************************************/

#include "SimpleTimer.h"
 
/************************** Configuration ***********************************/

// edit the config.h tab and enter your Adafruit IO credentials
// and any additional configuration needed for WiFi, cellular,
// or ethernet clients.
#include "config.h"

/************************ Program Starts Here *******************************/

// Variables
int x = 0;
int y = 0;

// Adafruit Feeds
AdafruitIO_Feed *pressure = io.feed("pressure");
AdafruitIO_Feed *altitude = io.feed("altitude");

void sendSensor()
{

  x++;
  y++;
  
  pressure->save(p);
  delay(2000);
  altitude->save(a);
}


void setup() {

  // start the serial connection
  Serial.begin(115200);

  // wait for serial monitor to open
  while(! Serial);

  Serial.print("Connecting to Adafruit IO");

  // connect to io.adafruit.com
  io.connect();

  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  // we are connected
  Serial.println();
  Serial.println(io.statusText());

  
}

void loop() {

  // io.run(); is required for all sketches.
  // it should always be present at the top of your loop
  // function. it keeps the client connected to
  // io.adafruit.com, and processes any incoming data.
  io.run();

  // Adafruit IO is rate limited for publishing, so a delay is required in
  // between feed->save events. 
  sendSensor();
  delay(5000);

}
