#include <TaskScheduler.h>
#include <NewPing.h>

#define TRIGGER_PIN  A5  
#define ECHO_PIN     A4  
#define MAX_DISTANCE 200 

//------BUZZER------
int outBuzzer = 22; 
//-------LEDS-------
int red_led = 53;
int green_led = 51;
//-------------------

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

int in1=2;
int in2=3;
int in3=4;
int in4=5;
int ENA=6;
int ENB=7;
int in5=8;
int in6=9;
int in7=10;
int in8=11;
int ENC=12;
int END=13;
int A;
int N;
int k[4]={0,0,0,0};
void avancerD();
void avancerG();
void avancerD1();
void reculerD();
void reculer();
void avancer();
void gauche();
void droite();
void droite1();
void gauche1();
void suiveur();
void avancerG1();
void stop();
void suiveur2();

void NormalLoopCallback();

void RedLed5secCallback();

void ZigzagLoopCallback();

void BuzzerCallback();

void MessageCallback();

void SonarCallback();

void SonarFoundCallback();


//--------------NORMAL LOOP--------------------------------------
Task NormalLoop(TASK_IMMEDIATE, TASK_FOREVER, &NormalLoopCallback);

//--------------RED LED-5SEC-------------------------------------
Task RedLed5sec(TASK_IMMEDIATE, TASK_FOREVER, &RedLed5secCallback);

//--------------ZIGZAG LOOP--------------------------------------
Task ZigzagLoop(TASK_IMMEDIATE, TASK_FOREVER, &ZigzagLoopCallback);

//--------------Buzzer LOOP--------------------------------------
Task Buzzer(TASK_IMMEDIATE, TASK_FOREVER, &BuzzerCallback); // 5sec

//--------------Message LOOP--------------------------------------
Task Message(TASK_IMMEDIATE, TASK_FOREVER, &MessageCallback); // 5sec

//--------------Sonar LOOP--------------------------------------
Task Sonar(TASK_IMMEDIATE, TASK_FOREVER, &SonarCallback); 

//--------------Sonar LOOP FOUND--------------------------------------
Task SonarFound(TASK_IMMEDIATE, TASK_FOREVER, &SonarFoundCallback); // 5sec


Scheduler runner;

//---------------------------------------------------------------NORMAL LOOP CALLBACK-----------------------------------------------------------------------
void NormalLoopCallback() { 
  RedLed5sec.disable(); Serial.println("RED LED 5sec DISABLED");
  digitalWrite(red_led,LOW);

  digitalWrite(green_led, HIGH); // led verte toujours active
  
    k[0]=digitalRead(A0);
    k[1]=digitalRead(A1);
    k[2]=digitalRead(A2);
    k[3]=digitalRead(A3);
    
    if ((k[0]==0)&&(k[1]==0)&&(k[2]==0)&&(k[3]==0)){
      if (N==1){
        droite();
      }
      else if (N==2){
        gauche();
      }
      else if (N==3){
        avancer();
      }}
   
   else if ((k[0]==0)&&(k[1]==0)&&(k[2]==0)&&(k[3]==1)){
      droite();
      N=1;
    }
   else if ((k[0]==0)&&(k[1]==0)&&(k[2]==1)&&(k[3]==0)){
      droite1();
       
    }
   else if ((k[0]==0)&&(k[1]==0)&&(k[2]==1)&&(k[3]==1)){
      droite();
       N=1;
    }
   else if ((k[0]==0)&&(k[1]==1)&&(k[2]==0)&&(k[3]==0)){
      gauche1();
    }
   else if ((k[0]==0)&&(k[1]==1)&&(k[2]==1)&&(k[3]==0)){
      avancer();
       N=3;
      
    }
   else if ((k[0]==0)&&(k[1]==1)&&(k[2]==1)&&(k[3]==1)){
      droite();
       N=1;
      
    }
   else if ((k[0]==1)&&(k[1]==0)&&(k[2]==0)&&(k[3]==0)){
      gauche();
       N=2;
    }
   else if ((k[0]==1)&&(k[1]==1)&&(k[2]==0)&&(k[3]==0)){
      gauche(); 
       N=2;
    }
   else if ((k[0]==1)&&(k[1]==1)&&(k[2]==1)&&(k[3]==0)){
      gauche();
       N=2;
      
    }
   else if ((k[0]==1)&&(k[1]==1)&&(k[2]==1)&&(k[3]==1)){
     digitalWrite(red_led,HIGH);delay(300);  digitalWrite(green_led, LOW); avancer();delay(500); stop();delay(2000); digitalWrite(red_led,LOW); digitalWrite(green_led, HIGH); avancer();
       N=3;
    }
}

//---------------------------------------------------------------RED LED 5 SEC CALLBACK----------------------------------------------------------------
void RedLed5secCallback() { 
   Serial.println("RED LED 5sec ENABLED");
    digitalWrite(green_led, LOW);
   int loopcount = 0 ;
   int starttime = millis();

   int endtime = starttime;
   
    while ((endtime - starttime) <=5000) 
    {
      digitalWrite(red_led,HIGH);
      loopcount = loopcount+1;
      endtime = millis();
    }

    RedLed5sec.disable();  Serial.println("RED LED 5sec DISABLED");
    digitalWrite(red_led,LOW);
}

