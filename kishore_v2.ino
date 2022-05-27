#define Input_1 5
#define Input_2 3
#define Input_3 4
#define Output_1 6

#define ON LOW
#define OFF HIGH


bool First_Half_On = false;
bool First_Half_Off = false;
bool Second_Half_On = false;
bool cycle_start = true;
bool error = false;

unsigned long Current_Time, Previous_Time;

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
digitalWrite(Output_1, OFF);
pinMode(LED_BUILTIN, OUTPUT);
digitalWrite(LED_BUILTIN, LOW);

Serial.println("Cycle Started");
Previous_Time = millis();
}

void loop(){
  if(cycle_start && (digitalRead(Input_2) || digitalRead(Input_3) )){
    Check_input();
  }
  if(cycle_start && !digitalRead(Input_2) && !digitalRead(Input_3) && digitalRead(Input_1)){
    delay(500);
    digitalWrite(LED_BUILTIN,LOW);
    error = false;
    Serial.println("First Input Detected, Turning ON the Output");
    digitalWrite(Output_1, ON);
    cycle_start = false;
    First_Half_On = true;
  }
  if(First_Half_On && (digitalRead(Input_3) || digitalRead(Input_1))){
    Check_input();
  }
  if(First_Half_On && digitalRead(Input_2) && !digitalRead(Input_1) && !digitalRead(Input_3)){
    delay(200);
    digitalWrite(LED_BUILTIN,LOW);
    error = false;
    Serial.println("Second Input Detected, Turning OFF the Output");
    digitalWrite(Output_1, OFF);
    First_Half_On = false;
    First_Half_Off = true;
  }
  if(First_Half_Off && (!digitalRead(Input_2) || digitalRead(Input_3)) ){
    Check_input();
  }
  if (First_Half_Off && digitalRead(Input_2) && digitalRead(Input_1)){
    delay(500);
    digitalWrite(LED_BUILTIN,LOW);
    error = false;
    Serial.println("Third Input Detected, Turning ON the Output");
    digitalWrite(Output_1, ON);
    First_Half_Off = false;
    Second_Half_On = true;
  }
  if(Second_Half_On && (!(digitalRead(Input_2)) || digitalRead(Input_1))){
     Check_input();
  }
  if(Second_Half_On && digitalRead(Input_2) && digitalRead(Input_3) && !digitalRead(Input_1)){
    delay(200);
    digitalWrite(LED_BUILTIN,LOW);
    error = false;
    Serial.println("Fourth Input Detected, Turning OFF the Output");
    Serial.println("Cycle Completed");
    digitalWrite(Output_1, OFF);
    Second_Half_On = false;
    cycle_start = true;
  }
  if(Second_Half_On && !digitalRead(Input_2) || digitalRead(Input_1)){
    Check_input();
  }
  if(!error)
      digitalWrite(LED_BUILTIN,LOW);
}

void Check_input(){
    Serial.println("Please Check the Inputs");
    digitalWrite(Output_1, OFF);
    error = true;
    Current_Time = millis();
    if((Current_Time - Previous_Time) > 500){
      digitalWrite(LED_BUILTIN, !(digitalRead(LED_BUILTIN)));
      Previous_Time = millis();
    }
}
