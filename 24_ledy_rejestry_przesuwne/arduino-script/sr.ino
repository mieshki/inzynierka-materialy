int latchPin = 8; //Pin connected to ST_CP of 74HC595

int clockPin = 12; //Pin connected to SH_CP of 74HC595

int dataPin = 11; //Pin connected to DS of 74HC595

void setup() {
  //set pins to output so you can control the shift register
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  Serial.begin(9600);
}

const int SHIFT_REGISTERS_8_BITS = 3;

void setLed(unsigned long mask_int){

  byte mask[SHIFT_REGISTERS_8_BITS]= {};
  mask[0] = mask_int & 0x000000FF; // czerwone
  mask[1] = (mask_int >> 8) & 0x000000FF; // zielone
  mask[2] = (mask_int >> 16) & 0x000000FF; // żółte


  Serial.print("mask[0]=");
  Serial.print(mask[0]);

  Serial.print(", mask[1]=");
  Serial.print(mask[1]);

  Serial.print(", mask[2]=");
  Serial.println(mask[2]);
  
  digitalWrite(latchPin, LOW);

  shiftOut(dataPin, clockPin, MSBFIRST, mask[2]);
  shiftOut(dataPin, clockPin, MSBFIRST, mask[1]);
  shiftOut(dataPin, clockPin, MSBFIRST, mask[0]);
  
  digitalWrite(latchPin, HIGH);
}


void loop() {
  // count from 0 to 255 and display the number
  // on the LEDs


  for(int i = 0; i < 24; i++){
    //byte mask[SHIFT_REGISTERS_8_BITS]= {};
    //mask[0] = 0b00000000; // czerwone
    //mask[1] = 0b00000000; // zielone
    //mask[2] = 0b00000000; // żółte
    unsigned long mask = 0;
    
    Serial.print("I=");
    Serial.println(i);
    
    mask = (unsigned long)1 << i;
    mask |= (unsigned long)2 << i;
    mask |= (unsigned long)4 << i;
    
    Serial.print("mask = ");
    Serial.println(mask, BIN);

    Serial.print("sizeof long = ");
    Serial.println(sizeof(long));
    
    setLed(mask);
    delay(100);  
  }
}
