#include <Servo.h>

#define SERVO_PIN 9
#define BUZZER_PIN 7
#define GREEN_LED_PIN 5
#define RED_LED_PIN 6
#define BUTTON_PIN_1 2 
#define BUTTON_PIN_2 3 
#define BUTTON_PIN_3 4 

const int passwordLength = 3;
int password[passwordLength];
int userInput[passwordLength];
bool isLocked = true;

// Posições do servo motor
// 0 graus = trancado, 90 graus = destrancado
Servo lockServo;
const int unlockedPosition = 90;
const int lockedPosition = 0;

void setup(){
  Serial.begin(9600);
  pinMode(GREEN_LED_PIN, OUTPUT); 
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT); 
  pinMode(BUTTON_PIN_1, INPUT);
  pinMode(BUTTON_PIN_2, INPUT); 
  pinMode(BUTTON_PIN_3, INPUT);
  lockServo.attach(SERVO_PIN);
  lockServo.write(lockedPosition); // Inicia trancado
  Serial.println("MODO DE CADASTRO DE SENHA POR CONTAGEM");
  
  // Cadastro da senha 
  for(int i=0; i<3; i++){
    digitalWrite(GREEN_LED_PIN, HIGH); 
    digitalWrite(RED_LED_PIN, HIGH); 
    delay(250);
    digitalWrite(GREEN_LED_PIN, LOW); 
    digitalWrite(RED_LED_PIN, LOW); 
    delay(250);
  }

  Serial.println("\n--- Cadastre sua nova senha de 3 digitos ---");
  enterPasswordCount(password);

  Serial.println("Cadastro finalizado. Cofre em operacao.");
  lockSafe();
}

void loop(){
  if(isLocked){
    Serial.println("\n--- Digite a senha para abrir ---");
    enterPasswordCount(userInput);
    checkPassword();
  }
}

// Função para guiar a entrada da senha (cadastro e operação)
void enterPasswordCount(int sequence[]){
  sequence[0] = countButtonPresses(BUTTON_PIN_1);
  sequence[1] = countButtonPresses(BUTTON_PIN_2);
  sequence[2] = countButtonPresses(BUTTON_PIN_3);
}

// Função que conta os toques em um botão
int countButtonPresses(int buttonToCount){
  int count = 0;
  
  if(buttonToCount == BUTTON_PIN_1) 
  Serial.println("Digite o 1o digito (no B1) e confirme com B3:");
  if(buttonToCount == BUTTON_PIN_2) 
  Serial.println("Digite o 2o digito (no B2) e confirme com B3:");
  if(buttonToCount == BUTTON_PIN_3) 
  Serial.println("Digite o 3o digito (no B3) e confirme com B1:");
  
  int confirmButtonPin = (buttonToCount == BUTTON_PIN_3) ? BUTTON_PIN_1 : BUTTON_PIN_3;

  while(true){
    if(digitalRead(buttonToCount) == HIGH){
      count++;
      Serial.print("Contagem: "); 
      Serial.println(count);
      tone(BUZZER_PIN, 1200, 100);
      delay(300);
    }
    
    if(digitalRead(confirmButtonPin) == HIGH){
      Serial.print("  -> Digito final: "); 
      Serial.println(count);
      tone(BUZZER_PIN, 1500, 150);
      delay(300);
      return count;
    }
  }
}

// Verifica se a senha da tentativa é a mesma que a senha salva
void checkPassword(){
  bool correct = true;
  for(int i = 0; i < passwordLength; i++){
    if(userInput[i] != password[i]){
      correct = false;
      break;
    }
  }
  if(correct){ 
    unlockSafe(); 
  }else{ 
    passwordFail(); 
  }
}

//Reseta a tentativa do usuário para a próxima entrada
void resetInput(){
  for(int i=0; i<passwordLength; i++){
    userInput[i] = 0;
  }
}

// abre o cofre
void unlockSafe(){
  isLocked = false;
  Serial.println("SENHA CORRETA! Cofre aberto.");
  digitalWrite(RED_LED_PIN, LOW);
  digitalWrite(GREEN_LED_PIN, HIGH);
  tone(BUZZER_PIN, 1500, 200); 
  delay(250); 
  tone(BUZZER_PIN, 2000, 200);
  lockServo.write(unlockedPosition);
  delay(5000);
  lockSafe(); // Tranca novamente após um tempo
}

// Ação de falha: avisa do erro e se prepara para nova tentativa
void passwordFail(){
  Serial.println("SENHA INCORRETA!");
  
  // Pisca o LED vermelho 3 vezes indicando erro
  for(int i=0; i<3; i++){
    digitalWrite(RED_LED_PIN, HIGH);
    tone(BUZZER_PIN, 300, 250);
    delay(300);
    digitalWrite(RED_LED_PIN, LOW);
    delay(300);
  }
  lockSafe();
}

//Ação de trancar
void lockSafe(){
  isLocked = true;
  digitalWrite(GREEN_LED_PIN, LOW);
  digitalWrite(RED_LED_PIN, HIGH); 
  lockServo.write(lockedPosition);
  resetInput();
  Serial.println("\nCofre trancado. Aguardando senha...");
}