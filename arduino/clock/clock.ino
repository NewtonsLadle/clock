/*
 * Nick Heller
 * 1/2/17
 * Word Clock Present for Hailey
 */

#include <Time.h>

// set word pinout integers
int w_ten = 52;
int w_half = 53;
int w_twenty = 51;
int w_minutes = 50;
int w_quarter = 48;
int w_to = 47;
int w_past = 44;
int w_five = 49;
int w_oclock = 33;

// set number pinout integers
int n_one = 38;
int n_two = 39;
int n_three = 45;
int n_four = 46;
int n_five = 37;
int n_six = 43;
int n_seven = 36;
int n_eight = 35;
int n_nine = 40;
int n_ten = 42;
int n_eleven = 34;
int n_twelve = 41;

// button pin
int b_button = 32;
int is_pressed = 0;

// last time incremented
int last_inc = 0;

// current hour
int t_hour = 0;

// current minute
int t_minute = 0;

// time since increment
int interval = 0;

void clearall() {
  // Iterate through all word displays
  digitalWrite(w_ten, LOW);
  digitalWrite(w_half, LOW);
  digitalWrite(w_quarter, LOW);
  digitalWrite(w_twenty, LOW);
  digitalWrite(w_five, LOW);
  digitalWrite(w_minutes, LOW);
  digitalWrite(w_past, LOW);
  digitalWrite(w_to, LOW);

  // Iterate through all number displays
  digitalWrite(n_one, LOW);
  digitalWrite(n_two, LOW);
  digitalWrite(n_three, LOW);
  digitalWrite(n_four, LOW);
  digitalWrite(n_five, LOW);
  digitalWrite(n_six, LOW);
  digitalWrite(n_seven, LOW);
  digitalWrite(n_eight, LOW);
  digitalWrite(n_nine, LOW);
  digitalWrite(n_ten, LOW);
  digitalWrite(n_eleven, LOW);
  digitalWrite(n_twelve, LOW);

  // Cap it off
  digitalWrite(w_oclock, LOW);
}

// It is _____ oclock
void blank() {
  digitalWrite(w_oclock, HIGH);  
}

// It is five minutes past _____
void blank_oh_five() {
  digitalWrite(w_five, HIGH);
  digitalWrite(w_minutes, HIGH);
  digitalWrite(w_past, HIGH);
}

// It is ten minutes past _____
void blank_ten() {
  digitalWrite(w_ten, HIGH);
  digitalWrite(w_minutes, HIGH);
  digitalWrite(w_past, HIGH);
}

// It is quarter past _____
void blank_fifteen() {
  digitalWrite(w_quarter, HIGH);
  digitalWrite(w_past, HIGH);
}

// It is twenty minutes past _____
void blank_twenty() {
  digitalWrite(w_twenty, HIGH);
  digitalWrite(w_minutes, HIGH);
  digitalWrite(w_past, HIGH);
}

// It is quarter past _____
void blank_twentyfive() {
  digitalWrite(w_twenty, HIGH);
  digitalWrite(w_five, HIGH);
  digitalWrite(w_minutes, HIGH);
  digitalWrite(w_past, HIGH);
}

// It is half past _____
void blank_thirty() {
  digitalWrite(w_half, HIGH);
  digitalWrite(w_past, HIGH);
}

// It is twenty five minutes to _____
void blank_thirtyfive() {
  digitalWrite(w_twenty, HIGH);
  digitalWrite(w_five, HIGH);
  digitalWrite(w_minutes, HIGH);
  digitalWrite(w_to, HIGH);
}

// It is twenty minutes to _____
void blank_forty() {
  digitalWrite(w_twenty, HIGH);
  digitalWrite(w_minutes, HIGH);
  digitalWrite(w_to, HIGH);
}

// It is quarter to _____
void blank_fortyfive() {
  digitalWrite(w_quarter, HIGH);
  digitalWrite(w_to, HIGH);
}

