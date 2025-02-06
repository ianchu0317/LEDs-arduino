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
// constantes para manipular boton
int button_val;
int last_button_val = 0;
bool button_pressed = false;
int last_button_press = 0;

// constantes globales para distintas funciones/efectos de luces
int effects_counter = 0;
int total_effects = 2;
bool is_turn_off = false;  // si esta apagado todo

// Variables para intercalateLed 
int intercalate_i = 0;  // contador para funcion intercalateLed
int intercalate_step = 1;

// Variables para fade
int fade_vel = 5;  // velocidad para fadeLeds en ms
int fade_step = 15;
int fade_count = 0;


void setup() {
  // configurar salidas de led
  byte led;
  for (int i = 0; i <= 5; i++){
    led = leds[i];
    pinMode(led, OUTPUT);
  }
  // entrada de boton input
  pinMode(pinButton, INPUT);
  // salida de fuente para boton en pulldown
  pinMode(fuente, OUTPUT); 
  digitalWrite(fuente, HIGH);

  // salida Serial para debug
  Serial.begin(9600);
}

void loop() {
  // leer entrada boton
  button_val = digitalRead(pinButton); 

  if (button_val && !last_button_val){
    if (millis() - last_button_press > 50){
      last_button_press = millis();
      button_pressed = true;
    }
  }
  
  last_button_val = button_val;
  //Serial.println(button_val);
  //Serial.println(button_pressed);
  
  // cambiar efecto
  if (button_pressed){
    effects_counter += 1;
    button_pressed = false;  
  }

  // resetear efecto si ya se pasaron todos
  if (effects_counter > total_effects){
    effects_counter = 0;
  }

  //Serial.println(effects_counter);
  
  // elección dde efectos
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
  
  //delay(50);
}


void setLedsIntensity(int intensity){
  /*
    Setear todos los LED dada una intensidad
  */
  byte led;
  for (int i = 0; i <= 5; i++){
    led = leds[i];
    analogWrite(led, intensity);
  }
}


void fadeLeds(){
  /*
    Enciende y apaga los LEDs usando PWM,
    regulando la intensidad progresivamente
  */

  // Actualizar intensidad
  setLedsIntensity(fade_count);
  fade_count = fade_count + fade_step;

  if (fade_count == 255 || fade_count == 0){
    fade_step = -fade_step;
  }

  delay(fade_vel);
}


void intercalateLed(){
  /*
    Función para encender y apagar los LEDs de manera alternada
  */
  byte led = leds[intercalate_i];

  digitalWrite(led, HIGH);
  delay(50);
  digitalWrite(led, LOW);
  
  intercalate_i = intercalate_i + intercalate_step;
  //Serial.println(intercalate_i);
  
  if (intercalate_i == 5 || intercalate_i == 0){
    intercalate_step = -intercalate_step;
  }
}


void turnOff(){
/*
  Funcion para apagar todos los LEDs si no están apagados
*/
  if (!is_turn_off){
    setLedsIntensity(0);
    
    is_turn_off = true;
  }
}

