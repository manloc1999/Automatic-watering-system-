#define BLYNK_PRINT Serial
#define pin_analog A0
#define pin_relay D1


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).

char auth[] = "cybZa1GGLSBHUm7n4new6rx2FDwjHx9V";
// Your WiFi credentials.


char ssid[] = "DESKTOP-3T5MH63 2575";
char pass[] = "(26866Ls";


void setup()
{
  // Debug console
  Serial.begin(9600);
  pinMode(pin_analog, INPUT);
  pinMode(pin_relay, OUTPUT);
  Blynk.begin(auth, ssid, pass);
}

void loop()
{
  int do_am_dat =  analogRead(pin_analog);     // Ta sẽ đọc giá trị hiệu điện thế của cảm biến
                                      // Giá trị được số hóa thành 1 số nguyên có giá trị trong khoảng từ 0 đến 1024 Đất càng ẩm thì giá trị càng nhỏ. Đất khô thì giá trị lớn
  
  if(do_am_dat > 1000){ //(đất khô)
  digitalWrite(pin_relay, LOW);  // kích hoạt rờ le bật máy bơm
  Blynk.virtualWrite(V7, "ĐANG TƯỚI CÂY"); // chuyển chuỗi ĐANG TƯỚI CÂY ra điện thoại 
  }
  else if(do_am_dat < 1000){ //(đất ẩm)
  digitalWrite(pin_relay, HIGH); // kích hoạt rờ le tắt máy bơm
  Blynk.virtualWrite(V7, "NGỪNG TƯỚI CÂY"); // chuyển chuỗi NGỪNG TƯỚI CÂY ra điện thoại 
  }
    
  float voltage = (100 - ((do_am_dat *100) / 1023)); // Công thức chuyển giá trị độ ẩm ra phần trăm 
  Blynk.virtualWrite(V5, do_am_dat);
  Blynk.virtualWrite(V6, voltage); // chuyển giá trị phần trăm của độ ẩm ra điện thoại 
  Blynk.run();
}
