#include <MsTimer2.h>

long EKG[] = {82,82,82,82,82,82,82,82,93,93,93,92,82,82,67,132,176,180,70,63,82,82,82,87,90,95,93,90,87,85,83,82,82,82,82,82,82,82};

Button myBtn(A3);

void writeAD() {
  static int index = 0;
  long init = analogRead(A1);
  long BPM = map(analogRead(A1),0, 1023, 20, 220);
  
  Serial.print(EKG[index++]*analogRead(A0)/100);
  Serial.print(",");
  long x = BPM*(sizeof(EKG)/sizeof(long));
  Serial.println(BPM);

  if (index >= sizeof(EKG)/sizeof(long)) {
    index = 0;  
  }

  if (init != analogRead(A1)) {
    MsTimer2::stop();
    MsTimer2::set(60000/x, writeAD);
    MsTimer2::start();
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  MsTimer2::set(50, writeAD);
  MsTimer2::start();
}

void loop() {
  // put your main code here, to run repeatedly:
}
