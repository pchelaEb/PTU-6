void setup()
{
 //IRRC_setup(IN1, 5);
 pinMode( OUT1 , OUTPUT );
 pinMode( OUT2 , OUTPUT );
 pinMode( OUT3 , OUTPUT );
}

void OutRandomLed()
{
  int port = random(3);
  switch(port){
    case 0: lightLed(OUT1); break;
    case 1: lightLed(OUT2);break;
    case 2: lightLed(OUT3);break;
    
  }
}
void lightLed(int port){
  led(port,HIGH); delay(1000); led(port, LOW);
  }
void loop()
{
 
 if(irBlack(OUT1,100)){
  OutRandomLed();
 }
}
 
