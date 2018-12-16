#define configFilePath "/config.json"

bool shouldSaveConfig = false;
char hostname[32] = "SmartLight";

void saveConfigCallback () {
  shouldSaveConfig = true;
}

void setupSpiffs(){
  //clean FS, for testing
  //SPIFFS.format();

  if (SPIFFS.begin()) {
    if (SPIFFS.exists(configFilePath)) {
      //file exists, reading and loading
      File configFile = SPIFFS.open(configFilePath, "r");
      if (configFile) {
        size_t size = configFile.size();
        // Allocate a buffer to store contents of the file.
        std::unique_ptr<char[]> buf(new char[size]);

        configFile.readBytes(buf.get(), size);
        DynamicJsonBuffer jsonBuffer;
        JsonObject& json = jsonBuffer.parseObject(buf.get());
        if (json.success()) {
          strcpy(hostname, json["hostname"]); // copy from config to variable
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
  WiFiManagerParameter setting_hostname("hostname", "Devicename: (e.g. smartlight-xxx)", hostname, 32);
  wm.addParameter(&setting_hostname);

  /*
  // configure mode of connected light
  WiFiManagerParameter setting_lamptype_text("<code>1=NeoPixel, 2=Analog, 3=???</code>");
  wm.addParameter(&setting_lamptype_text);
  WiFiManagerParameter setting_lamptype("lamptype", "Type of connected lamp:", lampTypes[lampType], 32);
  wm.addParameter(&setting_lamptype);
  */

  //if(!wm.autoConnect("SmartLight-" + String(ESP.getChipId()), "LightItUp"){
  if(!wm.autoConnect("SmartLight Setup", "LightItUp")){
    // shut down till the next reboot
    //ESP.deepSleep(86400000000); // 1 Day
    ESP.deepSleep(6000); // 1 Minute
    ESP.reset();
  }

   //save the custom parameters to FS
  if (shouldSaveConfig) {
    DynamicJsonBuffer jsonBuffer;
    JsonObject& json = jsonBuffer.createObject();

    json["hostname"] = setting_hostname.getValue();

    /*
    const char* typeString = setting_lamptype.getValue();
    if(typeString == lampTypes[0]){
      json["lampType"] = 0;
    }
    if(typeString == lampTypes[1]){
      json["lampType"] = 1;
    }*/

    File configFile = SPIFFS.open(configFilePath, "w");
    json.printTo(configFile);
    configFile.close();
    shouldSaveConfig = false;
  }
}