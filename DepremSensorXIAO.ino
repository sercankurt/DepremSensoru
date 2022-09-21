
#include <Wire.h>
#include <TinyMPU6050.h>

float pos_offset = 1;
float neg_offset = -1;
long angle_x, angle_y, angle_z, offset_x, offset_y, offset_z;
MPU6050 mpu (Wire);


void setup() {

  // Initialization
  mpu.Initialize();

  // Calibration
  SerialUSB.begin(9600);
  SerialUSB.println("=====================================");
  SerialUSB.println("Starting calibration...");
  mpu.Calibrate();
  SerialUSB.println("Calibration complete!");
  SerialUSB.println("Offsets:");
  SerialUSB.print("AccX Offset = "); SerialUSB.println(mpu.GetAccX());
  SerialUSB.print("AccY Offset = "); SerialUSB.println(mpu.GetAccY());
  SerialUSB.print("AccZ Offset = "); SerialUSB.println(mpu.GetAccZ());
  SerialUSB.print("GyroX Offset = ");SerialUSB.println(mpu.GetGyroXOffset());
  SerialUSB.print("GyroY Offset = ");SerialUSB.println(mpu.GetGyroYOffset());
  SerialUSB.print("GyroZ Offset = ");SerialUSB.println(mpu.GetGyroZOffset());

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  delay(1000);
  for(int i=0; i<50;i++){
   mpu.Execute();
  offset_x = mpu.GetAngX();
  offset_y = mpu.GetAngY();
  offset_z = mpu.GetAngZ();
  }
  SerialUSB.print("offset_x = ");
  SerialUSB.print(offset_x);
  SerialUSB.print("  /  offsetY = ");
  SerialUSB.print(offset_y);
  SerialUSB.print("  /  offsetZ = ");
  SerialUSB.println(offset_z);
  
}

void loop() {

  mpu.Execute();
  angle_x = mpu.GetAngX();
  angle_y = mpu.GetAngY();
  angle_z = mpu.GetAngZ();
 
  SerialUSB.print("AngX = ");
  SerialUSB.print(angle_x - offset_x);
  SerialUSB.print("  /  AngY = ");
  SerialUSB.print(angle_y - offset_y);
  SerialUSB.print("  /  AngZ = ");
  SerialUSB.println(angle_z - offset_z);
  

 if ( pos_offset < angle_x - offset_x || neg_offset > angle_x - offset_x || pos_offset < angle_y - offset_y || neg_offset > angle_y - offset_y || pos_offset < angle_z - offset_z || neg_offset > angle_z - offset_z){


  digitalWrite(LED_BUILTIN,LOW);
  delay(50);
  digitalWrite(LED_BUILTIN,HIGH);
  delay(50);
      
  mpu.Execute();
  offset_x = mpu.GetAngX();
  offset_y = mpu.GetAngY();
  offset_z = mpu.GetAngZ();
 }  
}
