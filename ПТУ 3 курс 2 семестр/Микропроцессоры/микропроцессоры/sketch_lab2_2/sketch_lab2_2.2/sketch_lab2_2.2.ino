void setup() {
 IRRC_setup(IN1, 1);
}
void Piano(int freq)
{
  tone(OUT1, freq);
   delay(100);
   noTone(OUT1);
}
void loop() {
  
  if (RC(F1_KEY))
  {
    Piano(261);
  }
  if (RC(F2_KEY))
  {
    Piano(293);
  }
  if (RC(F3_KEY))
  {
    Piano(329);
  }
  if (RC(F4_KEY))
  {
    Piano(349);
  }
  if (RC(F5_KEY))
  {
    Piano(391);
  }
  if (RC(F6_KEY))
  {
    Piano(440);
  }
}

