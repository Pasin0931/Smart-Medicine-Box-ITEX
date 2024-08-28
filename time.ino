void printLocalTime() {

  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("No time available (yet)");
    return;
  }

  strftime(timeHour, 3, "%H", &timeinfo);
  strftime(timeMinute, 3, "%M", &timeinfo);
  for (int i = 0; i <= 2; i++) {
    strHours += timeHour[i];
    strMinute += timeMinute[i];
  }
  numHour = strHours.toInt();
  numMinute = strMinute.toInt();

  if (setSetm == 1) {
    if (numMinute == setMinutes && numHour == setHours) {
      // Serial.println("MATCHHHH");
      leda(100, 0, 0);
      alarmH = numHour;
      alarmM = numMinute;
      while (true) {
        if (digitalRead(button) == 0) {
          LINE.notify("The user has noticed the alarm.");
          Serial.println("clicked");
          strHours.clear();
          strMinute.clear();
          strftime(timeHour, 3, "%H", &timeinfo);
          strftime(timeMinute, 3, "%M", &timeinfo);
          for (int i = 0; i <= 2; i++) {
            strHours += timeHour[i];
            strMinute += timeMinute[i];
          }
          numHour = strHours.toInt();
          numMinute = strMinute.toInt();
          delay(150);
          toSheet();
          i = i * 0;
          break;
        }
        // player.play(1);
        // delay(300);
        if (i < 1){
          LINE.notify("The alarm is setted!, waiting for user response.");
          i++;
        }
        Serial.println("ALARM!!!");
      }
      delay(1500);
      leda(0, 100, 0);
    } else {
      Serial.print(numHour);
      Serial.print(" : ");
      Serial.println(numMinute);
      delay(100);
      if (digitalRead(button) == 0) {
        leda(100, 100, 0);
        player.play(2);
        Serial.println("clicked");
        delay(5500);
      } else {
        delay(500);
        leda(0, 100, 0);
      }
    }
  } else {
    // Serial.println("Not recorded");
    if (digitalRead(button) == 0) {
      leda(100, 100, 0);
      player.play(2);
      // Serial.println("clicked");
      delay(5500);
    } else {
      delay(500);
      leda(0, 100, 0);
    }
  }

  strHours.clear();
  strMinute.clear();
}

// Callback function (get's called when time adjusts via NTP)
void timeavailable(struct timeval *t) {
  Serial.println("Got time adjustment from NTP!");
  printLocalTime();
}