//---------------------------------------------------------------ZIGZAG CALLBACK-----------------------------------------------------------------------
void ZigzagLoopCallback() { 
}

//---------------------------------------------------------------BUZZER CALLBACK-----------------------------------------------------------------------
void BuzzerCallback() {
 
 SonarFound.disable();
   int loopcount = 0 ;
   int starttime = millis();
   int endtime = starttime;
   
    while ((endtime - starttime) <=4000) 
    {    
     unsigned char i, j ;                                                                         
     for (i = 0; i <100; i++){                                                                    
       digitalWrite (outBuzzer, HIGH);                                                        
       delay (1) ;                                                                                      
       digitalWrite (outBuzzer, LOW);                                                        
       delay (1) ;                                                                                     
     }

     for (i = 0; i <190; i++){                                                                                        
       digitalWrite (outBuzzer, LOW);         
     }
     
     for (i = 0; i <100; i++){                                                                
       digitalWrite (outBuzzer, HIGH);                                                        
       delay (1) ;                    
       digitalWrite (outBuzzer, LOW); 
       delay (1) ;
     }

     for (i = 0; i <190; i++){
       digitalWrite (outBuzzer, LOW);
     }
 
      for (i = 0; i <100; i++){
       digitalWrite (outBuzzer, HIGH);
       delay (3) ;
       digitalWrite (outBuzzer, LOW);
       delay (3) ; 
     }

     for (i = 0; i <190; i++){                
       digitalWrite (outBuzzer, LOW);                     
     } 

      loopcount = loopcount+1;
      endtime = millis();
    }

    Buzzer.disable(); Serial.println("buzzer disabled");
    
}

//---------------------------------------------------------------MESSAGE CALLBACK-----------------------------------------------------------------------
void MessageCallback() { 
}

//---------------------------------------------------------------SONAR CALLBACK-----------------------------------------------------------------------
void SonarCallback() { 
  if( (sonar.ping_cm() <= 17 ) && (sonar.ping_cm()>= 13 )){
    SonarFound.enable();     Serial.println(" SonarFound enabled ");
  }
}

//---------------------------------------------------------------SONAR FOUND CALLBACK-----------------------------------------------------------------------
void SonarFoundCallback() { 
   stop();
   RedLed5sec.enable();  
   Buzzer.enable();    
   Sonar.delay(12000);
   NormalLoop.delay(5000);
}

void setup() {
  Serial.begin(9600);
  //--------------------- MOTORS ------------------------------------------
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
  pinMode(in5,OUTPUT);
  pinMode(in6,OUTPUT);
  pinMode(in7,OUTPUT);
  pinMode(in8,OUTPUT);
  pinMode(ENA,OUTPUT);
  pinMode(ENB,OUTPUT);
  pinMode(ENC,OUTPUT);
  pinMode(END,OUTPUT);
  //------------------ BUZZER ---------------------------------------------
  pinMode(outBuzzer, OUTPUT);
  pinMode(green_led, OUTPUT);     
  pinMode(red_led, OUTPUT);      

  //---------------TASK SCHEDULER------------------------------------------
  runner.init();
  runner.addTask(NormalLoop);
  runner.addTask(Sonar);
  runner.addTask(SonarFound);
  runner.addTask(Buzzer);
  runner.addTask(RedLed5sec);
  
  NormalLoop.enable();
  Sonar.enable();
}

void loop() {
  runner.execute();
}


//-------------------------------------------FONCTIONS SUIVEUR ----------------------------------------
void avancerD(){
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
  analogWrite(ENA,180);
  analogWrite(ENB,180);
}
void avancerG(){
  
  digitalWrite(in5,LOW);
  digitalWrite(in6,HIGH);
  digitalWrite(in7,HIGH);
  digitalWrite(in8,LOW);
  analogWrite(ENC,180);
  analogWrite(END,220);
}
void reculerD(){
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  analogWrite(ENA,180);
  analogWrite(ENB,180);
}
void reculerG(){
  
  digitalWrite(in5,HIGH);
  digitalWrite(in6,LOW);
  digitalWrite(in7,LOW);
  digitalWrite(in8,HIGH);
  analogWrite(ENC,180);
  analogWrite(END,220);
}
void avancerD1(){
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
  analogWrite(ENA,100);
  analogWrite(ENB,100);
}
void avancerG1(){
  
  digitalWrite(in5,LOW);
  digitalWrite(in6,HIGH);
  digitalWrite(in7,HIGH);
  digitalWrite(in8,LOW);
  analogWrite(ENC,100);
   analogWrite(END,130);
}

void avancer() {
  avancerG1();
  avancerD1();
 }

  
void reculer(){
reculerG();
reculerD();
}

void droite(){
reculerD();
avancerG();
}
void gauche(){
avancerD();
reculerG();
}
void droite1(){
reculerD();
avancerG();
}
void gauche1(){
avancerD();
reculerG();
}

void stop(){
digitalWrite(in1,LOW);
digitalWrite(in2,LOW);
digitalWrite(in3,LOW);
digitalWrite(in4,LOW);
digitalWrite(in5,LOW);
digitalWrite(in6,LOW);
digitalWrite(in7,LOW);
digitalWrite(in8,LOW);
}

