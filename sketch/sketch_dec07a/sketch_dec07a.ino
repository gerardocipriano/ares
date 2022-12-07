#include <Ethernet.h>
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>
#include <SPI.h>


byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xFD };
IPAddress ip(192, 168, 1, 15); // IP address, may need to change depending on network

IPAddress server_addr(20,85,184,109);  // IP of the MySQL *server* here

char user[] = "ares_svc_a1";       // MySQL user login username
char password[] = "gRaNdesThrOpocTo";        // MySQL user login password

// Sample query
char INSERT_DATA[] = "INSERT INTO ares.measurements (sensor, temperature, humidity,) VALUES ('%s','%s','%s')";
char query[128] = "INSERT INTO `measurements` (`id`, `sensor`, `location`, `temperature`, `humidity`, `reading_time`) VALUES (NULL, 'A2', 'CESENA', '32.5', '98', CURRENT_TIMESTAMP)"; 
char temperature[10];
char deviceName[10];

EthernetClient client;
MySQL_Connection conn((Client *)&client);

void setup() {
  Ethernet.init(10);  // Most Arduino shields

  SPI.begin();

  // start the Ethernet connection

  Ethernet.begin(mac, ip);

  // Open serial communications and wait for port to open:

  Serial.begin(9600);

  while (!Serial) {

    ; // wait for serial port to connect. Needed for native USB port only

  }

  // Check for Ethernet hardware present

  if (Ethernet.hardwareStatus() == EthernetNoHardware) {

    Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");

    while (true) {

      delay(1); // do nothing, no point running without Ethernet hardware

    }

  }

  if (Ethernet.linkStatus() == LinkOFF) {

    Serial.println("Ethernet cable is not connected.");

  }

}


void loop() {

    Serial.println("Connecting...");
  if (conn.connect(server_addr, 3306, user, password)) {
    delay(1000);
    // Initiate the query class instance
    MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);
    // Save
    dtostrf(50.12, 1, 1, temperature);
    //sprintf(query, INSERT_DATA, A2, 24, temperature);
    snprintf(query, sizeof(query),"A2" , temperature, 10);
    // Execute the query
    cur_mem->execute(query);
    // Note: since there are no results, we do not need to read any data
    // Deleting the cursor also frees up memory used
    delete cur_mem;
    Serial.println("Data recorded.");
  }
}
