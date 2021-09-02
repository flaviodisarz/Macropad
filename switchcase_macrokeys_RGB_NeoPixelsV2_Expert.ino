/*
====================================================== Controle do Teclado ======================================================
Keyboard.write();   Melhor para precionamento de teclas simples.
                    Podendo ser feito de duas formas:
                    1 - Keyboard.write('K') Será informado K - Maiúsculo como se fosse - SHIFT + k.
                    2 - Keyboard.write(32) Será informado Tecla de Espaço por se tratar de um codigo ASCII
                    Para melhor encontrar o codigo correto acesse o site: 
                    http://www.asciitable.com/
                    

Keyboard.press();   Melhor usado para precionar varias teclas, como copiar e colar.
                    Como exemplo a seguinte função [ctrl] + [shift] + [e] 
                      //Keyboard.press(KEY_LEFT_CTRL);
                      //Keyboard.press(KEY_LEFT_SHIFT);
                      //Keyboard.press('e'); 
                      //delay(100); Keyboard.releaseAll();
                

Keyboard.print();   Envia o Texto completo.
                    Keyboard.print("stop using aim bot"); // Digite isso como char ou int! (não é uma string)
                    

Keyboard.println(); Envia o Texto completo na outra linha.
                     Muito prático se você deseja digitar uma senha e fazer o login com um toque de botão!
                     

====================================================== Controle do Mouse ======================================================
Mouse.move(x, y, wheel);  Move o mouse e o scroll.
                          Intervalo é de -128 até 127.
                          Numeros negativos é para baixo
                          Numeros positivos é para cima
                        
Mouse.press(b);         Preciona o Botão do Mouse.
                        Mouse.press(MOUSE_LEFT)       //Botão esquerdo.
                        Mouse.press(MOUSE_RIGHT)      //Botão direito.
                        Mouse.press(MOUSE_MIDDLE)     //Botão do Meio.
                        Mouse.press(MOUSE_ALL)        //All three mouse buttons
                        
Mouse.release(b);       Relaxa todos os botões.

Mouse.click(b);         Clica e solta o botão.

*/

/*========================================================= Bibliotecas =========================================================*/

#include "Keyboard.h" //Biblioteca de definição de HID.
#include <Mouse.h> //Biblioteca para o uso do Encoder.
#include <Keypad.h> //Biblioteca para Matrix. 

const byte ROWS = 3; //Quantidade de Linhas.
const byte COLS = 4; //Quantidade de Colunas.

char previousPressedKey;
boolean hasReleasedKey = false;

#include <Encoder.h>   
Encoder RotaryEncoderA(14, 15); //Encoder Esquerdo (encoder A)
Encoder RotaryEncoderB(10, 16);  //Encoder Direito (encoder B)

/*==================================================== Bibliotecas Adicionais ====================================================*/

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

/*========================================================= Configurações =========================================================*/

#define PIN            A2 // Define o Pino em que os Led serão ligados no arduino
#define NUMPIXELS      13 // Define quantos led serão ligados, iniciando do 0, 1, 2..., 12.

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
int colorUpdate = 0;   
const int b = 3;       


char keys[ROWS][COLS] = {
  {'1', '2', '3', '4'},  
  {'5', '6', '7', '8'},
  {'9', '0', 'A', 'B'},  
};

//     |----------------------------|
//     |      [ 1] [ 2] [ 3] [ 4]   |     * Encoder A = key[1]      
//     |      [ 5] [ 6] [ 7] [ 8]   |     * Encoder B  = Key[4]
//     | [ 0] [ 9] [10] [11] [12]   |     * 0 = MODE.
//     |----------------------------|

// Variables that will change:
int modePushCounter = 0;       // Contador para o número de pressionamentos de botão.
int buttonState = 0;           // Estado atual do botão
int lastButtonState = 0;       // Estado anterior do botão
int mouseMove;                 // Variável que contém quantos pixels mover o cursor do mouse
String password;
int demoLoops = 0;             // Conta quantos loops de demonstração ocorreram desde a ativação (usado no modo de atração automática)
long int demoTime = 30000;     // Inicializar o tempo de demonstração como 30 segundos por padrão

long positionEncoderA  = -999;
long positionEncoderB  = -999;

