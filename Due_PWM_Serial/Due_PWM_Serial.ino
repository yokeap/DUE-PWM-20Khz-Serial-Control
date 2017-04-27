class thruster{

  private:
  unsigned int _dirPin, _pwmPin;

  public:
  //constructor
  thruster(unsigned int dirPin, unsigned int pwmPin){
    _dirPin = dirPin;
    _pwmPin = pwmPin;
    pinMode(_dirPin, OUTPUT);  
    pinMode(_pwmPin, OUTPUT); 
  }

  void setDirection(bool dir){
    digitalWrite(_dirPin, dir);    
  }

  void setPWM(unsigned int pwm){
    if ((_dirPin < 5) || (_dirPin > 9)) {
      analogWriteResolution(8);
      analogWrite(_pwmPin, map(pwm, 0, 100, 0, 255));
    }
    else {
      analogWriteResolution(12);
      analogWrite(_pwmPin, map(pwm, 0, 100, 0, 4095));
    }

  }
};

thruster T[5] = {
  thruster(22,5),
  thruster(23,6),
  thruster(24,7),
  thruster(25,8),
  thruster(26,9),
  };

String inString = "";    // string to hold input
int thuster_pos = 0;


void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(115200);

  // send an intro:
  Serial.println("\n\nString toInt():");
  Serial.println();

  T[0].setDirection(1);
  T[0].setPWM(50);
}

void loop() {
  // Read serial input:
  while (Serial.available() > 0) {
    int inChar = Serial.read();
    if(inChar == 'A') {
      thuster_pos = 0;
      inString = "";
    }
    if(inChar == 'B') {
      thuster_pos = 1;
     inString = "";
    }
    if(inChar == 'C') {
      thuster_pos = 2;
      inString = "";
    }
    if(inChar == 'D') {
      thuster_pos = 3;
      inString = "";
    }
    if(inChar == 'E') {
      thuster_pos = 4;
      inString = "";
    }
    if (isDigit(inChar)) {
      // convert the incoming byte to a char
      // and add it to the string:
      inString += (char)inChar;
      
    }
    // if you get a newline, print the string,
    // then the string's value:
    if (inChar == ',') {
      Serial.print("Value:");
      Serial.println(inString.toInt());
      Serial.print("String: ");
      Serial.println(inString);
      Serial.print("POS: ");
      Serial.println(thuster_pos);
      T[0].setPWM(inString.toInt());
      inString = "";
      // clear the string for new input:
    }
    if(inChar == '\n')
    {
      Serial.print("Value:");
      Serial.println(inString.toInt());
      Serial.print("String: ");
      Serial.println(inString);
      T[thuster_pos].setDirection(inString.toInt());
      inString = "";
    }
  }
}
