#include <Ethernet.h>
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>
#include <SPI.h>
#include <MQTT.h>
#include "env.h"

// Define the size of the buffer for the HTTP request
#define REQ_BUF_SZ 70

// Set the device's MAC address
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xFD};

// Set the device's IP address
IPAddress ip(192, 168, 0, 159);

// Set the IP address of the MySQL server
IPAddress server_addr(20, 85, 184, 109);

// Sample query for inserting data into the MySQL database
char INSERT_DATA[] = "INSERT INTO ares.measurements (`sensor`, `location`, `temperature`, `humidity`) VALUES ('%s', '%s', '%s', %d)";

// Query buffer
char query[128];

// Buffer for storing temperature data
char temperature[10];

// Variables for storing random data
long randNumber;
int randHumidity;
float flrandNumber;

// Device name and location
char deviceName[] = DEVICE_ID;
char location[] = DEVICE_LOCATION;

// Variable for storing the last time data was sent
unsigned long lastMillis;

EthernetClient net;
EthernetClient net2;
EthernetServer server(80); // create a server at port 80
MySQL_Connection conn((Client *)&net2);
MQTTClient client;

char HTTP_req[REQ_BUF_SZ] = {0}; // buffered HTTP request stored as null terminated string
char req_index = 0;              // index into HTTP_req buffer

void connect()
{
  Serial.print("connecting...");
  while (!client.connect(DEVICE_ID, SHIFTR_USER, SHIFTR_SECRET))
  {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\nconnected to MQTT!");

  client.subscribe("/MySql");
  client.publish("/MySQL", "Funzione di connessione");
  // client.unsubscribe("/hello");
}

void messageReceived(String &topic, String &payload)
{
  Serial.println("incoming: " + topic + " - " + payload);

  // Note: Do not use the client in the callback to publish, subscribe or
  // unsubscribe as it may cause deadlocks when other things arrive while
  // sending and receiving acknowledgments. Instead, change a global variable,
  // or push to a queue and handle it in the loop after calling `client.loop()`.
}

void sendData(float randTemp, int randHumidity)
{

  if (conn.connect(server_addr, 3306, SQL_USER, SQL_PASSWORD))
  {
    delay(1000);
    // Initiate the query class instance
    MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);
    // Save
    dtostrf(randTemp, 1, 1, temperature);
    sprintf(query, INSERT_DATA, deviceName, location, temperature, randHumidity);
    // Execute the query
    cur_mem->execute(query);
    // Note: since there are no results, we do not need to read any data
    // Deleting the cursor also frees up memory used
    delete cur_mem;
    client.publish("/MySQL", "Temp:" + String(flrandNumber) + ", Hum: " + String(randHumidity));
    Serial.println("Data recorded SERIAL");
  }
}

void StrClear(char *str, char length)
{
  for (int i = 0; i < length; i++)
  {
    str[i] = 0;
  }
}

// searches for the string sfind in the string str
// returns 1 if string found
// returns 0 if stßy Abrefa ring not found
char StrContains(char *str, char *sfind)
{
  char found = 0;
  char index = 0;
  char len;

  len = strlen(str);

  if (strlen(sfind) > len)
  {
    return 0;
  }
  while (index < len)
  {
    if (str[index] == sfind[found])
    {
      found++;
      if (strlen(sfind) == found)
      {
        return 1;
      }
    }
    else
    {
      found = 0;
    }
    index++;
  }

  return 0;
}

void setup()
{

  randomSeed(analogRead(0));
  SPI.begin();

  // start the Ethernet connection
  Ethernet.begin(mac, ip);

  // Open serial communications and wait for port to open:

  Serial.begin(9600);

  // Check for Ethernet hardware present
  if (Ethernet.hardwareStatus() == EthernetNoHardware)
  {
    Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
    while (true)
    {
      delay(1); // do nothing, no point running without Ethernet hardware
    }
  }
  if (Ethernet.linkStatus() == LinkOFF)
  {
    Serial.println("Ethernet cable is not connected.");
  }

  client.begin(SHIFTR_ADDRESS, net);
  client.onMessage(messageReceived);
  client.publish("/MySQL", "Setup");

  connect();
}

void loop()
{

  randNumber = random(-1000, 5000);
  randHumidity =random(10,100);
  flrandNumber = (float)randNumber / 100.000;
  
  client.loop();
  if (!client.connected())
  {
    connect();
  }

  if (millis() - lastMillis >= 2 * 60 * 1000UL)
  {
    if (!client.connected())
    {
      connect();
    }
    Serial.println("Schedule ------");
    lastMillis = millis(); // get ready for the next iteration
    sendData(flrandNumber, randHumidity);
    Serial.println("********** ------");
  }

  EthernetClient net = server.available(); // try to get client

  if (net)
  { // got client?
    if (!client.connected())
    {
      connect();
    }
    boolean currentLineIsBlank = true;
    String postText = "";
    while (net.connected())
    {
      if (net.available())
      {                      // client data available to read
        char c = net.read(); // read 1 byte (character) from client

        // buffer first part of HTTP request in HTTP_req array (string)
        // leave last element in array as 0 to null terminate string (REQ_BUF_SZ - 1)
        if (req_index < (REQ_BUF_SZ - 1))
        {
          HTTP_req[req_index] = c; // save HTTP request character
          req_index++;
        }

        // print HTTP request character to serial monitor
        Serial.print(c);
        // last line of client request is blank and ends with \n
        // respond to client only after last line received
        if (c == '\n' && currentLineIsBlank)
        {

          net.println("HTTP/1.1 200 OK");
          // remainder of header follows below, depending on if
          // web page or XML page is requested
          // Ajax request - send XML file

          // open requested web page file
          if (StrContains(HTTP_req, "GET /refresh"))
          {
            net.println("HTTP/1.1 200 OK");
            sendData(flrandNumber,randHumidity);
            delay(2000);   // give the web browser time to receive the data
            net.stop(); // close the connection
            delay(2000);   // give the web browser time to receive the data
          }
        }
      }
    }

  }
  if (!client.connected())
  {
    connect();
  }
}
