#include <Arduino.h>
#include <Bounce2.h>

#define TOGGLE_BUTTON_PIN 2
#define TOGGLE_LIGHT_PIN 3
#define TOGGLE_PREFIX "bouton0"

#define MOMENTARY_BUTTON_PIN 4
#define MOMENTARY_LIGHT_PIN 5
#define MOMENTARY_PREFIX "bouton1"

#define BAUD 115200

Bounce2::Button toggleButton = Bounce2::Button();
Bounce2::Button momentaryButton = Bounce2::Button();

bool toggleState = LOW;

void setup() {
  // LED config
  pinMode(TOGGLE_LIGHT_PIN, OUTPUT);
  digitalWrite(TOGGLE_LIGHT_PIN, toggleState);
  pinMode(MOMENTARY_LIGHT_PIN, OUTPUT);
  digitalWrite(MOMENTARY_LIGHT_PIN, LOW);

  // button config
  toggleButton.attach(TOGGLE_BUTTON_PIN, INPUT_PULLUP);
  toggleButton.setPressedState(LOW);

  momentaryButton.attach(MOMENTARY_BUTTON_PIN, INPUT_PULLUP);
  momentaryButton.setPressedState(LOW);

  // serial config
  Serial.begin(BAUD);
}

void loop() {
  toggleButton.update();
  momentaryButton.update();

  if (toggleButton.pressed()) {
    toggleState = !toggleState;

    digitalWrite(TOGGLE_LIGHT_PIN, toggleState);

    Serial.print(TOGGLE_PREFIX);
    Serial.print(" ");
    Serial.print(toggleState ? "1" : "0");
    Serial.print("\n");
  }

  if (momentaryButton.pressed() || momentaryButton.released()) {
    bool pressed = momentaryButton.isPressed();

    digitalWrite(MOMENTARY_LIGHT_PIN, pressed);

    if(pressed) {
        Serial.print(MOMENTARY_PREFIX);
        Serial.print(" 1\n");
    }
  }

}