const int ModeButton = A0;     // Define os pinos para ajuste do Mouse com o Encoder.
const int pot = A1;           

byte rowPins[ROWS] = {4, 5, A3 };    //Define os pinos de Linha da Matrix
byte colPins[COLS] = {6, 7, 8, 9 };  //Define os Pinos de Colunas da Matrix
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );


void loop() {
char key = keypad.getKey();
mouseMove = (analogRead(pot)); /
mouseMove = map(mouseMove, 0,1023, 1,124); 
checkModeButton();

  switch (modePushCounter) {
 //====================================================================================================================     
      
    case 0:                                   //Quando o Macro estiver em Modo 0
    encoderA_Mode0();                         //Customizar os Encoders
    encoderB_Mode0();
    setColorsMode0();                         //Indica o funcionamento dos Led.
     
       if (key) {
    switch (key) {
      case '1':
       Keyboard.press(KEY_LEFT_GUI); 
        Keyboard.press('r'); delay(150); 
        Keyboard.release(KEY_LEFT_GUI); 
        Keyboard.release('r'); 
        delay(150);
        Keyboard.println("notepad");  
      case '2': 
                break;    
      case '3': 
                break;
      case '4': 
                break;   
      case '5': 
                break;    
      case '6': 
                break;    
      case '7': 
                 break;   
      case '8': 
                break;    
      case '9': 
                break;     
      case '0': 
                break; 
      case 'A': 
                break;
      case 'B': 
                break;

    }
    pixels.show();
    delay(100); Keyboard.releaseAll();
    colorUpdate = 0; 
  }
      break;
 //====================================================================================================================     
      
    case 1:    
      encoderA_Mode2();                         
      encoderB_Mode2();                         
      setColorsMode1();
   if (key) {
    //Serial.println(key);
    switch (key) {
      case '1': Keyboard.print("admin_1");
                Keyboard.write(9); 
                Keyboard.println("password_1");  
                pixels.setPixelColor(1, 
                pixels.Color(0,150,0)); //Muda a cor para Verde quando precionada
                break;
      case '2': 
                break;    
      case '3': 
                break;
      case '4': 
                break;   
      case '5': 
                break;    
      case '6': 
                break;    
      case '7': 
                 break;   
      case '8': 
                break;    
      case '9': 
                break;     
      case '0': 
                break; 
      case 'A': 
                break;
      case 'B': 
                break;
          }
    pixels.show();
    delay(100); Keyboard.releaseAll();
    colorUpdate = 0;
  }
      break;
 //====================================================================================================================   
      
    case 2:
    encoderA_Mode2();
    encoderB_Mode2(); 
    setColorsMode2();
    if (key) {
     switch (key) {
      case '1': 
        Keyboard.press(KEY_LEFT_CTRL);    
        Keyboard.press('g');
        Keyboard.release(KEY_LEFT_CTRL);  
        Keyboard.release('g'); delay(250);
        for (int tab=0; tab<8; tab++){
           Keyboard.press(KEY_TAB); Keyboard.release(KEY_TAB); delay(100);}
        break;
        
      case '2': 
                break;    
      case '3': 
                break;
      case '4': 
                break;   
      case '5': 
                break;    
      case '6': 
                break;    
      case '7': 
                 break;   
      case '8': 
                break;    
      case '9': 
                break;     
      case '0': 
                break; 
      case 'A': 
                break;
      case 'B': 
                break;
  
     }
    pixels.show();
    delay(100); Keyboard.releaseAll();
    colorUpdate = 0;
     }
          break;
  //====================================================================================================================     
      
    case 3:
     setColorsMode3();
     encoderA_Mode3();
     encoderB_Mode3();  
     getDemoTime();
     key_sequencerRPi();
      if (key) {
        switch (key) {
        case '2': 
                break;    
      case '3': 
                break;
      case '4': 
                break;   
      case '5': 
                break;    
      case '6': 
                break;    
      case '7': 
                 break;   
      case '8': 
                break;    
      case '9': 
                break;     
      case '0': 
                break; 
      case 'A': 
                break;
      case 'B': 
                break;
          
          break;                                
               }
    pixels.show();
    delay(100); Keyboard.releaseAll();
    colorUpdate = 0;
               }
     break;
  }
  delay(1);  
}
//---------------------Sub Routine Section--------------------------------------------------------------------------
void setColorsMode0(){
  if (colorUpdate == 0){                                     // have the neopixels been updated?
      pixels.setPixelColor(0, pixels.Color(  80,  0,200));    
      pixels.setPixelColor(1, pixels.Color(  0,  0,100));    
      pixels.setPixelColor(2, pixels.Color(220,  0,  0));
      pixels.setPixelColor(3, pixels.Color(220,  0,200));
      pixels.setPixelColor(4, pixels.Color(220,  0,200));
      pixels.setPixelColor(5, pixels.Color( 80,102,  0));
      pixels.setPixelColor(6, pixels.Color(  0,200,  0));
      pixels.setPixelColor(7, pixels.Color(  0,200,  0));
      pixels.setPixelColor(8, pixels.Color(140,  0,  0));
      pixels.setPixelColor(9, pixels.Color(  0, 10, 20));
      pixels.setPixelColor(10,pixels.Color(  0, 10, 40));
      pixels.setPixelColor(11, pixels.Color(  0, 10,60));
      pixels.setPixelColor(12, pixels.Color(  0, 10,80));
      pixels.show();
      colorUpdate=1;              }                           // neoPixels have been updated. 
                                                              // Set the flag to 1; so they are not updated until a Mode change
}

