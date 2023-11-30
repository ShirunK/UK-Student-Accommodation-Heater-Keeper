#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <DHT.h>
#include <Servo.h>
#include <PID_v1.h>
Servo myservo;// Define the servo
int servoPin = 11;

unsigned long startTime = 0; // store the start time of clocker
const unsigned long heaterLastTime = 900000; // 15 min
bool heaterState = false; // Indicate if heater is on

#define DHTPIN 2     // DHT11 pin
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

//Define Buttons
const int buttonPin1 = 4;
const int buttonPin2 = 5;
const int buttonPin3 = 6;
const int buttonPin4 = 7;


// PID values 
double Setpoint, Input, Output;
double Kp=2, Ki=5, Kd=1;
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

void setup() {
  Serial.begin(9600); //initialize Serial
  Serial.println("Serial Setup!");
  dht.begin();

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize OLED
  display.display();
  delay(2000);
  display.clearDisplay();

  myservo.attach(servoPin, 500, 2400); // initialize Servo
  myservo.write(90);

  Setpoint = 20; // set default desired temperature (when detected temp below this, will turn on heater)

  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
  pinMode(buttonPin3, INPUT_PULLUP);
  pinMode(buttonPin4, INPUT_PULLUP);


  myPID.SetMode(AUTOMATIC);  // initialize PID
}

void increaseHeater() {
  myservo.write(90); // Find the angle make the servo horizontal
  delay(1000);
  myservo.write(130); // Find the angle that can press increase button
  delay(1000);
  myservo.write(90);
  delay(1000);
}

void decreaseHeater() {
  myservo.write(90);
  delay(1000);
  myservo.write(50);
  delay(1000);
  myservo.write(90);
  delay(1000);
}

void TurnOnHeater() {
    myservo.write(90);
    delay(1000);
    myservo.write(145);
    delay(1000);
    myservo.write(90);
    delay(1000);
    myservo.write(145);
    delay(1000);
    myservo.write(90);
    delay(1000);
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  Input = dht.readTemperature(); 
  myPID.Compute(); // Calculate PID Output

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);

  display.print("Temp: ");
  display.print(t);
  display.print(" C");
  if(20 <= t && t <= 24)
   display.println(" ^_^");
   else
   display.println(" TwT");

  display.print("Humi: ");
  display.print(h);
  display.print(" %");
  if(40 <= h && h <= 60)
   display.println(" ^_^");
   else
   display.println(" TwT");

  display.print("Setpoint: ");
  display.println(Setpoint);
  display.print("PID Output: ");
  display.println(Output);
  display.display();

  if(!heaterState && t < Setpoint) {
    TurnOnHeater();
    heaterState = true;
    startTime = millis(); // Record the timer start time
    Serial.println("Timer Start!");
    }
  // delay(2000);

  if (digitalRead(buttonPin1) == LOW) {
    // Button 1 pressed
    Serial.println("Button 1 pressed");
    increaseHeater();
  }
  if (digitalRead(buttonPin2) == LOW) {
    // Button 1 pressed
    Serial.println("Button 2 pressed");
    decreaseHeater();
  }
  if (digitalRead(buttonPin3) == LOW) {
    // Button 1 pressed
    Serial.println("Button 3 pressed");
    Setpoint = Setpoint + 1;
  }
  if (digitalRead(buttonPin4) == LOW) {
    // Button 1 pressed
    Serial.println("Button 4 pressed");
    Setpoint = Setpoint - 1;
  }

  delay(100); 
  // Check if 15 min passes
  if (heaterState && millis() - startTime >= heaterLastTime) {
    Serial.println("15 min has gone!");
    heaterState = false;
  }

  display.clearDisplay();
}
