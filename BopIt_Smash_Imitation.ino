/*

Bop It! Smash
Pablo Conde
pabloimconde@gmail.com

29-12-2018
16-01-2019
15-02-2019
*/
//-----------------A5,12,11,10,9,fre,5,6,3,2,A0
 int led[] = {A1,A4,10,11,12,88,A3,A5,4,2,5};//leds from left to right

 int lrgb[]= {A2,A0,13};
//-----------------R,G,B,----

const char nleds = 11; //number of leds
int nld=0; //position of led

int last_on[]={0,0};
char lastnld;
char rgb=' ';

const char pinBuzzer = 3;// PIN DEL BUZZER
const int tonos[] = {222, 265, 400, 600, 800, 900, 1200};

int button = 9;

int retar;
unsigned long prev = 0;
unsigned long lastpress;

bool bstate = false; //para el estado del pulsador current/prev
bool fstime=true; //first time. default yes. and so we can see welcome animation

int finta;//en los momentos previos a los tres leds del centro
int tiempo;
int azar;

  int vidas = 3;
  int score = 0;
  int lvl = 1;

  void BPG()//Sound animation when button pressed in a good moment
  {
    lasturnto(0);
    tone(pinBuzzer, tonos[0]); 
    delay(200);
    lasturnto(1);
    delay(180);
    tone(pinBuzzer, tonos[1]); 
    lasturnto(0);
    delay(200);
    noTone(pinBuzzer);
    lasturnto(1);    
  }

  void BPB()//Sound animation when button is pressed in a bad moment
  {
    lasturnto(0);
    tone(pinBuzzer, tonos[1]); 
    delay(200);
    lasturnto(1);
    delay(180);
    tone(pinBuzzer, tonos[0]);
    lasturnto(0);
    delay(200);
    noTone(pinBuzzer);
    lasturnto(1);
  }
  void BTS()//another sound animation 
  {
    for (int iTono = 0; iTono <= 3; iTono++)
    {
     tone(pinBuzzer, tonos[3]);
     delay(150);
     noTone(pinBuzzer);
     delay(50);
    }
    noTone(pinBuzzer);   
  }
void tiempolvl(){
  ///*
  if((score-(lvl*10))<=2 && (score-(lvl*10))>=0){//check when score is a 10 multiple
    //becuase for each 10 points you level up.
    score=lvl*10;
    lvl++;
    inicio();
  }
  
  randomSeed(millis());
  tiempo = random(10);
  if(tiempo<5){
    retar=55-(lvl*10);
    if(retar<=30)retar=30;//<--the less time it can reach. No matters how difficult.
  }  
  if(tiempo>=5 && tiempo<=8){
    retar=65-(lvl*10);
    if(retar<=35)retar=35;
  }
  if(tiempo>=9 && tiempo<12){   
    retar =70-(lvl*10);
    if(retar<=45)retar=40;
  }
}

void trick(){
  if((nld==(nleds/2)-2 || nld==(nleds/2)+2) && (lastnld==(nleds/2)-3 || lastnld==(nleds/2)+3) && lvl>=3){//if just before the three leds of center
    randomSeed(millis());
    char var=random(10);
    
    if(var>=3 && var<5){
      finta=-25;
    }
    else if(var>=8 && var<10){
      finta=700;
    }
    
    var=random(10);//JUMP OR NO JUMP
    if(var>5){//jump
      if(nld==(nleds/2)-2){//from left to right
        nld+=4;
      }
      else{//from right to left
        nld-=4;
      }
    }
    
  }
  else{
    finta=0;
  }
}
    
  void caso_1()
{
    lasturnto(0);
    digitalWrite(led[0],1);//primer y segundo led 
    digitalWrite(led[1],1);
    delay(1000);
    digitalWrite(led[0],0);
    digitalWrite(led[1],0);
    delay(100);
    digitalWrite(led[0],1); 
    delay(500);
    digitalWrite(led[0],0);
  
}

void caso_2()
{
    lasturnto(0);
    digitalWrite(led[0],1);//tres primeros leds
    digitalWrite(led[1],1);
    digitalWrite(led[2],1);
    delay(1000);
    digitalWrite(led[0],0);//tres primeros leds
    digitalWrite(led[1],0);
    digitalWrite(led[2],0);
    delay(100);
    digitalWrite(led[0],1);//dos primeros leds
    digitalWrite(led[1],1);
    delay(500);
    digitalWrite(led[0],0);//dos primeros leds
    digitalWrite(led[1],0);
  
}

void caso_2_R()
{
    
    lasturnto(0);
    digitalWrite(led[0],1);//led primero
    delay(1000);
    digitalWrite(led[0],0);//led primero
    delay(100);
    digitalWrite(led[0],1);//dos primeros
    digitalWrite(led[1],1);   
    delay(500);
    digitalWrite(led[0],0);//dos primeros
    digitalWrite(led[1],0);  
  
}

