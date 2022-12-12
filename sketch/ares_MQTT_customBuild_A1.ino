#include <Ethernet.h>
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>
#include <SPI.h>
#include <MQTT.h>


byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xFD };
IPAddress ip(192, 168, 1, 159); // IP address, may need to change depending on network

IPAddress server_addr(20, 85, 184, 109); // IP of the MySQL *server* here

char user[] = "ares_svc_a1";       // MySQL user login username
char password[] = "gRaNdesThrOpocTo";        // MySQL user login password

// Sample query
char INSERT_DATA[] = "INSERT INTO ares.measurements (`sensor`, `location`, `temperature`, `humidity`) VALUES ('%s', '%s', '%s', %d)";
char query[128];
char temperature[10];

char deviceName[] = "A1";
char location[] = "MODENA";

EthernetClient net;
MySQL_Connection conn((Client *)&net);
MQTTClient client;

void connect() {
  Serial.print("connecting...");
  while (!client.connect("A1", "aresmqtt", "CA08Qk33rggTAUpr")) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\nconnected to MQTT!");

  client.subscribe("/MySql");
  client.publish("/MySQL", "Funzione di connessione");
  // client.unsubscribe("/hello");
}

void messageReceived(String &topic, String &payload) {
  Serial.println("incoming: " + topic + " - " + payload);

  // Note: Do not use the client in the callback to publish, subscribe or
  // unsubscribe as it may cause deadlocks when other things arrive while
  // sending and receiving acknowledgments. Instead, change a global variable,
  // or push to a queue and handle it in the loop after calling `client.loop()`.
}


void setup() {
  
  SPI.begin();

  // start the Ethernet connection
  Ethernet.begin(mac, ip);

  // Open serial communications and wait for port to open:

  Serial.begin(9600);

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

  client.begin("aresmqtt.cloud.shiftr.io", net);
  client.onMessage(messageReceived);
  client.publish("/MySQL", "Setup");

  connect();

}


void loop() {



  if (conn.connect(server_addr, 3306, user, password)) {
    delay(1000);
    // Initiate the query class instance
    MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);
    // Save
    dtostrf(50.12, 1, 1, temperature);
    sprintf(query, INSERT_DATA, deviceName, location, temperature, 10);
    // Execute the query
    cur_mem->execute(query);
    // Note: since there are no results, we do not need to read any data
    // Deleting the cursor also frees up memory used
    delete cur_mem;
    
    Serial.println("Data recorded SERIAL");
    
  }
  client.loop();

  if (!client.connected()) {
    connect();
  }
  client.publish("/MySQL", "Data written on DB");
  delay(10000);
}