int hour = 15;
int minute = 53;
int CA_1 = 12;
int CA_2 = 11;
int CA_3 = 10;
int CA_4 = 9;
int clk = 6;
int latch = 5;
int data = 4;
int count = 0;
int digits[4] ;
unsigned long current_time = 0;
unsigned long previous_time = 0;
unsigned long interval = 60000;
int CAS[4] = {12, 11, 10, 9};
byte numbers[10] {B11111100, B01100000, B11011010, B11110010, B01100110, B10110110, B10111110, B11100000, B11111110, B11110110};
//byte combinations for each number 0-9
void setup() {
  pinMode(CA_1, OUTPUT);
  pinMode(CA_2, OUTPUT);
  pinMode(CA_3, OUTPUT);
  pinMode(CA_4, OUTPUT);
  pinMode(clk, OUTPUT);
  pinMode(latch, OUTPUT);
  pinMode(data, OUTPUT);
  digitalWrite(CA_1, HIGH);
  digitalWrite(CA_2, HIGH);
  digitalWrite(CA_3, HIGH);
  digitalWrite(CA_4, HIGH);
}

void loop() {
  clocknum();
  display_number();
  delay(2);
}

void clocknum() {
  digits[0]= hour/10;
  digits[1]= hour%10;
  digits[2] = minute/10;
  digits[3] = minute%10;

  current_time = millis();
  
  if (current_time - previous_time >= interval){
    minute += 1;
    digits[3] = minute%10;
    digits[2] = minute/10;
    if (minute == 60){
      hour += 1;
      minute = 0;
      digits[2]=0;
      digits[3]=0;
      digits[1]= hour%10;
      digits[0]= hour/10;
      if (hour == 24){
        hour = 0;
        digits[0]=0;
        digits[1]=0;
        }
      }
    previous_time = current_time;
  }
}

void display_number() { //scanning
  cathode_high(); //black screen
  digitalWrite(latch, LOW); //put the shift register to read
  shiftOut(data, clk, LSBFIRST, numbers[digits[count]]); //send the data
  digitalWrite(CAS[count], LOW); //turn on the relevent digit
  digitalWrite(latch, HIGH); //put the shift register to write mode
  count++; //count up the digit
  if (count == 4) { // keep the count between 0-3
    count = 0;
  }
}

void cathode_high() { //turn off all 4 digits
  digitalWrite(CA_1, HIGH);
  digitalWrite(CA_2, HIGH);
  digitalWrite(CA_3, HIGH);
  digitalWrite(CA_4, HIGH);
}