void caso_3()
{
    lasturnto(0);
    digitalWrite(led[0],1);//dos primeros
    digitalWrite(led[1],1);  
    delay(1000);
    digitalWrite(led[0],0);//dos primeros
    digitalWrite(led[1],0);  
    delay(100);
    digitalWrite(led[0],1);//tres primeros leds
    digitalWrite(led[1],1);
    digitalWrite(led[2],1);
    delay(500);
    digitalWrite(led[0],0);//tres primeros leds
    digitalWrite(led[1],0);
    digitalWrite(led[2],0);   
}

void inicio()//start animation
{
  tone(pinBuzzer, tonos[2]);
  for(int e= 0;e <(nleds/2); e++){
    if (e==(nleds/2)-2){
      noTone(pinBuzzer);
      tone(pinBuzzer, tonos[0]);
    }
    if (e==(nleds/2)-1){
      noTone(pinBuzzer);
      tone(pinBuzzer, tonos[2]);
    }  
    digitalWrite(led[0+e],HIGH);
    digitalWrite(led[(nleds-1)-e],HIGH);
    delay(40*(e*2));
  }
  noTone(pinBuzzer);
  tone(pinBuzzer, tonos[0]);
  digitalWrite(lrgb[2],HIGH);
  delay(200);
  noTone(pinBuzzer);  
  for(int e = 8; e>0; e--){
    for(int h = 0;h <nleds; h++){
      if(h==(nleds/2)){
        digitalWrite(lrgb[2],HIGH);
        continue;
      }
      digitalWrite(led[h],1);
    }
    if (e%2 == 0){
      tone(pinBuzzer, tonos[3]);
    }
    delay(e*10);
    noTone(pinBuzzer);
    for(int h = 0;h <nleds; h++){
      if(h==(nleds/2)){
        digitalWrite(lrgb[2],LOW);
        continue;
      }
      digitalWrite(led[h],LOW);
    }
    if (e%2 == 0){
      tone(pinBuzzer, tonos[5]);
    }
    delay(e*8);
    noTone(pinBuzzer); 
  }
off();
}

void game_over(){//game over animation
  off();
  for (int d = 1; d < (nleds/2)+1; d++){
    tone(pinBuzzer, tonos[6]+(10*d));
    turn_on(led[d-1]);
    turn_on(led[nleds-d]);
    delay(100 * d);
    turnofflast();
    noTone(pinBuzzer);    
  }
  off();
  turn_on(lrgb[0]);
  for(int f = 1; f< (nleds/2)+1; f++){
   tone(pinBuzzer, tonos[2]+(20*f));
   digitalWrite(led[(nleds/2)+f],HIGH);
   digitalWrite(led[(nleds/2)-f],HIGH);
   delay(100); 
   noTone(pinBuzzer); 
   }
   off();
}

void vidas_pierde(){ //when you lose a life
  BPB();
  if(vidas > 0){
    vidas = vidas - 1;
    switch (vidas){
      case 0:
        game_over();//animation
      break;    
      case 1:
        caso_1();//animation
      break; 
      case 2:
        caso_2();//animation
      break;
    }
  }
}
void vidas_gana()//when you earn a life
{
  BPG();
  if(vidas <3){  
    vidas = vidas + 1;
    switch (vidas){
    case 2:
      caso_2_R();//animation
    break;
    case 3:
      caso_3();//animation
    }
  }
  nscore();
} 
  
void nscore()
{
  BPG();
  if(rgb=='g'){
    score+=3;
  }
  else{
    score+=1;
  }   
  tiempolvl();
}

void off(){
  for(int e=0; e<nleds;e++){
    if(e==nleds/2)continue;
    digitalWrite(led[e],LOW);
  }
  turnofflast();
}

void turn_on(int i){
  digitalWrite(i,HIGH);
  if(last_on[0] !=0 ){
    last_on[1]=i;
  }
  else{
    last_on[0]=i;
  }
}

void lasturnto(int x){
  for(int i=0;i<2;i++){
    if(last_on[i]==0)continue;
    digitalWrite(last_on[i], x);
  }
}

void turnofflast(){
  lasturnto(0);
  last_on[0]=0;
  last_on[1]=0;
  rgb=' ';
}

bool outin(){// is any of the leds outside the center area?
  int x,y;
  x=getIndex(led,nleds,last_on[0]);//index of the two numbers turned on
  y=getIndex(led,nleds,last_on[1]);

  if((x<(nleds/2)-1 && x>=0) || x>(nleds/2)+1 || (y<(nleds/2)-1 && y>=0) || y>(nleds/2)+1){
    return true;
  }
  return false;
}


