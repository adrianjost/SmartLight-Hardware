#define configFilePath "/userconfig.json"

bool shouldSaveConfig = false;
char hostname[64];

void saveConfigCallback () {
  shouldSaveConfig = true;
}

void setupSpiffs(){
  ("SmartLight-" + String(ESP.getChipId(), HEX)).toCharArray(hostname, 64);

  if (SPIFFS.begin()) {
      String("Step-1").toCharArray(hostname, 64);
    if (SPIFFS.exists(configFilePath)) {
      String("Step-2").toCharArray(hostname, 64);
      //file exists, reading and loading
      File configFile = SPIFFS.open(configFilePath, "r");
      if (configFile) {
        String("Step-3").toCharArray(hostname, 64);
        size_t size = configFile.size();
        // Allocate a buffer to store contents of the file.
        std::unique_ptr<char[]> buf(new char[size]);

        configFile.readBytes(buf.get(), size);
        DynamicJsonBuffer jsonBuffer;
        JsonObject& json = jsonBuffer.parseObject(buf.get());
        if (json.success()) {
          String("Step-4").toCharArray(hostname, 64);
          // copy from config to variable
          strcpy(hostname, json["hostname"]);
          //strcpy(lampType, json["lampType"]);
        }
      }
    }
  }
}

void setupWifi(){
  WiFiManager wm;
  wm.setDebugOutput(false);
  wm.setTimeout(300);
  wm.setSaveConfigCallback(saveConfigCallback);
  wm.setHostname(hostname);

  // custom hostname
  WiFiManagerParameter setting_hostname("hostname", "Devicename: (e.g. smartlight-xxx)", hostname, 64);
  wm.addParameter(&setting_hostname);
/*
  // configure type of connected light
  WiFiManagerParameter setting_lamptype_text("<p>Options: <code>NeoPixel</code>, <code>Analog RGB</code></p>");
  wm.addParameter(&setting_lamptype_text);

  WiFiManagerParameter setting_lamptype("lamptype", "Type of connected lamp:", lampType, 64);
  wm.addParameter(&setting_lamptype);
*/
  if(!wm.autoConnect("SmartLight Setup", "LightItUp")){
    // shut down till the next reboot
    //ESP.deepSleep(86400000000); // 1 Day
    ESP.deepSleep(600000000); // 10 Minutes
    ESP.reset();
  }

   //save the custom parameters to FS
  if (shouldSaveConfig) {
    DynamicJsonBuffer jsonBuffer;
    JsonObject& json = jsonBuffer.createObject();

    json["hostname"] = setting_hostname.getValue();
    //json["lampType"] = setting_lamptype.getValue();

    File configFile = SPIFFS.open(configFilePath, "w");
    json.printTo(configFile);
    configFile.close();
    shouldSaveConfig = false;
  }
}