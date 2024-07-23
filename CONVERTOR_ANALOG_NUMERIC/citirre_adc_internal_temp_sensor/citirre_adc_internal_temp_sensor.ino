void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  //ADMUX|=B0000100;//citim A4 
  ADMUX|= B00001000;

  ADMUX|=B1100000;//REFS1 si REFS0 sunt egale cu 1 deci refereinta este la 1.1V
  //conversie
  ADCSRA|=B110000;//ADEN and ADSC equal to 1 (start conversion)
  while(bit_is_set(ADCSRA,ADSC));
  //int value  = ADCL | (ADCH<<8)//16 bit respond 
  //sa zicem ca vrem sa aflam sau sa afisam nivelul unei baterii pe ecranul lcd
  //float value =ADCL | (ADCH<<8);
  //value = value * 5.7;//voltage devider to the vcc input invered 
  //devider out = ln*(R1/R2 + R2)
  //1 k 4.7 k

  long raw_temperature = ADCL | (ADCH<<8);
  long temperature=(raw_tepererature -53)/1.22;
  Serial.println(temperature);
  delay(500);

}
