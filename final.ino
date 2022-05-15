#include<Servo.h>



/**********************************************/
#define EMG_CH_1    A0
#define EMG_CH_2    A1
/**********************************************/
#define THUMB_CH        7
#define FINGER_1_CH    8
#define FINGER_2_CH    9
#define FINGER_3_CH    10
#define FINGER_4_CH    11
#define FINGER_5_CH    12
/**********************************************/




/**********************************************/
#define Calibrated_Max   800
#define Calibrated_Min   500
/**********************************************/
typedef enum PATTERN_H
{
  PAT_GRASPING ,
  PAT_EXTENSION ,
  PAT_KEY_HOLDING
  
}PATTERN_t ;
/**********************************************/


void Pattern_Set(uint8_t Pattern) ;


/**********************************************/
Servo FIN_THUMB_2;
Servo FINGER_1, FINGER_2, FINGER_3, FINGER_4, FINGER_5;
/**********************************************/
int EMG_1_Reading , EMG_2_Reading  ;
uint8_t Pattern_1[6]= { 125,155,165,155,7,60 }  ;
uint8_t Pattern_2[6]= {70,60,60,60,1,45}  ;
uint8_t Pattern_3[6]= {70,60,170,170,9,40}  ;
uint8_t Pattern_4[6]= {70,60,60,180,9,40}  ;
/**********************************************/



/**********************************************/
void setup() {

  /* Actuators Init */
  FIN_THUMB_2.attach(THUMB_CH);
  
  FINGER_1.attach(FINGER_1_CH);
  FINGER_2.attach(FINGER_2_CH);
  FINGER_3.attach(FINGER_3_CH);
  FINGER_4.attach(FINGER_4_CH);
  FINGER_5.attach(FINGER_5_CH);

  /* Sensor Init */
  pinMode(EMG_CH_1,INPUT);
  pinMode(EMG_CH_2,INPUT);

  /* Serial Monitor */
  Serial.begin(9600); 

}
/**********************************************/






/**********************************************/
void loop() {

  /* Get data */
  EMG_1_Reading=analogRead(EMG_CH_1); 
  EMG_2_Reading=analogRead(EMG_CH_2); 

  Serial.print("s1=");   Serial.println(x);
  Serial.print("s2=");   Serial.println(y);


  /* Set Pattern */
  if(x>Calibrated_Max)
  {
    Pattern_Set(PAT_GRASPING) ;
  }
  else if (x<Calibrated_Min)
  {
    Pattern_Set(PAT_EXTENSION) ;
  }
  /* we used Neural network control for pattern recognition but we have issue in usage, So we used simple instruction for one patetrn */
  else if ((x<=Calibrated_Max) && (y>=Calibrated_Min))
  {
    Pattern_Set(PAT_KEY_HOLDING) ;
  }

}
/**********************************************/




/**********************************************/
int pos_update (int * array)  ;


void Pattern_Set(uint8_t Pattern) 
{
  switch (Pattern)
  {
   case PAT_GRASPING:    pos_update (Pattern_1) ;     break ;

   case PAT_EXTENSION:   pos_update (Pattern_2) ;     break ;
     
   case PAT_KEY_HOLDING:   pos_update (Pattern_3) ;   break ;

    }  
}
/**********************************************/


/**********************************************/
int pos_update (int * array)
{

  FIN_THUMB_2.write(array[5]);
  
  FINGER_1.write(array[0]);
  FINGER_2.write(array[1]);
  FINGER_3.write(array[2]);
  FINGER_4.write(array[3]);
  FINGER_5.write(array[4]);
}
/**********************************************/