void setColorsMode1(){
  if (colorUpdate == 0){                                     // have the neopixels been updated?
      pixels.setPixelColor(0, pixels.Color( 80,  0,200));    //gradient mix
      pixels.setPixelColor(1, pixels.Color( 10,  0,200));    //gradient mix
      pixels.setPixelColor(2, pixels.Color( 20,  0,200));
      pixels.setPixelColor(3, pixels.Color( 40,  0,200));
      pixels.setPixelColor(4, pixels.Color( 60,  0,200));
      pixels.setPixelColor(5, pixels.Color( 80,  0,200));
      pixels.setPixelColor(6, pixels.Color(100,  0,200));
      pixels.setPixelColor(7, pixels.Color(120,  0,200));
      pixels.setPixelColor(8, pixels.Color(140,  0,200));
      pixels.setPixelColor(9, pixels.Color(160,  0,200));
      pixels.setPixelColor(10,pixels.Color(180,  0,200));
      pixels.setPixelColor(11, pixels.Color(200,  0,200));
      pixels.setPixelColor(12, pixels.Color(220,  0,200));
      pixels.show();
      colorUpdate=1;              }                           // neoPixels have been updated. 
                                                              // Set the flag to 1; so they are not updated until a Mode change
}

void setColorsMode2(){
  if (colorUpdate == 0){                                      // have the neopixels been updated?
      pixels.setPixelColor(0, pixels.Color( 51,102,  0));
      pixels.setPixelColor(1, pixels.Color(  0,  0,150)); 
      pixels.setPixelColor(2, pixels.Color(  0,150, 0));
      pixels.setPixelColor(3, pixels.Color(150, 0,  0));
      pixels.setPixelColor(4, pixels.Color(220,  0,200));
      pixels.setPixelColor(5, pixels.Color(150,  0,150));
      pixels.setPixelColor(6, pixels.Color(  0, 80,150));
      pixels.setPixelColor(7, pixels.Color(  0, 80,150));
      pixels.setPixelColor(8, pixels.Color( 80,102,  0));
      pixels.setPixelColor(9, pixels.Color(  0, 0,  0));
      pixels.setPixelColor(10,pixels.Color(  0, 0,  0));
      pixels.setPixelColor(11, pixels.Color( 0, 0,  0));
      pixels.setPixelColor(12, pixels.Color( 0, 0,  0));
      pixels.show(); colorUpdate=1;                  }      // neoPixels have been updated. 
                                                            // Set the flag to 1; so they are not updated until a Mode change
}

