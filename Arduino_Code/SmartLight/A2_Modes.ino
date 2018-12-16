struct singleMode {
  byte id;
  RGB colors[100] = {};
  int durations [100] = {};
  bool fade;
};

class Mode {
  private:
    int _currentMode;
    singleMode _savedModes[10] = {};
  public:
     Mode();
     int nextMode();
     void setMode(int id);
     void setLastMode();
     int currentMode();
     void saveModes(String raw);
};

Mode::Mode() {
  // read currentMode & savedModes from EEPROM
  this->_currentMode = 0;
}

int Mode::nextMode() {
  return 1;
}

void Mode::setMode(int id) {
  this->_currentMode = id;
  return;
}

void Mode::setLastMode() {
  return;
}

int Mode::currentMode() {
  return 1;
}

void Mode::saveModes(String raw){
  DynamicJsonBuffer jsonBuffer(JSON_ARRAY_SIZE(300)); // 50
  JsonObject& modes = jsonBuffer.parseObject(raw);
  if (modes.success()){
    /*for( const auto& value : modes.as<JsonArray>() ) {
        Serial.println(value.as<char*>());
        RGB colors[100] = {};
        int durations[100] = {};
        int i = 0
        for( const auto& color : value["colors"].as<JsonArray>() ) {
            colors[i] = RGB{color["r"],color["g"],color["b"]};
            ++i;
        }
        int i = 0
        for( const auto& duration : value["durations"].as<JsonArray>() ) {
            durations[i] = <int>duration;
            ++i;
        }
        singleMode temp = {<byte>value["id"], colors, durations};
    }*/
  }
}
