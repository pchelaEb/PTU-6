void setup()
{
 pinMode( OUT1 , OUTPUT );
}


void loop()
{

 if(irBlack(IN1,100)) {
  led(OUT1,HIGH);
 }
 else led(OUT1, LOW);
}
 