// It is ten minutes to _____
void blank_fifty() {
  digitalWrite(w_ten, HIGH);
  digitalWrite(w_minutes, HIGH);
  digitalWrite(w_to, HIGH);
}

// It is five minutes to _____
void blank_fiftyfive() {
  digitalWrite(w_five, HIGH);
  digitalWrite(w_minutes, HIGH);
  digitalWrite(w_to, HIGH);
}

void render_minute(int loc_minute) {
  if (loc_minute == 0) {
    blank();
  }
  else if (loc_minute == 5) {
    blank_oh_five();
  }
  else if (loc_minute == 10) {
    blank_ten();
  }
  else if (loc_minute == 15) {
    blank_fifteen();
  }
  else if (loc_minute == 20) {
    blank_twenty();
  }
  else if (loc_minute == 25) {
    blank_twentyfive();
  }
  else if (loc_minute == 30) {
    blank_thirty();
  }
  else if (loc_minute == 35) {
    blank_thirtyfive();
  }
  else if (loc_minute == 40) {
    blank_forty();
  }
  else if (loc_minute == 45) {
    blank_fortyfive();
  }
  else if (loc_minute == 50) {
    blank_fifty();
  }
  else if (loc_minute == 55) {
    blank_fiftyfive();
  }  
}

void render_hour(int loc_hour) {
  if (loc_hour == 0) {
    digitalWrite(n_twelve, HIGH);
  }
  else if (loc_hour == 1) {
    digitalWrite(n_one, HIGH);
  }
  else if (loc_hour == 2) {
    digitalWrite(n_two, HIGH);
  }
  else if (loc_hour == 3) {
    digitalWrite(n_three, HIGH);
  }
  else if (loc_hour == 4) {
    digitalWrite(n_four, HIGH);
  }
  else if (loc_hour == 5) {
    digitalWrite(n_five, HIGH);
  }
  else if (loc_hour == 6) {
    digitalWrite(n_six, HIGH);
  }
  else if (loc_hour == 7) {
    digitalWrite(n_seven, HIGH);
  }
  else if (loc_hour == 8) {
    digitalWrite(n_eight, HIGH);
  }
  else if (loc_hour == 9) {
    digitalWrite(n_nine, HIGH);
  }
  else if (loc_hour == 10) {
    digitalWrite(n_ten, HIGH);
  }
  else if (loc_hour == 11) {
    digitalWrite(n_eleven, HIGH);
  }
}

void render() {
  // effective hour is actual hour that shows up
  int eff_hour = t_hour;
  /*
  if (minute > 35) {
    eff_hour = (hour + 1)%12;
  }
  */
  clearall();
  render_minute(t_minute);
  render_hour(eff_hour);
}

void increment() {
  Serial.println("INCREMENTING");
  last_inc = now();
  t_minute = (t_minute + 5)%60;
  if (t_minute == 35) {
    t_hour = (t_hour + 1)%12;
  }
  render();
}



