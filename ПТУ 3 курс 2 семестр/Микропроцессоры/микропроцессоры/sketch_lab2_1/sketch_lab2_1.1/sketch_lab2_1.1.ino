void setup()
{
 pinMode( OUT1 , OUTPUT );
}


void loop()
{
 int lightLevel = cdsAnalog(IN1);
 ledPWM(OUT1,lightLevel);

}
 
