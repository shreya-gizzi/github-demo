#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
char auth[] = "fb97bf650e544dfca075520440ca377f";
#define ssid "whatever"
#define pass "kiri9999"
#include <FirebaseArduino.h>
#define FIREBASE_HOST "project2-1b924.firebaseio.com"
#define FIREBASE_AUTH "dZewEt3BeHMDC0ygCMfuZgRX4YBAIBY3MRAwqMQp"
#define TRIGGERPIN D5
#define ECHOPIN    D6


const int m1 = D0;
const int m2 = D1;
const int m3 = D2;
const int m4 = D3;
  float v;
  float u;

BLYNK_WRITE(V1) {
  GpsParam gps(param);

  // Print 6 decimal places for Lat, Lon
  Serial.print("Lat: ");
  Serial.println(gps.getLat(), 7);
   v = (gps.getLat());
  Serial.print("Lon: ");
  Serial.println(gps.getLon(), 7);
   u = (gps.getLon());
  // Print 2 decimal places for Alt, Speed
  Serial.print("Altitute: ");
  Serial.println(gps.getAltitude(), 2);
  Serial.print("Speed: ");
  Serial.println(gps.getSpeed(), 2);
  Serial.println();
}



void setup() {

  Serial.begin(9600);

  pinMode(m1, OUTPUT);
    pinMode(A0, OUTPUT);
  pinMode(m2, OUTPUT);
  pinMode(m3, OUTPUT);
  pinMode(m4, OUTPUT);
  pinMode(TRIGGERPIN, OUTPUT);
  pinMode(ECHOPIN, INPUT);


  // connect to wifi.
  WiFi.begin(ssid, pass);
    Blynk.begin(auth, ssid, pass);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.set("forward", 0);
  Firebase.set("backward", 0);
  Firebase.set("left", 0);
  Firebase.set("right", 0);
  Firebase.set("stop", 0);
}



void loop() {
   int i= Firebase.getString("forward").toInt();
     if(i==1)
   {
    Serial.print(i);
    digitalWrite(m1, HIGH);
    digitalWrite(m2, LOW);
    digitalWrite(m3, HIGH);
    digitalWrite(m4, LOW);
   }
   int j= Firebase.getString("backward").toInt();
     if(j==1)
   {
    Serial.print(j);
    digitalWrite(m1, LOW);
    digitalWrite(m2, HIGH);
    digitalWrite(m3, LOW);
    digitalWrite(m4, HIGH);
   }
   int k= Firebase.getString("right").toInt();
      if(k==1)
   {
    Serial.print(k);
    digitalWrite(m1, LOW);
    digitalWrite(m2, LOW);
    digitalWrite(m3, HIGH);
    digitalWrite(m4, LOW);
   }
   int l= Firebase.getString("left").toInt();
        if(l==1)
   {
    Serial.print(l);
    digitalWrite(m1, HIGH);
    digitalWrite(m2, LOW);
    digitalWrite(m3, LOW);
    digitalWrite(m4, LOW);
   }
   int m= Firebase.getString("stop").toInt();  
     if(m==1)
   {
    Serial.print(m);
    digitalWrite(m1, LOW);
    digitalWrite(m2, LOW);
    digitalWrite(m3, LOW);
    digitalWrite(m4, LOW);
   }

 long duration, distance;
  digitalWrite(TRIGGERPIN, LOW);  
  delayMicroseconds(3); 
  
  digitalWrite(TRIGGERPIN, HIGH);
  delayMicroseconds(12); 
  
  digitalWrite(TRIGGERPIN, LOW);
  duration = pulseIn(ECHOPIN, HIGH);
  distance = (duration/2) / 29.1;
   Firebase.setInt("distance", distance);
  Serial.print(distance);
  Serial.println("Cm");
 

   
   Firebase.setFloat("lat", v);
   Serial.print(v);
   Firebase.setFloat("lon", u);
   Serial.print(u);

    float newLight = analogRead(A0);
    Firebase.setFloat("metal", newLight);
  


     Blynk.run();
     delay(1500);
     delay(200);
}