void setColorsMode3(){
  if (colorUpdate == 0){                                     // have the neopixels been updated?
      pixels.setPixelColor(0, pixels.Color(100,  0,  0));   // red
      pixels.setPixelColor(1, pixels.Color(  0,  0, 30));   // green
      pixels.setPixelColor(2, pixels.Color(  0,  0,110));   // off 
      pixels.setPixelColor(3, pixels.Color( 80,102,  0));   // yellow
      pixels.setPixelColor(4, pixels.Color(220,  0,200));   // magenta
      pixels.setPixelColor(5, pixels.Color(150,  0, 10));   // red
      pixels.setPixelColor(6, pixels.Color(  0,100,100));   // green
      pixels.setPixelColor(7, pixels.Color( 80,102,  0));   // yellow
      pixels.setPixelColor(8, pixels.Color(220,  0,200));   // magenta
      pixels.setPixelColor(9, pixels.Color(  0,100, 100));   // green
      pixels.setPixelColor(10, pixels.Color(  0,100,100));   // green
      pixels.setPixelColor(11, pixels.Color(  0,100,100));   // green
      pixels.setPixelColor(12, pixels.Color(  0,100,  0));   // blue
      pixels.show(); colorUpdate=1;                 }       // neoPixels have been updated. 
                                                            // Set the flag to 1; so they are not updated until a Mode change
}

void checkModeButton(){
  buttonState = digitalRead(ModeButton);
  if (buttonState != lastButtonState) { 
    if (buttonState == LOW) { 
      modePushCounter++;

      colorUpdate = 0;

    } 
    delay(50);
  }
  lastButtonState = buttonState;
   if (modePushCounter >3){
      modePushCounter = 0;}
}

void encoderA(){
  long newPos = RotaryEncoderA.read()/4; 
  
  if (newPos != positionEncoderA && newPos > positionEncoderA) {
    positionEncoderA = newPos;
    Keyboard.press(KEY_LEFT_ARROW);
    Keyboard.release(KEY_LEFT_ARROW);                      }

  if (newPos != positionEncoderA && newPos < positionEncoderA) {
    positionEncoderA = newPos;
    Keyboard.press(KEY_RIGHT_ARROW);
    Keyboard.release(KEY_RIGHT_ARROW);                      }
}

void encoderB(){
  long newPos = RotaryEncoderB.read()/4;
  if (newPos != positionEncoderB && newPos > positionEncoderB) {
    positionEncoderB = newPos;
    Keyboard.press(KEY_UP_ARROW);
    Keyboard.release(KEY_UP_ARROW);                      }

  if (newPos != positionEncoderB && newPos < positionEncoderB) {
    positionEncoderB = newPos;
    Keyboard.press(KEY_DOWN_ARROW);
    Keyboard.release(KEY_DOWN_ARROW);                      }
}

//=============== encoder definitions/assignments ===========================================


//=============Encoder A & B Function ====== Set 0 =========================================================
void encoderA_Mode0(){
  long newPos = RotaryEncoderA.read()/4;

  if (newPos != positionEncoderA && newPos > positionEncoderA) {
    positionEncoderA = newPos;
    Keyboard.press(KEY_RIGHT_ARROW);
    Keyboard.release(KEY_RIGHT_ARROW);                      }

  if (newPos != positionEncoderA && newPos < positionEncoderA) {
    positionEncoderA = newPos;
    Keyboard.press(KEY_LEFT_ARROW);
    Keyboard.release(KEY_LEFT_ARROW);                      }
}

void encoderB_Mode0(){
  long newPos = RotaryEncoderB.read()/4; 
  if (newPos != positionEncoderB && newPos > positionEncoderB) {
    positionEncoderB = newPos;
     Keyboard.press(KEY_DOWN_ARROW);
    Keyboard.release(KEY_DOWN_ARROW);                      }

  if (newPos != positionEncoderB && newPos < positionEncoderB) {
    positionEncoderB = newPos;

    Keyboard.press(KEY_UP_ARROW);
    Keyboard.release(KEY_UP_ARROW);                         }
}
//=============Encoder A & B Function ====== Set 1 =========================================================
void encoderA_Mode1(){
  long newPos = RotaryEncoderA.read()/2; 
  if (newPos != positionEncoderA && newPos < positionEncoderA) {
    positionEncoderA = newPos;

    Keyboard.write(9);
     }

  if (newPos != positionEncoderA && newPos > positionEncoderA) {
    positionEncoderA = newPos;

    Keyboard.press(KEY_LEFT_SHIFT); 
    Keyboard.write(9);
    Keyboard.release(KEY_LEFT_SHIFT);                      }

}

