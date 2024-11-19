#include <WiFiManager.h> 

int counter1 = 0;
int counter2 = 0;

void task1(void * parameters){
  Serial.println("task one started");
  for(;;){
    // Serial.print("task one counter: ");
    // Serial.println(counter1++);
    digitalWrite(25, HIGH);
    vTaskDelay(500 / portTICK_PERIOD_MS);
    digitalWrite(25, LOW);
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}

void task2(void * parameters){
  Serial.println("task two started");
  for(;;){
    // Serial.print("task two counter: ");
    // Serial.println(counter2++);
    digitalWrite(26, HIGH);
    vTaskDelay(100 / portTICK_PERIOD_MS);
    digitalWrite(26, LOW);
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  pinMode(25, OUTPUT);
  pinMode(26, OUTPUT);
  pinMode(2, OUTPUT);

  xTaskCreate(
    task1,
    "task 1",
    1024,
    NULL,
    1,
    NULL
  );

  xTaskCreate(
    task2,
    "task 2",
    1024,
    NULL,
    1,
    NULL
  );
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(2, HIGH);
  delay(1000);
  digitalWrite(2, LOW);
  delay(1000);
}
