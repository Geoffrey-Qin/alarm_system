/*
   Project Name: Alarm System
   Purpose: This product is designed to protect you and your family's safety it will alert you
   with alarm souding if there is a breach in the house and the alarm system is armed.
   Author Name: Geoffrey, Qin & Manbir, Arora
   Date : October 4th, 2017
   Instruction:
   1.After assemble the circuit and connect it to power, the yellow LED will stay on all the time, and the LCD will display "Factory Password”.
   2.Enter the factory password to begin to set alarm system up, the default password on this one is “3957”, push “#” key in the end to send password.
   3.If the password entered is correct, the LCD will display “New Password” on the top row and “Correct” on the bottom row. The system will allow the user to set up a new password, push # key to finish entering.
   4.After the # key is pushed, the LCD will display the password that user entered on the bottom row and asks the user to confirm it by pushing # key or clear it by pushing * key. If the * key is pressed, the system will go back to step 2 which is setting up a new password and repeat this process until the user confirmed password.
   5. After the user has confirmed the password by pushing the # key, the LCD will display “Status: Armed”, the red LED will light up, and the alarm system is armed now.
   6. The alarm will be triggered and entered a grace period of 30 seconds if the laser sensor(combination of light sensor and yellow LED) is blocked, or the blue wire connected from A7 port of Arduino to the ground(simulating the contact between the door and the door frame) is unplugged and exposed to the air(simulating the door is opened). The LCD will displays “Status: Armed” followed by the countdown of grace period, the buzzer will blips every second, and the red LED will blink once a second.
   7.If the correct password is not entered within the grace period, the alarm will sound loudly with different tones, and the LCD will display intruder message “Calling 911…” on the bottom row.
   8. After entered the correct password at any time that alarm system is armed, the alarm will disarm, the LCD will display “Status: Disarmed” on the top row, red LED turns off, and green LED turns on.
   9. Entering the correct password when the alarm system is disarmed will arm the system, the LCD will display “Status: Armed”, the green LED turns off, the red LED will light up, andthe alarm system is armed now.
   Special Functions:
   a)  Menu Option
    The users could enter setup menu when the alarm system is disarmed by pressing * key 5 times, they could change the password of the alarm system and look at system information as well. The LCD will display “1-Password Reset” on the top row and “2-Information” on the bottom row. The user could enter the number corresponding to each option (either 1 or 2) following by # key to select option.
   b). Factory-Reset
    Factory-Reset will reset the program to factory settings, that includes the password of alarm system and the number of alarm tripped since it run.
   c). Custom Code
    The user can reset their password by selecting this option, the program will ask them to set up a new password and confirm it afterword. Note: the number of alarm tripped will not be reset in this operation.
   d). Information
    The user could view how many times that the alarm is tripped (alarm began sounding) since it run.
    The number of alarm tripped can be reset to 0 by applying factory-reset
   e). Suspense Period:
    In alarm state (not triggered, or in grace period, or alarm sounding), the system will freeze itself for 10 seconds if the password is entered wrong too many times (10 seconds freeze every 5 incorrect entry).
   For more detailed explanation with images, please view alarm system manual attached.
*/
///////////////// Buzzer Set up //////////////
#define NOTE_B0 31
#define NOTE_C1 33
#define NOTE_CS1 35
#define NOTE_D1 37
#define NOTE_DS1 39
#define NOTE_E1 41
#define NOTE_F1 44
#define NOTE_FS1 46
#define NOTE_G1 49
#define NOTE_GS1 52
#define NOTE_A1 55
#define NOTE_AS1 58
#define NOTE_B1 62
#define NOTE_C2 65
#define NOTE_CS2 69
#define NOTE_D2 73
#define NOTE_DS2 78
#define NOTE_E2 82
#define NOTE_F2 87
#define NOTE_FS2 93
#define NOTE_G2 98
#define NOTE_GS2 104
#define NOTE_A2 110
#define NOTE_AS2 117
#define NOTE_B2 123
#define NOTE_C3 131
#define NOTE_CS3 139
#define NOTE_D3 147
#define NOTE_DS3 156
#define NOTE_E3 165
#define NOTE_F3 175
#define NOTE_FS3 185
#define NOTE_G3 196
#define NOTE_GS3 208
#define NOTE_A3 220
#define NOTE_AS3 233
#define NOTE_B3 247
#define NOTE_C4 262
#define NOTE_CS4 277
#define NOTE_D4 294
#define NOTE_DS4 311
#define NOTE_E4 330
#define NOTE_F4 349
#define NOTE_FS4 370
#define NOTE_G4 392
#define NOTE_GS4 415
#define NOTE_A4 440
#define NOTE_AS4 466
#define NOTE_B4 494
#define NOTE_C5 523
#define NOTE_CS5 554
#define NOTE_D5 587
#define NOTE_DS5 622
#define NOTE_E5 659
#define NOTE_F5 698
#define NOTE_FS5 740
#define NOTE_G5 784
#define NOTE_GS5 831
#define NOTE_A5 880
#define NOTE_AS5 932
#define NOTE_B5 988
#define NOTE_C6 1047
#define NOTE_CS6 1109
#define NOTE_D6 1175
#define NOTE_DS6 1245
#define NOTE_E6 1319
#define NOTE_F6 1397
#define NOTE_FS6 1480
#define NOTE_G6 1568
#define NOTE_GS6 1661
#define NOTE_A6 1760
#define NOTE_AS6 1865
#define NOTE_B6 1976
#define NOTE_C7 2093
#define NOTE_CS7 2217
#define NOTE_D7 2349
#define NOTE_DS7 2489
#define NOTE_E7 2637
#define NOTE_F7 2794
#define NOTE_FS7 2960
#define NOTE_G7 3136
#define NOTE_GS7 3322
#define NOTE_A7 3520
#define NOTE_AS7 3729
#define NOTE_B7 3951
#define NOTE_C8 4186
#define NOTE_CS8 4435
#define NOTE_D8 4699
#define NOTE_DS8 4978

