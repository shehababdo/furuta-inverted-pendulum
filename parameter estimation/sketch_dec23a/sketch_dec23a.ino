#define pin1 2
#define pin2 4   
#define theta0_ppr 500

#define motor_pwm 6
#define motor_p1  7
#define motor_p2  8

#define VOLTAGE 10.2

volatile int counter = 0; // Variable to track encoder pulses
int start_time = 0, current_time = 0;
float my_speed = 0, elapsed_time = 0.0, speed_controller = 0, PWM, voltage;
bool motor_direction = 0;
unsigned long last_update_time = 0; // Timer for speed and direction changes

void setup() 
{
  pinMode(motor_pwm, OUTPUT);
  pinMode(motor_p1, OUTPUT);
  pinMode(motor_p2, OUTPUT);

  Serial.begin(9600);

  // Setting up interrupts for encoder
  pinMode(pin1, INPUT_PULLUP);
  pinMode(pin2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(pin1), intr1, RISING);
  attachInterrupt(digitalPinToInterrupt(pin2), intr2, RISING);

  start_time = millis();
}

void loop() 
{
  current_time = millis();

  // Calculate speed every 100ms
  if ((current_time - start_time) % 100 == 0) 
  {
    elapsed_time += 0.1;
    my_speed = ((long)counter * 60 * 10 / (2 * theta0_ppr));

    Serial.print(elapsed_time);
    Serial.print(" , ");
    if (!motor_direction) Serial.print("-");
    Serial.print(voltage);
    Serial.print(" , ");
    Serial.println(my_speed);

    counter = 0;
  }

  // Automatically change speed and direction every 4 seconds
  if (current_time - last_update_time >= 4000) 
  {
    last_update_time = current_time;

    // Toggle motor direction
    motor_direction = !motor_direction;
    digitalWrite(motor_p1, motor_direction);
    digitalWrite(motor_p2, !motor_direction);

    // Increment speed
    speed_controller += 0.1;
    if (speed_controller > 1) speed_controller = 0; // Reset speed to 0 after reaching max

    // Update PWM and voltage
    PWM = 255 * speed_controller;
    analogWrite(motor_pwm, PWM);

    voltage = VOLTAGE * speed_controller;

    // Serial.print("Direction: ");
    // Serial.println(motor_direction ? "Forward" : "Reverse");
    // Serial.print("Speed Controller: ");
    // Serial.println(speed_controller);
  }
}

void intr1() 
{
  // Determine direction from encoder signals
  if (digitalRead(pin2) == LOW) {
    counter++;
  } else {
    counter--;
  }
}

void intr2() 
{
  // Determine direction from encoder signals
  if (digitalRead(pin1) == LOW) {
    counter--;
  } else {
    counter++;
  }
}
