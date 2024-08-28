BLYNK_WRITE(V0){
  int hours = param.asInt();
  // Serial.println(hours);
  setHours = hours;
}

BLYNK_WRITE(V1){
  int minutes = param.asInt();
  // Serial.println(minutes);
  setMinutes = minutes;
  // Serial.println(setMinutes);
}

BLYNK_WRITE(V2){
  int setm = param.asInt();
  // Serial.println(setm);
  setSetm = setm;
}

BLYNK_CONNECTED(){
  Blynk.virtualWrite(V0, 0); 
  Blynk.virtualWrite(V1, 0); 
  Blynk.virtualWrite(V2, 0); 
}