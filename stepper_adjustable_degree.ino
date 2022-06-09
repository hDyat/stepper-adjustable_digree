#define DIR_PIN 8
#define PUL_PIN 7
#define analog_pin A0

int val = 0;
int current_pos = 0;
int next_pos = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(DIR_PIN, OUTPUT);
  pinMode(PUL_PIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  val = analogRead(analog_pin);
  int degree = map(val, 0, 1023, 0, 180);
  controller(degree);
}

void controller(int degree)
{
  int temp_pos = map(degree, 0, 360, 0, 3200);
  next_pos = temp_pos - current_pos;
  Serial.println(String(next_pos) + " " + String(current_pos));
  if(next_pos > 0)
  {
    digitalWrite(DIR_PIN, HIGH);
    for(int i=0; i<next_pos; i++)
    {
      digitalWrite(PUL_PIN, HIGH);
      delayMicroseconds(100);
      digitalWrite(PUL_PIN, LOW);
      delayMicroseconds(100);
    }
    current_pos = temp_pos;
  } 
  else if(next_pos < 0)
  {
    digitalWrite(DIR_PIN, LOW);
    int temp = abs(next_pos);
    for(int i=0; i<temp; i++)
    {
      digitalWrite(PUL_PIN, HIGH);
      delayMicroseconds(100);
      digitalWrite(PUL_PIN, LOW);
      delayMicroseconds(100);
    }
    current_pos = temp_pos;
  }
  else
  {
    digitalWrite(PUL_PIN, LOW);
    delay(1);
  }
}
