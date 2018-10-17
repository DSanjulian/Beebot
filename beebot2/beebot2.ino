int valorf,valorr, valorl, valorb, valorm, valorp; //lecturas teclas
int i=0;
int cont=0; // contador para los comandos
int contmode = 0; //contador boton modo
int mode = 0; //0 leer, 1 ejecutar
int commands[100];


int dirA = 4;
int velA = 5;

int dirB = 7;
int velB = 6;
//pines conectados
int forward = 8;
int backward = 9;
int right = 10;
int left = 11;
int modo = 12;
int ledleer = 13;
int ledejecutar = 7;


void parar(){
  analogWrite(velA, 0);
  analogWrite(velB, 0);
  }

void palante(){
  Serial.println("Voy palante a fuuul");
  digitalWrite(dirA, 1);
  digitalWrite(dirB, 1);
  analogWrite(velA, 255);
  analogWrite(velB, 255);
}

void patras(){
  Serial.println("Si voy patrás es sólo pa coger más carrerilla!");
  digitalWrite(dirA, 0);
  digitalWrite(dirB, 0);
  analogWrite(velA, 255);
  analogWrite(velB, 255);
}

void derecha(){
  Serial.println("Viva el rey");
  digitalWrite(dirA, 1);
  digitalWrite(dirB, 0);
  analogWrite(velA, 255);
  analogWrite(velB, 0);
}

void izquierda(){
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
  pinMode(forward, INPUT);
  pinMode(backward, INPUT);
  pinMode(right, INPUT);
  pinMode(left, INPUT);
  pinMode(modo, INPUT);
  pinMode(ledleer, OUTPUT);
  pinMode(ledejecutar, OUTPUT);
  Serial.begin(9600);

}

void loop() {

  
  
  while (!mode) {
  digitalWrite(ledejecutar, 0);
  digitalWrite(ledleer, 1);
  valorf=digitalRead(forward);
  valorb=digitalRead(backward);
  valorl=digitalRead(left);
  valorr=digitalRead(right);
  valorm=digitalRead(modo);
 

  if ((valorf) && (cont)){
    commands[i]=1;
    cont=0;
    Serial.print(i);
    Serial.print("  forward  ");
    Serial.println(commands[i]);
    i++;
   
  }
  
  if ((valorb) && (cont)) {
    commands[i]=2;
    cont=0;
    Serial.print(i);
    Serial.print("  backward  ");
    Serial.println(commands[i]);
    i++;
    }  
    
  if ((valorl) && (cont)) {
    commands[i]=3;
    cont=0;
    Serial.print(i);
    Serial.print("  left  ");
    Serial.println(commands[i]);
    i++;
    }  
    
  if ((valorr) && (cont)) {
    commands[i]=4;
    cont=0;
    Serial.print(i);
    Serial.print("  right  ");
    Serial.println(commands[i]);
    i++;
    }
    
     if ((valorp) && (cont)){
    commands[i]=5;
    cont=0;
    Serial.print(i);
    Serial.print("  parar  ");
    Serial.println(commands[i]);
    i++;
   
  }
    
  if (((!valorf) && (!valorb) && (!valorl) && (!valorr))&&(!cont)){
    cont=1;
  }
  if(valorm){
    mode=1;
  }
  }
  while(mode) {
      digitalWrite(ledleer, 0);
      digitalWrite(ledejecutar, 1);
      for (int a =0; a<i; a++){
        switch(commands[a]){
          case 1:
          palante();
          break;
          case 2:
          patras();
          break;
          case 3:
          derecha();
          break;
          case 4:
          izquierda();
          break;
          case 5:
          parar();
          break;
          }
        } 
      mode=0;
      contmode=0;
      i=0;
    }
}
