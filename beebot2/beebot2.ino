int valueForward,valueBackward, valueTurnCW, valueTurnCCW, valueMode, valuePause, valueClear; //Pushbuttons readings
int i=0; //Pointer for commands array
int cont=0; // Counter to check pressed buttons
int contmode = 0;
int mode = 0; //Read -> 0 ; Execute -> 1;
int commands[100]; //Array with commands

//Pins variables
int dirA = 4;
int velA = 5;
int dirB = 7;
int velB = 6;
int pinForward = 8;
int pinBackward = 9;
int pinTurnCW = 10;
int pinTurnCCW = 11;
int pinMode = 12;
int pinLEDread = 13;
int pinLEDexecute = 7;
int pinClear = 2

//Commands functions
void dopause(){
  Serial.println("Descansito");
  analogWrite(velA, 0);
  analogWrite(velB, 0);
  }

void goForward(){
  Serial.println("Voy palante a fuuul");
  digitalWrite(dirA, 1);
  digitalWrite(dirB, 1);
  analogWrite(velA, 255);
  analogWrite(velB, 255);
}

void goBackward(){
  Serial.println("Si voy patrás es sólo pa coger más carrerilla!");
  digitalWrite(dirA, 0);
  digitalWrite(dirB, 0);
  analogWrite(velA, 255);
  analogWrite(velB, 255);
}

void turnCW(){
  Serial.println("Viva el rey");
  digitalWrite(dirA, 1);
  digitalWrite(dirB, 0);
  analogWrite(velA, 255);
  analogWrite(velB, 0);
}

void turnCCW(){
  Serial.println("Camino a la perdición");
  digitalWrite(dirA, 0);
  digitalWrite(dirB, 1);
  analogWrite(velA, 0);
  analogWrite(velB, 255);
}


void setup() {
  pinMode(dirA, OUTPUT);
  pinMode(velA, OUTPUT);
  pinMode(dirB, OUTPUT);
  pinMode(velB, OUTPUT);
  pinMode(pinForward, INPUT);
  pinMode(pinBackward, INPUT);
  pinMode(pinTurnCW, INPUT);
  pinMode(pinTurnCCW, INPUT);
  pinMode(pinMode, INPUT);
  pinMode(pinLEDread, OUTPUT);
  pinMode(pinLEDexecute, OUTPUT);
  Serial.begin(9600);

}

void loop() {

  
  
  while (!mode) { //mode == 0, READING
  digitalWrite(pinLEDexecute, 0);
  digitalWrite(pinLEDread, 1);
  valueForward=digitalRead(pinForward);
  valueBackward=digitalRead(pinBackward);
  valueTurnCCW=digitalRead(pinTurnCCW);
  valueTurnCW=digitalRead(pinTurnCW);
  valueMode=digitalRead(pinMode);
 

  if ((valueForward) && (cont)){ //Check if pushbutton for Forward is pressed. With cont we check that it wasn't already pressed
    commands[i]=1; //Add command to array
    cont=0; //Warn that a button is pressed
    Serial.print(i);
    Serial.print("  forward  ");
    Serial.println(commands[i]);
    i++;
   
  }
  
  if ((valueBackward) && (cont)) {
    commands[i]=2;
    cont=0;
    Serial.print(i);
    Serial.print("  backward  ");
    Serial.println(commands[i]);
    i++;
    }  
    
  if ((valueTurnCCW) && (cont)) {
    commands[i]=3;
    cont=0;
    Serial.print(i);
    Serial.print("  left  ");
    Serial.println(commands[i]);
    i++;
    }  
    
  if ((valueTurnCW) && (cont)) {
    commands[i]=4;
    cont=0;
    Serial.print(i);
    Serial.print("  right  ");
    Serial.println(commands[i]);
    i++;
    }
    
     if ((valuePause) && (cont)){
    commands[i]=5;
    cont=0;
    Serial.print(i);
    Serial.print("  parar  ");
    Serial.println(commands[i]);
    i++;
   
  }
    
      if ((valueClear) && (cont)){
         for (int c = 0; c<=100; c++) { //Erase commands
           commands[c]=0; 
         i=0; //Set pointer to first position
  }
   
  }
    //Check if no button is pressed and update variable accordingly
  if ((!valueForward) && (!valueBackward) && (!valueTurnCW) && (!valueTurnCCW) && (!valuePause) && (!valueClear) && (!cont)){
    cont=1;
  }
    
  if(valueMode){ //EXECUTE
    mode=1;
  }
    
  }
  while(mode) {
      digitalWrite(pinLEDread, 0);
      digitalWrite(pinLEDexecute, 1);
      for (int a =0; a<i; a++){
        switch(commands[a]){
          case 1:
          goForward();
          break;
          case 2:
          goBackward();
          break;
          case 3:
          turnCW();
          break;
          case 4:
          turnCCW();
          break;
          case 5:
          dopause();
          break;
          }
        } 
      mode=0;
      contmode=0;
      i=0;
    }
}
