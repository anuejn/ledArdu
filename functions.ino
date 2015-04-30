void fillWithTo(int fr, int fg, int fb, int br, int bg, int bb, float to) {
  float criticalPixel = to * NUMPIXELS;
  float modCriticalPixel = fmod(criticalPixel, 1);
  for(int i=0; i<NUMPIXELS; i++){
    if(i < criticalPixel -1) {
      pixels.setPixelColor(i, pixels.Color(fr, fg, fb)); // Moderately bright green color.
    } 
    else if(i > criticalPixel) {
      pixels.setPixelColor(i, pixels.Color(br, bg, bb)); // Moderately bright green color.
    } 
    else {
      pixels.setPixelColor(i, pixels.Color((1 - modCriticalPixel) * br, modCriticalPixel * fg, modCriticalPixel * fb)); // Moderately bright green color.
    }
  }
  pixels.setPixelColor(round(to * 100 * NUMPIXELS) % NUMPIXELS, pixels.Color(0, 0, 255 * to)); // Moderately bright green color.
}

void fillWith(int fr, int fg, int fb) {
  for(int i=0; i<NUMPIXELS; i++){
    pixels.setPixelColor(i, pixels.Color(fr, fg, fb)); // Moderately bright green color.
  }
}

long readVcc() {
  // Read 1.1V reference against AVcc
  // set the reference to Vcc and the measurement to the internal 1.1V reference
  #if defined(__AVR_ATmega32U4__) || defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
    ADMUX = _BV(REFS0) | _BV(MUX4) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
  #elif defined (__AVR_ATtiny24__) || defined(__AVR_ATtiny44__) || defined(__AVR_ATtiny84__)
    ADMUX = _BV(MUX5) | _BV(MUX0);
  #elif defined (__AVR_ATtiny25__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__)
    ADMUX = _BV(MUX3) | _BV(MUX2);
  #else
    ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
  #endif  
 
  delay(2); // Wait for Vref to settle
  ADCSRA |= _BV(ADSC); // Start conversion
  while (bit_is_set(ADCSRA,ADSC)); // measuring
 
  uint8_t low  = ADCL; // must read ADCL first - it then locks ADCH  
  uint8_t high = ADCH; // unlocks both
 
  long result = (high<<8) | low;
 
  result = 1125300L / result; // Calculate Vcc (in mV); 1125300 = 1.1*1023*1000
  return result; // Vcc in millivolts
}