void encoderB_Mode1(){
  long newPos = RotaryEncoderB.read()/2; 
  if (newPos != positionEncoderB && newPos < positionEncoderB) {
    positionEncoderB = newPos;

    Keyboard.press(KEY_LEFT_CTRL); 
    Keyboard.press('-');
    Keyboard.release('-');  Keyboard.release(KEY_LEFT_CTRL);         }

  if (newPos != positionEncoderB && newPos > positionEncoderB) {
    positionEncoderB = newPos;

    Keyboard.press(KEY_LEFT_CTRL); 
    Keyboard.press('=');
    Keyboard.release('=');   Keyboard.release(KEY_LEFT_CTRL);       }
}

//=============Encoder A & B Function ====== Set 2 =========================================================
void encoderA_Mode2(){ 

  long newPos = RotaryEncoderA.read()/2; 
  if (newPos != positionEncoderA && newPos > positionEncoderA) {
    positionEncoderA = newPos;

     Mouse.move(-mouseMove,0,0);
                        }

  if (newPos != positionEncoderA && newPos < positionEncoderA) {
    positionEncoderA = newPos;
    Mouse.move(mouseMove,0,0); 
                         }
}

void encoderB_Mode2(){
  long newPos = RotaryEncoderB.read()/2;
  if (newPos != positionEncoderB && newPos < positionEncoderB) {
    positionEncoderB = newPos;
    Mouse.move(0,-mouseMove,0);                                                           }

  if (newPos != positionEncoderB && newPos > positionEncoderB) {
    positionEncoderB = newPos;
    Mouse.move(0,mouseMove,0);            
                                                              }
}

//=============Encoder A & B Function ====== Set 3 =========================================================
void encoderA_Mode3(){
  long newPos = RotaryEncoderA.read()/2; 
  if (newPos != positionEncoderA && newPos > positionEncoderA) {
    positionEncoderA = newPos;
    Mouse.press(MOUSE_LEFT);
    Mouse.move(0,4,0); 
    Mouse.release(MOUSE_LEFT); 
                                                               }

  if (newPos != positionEncoderA && newPos < positionEncoderA) { 
    positionEncoderA = newPos;
    Mouse.press(MOUSE_LEFT);
    Mouse.move(0,-4,0);
    Mouse.release(MOUSE_LEFT)                  
                                                              }
}

void encoderB_Mode3(){
  long newPos = RotaryEncoderB.read()/2;
  if (newPos != positionEncoderB && newPos > positionEncoderB) {
    positionEncoderB = newPos;
    Mouse.press(MOUSE_LEFT);
    Mouse.move(-4,0,0);
    Mouse.release(MOUSE_LEFT);
                                                               }

  if (newPos != positionEncoderB && newPos < positionEncoderB) {
    positionEncoderB = newPos;
    Mouse.press(MOUSE_LEFT);
    Mouse.move(4,0,0)
    Mouse.release(MOUSE_LEFT);                  
                                                              }
}

void RandoPasswordGenerator(){
  long random_alpha;
  long random_ALPHA;
  long random_numeric;
  long random_special;
  
  char alpha; 
  char ALPHA;
  char number;
  char specialChar; 
  char randoPassword; 
   
  char alphabet[]="qwertyuiopasdfghjklzxcvbnm"; 
  char ALPHABET[]="QWERTYUIOPASDFGHJKLZXCVBNM"; 
  char numeric[] ="1234567890";
  char special[] ="!@#$%^&*()";
  
  random_alpha = random(sizeof(alphabet)-1);   
  random_ALPHA = random(sizeof(ALPHABET)-1);    
  random_numeric = random(sizeof(numeric)-1);  
  random_special = random(sizeof(special)-1);   
  
  alpha = alphabet[random_alpha]; 
  ALPHA = ALPHABET[random_ALPHA];
  number = numeric[random_numeric];
  specialChar = special[random_special];
  
  String alpha_String = String(alpha); 
  String ALPHA_String = String(ALPHA);
  String number_String = String(number);
  String specialChar_String = String(specialChar);
  
  password = (alpha_String + ALPHA_String + number_String + specialChar_String); 
  password.toCharArray(randoPassword,sizeof(randoPassword)); 
  Keyboard.print(password);
  }