int getIndex(int list[],int sie, int num){// array, size of array, number looking for
  /*
  Serial.print("Searching: ");
  Serial.println(num);
  */
  for(int i=0; i<sie-1;i++){
    if(list[i]==num){
      return i;//return index
    }
  }
  return -1;//if there is no result found
}

void centered(){
  int i;
  randomSeed(millis());
  int rando=random(15);
  if(rando>=0 && rando <2 && lvl>1){
    rgb='r';
    i=0;
  }
  else if(rando>=2 && rando<=10){
    rgb='g';
    i=1;
  }
  else if(rando>=11 && rando<=14){
    rgb='b';
    i=2;
  }
  turn_on(lrgb[i]);
}

void catchu(){
  int ext;

  if((nld==0) || (nld==(nleds-1)) || (rgb=='r')){
      ext=650;
    }
    else if(nld==(nleds/2)){
      ext=40;
    }
    else{
      ext=0;
    }
  
  while(true){
    if((millis()-prev) <=(retar+finta+ext)){
      if (digitalRead(button) == HIGH){
        if (bstate == false){//if button was'nt pressed 
          bstate=true;
          lastpress=millis();
          //if((nleds/2)-1==nld || (nleds/2)+1==nld){
          if(outin()==false){
            if((nleds/2)==nld){
              switch(rgb){
                case 'r':
                vidas_pierde();
                break;
                case 'g':
                vidas_gana();
                break;
                case 'b':
                nscore();
                break;
              }
            }
            else{
              nscore();
            }
          }
          else{
            vidas_pierde();
          }
        }
      }
      else {
          bstate=false;
      }
    }
    else{
      prev = millis();
      break;
    }
  }
}

void setup() {
  //Serial.begin(9600);
  pinMode(button,INPUT);
  for(int e=0; e<nleds; e++)//declare all leds as OUTPUTs
  {
    //if(e==(nleds/2))continue;
    pinMode(led[e],OUTPUT);
  }
  for(int e=0;e<3;e++){
    pinMode(lrgb[e],OUTPUT);
  }

}

void loop() {
  if(digitalRead(button)==HIGH){ //comienza el juego
    if(bstate==false){
      bstate=true;
      delay(200);
      lastpress=millis();
      vidas = 3;
      score = 0;
      lvl = 1;
      nld=0;
      if(fstime==true){
        inicio();
        fstime=false;
     } 
     while(vidas>0)
      {
        if(millis()-lastpress >=120000){
          off();
          break;
        }
        ///*
        randomSeed(millis());
        azar=random(13);
        
        if(azar>=0 && azar<=4){
          if(nld==0){
            juego_uno_rev(1);
          }
          if(nld==(nleds-1)){
            juego_uno_rev(-1);
          }
        }
        if(azar>=5 && lvl>1 && azar<=8){
          juego_dos();
        }
        if(azar>=9){
          if(nld==0){
            juego_tres(1);
          }
          else if(nld==(nleds-1)){
            juego_tres(-1);
          }
        }
        //*/
      }
      off();
    }
  }
  else{
    bstate=false;
  }
}

void juego_uno_rev(int y)
{
  tiempolvl();
  while(nld>=0 && nld<nleds){
    prev = millis();
    turnofflast();
    if(nld==(nleds/2)){
      centered();
    }
    else{
      trick();
      turn_on(led[nld]);
      rgb='b';
    }
    catchu();
    lastnld=nld;
    if(vidas==0 || (nld+y)==nleds || (nld+y)==-1){
      break;
    }
    nld=nld+y;
  }
}


void juego_dos()
{
  tiempolvl();
  for(nld=0; nld<nleds; nld++){
    prev = millis();
    turnofflast();
    if(nld==(nleds/2)){
      centered();
    }
    else{
      trick();
      turn_on(led[nld]);
      turn_on(led[nleds-1-nld]);
      rgb='b';
    }
    catchu();
    if(vidas==0)break;
    lastnld=nld;
  }
  randomSeed(millis());
  azar=random(10);
  if(azar<5){
    nld=0;
  }
  else{
    nld=nleds-1; 
  }
}

void juego_tres(int y){
  tiempolvl();
  retar+=20;
  while(nld>=0 && nld<nleds){
    prev = millis();
    turnofflast();
    
      trick();
      if(nld != (nleds/2)){
        turn_on(led[nld]);
      }
      else{
        turn_on(lrgb[2]);
      }
      if(nld>=2 || nld<=nleds-3){
        if(nld+(y*2) == (nleds/2)){
          turn_on(lrgb[2]);
        }
        else{
          turn_on(led[nld+(y*2)]); 
        }
      }
      rgb='b';

    catchu();
    lastnld=nld;
    if(vidas==0 || (nld+y)==nleds || (nld+y)==-1){
      break;
    }
    nld=nld+y;
  }
}

/*
 * 
 */
