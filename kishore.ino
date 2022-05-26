#define Input_1 5
#define Input_2 3
#define Input_3 4
#define Output_1 6

bool Out_Status = false;
bool First_Half = false;
bool Second_Half = false;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
while(!Serial){};
delay(500);
Serial.println("System Started");

pinMode(Input_1, INPUT);
pinMode(Input_2, INPUT);
pinMode(Input_3, INPUT);
pinMode(Output_1, OUTPUT);

pinMode(LED_BUILTIN, OUTPUT);
digitalWrite(LED_BUILTIN, HIGH);
Serial.println("Cycle Started");
}

void loop() {
  // put your main code here, to run repeatedly:
  
  
  if(Out_Status){
    if(digitalRead(Input_2) && !(digitalRead(Input_1)) && First_Half ){
    Serial.println("Input 2 Detected, Turning OFF the OUTPUT");
    digitalWrite(Output_1, LOW);
    Out_Status = false;
    First_Half = false;
    Second_Half = true;  
    }
    else if(digitalRead(Input_2) && digitalRead(Input_3) && Second_Half){
    digitalWrite(Output_1, LOW);
    Serial.println("Input 3 Detected, Turning OFF the OUTPUT");
    Out_Status = false;
    Second_Half = false;
    delay(100);
    Serial.println("Cycle Completed"); 
   // delay(1000);   
    }
        
    if(First_Half)
      Serial.println("Waiting for the 2nd Input to Turn OFF the Output");
    if(Second_Half)
      Serial.println("Waiting for the 3rd Input to Turn OFF the Output");
   
  }
  
  else {
    if (digitalRead(Input_1) && !(digitalRead(Input_2))){
      delay(100);
      Serial.println("Input 1 Detected, Turning ON the OUTPUT");
      digitalWrite(Output_1, HIGH);
      Out_Status = true;
      First_Half = true;
    }
    else if(digitalRead(Input_1) && digitalRead(Input_2)){
      delay(100);
      Serial.println("Input 3 Detected, Turning ON the OUTPUT");
      digitalWrite(Output_1, HIGH);
      Out_Status = true;
    }
    if(First_Half)
      Serial.println("Waiting for the 2nd Input to Turn OFF the Output");
    else if (Second_Half)
      Serial.println("Waiting for the 3rd(1st) Input to Turn ON the Output");
    else 
      Serial.println("Waiting for the 1st Input to Turn ON the Output");
  }
    
}
