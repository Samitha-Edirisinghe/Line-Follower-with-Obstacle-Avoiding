
int mr1=8;  //motor right 1
int mr2=9;  //motor right 2
int ml1=10; //motor left 1
int ml2=11; //motor left 2
int sr=6;   //sensor right
int sl=7;   //sensor left
int svr=0;
int svl=0;
int enr=3; 
int enl=5;

int vspeed=120;    
int tspeed=220;
int tdelay=20;

#define echo A0    //Echo pin
#define trigger A1 //Trigger pin

#define servo A2

int Set=15;
int distance_L, distance_F, distance_R; 

void   setup()
{
 Serial.begin(9600); // start serial communication at 9600bps

 pinMode(mr1,OUTPUT);
 pinMode(mr2,OUTPUT);
 pinMode(ml1,OUTPUT);
 pinMode(ml2,OUTPUT);
 pinMode(sr,INPUT);
 pinMode(sl,INPUT);

 pinMode(echo, INPUT );// declare ultrasonic sensor Echo pin as input
 pinMode(trigger, OUTPUT); // declare ultrasonic sensor Trigger pin as Output  

pinMode(servo, OUTPUT);

   for (int angle = 70; angle <= 140; angle += 5)  {
     servoPulse(servo, angle);  }
   for (int angle = 140; angle >= 0; angle -= 5)  {
     servoPulse(servo, angle);  }

   for (int angle = 0; angle <= 70; angle += 5)  {
     servoPulse(servo, angle);  }

 distance_F = Ultrasonic_read();
 delay(3000);
}

void loop()
{
//==============================================
//     Line Follower and Obstacle Avoiding
//============================================== 
 distance_F = Ultrasonic_read();
 Serial.print("D F=");Serial.println(distance_F);

 svr=digitalRead(sr);
 svl=digitalRead(sl);
   
  if(svl==LOW && svr==LOW)
  {
  forward(); // Move forward
  }

  if(svl==HIGH   && svr==LOW)
  {
  left(); // Move left
  }
 
  if(svl==LOW && svr==HIGH)
   { 
  right(); // Move right
  }
  
  if(svl==HIGH && svr==HIGH)
   {
  stop(); // Move stop
  }
  delay(10);

}

void servoPulse (int pin, int angle){
int pwm = (angle*11) + 500;      // Convert angle to microseconds
 digitalWrite(pin, HIGH);
 delayMicroseconds(pwm);
 digitalWrite(pin, LOW);
 delay(50); // Refresh cycle of servo
}


//**********************Ultrasonic_read****************************
long Ultrasonic_read(){
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  long time = pulseIn (echo, HIGH);
  return time / 29 / 2;
}

void compareDistance(){
    if(distance_L > distance_R){
  right();
  delay(500);
  forward();
  delay(600);
  right();
  delay(500);
  forward();
  delay(600);
  right();
  delay(400);
  }
  else{
  right();
  delay(500);
  forward();
  delay(600);
  right();
  delay(500);
  forward();
  delay(600);  
  left();
  delay(400);
  }
}

void Check_side(){
    stop();
    delay(100);
 for (int angle = 70; angle <= 140; angle += 5)  {
   servoPulse(servo, angle);  }
    delay(300);
    distance_R = Ultrasonic_read();
    Serial.print("D R=");Serial.println(distance_R);
    delay(100);
  for (int angle = 140; angle >= 0; angle -= 5)  {
   servoPulse(servo, angle);  }
    delay(500);
    distance_L = Ultrasonic_read();
    Serial.print("D L=");Serial.println(distance_L);
    delay(100);
 for (int angle = 0; angle <= 70; angle += 5)  {
   servoPulse(servo, angle);  }
    delay(300);
    compareDistance();
}


void forward()
 {
  digitalWrite(mr1,HIGH);
   digitalWrite(mr2,LOW);
  digitalWrite(ml1,HIGH);
  digitalWrite(ml2,LOW);
   analogWrite (enr,vspeed);
  analogWrite (enl,vspeed);
 } 

void backward()
   {
  digitalWrite(mr1,LOW);
  digitalWrite(mr2,HIGH);
  digitalWrite(ml1,LOW);
   digitalWrite(ml2,HIGH);
  analogWrite (enr,vspeed);
  analogWrite (enl,vspeed);
   }

void right()
 {
  digitalWrite(mr1,LOW);
  digitalWrite(mr2,HIGH);
   digitalWrite(ml1,HIGH);
  digitalWrite(ml2,LOW);
  analogWrite (enr,tspeed);
   analogWrite (enl,tspeed);
  delay(tdelay);
 } 

void left()
 {
   digitalWrite(mr1,HIGH);
  digitalWrite(mr2,LOW);
  digitalWrite(ml1,LOW);
   digitalWrite(ml2,HIGH);
  analogWrite (enr,tspeed);
  analogWrite (enl,tspeed);
   delay(tdelay);
}  

void stop()
 {
  analogWrite (enr,0);
  analogWrite   (enl,0);
 }