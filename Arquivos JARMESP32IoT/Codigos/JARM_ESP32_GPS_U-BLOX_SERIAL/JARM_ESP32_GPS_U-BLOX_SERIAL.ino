#include "UBLOX.h"

// a uBlox object, which is on hardware
// serial port 1 with a baud rate of 115200
UBLOX gps(Serial,115200);

void setup() {
  // serial to display data
  Serial.begin(115200);

  // starting communication with the GPS receiver
  gps.begin();
}

void loop() {
  // checking to see if a good packet has
  // been received and displaying some
  // of the packet data
  if(gps.readSensor()) {
    Serial.print(gps.getYear());                ///< [year], Year (UTC)
    Serial.print("\t");
    Serial.print(gps.getMonth());               ///< [month], Month, range 1..12 (UTC)
    Serial.print("\t");
    Serial.print(gps.getDay());                 ///< [day], Day of month, range 1..31 (UTC)
    Serial.print("\t");
    Serial.print(gps.getHour());                ///< [hour], Hour of day, range 0..23 (UTC)
    Serial.print("\t");
    Serial.print(gps.getMin());                 ///< [min], Minute of hour, range 0..59 (UTC)
    Serial.print("\t");
    Serial.print(gps.getSec());                 ///< [s], Seconds of minute, range 0..60 (UTC)
    Serial.print("\t");
    Serial.print(gps.getNumSatellites());       ///< [ND], Number of satellites used in Nav Solution
    Serial.print("\t");
    Serial.print(gps.getLatitude_deg(),10);     ///< [deg], Latitude
    Serial.print("\t");
    Serial.print(gps.getLongitude_deg(),10);    ///< [deg], Longitude
    Serial.print("\t");
    Serial.println(gps.getMSLHeight_ft());      ///< [ft], Height above mean sea level
  }
}

