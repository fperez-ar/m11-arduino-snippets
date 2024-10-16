#include <Keyboard.h>
#define DEBUG true
#define HOW_MANY_BTNS 4
#define INTERKEY_DELAY 50
// normal mapping buttons
const uint8_t pin_btn[HOW_MANY_BTNS] = {5,6,7,8};
uint8_t last_state[HOW_MANY_BTNS];

// 2 extra buttons, on/off, config switch 
const uint8_t pin_kswitch,  pin_cfgswitch;
uint8_t lstate_kswitch, lstate_cfgswitch;

// configurations
const uint8_t cfgs[][8] = {
  { KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5, KEY_F6, KEY_F7, KEY_F8 },
  { KEY_KP_1, KEY_KP_2, KEY_KP_3, KEY_KP_4, KEY_KP_5, KEY_KP_6, KEY_KP_7, KEY_KP_8 }
};
uint8_t config_size = 4, config_index = 0;

void setup() {
#if DEBUG
  Serial.begin(9600);
#endif
  pinMode(pin_cfgswitch, INPUT_PULLUP);
  for (uint8_t i=0; i<HOW_MANY_BTNS; i++) {
    pinMode(pin_btn[i], INPUT); // INPUT_PULLUP for no resistor per button
    last_state[i] = 0;
  }
}

void loop() {
  uint8_t cfgswitch_state = digitalRead(pin_cfgswitch);
  if (cfgswitch_state != lstate_cfgswitch) { // state change
    if (cfgswitch_state == LOW) { // on release
      lstate_cfgswitch = cfgswitch_state;
      switch_config();
    }
  }

  for (uint8_t i=0; i<HOW_MANY_BTNS; i++) {
    uint8_t state = digitalRead(pin_btn[i]);
    // button(i, state);
    if (btn_state(state, i)) {
      last_state[i] = state;
    }
  }
  delay(INTERKEY_DELAY);
}

bool btn_state(uint8_t current, uint8_t idx) {
  const bool state_changed = current != last_state[idx];
  if (state_changed) {
    if (current == HIGH) { // pressed
      on_pressed(idx);
    }
    if (current == LOW) { // released
      on_released(idx);
    }
  }
  return state_changed;
}

/* void button(uint8_t idx, uint8_t current) {
  if (current != last_state[idx]) {
    last_state[idx] = current;
    if (current == HIGH) { // pressed
      switch_config();
    }
    if (current == LOW) { // released
  #if DEBUG
      Serial.print("BTN Released: ");
      Serial.print(pin_btn[idx]);
      Serial.print("-");
      Serial.println(current);
  #endif
    }
  }
} */

void on_released(uint8_t idx) {
  #if DEBUG
      Serial.print(" - Released: ");
      Serial.print(pin_btn[idx]);
      Serial.print(" : ");
      Serial.println(cfgs[config_index][idx]);
  #endif
  Keyboard.write(cfgs[config_index][idx]);
}


void on_pressed(uint8_t idx) {
  #if DEBUG
      Serial.print("BTN Pressed: ");
      Serial.print(pin_btn[idx]);
  #endif
}

void switch_config() {
  config_index = (config_index + 1) % config_size;
  #if DEBUG
    Serial.println(config_index);
  #endif
}