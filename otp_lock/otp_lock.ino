#include <Keypad.h>

// Define the 4x4 keypad matrix
const byte ROWS = 4;
const byte COLS = 3;
char keys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};
byte rowPins[ROWS] = {2, 3, 4, 5}; // Connect to the row pinouts of the keypad
byte colPins[COLS] = {6, 7, 8}; // Connect to the column pinouts of the keypad
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Define the relay pin
const int relayPin = 10;

// Define the length of the OTP
const int otpLength = 6;

// Initialize the serial communication
void setup() {
  Serial.begin(9600);
  pinMode(relayPin, OUTPUT);
  
}

void loop() {
  
  // Generate a new OTP
  int otp = generateOTP();
  
  // Prompt the user to enter the OTP
  Serial.println("Please enter the 6-digit OTP:");
  String user_input = "";
  while (user_input.length() < otpLength) {
    char key = keypad.getKey();
    if (key) {
      user_input += key;
      Serial.print(key);
    }
  }
  Serial.println();

  // Check if the user input matches the generated OTP
  if (user_input.toInt() == otp) {
    Serial.println("OTP verified. Activating relay.");
    // Activate the relay
    digitalWrite(relayPin, HIGH);
    delay(5000); // Keep the relay on for 5 seconds
    digitalWrite(relayPin, LOW);
  }
  else {
    Serial.println("Invalid OTP. Access denied.");
  }
}

// Function to generate a new OTP
int generateOTP() {
  randomSeed(analogRead(0));
  int otp = 0;
  for (int i = 0; i < otpLength; i++) {
    otp = otp * 10 + random(0, 10);
  }
  // Print the new OTP to the serial monitor
  Serial.print("Your OTP is: ");
  Serial.println(otp);
  return otp;
}
