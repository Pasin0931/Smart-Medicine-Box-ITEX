void toSheet(){
  String urlFinal = "https://script.google.com/macros/s/" + GOOGLE_SCRIPT_ID + "/exec?" + "timeH=" + alarmH + "&timeM=" + alarmM + "&clickedH=" + numMinute + "&clickedM=" + numHour;
  Serial.print("POST data to spreadsheet:");
  Serial.println(urlFinal);
  HTTPClient http;
  http.begin(urlFinal.c_str());
  http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
  int httpCode = http.GET();
  // Serial.print("HTTP Status Code: ");
  // Serial.println(httpCode);

  String payload;
  if (httpCode > 0) {
    payload = http.getString();
    Serial.println("Payload: " + payload);
  }
  http.end();
  delay(100);
}