////////////////// constants //////////////////

const int COL1 = 35;  //hardcode the pin numbers for keypad
const int COL2 = 31;
const int COL3 = 39;
const int ROW1 = 33;
const int ROW2 = 43;
const int ROW3 = 41;
const int ROW4 = 37;
const int FACTORY_PASSWORD = 3957;  //hardcode the factory password
const int WELCOME_MESSAGE_STATE = 0;    //set up each state of alarm system
const int FACTORY_INITIALIZATION_STATE = 1;
const int SET_UP_PASSWORD_STATE = 2;
const int CONFIRM_PASSWORD_STATE = 3;
const int ARMED_STATE = 4;
const int DISARMED_STATE = 5;
const int GRACE_PERIOD_STATE = 6;
const int ALARM_STATE = 7;
const int MENU_STATE = 8;
const int CHANGE_PASSWORD_STATE = 9;
const int INFORMATION_STATE = 10;
const int COUNT_DOWN_PERIOD = 30;     //hardcode the length of grace period
const int SUSPENSE_PERIOD = 10;       //hardcode the length of suspense period
const int SUSPENSE_STANDARD_TIMES = 5;  //hardcode the number of inputting wrong password that triggers suspense


////////////// global variables //////////////
int total;     //create a variable stores the number enterd
int password;  //create a varaible stores the set password
int pound;     //create a varaible stores the number of # key pressed
int star;      //create a varaible stores the number of * key pressed
int pressed;  //keeps track of how many digits are pressed
int state;    //create a varaible stores state of program
int armed;    //create a varaible stores whether the system is armed or disarmed
int count;    //create a varaible stores the length of grace period
int wrong_password;     //create a varaible stores how many times the user get the password wrong
int suspense_times;     //create a varaible stores the number of inputting wrong password that triggers suspense
int suspense_count;     //create a varaible stores the length of suspense period
int suspense_state;     //create a varaible holds the suspense period is triggered or not
int sensorValue;        //create a varaible stores the value of light sensor
int buzzer_order;       //create a varaible stores the order of the tones that make up the alarm sound
int menu_count;          //create a varaible stores the number of time that * key is pressed to enter menu at disarmed state
int tripped_times;        //create a varaible stores how many times alarm is triggered

long target;            //create a timer for grace period
long dura_target;       //create a timer for alarm buzzer sound
long dura_target2;      //create a second timer for alarm buzzer sound(swithcing tones)
long suspense_period;   //create a timer for suspense period

