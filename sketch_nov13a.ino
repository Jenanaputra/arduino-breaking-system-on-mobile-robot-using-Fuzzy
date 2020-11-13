int trigPin1 = 11;
int echoPin1 = 12;
int Motor;
int s2 = 3;
int s1 = 4;
int en1= 5;
int en2 = 10;
int s3 = 6;
int s4 =7;
float x1,duration1,negatif1,zero1,positif1,unegatif1,uzero1,upositif1,negatif2,zero2,positif2,unegatif2,uzero2,upositif2,e1,e0,e2;
double uMotor,utotal;

void fuzzyfikasie1(){
  if(e1<0){
    negatif1=1;
    if (e1<=(-10)){
      unegatif1=1;} else if ((e1>-10) && (e1<=0)){
        unegatif1=((-0.1)*(e1));}
    } if ((e1>=(-10)) && (e1<=10)){
      zero1=1;
      if((e1>=-10) && (e1<=0)){
        uzero1=((0.1)*(e1+10));} else if ((e1>0) && (e1<=10)){
          uzero1=((-0.1)*(e1-10));}
      }
      if (e1>0){
        positif1=1;
        if ((e1>0) && (e1<=10)){
          upositif1=((0.1)*(e1));
          } else if (e1>10){
            upositif1=1;}
        }
  }

  void fuzzyfikasie2(){
      if(e2<0){
    negatif2=1;
    if (e2<=(-5)){
      unegatif2=1;} else if ((e2>-5) && (e2<=0)){
        unegatif2=((-0.2)*(e2));}
    } if ((e2>=(-5)) && (e2<=5)){
      zero2=1;
      if((e2>=-5) && (e2<=0)){
        uzero2=((0.2)*(e2+5));} else if ((e2>0) && (e2<=5)){
          uzero2=((-0.2)*(e2-5));}
      }
      if (e2>0){
        positif2=1;
        if ((e2>0) && (e2<=5)){
          upositif2=((0.2)*(e2));
          } else if (e2>5){
            upositif2=1;}
        }
    }


  void fuzzyrules(){
    Motor=0;
    utotal=0;
    if((negatif1==1) && (negatif2==1)){
      Motor=Motor+(min(unegatif1,unegatif2)*250);
      utotal=utotal+min(unegatif1,unegatif2);
      }
    if((negatif1==1) && (zero2==1)){
      Motor=Motor+(min(unegatif1,uzero2)*250);
      utotal=utotal+min(unegatif1,uzero2);
      }
      if((negatif1==1) && (positif2==1)){
        Motor=Motor+(min(unegatif1,upositif2)*250);
        utotal=utotal+min(unegatif1,upositif2);
        }
        if((zero1==1) && (negatif2==1)){
          Motor=Motor+(min(uzero1,unegatif2)*250);
          utotal=utotal+min(uzero1,unegatif2);
          }
          if((zero1==1) && (zero2==1)){
            Motor=Motor+(min(uzero1,uzero2)*0);
            utotal=utotal+min(uzero1,uzero2);
           }
           if((zero1==1) && (positif2==1)){
             Motor=Motor+(min(uzero1,upositif2)*(-250));
             utotal=utotal+min(uzero1,upositif2);
            }
            if((positif1==1) && (negatif2==1)){
          Motor=Motor+(min(upositif1,unegatif2)*(-250));
          utotal=utotal+min(upositif1,unegatif2);
          }
          if((positif1==1) && (zero2==1)){
            Motor=Motor+(min(upositif1,uzero2)*(-250));
            utotal=utotal+min(upositif1,uzero2);
           }
           if((positif1==1) && (positif2==1)){
             Motor=Motor+(min(upositif1,upositif2)*(-250));
             utotal=utotal+min(upositif1,upositif2);
            }
        
    }


    void defuzzyfication(){
      uMotor=Motor/utotal;
      }

   
 void output2(){
 
        if (uMotor>=0){
             digitalWrite(s1, LOW);
            digitalWrite(s2, HIGH);
            digitalWrite(s3, LOW);
            digitalWrite(s4, HIGH);        
          for (int m_speed =(0); m_speed<=uMotor; m_speed++){
            analogWrite(en1,m_speed);
            analogWrite(en2,m_speed);
          }  
          } else if (uMotor<0){
          digitalWrite(s1, HIGH);
          digitalWrite(s2, LOW);
          digitalWrite(s3, HIGH);
          digitalWrite(s4, LOW);
          for (int m_speed =(0); m_speed<=(-1*uMotor); m_speed++){
            analogWrite(en1,m_speed);
            analogWrite(en2,m_speed);
          }  
        }
 }
 
void baca_sensor1(){
        //delayMicroseconds(5);
        digitalWrite(trigPin1, LOW);
        delayMicroseconds(5);
        digitalWrite(trigPin1, HIGH);
        delayMicroseconds(10);
         digitalWrite(trigPin1, LOW);
        pinMode(echoPin1, INPUT);
        duration1 = pulseIn(echoPin1, HIGH);
        x1 = (duration1/2) / 29.1;
        }


void hapus(){
  Motor=0;
  utotal=0;
  uMotor=0;

  }
void setup() {
  // put your setup code here, to run once:
 Serial.begin (9600);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(s4, OUTPUT);
  pinMode(en1, OUTPUT);
  pinMode(en2, OUTPUT);
  e0=0;
}

void loop() {
baca_sensor1();
e1=20-x1;
e2=e1-e0;
fuzzyfikasie1();
fuzzyfikasie2();
fuzzyrules();
defuzzyfication();
output2();
Serial.println(x1);
//delay(1000);
hapus();
e0=e1;
}
