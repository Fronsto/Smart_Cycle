// Name: GPS_Module.ino

// Setup the GPS sensor by starting the SoftwareSerial channel
void setupGPS()
{
  ss.begin(9600);
  Serial.println("Set up GPS done!");
}

// Function to get the GPS data from the stream
void getGPSData()
{
  while (ss.available() > 0) // while data is available
  {

    if (gps.encode(ss.read())) // read gps data
    {
      latitude = gps.location.lat(); // get the latitude value from the library
      lat_str = String(latitude, 6); // latitude location is stored in a string
      longitude = gps.location.lng(); // get the longitude value from the library
      lng_str = String(longitude, 6); // longitude location is stored in a string
      lats = lat_str;
      longs = lng_str;

      Serial.println("latitude: ");
      Serial.println(lat_str);
      Serial.println("longitude: ");
      Serial.println(lng_str);
    }
  }
}
