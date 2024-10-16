#define HOW_MANY_BTNS 3
const int pin_btn[HOW_MANY_BTNS] = {8, 9, 10};
bool last_state[HOW_MANY_BTNS];
void setup() {
  Serial.begin(9600);
  for (int i=0; i<HOW_MANY_BTNS; i++) {
    pinMode(pin_btn[i], INPUT); // INPUT_PULLUP for no resistor per button
    last_state[i] = false;
  }
}
void loop() {
  for (int i=0; i<HOW_MANY_BTNS; i++) {
    int state = digitalRead(pin_btn[i]);
    if (state != last_state[i]) {
      last_state[i] = state;
      if (state == LOW) {
        // released 'event'
        Serial.print("BTN Released: ");
        Serial.print(pin_btn[i]);
        Serial.print("-");
        Serial.println(state);
        // send signal, change display, etc
      }
    }
  }
  delay(100);
}
