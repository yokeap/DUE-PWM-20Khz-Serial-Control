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

thruster T[6] = {
  thruster(22,5),
  thruster(23,6),
  thruster(24,7),
  thruster(25,8),
  thruster(26,9),
  thruster(27,10)
  };

String inString = "";    // string to hold input
int n = 0;
bool blFlag = 0;
int value[6];


void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(115200);

  // send an intro:
  Serial.println("\n\nString toInt():");
  Serial.println();
}

void loop() {
  // Read serial input:
  if(Serial.available() > 0) {
    n = 0;
    int inChar = 0;
    inString = "";  
    while(inChar != '\n'){
      inChar = Serial.read();
      if ((isDigit(inChar)) || (inChar == '-')) {
      // convert the incoming byte to a char
      // and add it to the string:
      inString += (char)inChar;
      }

      if (inChar == ',') {
        Serial.print("\nValue:");
        Serial.println(inString.toInt());
        Serial.print("String: ");
        Serial.println(inString);
        Serial.print("POS: ");
        Serial.println(n);
        value[n] = inString.toInt();
        
        // clear the string for new input:
        inString = "";

        //increase Thruster Position
        n++;
      }
    }
    blFlag = true;
  }
  if(blFlag){
    blFlag = false;
    H_Control();
  }
}

void H_Control()
{
  int i = 0;
  for(i = 0; i < 6 ; i++){
    if(value[0] > 0) T[i].setDirection(1);
    else T[i].setDirection(0);
        T[i].setPWM(abs(value[i]));
    }
}

 /*   
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

*/
