/*
Control luces y MP3
*/
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>


char wifi_name[] = "Martunio_1";
char wifi_password[] = "vicente1234"; // al menos 8 caracteres
WiFiServer server(8080);
boolean alreadyConnected = false;
String NumSerie = "CLIAMO0001";
char horarios[50];
uint8_t flash_buffer3[50]; //Se guarda los horarios
int indiceflash3 = 0;

void setup()
{
  Serial.begin(9600);
  // Arranca wifi y creamos la red propia con nombre SSID        //wifi_name y con wifi_password como contrase�a.
  Serial.print("Arrancando wifi...");
  WiFi.beginNetwork(wifi_name, wifi_password);
  Serial.println("Hecho.");
  server.begin();
  SerFlash.begin();  
  //Lee de la memoria con los horarios
  SerFlash.open("datos.txt", FS_MODE_OPEN_READ);
  for (int i=0; i<50;i++){
    flash_buffer3[i] = SerFlash.read(); 
  }
  SerFlash.close();
  for (int a=0;a<50;a++){
    if (flash_buffer3[a] != 0){
     horarios[a] = char(flash_buffer3[a]);
    }
  }
}

void loop()
{
  // Escucha para conexiones entrantes
  WiFiClient client = server.available();
  if (client) {
    if (!alreadyConnected) {
      // clead out the input buffer:
      client.flush();
      Serial.println("We have a new client");
      client.println("HELLO");
      alreadyConnected = true;
    }

    if (client.available() > 0) {
      // read the bytes incoming from the client:
      char thisChar = client.read();
      // echo the bytes back to the client:
      server.write(thisChar);
      
    }

  } 
}