boolean correct_password; //create a boolean that checks if correct password is enterd
boolean enter_menu;       //create a boolean that checks if user entered setting menu
#include <LiquidCrystal.h>                // include the library code
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);      // select the pins used on the LCD panel
void setup() {
  pinMode(ROW1, INPUT_PULLUP); //Set up the pins for keypad
  pinMode(ROW2, INPUT_PULLUP);
  pinMode(ROW3, INPUT_PULLUP);
  pinMode(ROW4, INPUT_PULLUP);
  pinMode(COL1, OUTPUT);
  pinMode(COL2, OUTPUT);
  pinMode(COL3, OUTPUT);
  pinMode(52, OUTPUT);  //set up the pin for RED LED
  pinMode(53, OUTPUT);  //set up the pin for GREEN LED
  pinMode(50, OUTPUT);  //set up the pin for YELLOW LED
  pinMode(22, OUTPUT);  //set up the pin for buzzer
  digitalWrite (COL1, HIGH);  //output high to column pins of keypad
  digitalWrite (COL2, HIGH);
  digitalWrite (COL3, HIGH);
  digitalWrite(50, HIGH);   //lights up yellow LED which is shining at light sensor to simulate laser gate
  password = FACTORY_PASSWORD;  //stores the factory password
  Serial.begin(9600);       //set up serial monitor
  Serial.println("Ready");
  lcd.begin(16, 2);         //set up lcd
  total = 0;                //set varaibles to 0
  password = 0;
  pound = 0;
  star = 0;
  pressed = 0;
  state = 0;
  armed = 0;
  wrong_password = 0;
  suspense_state = 0;
  sensorValue = 0;
  buzzer_order = 0;
  menu_count = 0;
  tripped_times = 0;

  target = 0;
  dura_target = 0;
  dura_target2 = 0;
  suspense_period = 0;

  suspense_times = SUSPENSE_STANDARD_TIMES; //set the number of inputting wrong password that triggers suspense to preset value
  suspense_count = SUSPENSE_PERIOD;   //set the length of suspense period to preset value
  count = COUNT_DOWN_PERIOD;    //set the length of grace period to preset value

  correct_password = false;     //set booleans to false
  enter_menu = false;
}
////////////// function/methods  //////////////
void lcdOutputRow2(int totalDisp) {
  lcd.setCursor(0, 1);              //set the cursor to the bottom row of lcd
  lcd.print("                ");    //clear the content on the bottom row
  lcd.setCursor(0, 1);              //set the cursor to the bottom row of lcd
  lcd.print("Inputted: ");          //display "Inputted: "
  lcd.print(totalDisp);             //display numbers entered

}
void lcdOutputRow1(String msg) {
  lcd.setCursor(0, 0);               //set the cursor to the top row of lcd
  lcd.print("                ");     //clear the content on the top row
  lcd.setCursor(0, 0);               //set the cursor to the top row of lcd
  lcd.print(msg);                    //display the message
}
void lcdOutputRow1CountDown(String msg, int num) {
  lcd.setCursor(0, 0);               //set the cursor to the top row
  lcd.print("                ");     //clear the content on the top row
  lcd.setCursor(0, 0);               //set the cursor to the top row
  lcd.print(msg);                    //display the message and number entered
  lcd.print(num);
}
void clearRow1() {
  lcd.setCursor(0, 0);              //set the cursor to the bottom row
  lcd.print("                ");    //clear the content on that row
  lcd.setCursor(0, 0);              //set the cursor to the bottom row
}
void clearRow2() {
  lcd.setCursor(0, 1);              //set the cursor to the top row
  lcd.print("                ");    //clear the content on that row
  lcd.setCursor(0, 1);              //set the cursor to the top row
}
void tonePad() {
  tone(22, NOTE_G7);                //keypad press tone
  delay(100);
  noTone(22);
  delay(100);
}
void checkKeypad () {       //check what number is pressed on the keypad

  ////////////// Column 1 /////////////////
  digitalWrite(COL1, LOW);
  digitalWrite (COL2, HIGH);
  digitalWrite (COL3, HIGH);
  if (digitalRead(ROW1) == LOW) {   //key 1
    total = total * 10;
    total = total + 1;
    tonePad();
    //    Serial.print("Row 1:    ");             //Button Press Diagnostic
    //    Serial.println(digitalRead(ROW1));
    //    Serial.print("Row 2:    ");
    //    Serial.println(digitalRead(ROW2));
    //    Serial.print("Row 3:    ");
    //    Serial.println(digitalRead(ROW3));
    //    Serial.print("Row 4:    ");
    //    Serial.println(digitalRead(ROW4));
    //    Serial.print("COL 1:    ");
    //    Serial.println(digitalRead(COL1));
    //    Serial.print("COL 2:    ");
    //    Serial.println(digitalRead(COL2));
    //    Serial.print("COL 3:    ");
    //    Serial.println(digitalRead(COL3));
    while (digitalRead(ROW1) == LOW) {
      delay(100);
    }
    lcdOutputRow2(total);
    Serial.print("Current Output:");
    Serial.println(total);
    pressed ++;
  }
  if (digitalRead(ROW2) == LOW) {   //key 4
    total = total * 10;
    total = total + 4;
    tonePad();
    while (digitalRead(ROW2) == LOW) {
      delay(100);
    }
    lcdOutputRow2(total);
    Serial.print("Current Output:");
    Serial.println(total);
    pressed ++;
  }
  if (digitalRead(ROW3) == LOW) {   //key 7
    total = total * 10;
    total = total + 7;
    tonePad();
    while (digitalRead(ROW3) == LOW) {
      delay(100);
    }
    lcdOutputRow2(total);
    Serial.print("Current Output:");
    Serial.println(total);
    pressed ++;
  }
  if (digitalRead(ROW4) == LOW) {   //key *
    tonePad();
    star = 1;
    while (digitalRead(ROW4) == LOW) {
      delay(100);
    }
  }
  ////////////// Column 2 /////////////////
  digitalWrite(COL1, HIGH);
  digitalWrite(COL2, LOW);
  digitalWrite (COL3, HIGH);
  if (digitalRead(ROW1) == LOW) {   //key 2
    total = total * 10;
    total = total + 2;
    tonePad();
    while (digitalRead(ROW1) == LOW) {
      delay(100);
    }
    lcdOutputRow2(total);
    Serial.print("Current Output:");
    Serial.println(total);
    pressed ++;
  }
  if (digitalRead(ROW2) == LOW) {   //key 5
    total = total * 10;
    total = total + 5;
    tonePad();
    while (digitalRead(ROW2) == LOW) {
      delay(100);
    }
    lcdOutputRow2(total);
    Serial.print("Current Output:");
    Serial.println(total);
    pressed ++;
  }
  if (digitalRead(ROW3) == LOW) {   //key 8
    total = total * 10;
    total = total + 8;
    tonePad();
    while (digitalRead(ROW3) == LOW) {
      delay(100);
    }
    lcdOutputRow2(total);
    Serial.print("Current Output:");
    Serial.println(total);
    pressed ++;
  }
  if (digitalRead(ROW4) == LOW) {   //key 0
    total = total * 10;
    total = total + 0;
    tonePad();
    while (digitalRead(ROW4) == LOW) {
      delay(100);
    }
    lcdOutputRow2(total);
    Serial.print("Current Output:");
    Serial.println(total);
    pressed ++;
  }
  ////////////// Column 3 /////////////////
  digitalWrite (COL1, HIGH);
  digitalWrite(COL2, HIGH);
  digitalWrite(COL3, LOW);
  if (digitalRead(ROW1) == LOW) {   //key 3
    total = total * 10;
    total = total + 3;
    tonePad();
    while (digitalRead(ROW1) == LOW) {
      delay(100);
    }
    lcdOutputRow2(total);
    Serial.print("Current Output:");
    Serial.println(total);
    pressed ++;
  }
  if (digitalRead(ROW2) == LOW) {   //key 6
    total = total * 10;
    total = total + 6;
    tonePad();
    while (digitalRead(ROW2) == LOW) {
      delay(100);
    }
    lcdOutputRow2(total);
    Serial.print("Current Output:");
    Serial.println(total);
    pressed ++;
  }
  if (digitalRead(ROW3) == LOW) {   //key 9
    total = total * 10;
    total = total + 9;
    tonePad();
    while (digitalRead(ROW3) == LOW) {
      delay(100);
    }
    lcdOutputRow2(total);
    Serial.print("Current Output:");
    Serial.println(total);
    pressed ++;
  }
  if (digitalRead(ROW4) == LOW) {   //key #
    pound = 1;
    tonePad();
    while (digitalRead(ROW4) == LOW) {
      delay(100);
    }
  }
}
void loop() {
  switch (state) {          //perform different function according to the value of the state
    case WELCOME_MESSAGE_STATE :      //display message state
      lcdOutputRow1("Factory Password");    // display LCD messages
      Serial.println("Thank you for purchasing the product");
      Serial.println ("Please enter your 4-digits password ");
      Serial.println ("Push # key to finish entering");
      state = FACTORY_INITIALIZATION_STATE;  //go to FACTORY_INITIALIZATION_STATE
      break;
    case FACTORY_INITIALIZATION_STATE :   //check if the password entered matched factory password
      checkKeypad();        //get the number entered from the keypad
      if (pound == 1) {     //if # key is pressed (user finished inputting)
        if (pressed <= 4 && total >= 0) {     // check if the password is legitmate
          if (total == FACTORY_PASSWORD) {    //check if the number entered match the factory password
            correct_password = true;      //password correct
            clearRow2();            //clear content on the bottom row of lcd
            lcd.setCursor(0, 1);    //display "Correct" message
            lcd.print("Correct");
            Serial.println("Password Correct");
            pound = 0;              //reset keypad variables to 0
            total = 0;
            pressed = 0 ;
            state = SET_UP_PASSWORD_STATE;  //go to SET_UP_PASSWORD_STATE
            lcdOutputRow1("New Password:"); //display "New password" message
          }//end if (total == FACTORY_PASSWORD)
          else {
            clearRow2();                //clear content on the bottom row of LCD
            lcd.setCursor(0, 1);        //display "Wrong Password" message
            lcd.print("Wrong Password");
            Serial.println("Wrong password, enter again");
            pound = 0;                  //reset keypad variables to 0
            total = 0;
            pressed = 0 ;
          }//end else if (total == FACTORY_PASSWORD)
        }//end if (pressed <= 4 && total >= 0)
        else {                      //illegitmate password entered(too long)
          Serial.println("Too many digits, try a shorter password");
          lcdOutputRow1("Too Long");  //display "Too long" message
          clearRow2();                //clear content on the bottom row of LCD
          pound = 0;                  //reset kaypad variables to 0
          total = 0;
          pressed = 0;
        }//end else if (pressed <= 4 && total >= 0)
      }//end if (pound == 1)
    case SET_UP_PASSWORD_STATE :     //set up user's own password
      Serial.println("Set up your own password"); //display message
      checkKeypad();                //get the input from keypad
      if (pound == 1) {             //check if # key is pressed(user finished inputting)
        if (pressed <= 4 && total >= 0) {     // check if the password is legitmate
          password = total;         //store the new password
          pound = 0;                //reset keypad variables
          total = 0;
          pressed = 0 ;
          state = CONFIRM_PASSWORD_STATE; //go to CONFIRM_PASSWORD_STATE
          lcdOutputRow1("Right?yes:# no:*");    //display "confirm message"
          Serial.print("You have entered: ");
          Serial.println(password);
          Serial.println("Is this correct? Push # key to confirm, or * key to reset");
        }//end if (pressed <= 4 && total >= 0)
        else {                //if the password is not legitmate
          lcdOutputRow1("Too Long");    //display "too long" message
          clearRow2();                  //clear the content on the bottom row
          Serial.println("Too many digits, try a shorter password");
          pound = 0;                  //reset the variables of keypad
          total = 0;
          pressed = 0;
        }//end else if (pressed <= 4 && total >= 0)
      }//end if (pound == 1)
      break;
    case CONFIRM_PASSWORD_STATE:
      ////////////// Checking for * /////////////////
      digitalWrite(COL1, LOW);
      digitalWrite (COL2, HIGH);
      digitalWrite (COL3, HIGH);
      if (digitalRead(ROW4) == LOW) {   //check if key * is pressed
        star = 1;
        tonePad();
        while (digitalRead(ROW4) == LOW) {
          delay(100);
        }//end while (digitalRead(ROW4) == LOW)
        state = SET_UP_PASSWORD_STATE;  //enter SET_UP_PASSWORD_STATE
        password = 0;       //reset keypad variables
        pound = 0;
        star = 0;
        lcdOutputRow1("New Password:"); //display "New Password" message
        clearRow2();        //clear content on the bottom row of LCD
      }//end if (digitalRead(ROW4) == LOW)
      ////////////// Checking for # /////////////////
      digitalWrite (COL1, HIGH);
      digitalWrite(COL2, HIGH);
      digitalWrite(COL3, LOW);
      if (digitalRead(ROW4) == LOW) {   //check if key # is pressed
        pound = 1;
        tonePad();
        while (digitalRead(ROW4) == LOW) {
          delay(100);
        }//end while (digitalRead(ROW4) == LOW)
        armed = 1;        //reset keypad password
        pound = 0;
        star = 0;
        sensorValue = analogRead(A10); //engage light sensor
        digitalWrite(52, HIGH);   //light up RED LED
        digitalWrite(53, LOW);    //Turn off GREEN LED
        state = ARMED_STATE;      //go to ARMED_STATE
        lcdOutputRow1("Status: Armed"); //display "Armed" message
        clearRow2();              //clear the content on the bottom row of LCD
        wrong_password = 0;       //reset the number of incorrect password entered to 0
        suspense_times = SUSPENSE_STANDARD_TIMES; //reset the number of incorrect-entered-password that triggers suspense period to preset
        Serial.println("The system is armed!");   //display message
      }//end if (digitalRead(ROW4) == LOW)
      break;
    case ARMED_STATE:  //armed status
      sensorValue = analogRead(A10); //engage light sensor
      if (sensorValue < 830 || analogRead(A7) > 200) {  //if the laser sensor is blocked or physical contact is broken
        target = millis(); //sync grace period timer with the time in millis
        state = GRACE_PERIOD_STATE;   //go to GRACE_PERIOD_STATE
      }//end if (sensorValue < 830 || analogRead(A7) > 200)
      if (wrong_password >= suspense_times) { //if passcode are entered incorrectly too many times
        suspense_times = suspense_times + 5;  //increase the number of  incorrect-entered-password that triggers suspense period by 5
        suspense_count = SUSPENSE_PERIOD;     //set suspense period as preset(10 seconds)
        suspense_state = 1;                   //enable suspense period
        clearRow2();                          //clear the content on the bottom row of LCD
        lcd.setCursor(0, 1);                  //display "suspense" message
        lcd.print("Too many errors!");
      }//end if (wrong_password >= suspense_times)
      if (suspense_state == 1 ) {           //check if suspense period is engaged
        lcdOutputRow1CountDown("Suspended! ", suspense_count);  //display the status and count down of suspension period
        if (suspense_count > 0) {           //if the suspense period is not expired
          delay(1000);                      //freeze the program for 1 second
          suspense_count--;                 //count 1 second down in suspense_count
        }//end if (suspense_count > 0)
      }//end if (suspense_state == 1)
      if (suspense_state == 1) {    //check if suspense period is enabled
        if (suspense_count == 0) {  //check if the suspense period expired
          suspense_state = 0;       //disable the suspense period to resume normal operations of alarm system
          lcdOutputRow1("Status: Armed"); //display "Armed" message
          clearRow2();               //clear the contents on the bottom row of LCD
          pound = 0;                  //reset the keypad variables
          total = 0;
          star = 0;
          pressed = 0;
        }//end if (suspense_count == 0)
      }//end if (suspense_state == 1)
      else {              //if the program is not suspended
        checkKeypad();    //get the input number from keypad
      }//end else if (suspense_state == 1)
      if (star == 1) {    //if * key is pressed
        star = 0;         //reset keypad variables
        pound = 0;
        total = 0;        //clear the numbers entered
        pressed = 0;
        clearRow2();      //clear the content on the bottom row of LCD
      }//end if (star == 1)
      if (pound == 1) {   //check if # key is pressed
        if (total == password) {  //check if the numbers entered matched the password
          if (armed == 1) {     //check if the alarm is armed
            armed = 0;          //disarm the system
            pound = 0;          //reset keypad variables
            total = 0;
            pressed = 0 ;
            wrong_password = 0;   //reset suspense period variables
            suspense_times = SUSPENSE_STANDARD_TIMES;
            suspense_count = SUSPENSE_PERIOD;
            sensorValue = 0; //disengage light sensor
            digitalWrite(52, LOW);  //Turn off RED LED
            digitalWrite(53, HIGH); //Turn on GREEN LED
            state = DISARMED_STATE; //go to DISARMED_STATE
            lcdOutputRow1("Status: Disarmed");  //display "Disarmed" message on the LCD
            clearRow2();            //clear the content on the bottom row of LCD
            Serial.println("The system is disarmed!");
          }//end if (armed == 1)
        }//end if (total == password)
        else {    //if the number entered does not match the password
          clearRow2();      //clear the content on the bottom row of LCD
          lcd.setCursor(0, 1);      //display "Wrong Password" message
          lcd.print("Wrong Password");
          Serial.println("Wrong password, enter again");
          pound = 0;        //reset keypad's variables
          total = 0;
          pressed = 0 ;
          wrong_password++; //add one to the value of wrong_password to record the # of incorrect password input
        }//end else if (total == password)
      }//end if(pound == 1)
      break;
    case DISARMED_STATE:  //disarmed status
      if (menu_count >= 5) {    //if * key has been pressed for 5 times
        state = MENU_STATE; //go to MENU_STATE
        lcdOutputRow1("1-Password Reset");  //display "Password Reset" option on the top row of LCD
        clearRow2();    //clear the bottom row of LCD
        lcd.setCursor(0, 1);    //display "Information" option on the bottom row of LCD
        lcd.print("2-Information");
        total = 0;    //reset keypad variables
        pound = 0;
        star = 0;
        menu_count = 0;   //reset menu_count value to 0
        enter_menu = true;  //set enter_menu to true enable menu options
      }//end if (menu_count >= 5)
      count = COUNT_DOWN_PERIOD;  // set count to the preset value for the length of grace period
      checkKeypad();    //get the numbers input from keypad
      if (star == 1) {   //check if * key is pressed
        star = 0;       //reset keypad variables
        pound = 0;
        total = 0;
        pressed = 0;
        clearRow2();    //clear the content on the bottom row of LCD
        menu_count++;   //add one to the value of menu_count to record the number of * key has been pressed
      }// end if (star == 1)

      if (pound == 1) {   //check if * key is pressed
        if (total == password) {  //check if the numbers inputted match the password
          if (armed == 0) {   //check if the alarm system is disarmed
            armed = 1;      //set the alarm system to "armed"
            pound = 0;      //reset keypad variables
            total = 0;
            pressed = 0 ;
            wrong_password = 0;    //reset suspense period variables
            suspense_times = SUSPENSE_STANDARD_TIMES;
            suspense_count = SUSPENSE_PERIOD;
            sensorValue = analogRead(A10); //engage light sensor
            digitalWrite(52, HIGH);   //turn on RED LED
            digitalWrite(53, LOW);    //turn off GREEN LED
            state = ARMED_STATE;      //go to ARMED_STATE
            lcdOutputRow1("Status: Armed"); //display "Armed" message
            clearRow2();              //clear the content on the bottom row of LCD
            Serial.println("The system is armed!");
          }//end if (armed == 0)
        }//end if (total == password)
        else {    //if the number entered does not match with password
          clearRow2();    //clear the content on the bottom row of LCD
          lcd.setCursor(0, 1);    //display "Wrong Password" message
          lcd.print("Wrong Password");
          Serial.println("Wrong password, enter again");
          pound = 0;              //reset keypad variables
          total = 0;
          pressed = 0 ;
        }//end else if(total == password)
      }//end if (pound == 1)
      break;
    case GRACE_PERIOD_STATE: //30 seconds grace period
      if (count <= 0) {     //the the grace period expires
        state = ALARM_STATE;  //go to ALARM_STATE
        lcdOutputRow1("Status: Armed"); //display "Armed" message
        dura_target = millis() + 250;   //set the target time for first buzzer timer
        buzzer_order = 0;      //set the order of buzzer to 0
        clearRow2;            // clear the content on the bottom row of LCD
        pound = 0;            //reset keypad variables
        star = 0;
        total = 0;
        pressed = 0;
        lcd.setCursor(0, 1);      //display "Intruder" message on LCD
        lcd.print("Calling 911...");
      }//end if (count <= 0)
      else {    // if the grace period has not expeired yet
        noTone(22);   //stop buzzer tone
        digitalWrite(52, LOW);  //turn off RED LED
        if (target <= millis()) {   // if the millis is greater than target
          target = millis() + 1000; //set the target 1 second later than the time on millis
          count --;                 //substract one from count to time the grace period
          tone(22, NOTE_G5);        //play "blips" sound on buzzer
          digitalWrite(52, HIGH);    //turn on RED LED
          lcdOutputRow1CountDown("Status: Armed ", count);  //display the status and count down of alarm system
          Serial.print("Count Down: ");
          Serial.println(count);
        }//end if (target <= millis())
        checkKeypad();    //get the numbers inputted from keypad
        if (star == 1) {    //check if * key is pressed
          star = 0;         //reset keypad variables
          pound = 0;
          total = 0;
          pressed = 0;
          clearRow2();      //clear the content on the bottom row of LCD
        }//end if (star == 1)
        if (pound == 1) {   //check if # key is pressed
          if (total == password) {  //check if the number inputted match the password
            armed = 0;          //disarm the system
            state = DISARMED_STATE; //go to DISARMED_STATE
            pound = 0;          //reset keypad variables
            total = 0;
            pressed = 0 ;
            digitalWrite(52, LOW);  //turn off RED lED
            digitalWrite(53, HIGH); //turn on GREEN LED
            lcdOutputRow1("Status: Disarmed");  //display "Disarmed" Message
            clearRow2();    //clear the content on the bottom row of LCD
            Serial.println("The system is disarmed.");
          }// end if (total == password)
          else {    //if the numbers entered does not match with password
            clearRow2();    //clear the content on the bottom row of LCD
            lcd.setCursor(0, 1);      //display "Wrong Password" message on LCD
            lcd.print("Wrong Password");
            Serial.println("Wrong password, enter again");
            pound = 0;      //reset keypad variables
            total = 0;
            pressed = 0 ;
          }//end else if(total == password)
        }//end if (pound == 1)
      }//end else if(count <= 0)
      break;
    case ALARM_STATE:     // alarm soudning state
      checkKeypad();      //get the numbers inputted from the keypad
      if (pressed != 0 && pound == 0) {   //if the password entering is not finished(user is still entering password)
        dura_target = millis() + 50;   //set the target time for first buzzer timer
        buzzer_order = 0;    //set the order of buzzer to 0
      }//end if (pressed != 0 && pound == 0)
      if (star == 1) {    //check if * key is pressed
        star = 0;         //reset keypad variables
        pound = 0;
        total = 0;
        pressed = 0;
        buzzer_order = 0;  //set the order of buzzer to 0
        clearRow2();       //clear the content on the bottom row of LCD
        dura_target = millis() + 50;    //set the target time for first buzzer timer
      }// end if (star == 1)
      if (pound == 1) {     //check if # key is pressed
        if (total == password) {    //check if the numbers entered match with the password
          armed = 0;          //disarm the system
          state = DISARMED_STATE; //go to DISARMED_STATE
          pound = 0;          //reset keypad variables
          total = 0;
          star = 0;
          menu_count = 0;     //reset menu_count to 0
          pressed = 0 ;
          tripped_times ++;   //add one to the value of trippe_times to record the number of alarm tripped
          lcdOutputRow1("Status: Disarmed");  //display "Disarmed" message
          clearRow2();        //clear the content on the bottom row of LCD
          digitalWrite(52, LOW);    //turn off RED LED
          digitalWrite(53, HIGH);   //turn on GREEN LED
          Serial.println("The system is disarmed after lock down!");
        }//end if (total == password)
        else {    //if the numbers enter does not match with password
          clearRow2();    //clear the content of the bottom row of LCD
          lcd.setCursor(0, 1);      //display "Wrong Password" message
          lcd.print("Wrong Password");
          Serial.println("Wrong password, enter again");
          pound = 0;          //reset keypad variables
          total = 0;
          pressed = 0 ;
          buzzer_order = 0;   //set the order of buzzer to 0
          dura_target = millis() + 50;     //set the target time for first buzzer timer
        }//end else if(total == password)
      }//end if (pound == 1)
      if (total != password || pound == 0) {  //if the numbers entered does not match with password or # key is not pressed
        if (dura_target >= millis() && buzzer_order == 0) {   //play the first tone of alarm sound until the first buzzer timer expire
          tone(22, NOTE_D5);
          dura_target2 = millis() + 100;   //set the target time for second buzzer timer
          buzzer_order = 1;   //go the second part of alarm sound
        }//end if buzzer_order == 0
        else {
          if (dura_target2 >= millis() && buzzer_order == 1) {   //play no tone until the second buzzer timer expire
            noTone(22);
            dura_target = millis() + 50;   //set the target time for first buzzer timer
            buzzer_order = 2;  //go the third part of alarm sound
          }//end if buzzer_order == 1
          else {
            if (dura_target >= millis() && buzzer_order == 2) {  //play the second note of alarm sound until the first buzzer timer expire
              tone(22, NOTE_A5);
              dura_target2 = millis() + 100;   //set the target time for second buzzer timer
              buzzer_order = 3;  //go the last part of alarm sound
            }//end if buzzer_order == 2
            else {
              if (dura_target2 >= millis() && buzzer_order == 3) {   //play no tone until the second buzzer timer expire
                noTone(22);
                dura_target = millis() + 50;   //set the target time for first buzzer timer
                buzzer_order = 0; //reset the order of alarm sound to 0 to loop
              }//end if buzzer == 3
            }//end else if buzzer == 2
          }//end else if buzzer == 1
        }//end else if buzzer == 0
      }//end if (total != password || pound == 0)
    case MENU_STATE:   //Setting Menu State
      if (enter_menu == true) { //check if the user entered menu and has not selected an option yest
        checkKeypad();    //get the numbers inputted from the keypad
        if (pound == 1) {   //check if # key is pressed
          if (total == 1) {   //check if option 1 is selected (Changing password)
            state = CHANGE_PASSWORD_STATE;  //go to CHANGE_PASSWORD_STATE
            pound = 0;    //reset keypad variables
            total = 0;
            pressed = 0 ;
            lcdOutputRow1("3-Factory Code");  //display "Factory Code" option on the top row of LCD
            clearRow2();                      //clear the content of the bottom row of LCD
            lcd.setCursor(0, 1);
            lcd.print("4-Custom Code");   //display "Custom Code" option on the bottom row of LCD
          }//end if (total == 1)
          else {      //if option 1(Change password) is not selected
            if (total == 2) {   //check if option 2(System Information) is selected
              state = INFORMATION_STATE;  //go to INFORMATION_STATE
              pound = 0;    //reset keypad variables
              total = 0;
              pressed = 0 ;
              clearRow1();    //clear the contents on the LCD
              clearRow2();
              lcdOutputRow1CountDown("Tripped #: ", tripped_times); //display "Tripped Times" on the top row of LCD
              lcd.setCursor(0, 1);
              lcd.print("Push # to menu");
            }//end if (total == 2)
            else {      //if both option 1(Change Password) and option 2(System Information) are not selected
              lcdOutputRow1("Status: Disarmed");   //display "Disarmed" message on LCD
              clearRow2();        //clear the content on the bottom row of LCD
              lcd.setCursor(0, 1);
              lcd.print("Invalid Input");   //display "Invalid Input" message on the bottom row of LCD
              state = DISARMED_STATE;   //go to DISARMED_STATE
              enter_menu = false;   //disable menu option to resume normal operation
              pound = 0;        //reset keypad variables
              total = 0;
              star = 0;
              pressed = 0;
            }//end else if(total == 2)
          }//end else if (total == 1)
        }//end if (pound == 1)
      }//end if (enter_menu == true)
    case CHANGE_PASSWORD_STATE:     //Change password state
      if (enter_menu == true) {     //check if the user entered menu and has not select any option yet
        checkKeypad();      //get the numbers inputted from keypad
        if (pound == 1) {   //check if # key is pressed
          if (total == 3) {   //check if option 3(Factory Reset) is selected
            password = FACTORY_PASSWORD;  //reset the password to FACTORY_PASSWORD
            tripped_times = 0;    //reset the value of tripped_times
            pound = 0;          //reset keypad variables
            total = 0;
            pressed = 0 ;
            state = DISARMED_STATE; //go to DISARMED_STATE
            enter_menu = false;   //exit menu and resume normal functions
            clearRow2();        //clear the content on the bottom row of LCD
            lcd.setCursor(0, 1);      //display "Reset Succeed" message on LCD
            lcd.print("Reset Succeed!");
            lcdOutputRow1("Status: Disarmed");  //display "Disarmed" message
          }//end if (total == 3)
          else {    //if option 3(Factory Reset) is not selected
            if (total == 4) {   //check if option 4(Custom Code) is selected
              pound = 0;    //reset keypad variables
              total = 0;
              pressed = 0 ;
              state = SET_UP_PASSWORD_STATE;  //go to SET_UP_PASSWORD_STATE
              enter_menu = false;   //exit menu and resume normal functions
              lcdOutputRow1("New Password:"); //display "New Password" message on LCD
              clearRow2();      //clear the content on the bottom row of LCD
            }//end if (tota; == 4)
            else {  //check if both option 3(Factory Reset) and option 4 (Custom Code) are not selected
              lcdOutputRow1("Status: Disarmed");  //display "Disarmed" message on LCD
              clearRow2();       //clear the content on the bottom row of LCD
              lcd.setCursor(0, 1);    //display "Invalid Input" on LCD
              lcd.print("Invalid Input!");
              state = DISARMED_STATE;   //go to DISARMED_STATE
              pound = 0;    //reset keypad variables
              total = 0;
              star = 0;
              pressed = 0;
              enter_menu = false; //exit menu and resume normal functions
            }//end else if(total == 4)
          }//end else if(total == 3)
        }//end if (pound == 1)
      }//end if (enter_menu == true)
    case INFORMATION_STATE:     //system information
      if (enter_menu == true) { //check if user entered this menu and has not selected other options
        checkKeypad();    //get the number inputted from keypad
        if (pound == 1) {  //check if # key is pressed
          state = DISARMED_STATE;   //go to DISARMED_STATE
          pound = 0;  //reset keypad variables
          total = 0;
          pressed = 0 ;
          enter_menu = false;   //exit menu and resumer normal functions
          clearRow2();      //clear the content on the bottom row of LCD
          lcdOutputRow1("Status: Disarmed");    //display "Disarmed" message on LCD
        }//end if (pound == 1)
      }//end if (enter_menu == true)
    default: if (state > INFORMATION_STATE) {   //if the value of state does not match with any of above options
        Serial.print("Problem State::::::");    //print out erro message
        Serial.println(state);
        clearRow2();                  //clear the bottom row of LCD
        lcd.setCursor(0, 1);
        lcd.print("Invalid Input!");    //display "Invalid Input" message on LCD
        state = WELCOME_MESSAGE_STATE;  //reset state to WELCOME_MESSAGE_STATE
      }//end if(state > INFORMATION_STATE)
      break;
  }//end switch(state)
}//end loop



