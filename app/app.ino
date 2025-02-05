// numero de pin de los leds
const byte led_1 = 11;
const byte led_2 = 10;
const byte led_3 = 9;
const byte led_4 = 6;
const byte led_5 = 5;
const byte led_6 = 3;
const byte leds[6] = {led_1, led_2, led_3, led_4, led_5, led_6};

const byte fuente = 13;  // pin para usar como fuente 3.3V
const byte pinButton = 2; // entrada del botón

void setup() {
  // configurar salidas de led
  byte led;
  for (int i = 0; i <= 5; i++){
    led = leds[i];
    pinMode(led, OUTPUT);
  }

  // salida de boton input
  pinMode(pinButton, INPUT);
  // salida de fuente para boton
  pinMode(fuente, OUTPUT); 
  digitalWrite(fuente, HIGH);
}

void loop() {
  byte led;
  for (int i = 0; i <= 5; i++){
    led = leds[i];
    digitalWrite(led, HIGH);
    delay(50);
    digitalWrite(led, LOW);
  }
  delay(50);
}
