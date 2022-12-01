#include <Ethernet.h>
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>

byte mac_addr[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

IPAddress server_addr(20,85,184,109);  // IP of the MySQL *server* here
char user[] = "ares_svc_a1";       // MySQL user login username
char password[] = "gRaNdesThrOpocTo";        // MySQL user login password

// Sample query
char INSERT_DATA[] = "INSERT INTO ares.measurements (temperature, humidity) VALUES ('%s','%s')";
char query[128];
char temperature[10];

EthernetClient client;
MySQL_Connection conn((Client *)&client);

void setup() {
  Serial.begin(115200);
  while (!Serial); // wait for serial port to connect
  Ethernet.begin(mac_addr);
  Serial.println("Connecting...");
  if (conn.connect(server_addr, 3306, user, password)) {
    delay(1000);
    // Initiate the query class instance
    MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);
    // Save
    dtostrf(50.125, 1, 1, temperature);
    //sprintf(query, INSERT_DATA, 24, temperature);
    snprintf(query, sizeof(query), temperature, 10);
    // Execute the query
    cur_mem->execute(query);
    // Note: since there are no results, we do not need to read any data
    // Deleting the cursor also frees up memory used
    delete cur_mem;
    Serial.println("Data recorded.");
  }
  else
    Serial.println("Connection failed.");
  conn.close();
}


void loop() {
}