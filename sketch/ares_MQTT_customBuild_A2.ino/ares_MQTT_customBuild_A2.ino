#include <Ethernet.h>
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>
#include <SPI.h>
#include <MQTT.h>
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xFD };
IPAddress ip(192, 168, 137, 15); // IP address, may need to change depending on network
IPAddress server_addr(20, 85, 184, 109); // IP of the MySQL *server* here
char user[] = "ares_svc_a1";       // MySQL user login username
char password[] = "gRaNdesThrOpocTo";        // MySQL user login password
char INSERT_DATA[] = "INSERT INTO ares.measurements (`sensor`, `location`, `temperature`, `humidity`) VALUES ('%s', '%s', '%s', %d)";
char query[128];
char temperature[10];
char deviceName[] = "A2";
char location[] = "CESENA";
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
}
void messageReceived(String &topic, String &payload) {
  Serial.println("incoming: " + topic + " - " + payload);
}
void setup() {
   SPI.begin();
   Ethernet.begin(mac, ip);
  Serial.begin(9600);
  client.begin("aresmqtt.cloud.shiftr.io", net);
  client.onMessage(messageReceived);
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
