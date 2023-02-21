#include <ESP8266WiFi.h>  //Esp8266-01 Kütüphanesi
#include <TinyMPU6050.h>  //MPU gyrp sensörü küütüpanesi

const char* ssid = "TA1AFS";   //esp modem bağlantısı
const char* password = "?sngMuDvk@#";  //esp modem bağlantısı

float pos_offset = 0.90;  // MPU hassasiyet
float neg_offset = -0.90; // MPU hassasiyet
long angle_x, angle_y, angle_z, offset_x, offset_y, offset_z;
MPU6050 mpu (Wire);  // MPU'yu I2C olarak cihaza tanıtmak için


void setup() {

  Wire.begin(0, 2);  // I2C pinleri tanıtıldı. 0=SDA, 2=SCL

  // Initialization
  mpu.Initialize();

  // Calibration
  Serial.begin(9600);
  Serial.println("=====================================");
  Serial.println("Starting calibration...");
  mpu.Calibrate();
  Serial.println("Calibration complete!");

    for(int i=0; i<200; i++){
   mpu.Execute();
  offset_x = mpu.GetAngX();
  offset_y = mpu.GetAngY();
  offset_z = mpu.GetAngZ();
  }
  
  Serial.println("Offsets:");
  Serial.print("GyroX Offset = ");
  Serial.println(mpu.GetGyroXOffset());
  Serial.print("GyroY Offset = ");
  Serial.println(mpu.GetGyroYOffset());
  Serial.print("GyroZ Offset = ");
  Serial.println(mpu.GetGyroZOffset());

  pinMode(3, OUTPUT);  //Tx 01 pini çıkış pini olarak tanıtıldı
  digitalWrite(3, LOW); //1.pin lojik 0'a çekildi

  
  digitalWrite(3, HIGH); //1.pin lojik 0'a çekildiz
  delay(1000);
  digitalWrite(3, LOW); //1.pin lojik 0'a çekildiz
  delay(1000);
  digitalWrite(3, HIGH); //1.pin lojik 0'a çekildiz
  delay(1000);
  digitalWrite(3, LOW); //1.pin lojik 0'a çekildiz
  delay(1000);

}

void loop() {

 for(int i=0; i<10; i++){
  mpu.Execute();
  angle_x = mpu.GetAngX();
  angle_y = mpu.GetAngY();
  angle_z = mpu.GetAngZ(); }

  Serial.print("AngX = ");
  Serial.print(mpu.GetAngX());
  Serial.print("  /  AngY = ");
  Serial.print(mpu.GetAngY());
  Serial.print("  /  AngZ = ");
  Serial.println(mpu.GetAngZ());

  if ( pos_offset < angle_x - offset_x ||
       neg_offset > angle_x - offset_x ||
       pos_offset < angle_y - offset_y ||
       neg_offset > angle_y - offset_y ||
       pos_offset < angle_z - offset_z ||
       neg_offset > angle_z - offset_z) {

  
      digitalWrite(3, HIGH);
      delay(50);
      digitalWrite(3, LOW);
      delay(50);
    

    mpu.Execute();
    offset_x = mpu.GetAngX();
    offset_y = mpu.GetAngY();
    offset_z = mpu.GetAngZ();
  }
}
