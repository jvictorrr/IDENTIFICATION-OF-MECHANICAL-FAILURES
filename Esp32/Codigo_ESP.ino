// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. 

#include <WiFi.h>
#include "AzureIotHub.h"
#include "Esp32MQTTClient.h"

#define RXD2 16
#define TXD2 17

#define INTERVAL 500
#define DEVICE_ID "Esp32Device"
#define MESSAGE_MAX_LEN 256
char *receber;
int i=0;

// Please input the SSID and password of WiFi
const char* ssid     = "Joao Victor- 2.4";
const char* password = "03061516";

/*String containing Hostname, Device Id & Device Key in the format:                         */
/*  "HostName=<host_name>;DeviceId=<device_id>;SharedAccessKey=<device_key>"                */
/*  "HostName=<host_name>;DeviceId=<device_id>;SharedAccessSignature=<device_sas_token>"    */
static const char* connectionString = "HostName=IotHubEsp.azure-devices.net;DeviceId=esp32;SharedAccessKey=HQP8wBVC97aj2AYqaxjijki3tkSmtT7Q/VUkjfSa0Xo=";
//const char *messageData = "{ \"Frequencia\":231.27,  \"Eixo X\":0000.38000, \"Eixo Y\":0000.4700,  \"Eixo Z\":0000.9800}";
//const char *messageData = "{\"F\":1304.23, \"X\":000.001, \"Y\":000.001, \"Z\":000.001}";
const char *messageData = "{\"Frequencia\":231.27, \"Eixo X\":0.38, \"Eixo Y\":0.47, \"Z\":000.01}";
static bool hasIoTHub = false;
static bool hasWifi = false;
int messageCount = 1;
static bool messageSending = true;
static uint64_t send_interval_ms;


//////////////////////////////////////////////////////////////////////////////////////////////////////////
// Utilities
static void InitWifi()
{
  Serial.println("Connecting...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  hasWifi = true;
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

static void SendConfirmationCallback(IOTHUB_CLIENT_CONFIRMATION_RESULT result)
{
  if (result == IOTHUB_CLIENT_CONFIRMATION_OK)
  {
    Serial.println("Send Confirmation Callback finished.");
  }
}

static void MessageCallback(const char* payLoad, int size)
{
  Serial.println("Message callback:");
  Serial.println(payLoad);
}

static void DeviceTwinCallback(DEVICE_TWIN_UPDATE_STATE updateState, const unsigned char *payLoad, int size)
{
  char *temp = (char *)malloc(size + 1);
  if (temp == NULL)
  {
    return;
  }
  memcpy(temp, payLoad, size);
  temp[size] = '\0';
  // Display Twin message.
  Serial.println(temp);
  free(temp);
}

static int  DeviceMethodCallback(const char *methodName, const unsigned char *payload, int size, unsigned char **response, int *response_size)
{
  LogInfo("Try to invoke method %s", methodName);
  const char *responseMessage = "\"Successfully invoke device method\"";
  int result = 200;

  if (strcmp(methodName, "start") == 0)
  {
    LogInfo("Start sending JSON data");
    messageSending = true;
  }
  else if (strcmp(methodName, "stop") == 0)
  {
    LogInfo("Stop sending JSON data");
    messageSending = false;
  }
  else
  {
    LogInfo("No method %s found", methodName);
    responseMessage = "\"No method found\"";
    result = 404;
  }

  *response_size = strlen(responseMessage) + 1;
  *response = (unsigned char *)strdup(responseMessage);

  return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
// Arduino sketch
void setup()
{

  int x=0;
          
  Serial.begin(115200);
  Serial2.begin(230400,SERIAL_8N1,RXD2,TXD2);
  Serial.println("ESP32 Device");
  Serial.println("Initializing...");

  // Initialize the WiFi module
  Serial.println(" > WiFi");
  hasWifi = false;
  InitWifi();
  if (!hasWifi)
  {
    return;
  }
  randomSeed(analogRead(0));

  Serial.println(" > IoT Hub");
  Esp32MQTTClient_SetOption(OPTION_MINI_SOLUTION_NAME, "GetStarted");
  Esp32MQTTClient_Init((const uint8_t*)connectionString, true);

  Esp32MQTTClient_SetSendConfirmationCallback(SendConfirmationCallback);
  Esp32MQTTClient_SetMessageCallback(MessageCallback);
  Esp32MQTTClient_SetDeviceTwinCallback(DeviceTwinCallback);
  Esp32MQTTClient_SetDeviceMethodCallback(DeviceMethodCallback);

  send_interval_ms = millis();
}

void loop()
{
   
  if (hasWifi)
  {
    if (messageSending && 
        (int)(millis() - send_interval_ms) >= INTERVAL)
    {
      // Send teperature data
      if(x==0)
      {
        EVENT_INSTANCE* message_init = Esp32MQTTClient_Event_Generate('[', MESSAGE);
     Esp32MQTTClient_SendEventInstance(message_init);
        
        };
      char messagePayload[MESSAGE_MAX_LEN];
      String str = Serial2.readString(); 
    int str_len = str.length(); 
      receber= new char[str_len];
      strcpy (receber, str.c_str());
      receber[str_len -1]=',';
      const char *json= receber;
        Serial.println(json);
     EVENT_INSTANCE* message = Esp32MQTTClient_Event_Generate(json, MESSAGE);
     Esp32MQTTClient_SendEventInstance(message);
     x=x+1;
      send_interval_ms = millis();


      if(x==200){
        EVENT_INSTANCE* message_init = Esp32MQTTClient_Event_Generate(']', MESSAGE);
     Esp32MQTTClient_SendEventInstance(message_init);
        
        };
    }
    else
    {
      Esp32MQTTClient_Check();
    }
      delay(10);
  }
}
