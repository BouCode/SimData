#define t1 5000
int temperatura1;
int temperatura2;
int humedad1;
int humedad2;

 
void setup () {
  Serial.begin (9600);
  randomSeed(analogRead(0));
}

void loop () {
  temperatura1 = random (20, 30);
  humedad1 = random (60, 70);
  temperatura2 = random (20, 40);
  humedad2 = random (60, 80);
  createJson ("NODO1", temperatura1, humedad1, temperatura2, humedad2);
  delay (t1);
} 

void creaArray (int temp, int hum, bool isLast = false) {
  Serial.print ("[");
  Serial.print (temp);
  Serial.print (",");
  Serial.print (hum);
  Serial.print ("]");
  if (!isLast) {
    Serial.print (",");
  }
}

void createJson (char *tag, int temp1, int hum1, int temp2, int hum2) {
  Serial.print ("{\"node\":\"");
  Serial.print (tag);
  Serial.print ("\",");
  Serial.print ("\"data\":[");
    creaArray (temp1, hum1, false);
    creaArray (temp2, hum2, true);
  Serial.println ("]}");
}
