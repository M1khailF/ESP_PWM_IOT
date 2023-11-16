#include <PWM.h>

const int BUFFER_SIZE = 50;
char buf[BUFFER_SIZE];

String msg = "";
String mas = "";

int val[] = {0, 0, 0, 0, 0};
const int pins[] = {2, 3, 6, 7};

int32_t frequency = 100;

void setup() {
  Serial.begin(115200);
  Serial2.begin(115200);
  InitTimersSafe();

  bool success1 = SetPinFrequencySafe(pins[0], frequency);
  bool success2 = SetPinFrequencySafe(pins[1], frequency);
  bool success3 = SetPinFrequencySafe(pins[2], frequency);
  bool success4 = SetPinFrequencySafe(pins[3], frequency);

  if (success1 && success2 && success3 && success4) {
    for (int i = 0; i <= sizeof(pins); i++) {
      pinMode(pins[i], OUTPUT);
    }
  }
}

void loop() {
  msg = "";
  if (Serial2.available() > 0) {
    int rlen = Serial2.readBytesUntil('#', buf, BUFFER_SIZE);
    for (int i = 0; i < rlen; i++)
      msg += buf[i];
  }

  mas = "";
  int k = 0;
  for (int i = 0; i <= msg.length(); i++) {
    if (msg[i] != ':') {
      mas += msg[i];
    }
    else {
      val[k] = mas.toInt();
      mas = "";
      k += 1;
    }
  }

  analogWrite(pins[0], map(val[0], 0, 100, 999, 1999));
  analogWrite(pins[1], map(val[1], 0, 100, 999, 1999));
  analogWrite(pins[2], map(val[2], 0, 100, 999, 1999));
  analogWrite(pins[3], map(val[3], 0, 100, 999, 1999));

  Serial.println("");
  Serial.print(map(val[0], 0, 100, 125, 250));
  Serial.print(" ");
  Serial.print(map(val[1], 0, 100, 125, 250));
  Serial.print(" ");
  Serial.print(map(val[2], 0, 100, 125, 250));
  Serial.print(" ");
  Serial.print(map(val[3], 0, 100, 125, 250));
}
