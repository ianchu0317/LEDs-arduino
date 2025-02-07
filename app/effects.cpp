#include "effects.h"

/* *** DEFINIR PINES *** */
const byte led_1 = 11;
const byte led_2 = 10;
const byte led_3 = 9;
const byte led_4 = 6;
const byte led_5 = 5;
const byte led_6 = 3;
const byte leds[6] = {led_1, led_2, led_3, led_4, led_5, led_6};

const byte fuente = 13;     // pin para usar como fuente 3.3V
const byte pinButton = 2;   // entrada del botón



/* *** VARIABLES ****/
// variables para manipular botón  
int button_val;
int last_button_val = 0;
bool button_pressed = false;
int last_button_press = 0;

//  variables para manejar efectos
int effects_counter = 0;
int total_effects = 2;
bool is_turn_off = false;  // si esta apagado todo

//  variables para intercalateLED
int intercalate_i = 0;    // contador para funcion intercalateLed
int intercalate_step = 1;

//  variables para fade 
int fade_vel = 5;         // velocidad de fade en ms
int fade_step = 15;       // cambio de intensidad
int fade_count = 0;



/* *** CONFIGURACIONES *** */
// configurar salidas de led
void setupLeds(){
  byte led;
  for (int i = 0; i <= 5; i++){
    led = leds[i];
    pinMode(led, OUTPUT);
  }
}


// configurar botón 
void setupButton(){
  pinMode(pinButton, INPUT);

  // salida de fuente para boton en pulldown
  pinMode(fuente, OUTPUT); 
  digitalWrite(fuente, HIGH);
}


// chequear estado del botón
void checkButtonPress(){
  
  button_val = digitalRead(pinButton); 

  if (button_val && !last_button_val){
    // chequear debounce
    if (millis() - last_button_press > 50){
      last_button_press = millis();
      button_pressed = true;
    }
  }
  
  last_button_val = button_val;
  
  // cambiar efecto
  if (button_pressed){
    effects_counter += 1;
    button_pressed = false;
    is_turn_off = false;  
  }

  // resetear efecto si ya se pasaron todos
  if (effects_counter > total_effects){
    effects_counter = 0;
  }
}


// cambiar efecto actual 
void switchEffect(){
  switch (effects_counter){
    case 0:
      turnOff();
      break;
    case 1:
      intercalateLed();
      break;
    case 2: 
      fadeLeds();
      break;
  }
}




/* *** FUNCIONES *** */
// apagar todos los LEDs si no están apagados
void turnOff(){
  if (!is_turn_off){
    setLedsIntensity(0);
    is_turn_off = true;
  }
}


// configurar todos los LED dada una intensidad
void setLedsIntensity(int intensity){
  byte led;
  for (int i = 0; i <= 5; i++){
    led = leds[i];
    analogWrite(led, intensity);
  }
}


// regular la intensidad progresivamente con pwm 
void fadeLeds(){
  setLedsIntensity(fade_count);
  fade_count = fade_count + fade_step;

  if (fade_count == 255 || fade_count == 0){
    fade_step = -fade_step;
  }

  delay(fade_vel);
}


// alternar el encendido y apagado de los LEDs
void intercalateLed(){
  byte led = leds[intercalate_i];

  digitalWrite(led, HIGH);
  delay(50);
  digitalWrite(led, LOW);
  
  intercalate_i = intercalate_i + intercalate_step;
  
  if (intercalate_i == 5 || intercalate_i == 0){
    intercalate_step = -intercalate_step;
  }
}