void diagnostics() {
  Serial.println("RUNNING DIAGNOSTIC");
  int delay_time = 200;
  // Iterate through all word displays
  digitalWrite(w_ten, HIGH);
  delay(delay_time);
  digitalWrite(w_ten, LOW);
  delay(delay_time);

  digitalWrite(w_half, HIGH);
  delay(delay_time);
  digitalWrite(w_half, LOW);
  delay(delay_time);

  digitalWrite(w_quarter, HIGH);
  delay(delay_time);
  digitalWrite(w_quarter, LOW);
  delay(delay_time);

  digitalWrite(w_twenty, HIGH);
  delay(delay_time);
  digitalWrite(w_twenty, LOW);
  delay(delay_time);

  digitalWrite(w_five, HIGH);
  delay(delay_time);
  digitalWrite(w_five, LOW);
  delay(delay_time);
  
  digitalWrite(w_minutes, HIGH);
  delay(delay_time);
  digitalWrite(w_minutes, LOW);
  delay(delay_time);

  digitalWrite(w_past, HIGH);
  delay(delay_time);
  digitalWrite(w_past, LOW);
  delay(delay_time);

  digitalWrite(w_to, HIGH);
  delay(delay_time);
  digitalWrite(w_to, LOW);
  delay(delay_time);

  // Iterate through all number displays
 
  digitalWrite(n_one, HIGH);
  delay(delay_time);
  digitalWrite(n_one, LOW);
  delay(delay_time);

  digitalWrite(n_two, HIGH);
  delay(delay_time);
  digitalWrite(n_two, LOW);
  delay(delay_time);

  digitalWrite(n_three, HIGH);
  delay(delay_time);
  digitalWrite(n_three, LOW);
  delay(delay_time);

  digitalWrite(n_four, HIGH);
  delay(delay_time);
  digitalWrite(n_four, LOW);
  delay(delay_time);

  digitalWrite(n_five, HIGH);
  delay(delay_time);
  digitalWrite(n_five, LOW);
  delay(delay_time);

  digitalWrite(n_six, HIGH);
  delay(delay_time);
  digitalWrite(n_six, LOW);
  delay(delay_time);

  digitalWrite(n_seven, HIGH);
  delay(delay_time);
  digitalWrite(n_seven, LOW);
  delay(delay_time);

  digitalWrite(n_eight, HIGH);
  delay(delay_time);
  digitalWrite(n_eight, LOW);
  delay(delay_time);

  digitalWrite(n_nine, HIGH);
  delay(delay_time);
  digitalWrite(n_nine, LOW);
  delay(delay_time);

  digitalWrite(n_ten, HIGH);
  delay(delay_time);
  digitalWrite(n_ten, LOW);
  delay(delay_time);

  digitalWrite(n_eleven, HIGH);
  delay(delay_time);
  digitalWrite(n_eleven, LOW);
  delay(delay_time);

  digitalWrite(n_twelve, HIGH);
  delay(delay_time);
  digitalWrite(n_twelve, LOW);
  delay(delay_time);

  // Cap it off
  digitalWrite(w_oclock, HIGH);
  delay(delay_time);
  digitalWrite(w_oclock, LOW);
  delay(delay_time);

  Serial.println("FINISHED DIAGNOSTIC");
}

void check_button() {
  //Serial.println("CHECKING BUTTON");
  digitalWrite(b_button, HIGH);
  if (digitalRead(b_button) == LOW) {
    //Serial.println("BUTTON PRESSED");
    if (is_pressed == 0) {
      increment();
    }
    is_pressed = 1;
  }
  else {
    //Serial.println("BUTTON NOT PRESSED");
    is_pressed = 0;
  }
  digitalWrite(b_button, LOW);
}

void setup() {
  Serial.begin(9600);

  // set word pinout types
  pinMode(w_ten, OUTPUT);
  pinMode(w_half, OUTPUT);
  pinMode(w_twenty, OUTPUT);
  pinMode(w_minutes, OUTPUT);
  pinMode(w_quarter, OUTPUT);
  pinMode(w_to, OUTPUT);
  pinMode(w_past, OUTPUT);
  pinMode(w_five, OUTPUT);
  pinMode(w_oclock, OUTPUT);

  // set number pinout types
  pinMode(n_one, OUTPUT);
  pinMode(n_two, OUTPUT);
  pinMode(n_three, OUTPUT);
  pinMode(n_four, OUTPUT);
  pinMode(n_five, OUTPUT);
  pinMode(n_six, OUTPUT);
  pinMode(n_seven, OUTPUT);
  pinMode(n_eight, OUTPUT);
  pinMode(n_nine, OUTPUT);
  pinMode(n_ten, OUTPUT);
  pinMode(n_eleven, OUTPUT);
  pinMode(n_twelve, OUTPUT);

  // set button pin
  pinMode(b_button, INPUT);

  diagnostics();

  clearall();

  render();
}

void loop() {
  check_button();
  interval = now() - last_inc;
  Serial.print(interval);
  Serial.println(" since last increment");
  if (interval > 300) {
    increment();
  }
  delay(50);

}
