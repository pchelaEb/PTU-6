void setup() {

}

void loop() {
 if(flame(IN1))
 {
   tone(OUT1, 1000);
   delay(1000);
   noTone(OUT1);
   delay(1000);
 }
}


