/**
 * Ten Sided Die
 *
 * This sketch uses digital inputs and outputs to allow a momentary pushbutton
 * to trigger a "dice roll" resulting in a random digit between 0 and 9
 *
 * @author sprky0
 */

/**
 * range of digital pins used by the 7 segment display
 */
int dp1 = 2; // decimal
int dp2 = 3; // bottom right
int dp3 = 4; // bottom
int dp4 = 5; // bottom left
int dp5 = 6; // middle
int dp6 = 7; // top left
int dp7 = 8; // top
int dp8 = 9; // top right

/**
 * digital pin for reading button presses
 */
int button_pin = 11;

/**
 * "ready" blinker
 */
int cycle_delay = 10;
int blink_rate = 250;
int count = 0;
int answer_wait_time = 2000;

/**
 * Numeral templates which relate the order of the above pins to a string containing
 * the pattern which matches its index (eg: index 0 contains the pattern for 0 as a string)
 */ 
int pins[] = {dp1,dp2,dp3,dp4,dp5,dp6,dp7,dp8};
char* numbers[] = {"01110111","01000001","00111011","01101011","01001101","01101110","01111110","01000011","01111111","01001111"};

/**
 * "Meaning" of the above chars
 */
char on = '0';
char off = '1';

/**
 * Loader "spinner" template from above pins
 */
int loader[] = {dp5,dp6,dp7,dp8};

/**
 * Setup the pin ins and outs and clear the display
 */
void setup()
{
  // logging
  Serial.begin(9600);

  // setup output pins
  for(int i = 0; i < 8; i++) {
     pinMode(pins[i], OUTPUT);
  }
  
  pinMode(button_pin, INPUT);

  all_off();

}

/**
 * loop and test the pushedness of the button, as well as making the decimal place blink when ready to be pushed
 */
void loop()
{

  int val = digitalRead(button_pin);  // read input value - 0 or 1 from the digital in

  if (val == LOW) {         // check if the input is HIGH (button released)

    digitalWrite(pins[0],LOW);
    new_random();
    delay(answer_wait_time);
    all_off();

  } else {

    if (count > blink_rate && count < blink_rate * 2) {
      digitalWrite(pins[0],HIGH);
    }else if (count >= blink_rate * 2) {
      digitalWrite(pins[0],LOW);
      count = 0;
    } else {
      // nothin 
    }

    count = count + cycle_delay;
    delay(cycle_delay);

  }

}

void new_random() {
 
  show_spinner(2); 

  int randy = random(1,8);

  show(randy);

}

/**
 * Show a numeral on the display
 */
void show(int number) {

  int pin_state = HIGH;

  all_off();

  for (int i = 0; i < 8; i++) {
    pin_state = numbers[number][i] == on ? HIGH : LOW;
    digitalWrite(pins[i], pin_state);
  }

}

/**
 * Show the "spinner" loading pattern for a certain number of loops
 */
void show_spinner(int loops) {

  int loopcount = 0;
  int i = 0;

  for(loopcount = 0; loopcount < loops; loopcount++) {
    for(i = 0; i < 4; i++) {
      all_off();
      digitalWrite(loader[i],LOW);
      delay(50);
    }
  }
  
  all_off();

}

/**
 * Turn off all parts of the display
 */
void all_off() {

  for (int i =0; i < 8; i++)
    digitalWrite(pins[i],HIGH);

}

/**
 * Loop throgh all the available numerals for testing purposes
 */
void all_numerals() {

  for(int n = 0; n < 10; n++) {

    show(n);
    delay(200);

  }

  all_off();
 
}
