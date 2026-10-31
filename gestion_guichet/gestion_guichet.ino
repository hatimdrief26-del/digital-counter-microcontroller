const int segPins[7] = {2, 3, 4, 5, 6, 7, 8};

const int digit1 = 9;   // dizaine
const int digit2 = 10;  // unité

const int buttonNext = 11;
const int buttonReset = 12;
const int buzzer = 13;

int counter = 0;

bool lastNext = HIGH;
bool lastReset = HIGH;

// A B C D E F G
byte numbers[10][7] = {
  {1,1,1,1,1,1,0}, // 0
  {0,1,1,0,0,0,0}, // 1
  {1,1,0,1,1,0,1}, // 2
  {1,1,1,1,0,0,1}, // 3
  {0,1,1,0,0,1,1}, // 4
  {1,0,1,1,0,1,1}, // 5
  {1,0,1,1,1,1,1}, // 6
  {1,1,1,0,0,0,0}, // 7
  {1,1,1,1,1,1,1}, // 8
  {1,1,1,1,0,1,1}  // 9
};

void setup() {
  for (int i = 0; i < 7; i++) {
    pinMode(segPins[i], OUTPUT);
  }

  pinMode(digit1, OUTPUT);
  pinMode(digit2, OUTPUT);

  pinMode(buttonNext, INPUT_PULLUP);
  pinMode(buttonReset, INPUT_PULLUP);

  pinMode(buzzer, OUTPUT);

  digitalWrite(digit1, HIGH);
  digitalWrite(digit2, HIGH);
}

void loop() {
  readButtons();
  displayNumber(counter);
}

void readButtons() {
  bool nextState = digitalRead(buttonNext);
  bool resetState = digitalRead(buttonReset);

  if (lastNext == HIGH && nextState == LOW) {
    counter++;

    if (counter > 30) {
      counter = 0;
    }

    beep();
    delay(200);
  }

  if (lastReset == HIGH && resetState == LOW) {
    counter = 0;
    beep();
    delay(200);
  }

  lastNext = nextState;
  lastReset = resetState;
}

void beep() {
  digitalWrite(buzzer, HIGH);
  delay(100);
  digitalWrite(buzzer, LOW);
}

void showDigit(int digit) {
  for (int i = 0; i < 7; i++) {
    digitalWrite(segPins[i], numbers[digit][i]);
  }
}

void displayNumber(int number) {
  int tens = number / 10;
  int units = number % 10;

  // Afficheur 1 = dizaine
  digitalWrite(digit2, HIGH);
  showDigit(tens);
  digitalWrite(digit1, LOW);
  delay(5);
  digitalWrite(digit1, HIGH);

  // Afficheur 2 = unité
  digitalWrite(digit1, HIGH);
  showDigit(units);
  digitalWrite(digit2, LOW);
  delay(5);
  digitalWrite(digit2, HIGH);
}