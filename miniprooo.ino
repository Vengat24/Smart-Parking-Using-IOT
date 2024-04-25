#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Servo.h>

Servo myservo; 
int stopper1 =0;
String updateWebpage(uint8_t LEDstatus , uint8_t LEDstatus1,uint8_t LEDstatus2 , uint8_t LEDstatus3 );
const char* ssid = "vengat";
const char* password = "12345678";

ESP8266WebServer server(80);

int st[4];
bool LEDstatus = LOW;
bool LEDstatus1 =  LOW ;
bool LEDstatus2 = LOW;
bool LEDstatus3 =  LOW ;

void setup() {
  Serial.begin(9600);
  delay(100);
   myservo.attach(D4); 
  myservo.write(180);
  Serial.println("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

   while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected..!");
  Serial.print("Got IP: ");
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, []() {
    String content = updateWebpage(LEDstatus, LEDstatus1,LEDstatus2, LEDstatus3);
    server.send(200, "text/html", content);
  });

  server.begin();
  Serial.println("HTTP Server Started");
}

void loop() {
  int ir1val = digitalRead(D5);
  int ir2val = digitalRead(D6);
  if (ir1val == LOW && stopper1 == 0) {    
   myservo.write(0);
    stopper1 = 1;
  }
  if (ir2val == LOW && stopper1 == 1) {    
   myservo.write(180);
    stopper1 = 0;
  }

  st[0] = digitalRead(D1);
  st[1] = digitalRead(D2);
  st[2] = digitalRead(D3);
  st[3] = digitalRead(D0);
  delay(300);

  server.handleClient();

  if (st[0] < 1) {
   LEDstatus  = LOW; 
  }
  else {
    LEDstatus   = HIGH ; 
  }
  if (st[1] < 1) {
    LEDstatus1   = LOW; 
  }
  else {
    LEDstatus1   = HIGH ; 
  }
  if (st[2] < 1) {
   LEDstatus2  = LOW; 
  }
  else {
    LEDstatus2   = HIGH ; 
  }
  if (st[3] < 1) {
    LEDstatus3   = LOW; 
  }
  else {
    LEDstatus3   = HIGH; 
  }
}
String updateWebpage(uint8_t LEDstatus ,uint8_t LEDstatus1 , uint8_t LEDstatus2 ,uint8_t LEDstatus3) {
int LEDsta[] ={LEDstatus,LEDstatus1,LEDstatus2 ,LEDstatus3};
int c = sizeof(LEDsta)/sizeof(LEDsta[0]);
  int j=0;
  Serial.println(LEDstatus );
  Serial.println(LEDstatus1 );
  Serial.println(LEDstatus2 );
  Serial.println(LEDstatus3 );  
  Serial.println(c);
  String ptr = "<!DOCTYPE html> <html>";
ptr +="<body>";
ptr +="<style>";
ptr +=" *, *:before, *:after {  box-sizing: border-box;}";
ptr +="html {  font-size: 16px;  font-style:italic;  background-color:black; border: 3px solid #d8d8d8;  border-radius: 25px;  margin: 35px 10px ;  margin-bottom:50px;}";
ptr +="h1 {margin-top:30px;color:white;font-size:50px;}";
ptr +="ol { list-style: none;  padding: 5px;  margin: 0;}";
ptr +=".park:nth-child(4) {  margin-right: 6.28571428571429%;}";
ptr +=".parks {  display: flex;  flex-direction: row;  flex-wrap: nowrap;  justify-content: flex-start;}";
ptr +=".set {  display: flex;  margin-top:20px;  flex-direction: row;  flex-wrap: nowrap;  justify-content: flex-start;}";
ptr +=".redd {  display: flex;  margin-left:90px;  flex: 0 0 32.8%;  padding: 8px 40px;  position: relative;}";
ptr +=".redd label {  display: block;  position: relative;  left:20px;  width: 200px;  text-align:center;  font-size: 25px;  font-weight: bold;  line-height: 1.5rem;  padding: 20px 10px 20px;  background:red ;  border: 3px solid #d8d8d8;  border-radius: 5px;}";
ptr +=".greenn {  display: flex;  flex: 0 0 32.8%;  padding: 8px 40px;  position: relative;}";
ptr +=".greenn label {  display: block;  position: relative;  left:20px;  width: 200px;  text-align:center;  font-size: 25px;  font-weight: bold;  line-height: 1.5rem;  padding: 20px 20px 20px;background:green ;  border: 3px solid #d8d8d8;  border-radius: 5px;}";
ptr +=".pinkk {  display: flex;  flex: 0 0 12.8%;  padding: 8px 40px;  position: relative;}";
ptr +=".pinkk label {  display: block;  position: relative;  left:20px;  width: 200px;  text-align:center;  font-size: 25px;  font-weight: bold;  line-height: 1.5rem;  padding: 20px 10px 20px;  background:grey ;  border: 3px solid #d8d8d8;  border-radius: 5px;}";
ptr +=".park {  display: flex;  flex: 0 0 12.8%;  padding: 4px 40px;  position: relative;}";
ptr +=".park label { display: block;  position: relative;  z-index: 1;  left:-35px;  width: 50%;  text-align:center;  font-size: 20px;  font-weight: bold;  line-height: 1.5rem;  padding: 10px 10px 20px;  background:green;  border: 1.5px solid white;  border-radius: 5px;}";
ptr +=".park label:before {  content: "";  position: absolute;  z-index: -1;  width: 75%;  height: 75%; top: 6.5px;  left: 50%;  transform: translate(-50%, 0%);  background: rgba(255, 255, 255, 0.4);  border-radius: 3px;    opacity:50%;}";
ptr +="</style>";
ptr +="<script>window.onload = function() {const labels = document.querySelectorAll('.park label'); const targetSlot = '1A';  let nearestSlot = null;  let shortestDistance = Infinity;";
ptr +="const label0 = labels[0];  const slot0 = label0.getAttribute('for'); if ("+ String(LEDsta[0]) +" === 0) {label0.style.backgroundColor = 'red';} else{  const distance0 = Math.abs(parseInt(slot0) - parseInt(targetSlot));      if (distance0 < shortestDistance) {        shortestDistance = distance0;        nearestSlot = slot0;     } }";
ptr +="const label1 = labels[1];  const slot1 = label1.getAttribute('for'); if ("+ String(LEDsta[1]) +" === 0) {label1.style.backgroundColor = 'red';} else{  const distance1 = Math.abs(parseInt(slot1) - parseInt(targetSlot));      if (distance1 < shortestDistance) {        shortestDistance = distance1;        nearestSlot = slot1;     }} ";
ptr +="const label2 = labels[2];  const slot2 = label2.getAttribute('for'); if ("+ String(LEDsta[2]) +" === 0) {label2.style.backgroundColor = 'red';} else{ const distance2 = Math.abs(parseInt(slot2) - parseInt(targetSlot));      if (distance2 < shortestDistance) {        shortestDistance = distance2;        nearestSlot = slot2;     }}  ";
ptr +="const label3 = labels[3];  const slot3 = label3.getAttribute('for'); if ("+ String(LEDsta[3]) +" === 0) {label3.style.backgroundColor = 'red';} else{  const distance3 = Math.abs(parseInt(slot3) - parseInt(targetSlot));      if (distance3 < shortestDistance) {        shortestDistance = distance3;        nearestSlot = slot3;     }} ";
ptr +="const label4 = labels[4];  const slot4 = label4.getAttribute('for'); if ("+ String(LEDsta[0]) +" === 0 && "+ String(LEDsta[1]) +" === 0 && "+ String(LEDsta[2]) +" === 0 && "+ String(LEDsta[3]) +" === 0 ) {const distance4 = Math.abs(parseInt(slot4) - parseInt(targetSlot));      if (distance4 < shortestDistance) {        shortestDistance = distance4;        nearestSlot = slot4;     }} ";
ptr +="if (nearestSlot) {    const nearestLabel = document.querySelector(`label[for='${nearestSlot}']`);    nearestLabel.style.backgroundColor = 'gray';  }  };";
ptr +="</script>";
ptr +="<body>";
ptr +="<center><h1>Smart parking System</h1></center><div class='car-park'><ol class='cabin fuselage'><li class='row row--1'><ol class='parks' type='A'><li class='park'><label for='1A'>1A</label></li><li class='park'><label for='1B'>1B</label></li><li class='park'><label for='1C'>1C</label></li><li class='park'><label for='1D'>1D</label></li><li class='park'><label for='1E'>1E</label></li>";
ptr +="<li class='park'><label for='1F'>1F</label></li><li class='park'><label for='1G'>1G</label></li><li class='park'><label for='1H'>1H</label></li></ol></li>";
ptr +="<div class='car-park'><ol class='cabin fuselage'><li class='row row--1'><ol class='parks' type='A'><li class='park'><label for='1A'>1A</label></li><li class='park'><label for='1B'>1B</label></li><li class='park'><label for='1C'>1C</label></li><li class='park'><label for='1D'>1D</label></li><li class='park'><label for='1E'>1E</label></li>";
ptr +="<li class='park'><label for='1F'>1F</label></li><li class='park'><label for='1G'>1G</label></li><li class='park'><label for='1H'>1H</label></li></ol></li>";
ptr +="<div class='car-park'><ol class='cabin fuselage'><li class='row row--1'><ol class='parks' type='A'><li class='park'><label for='1A'>1A</label></li><li class='park'><label for='1B'>1B</label></li><li class='park'><label for='1C'>1C</label></li><li class='park'><label for='1D'>1D</label></li><li class='park'><label for='1E'>1E</label></li>";
ptr +="<li class='park'><label for='1F'>1F</label></li><li class='park'><label for='1G'>1G</label></li><li class='park'><label for='1H'>1H</label></li></ol></li>";
ptr +="<div class='car-park'><ol class='cabin fuselage'><li class='row row--1'><ol class='parks' type='A'><li class='park'><label for='1A'>1A</label></li><li class='park'><label for='1B'>1B</label></li><li class='park'><label for='1C'>1C</label></li><li class='park'><label for='1D'>1D</label></li><li class='park'><label for='1E'>1E</label></li>";
ptr +="<li class='park'><label for='1F'>1F</label></li><li class='park'><label for='1G'>1G</label></li><li class='park'><label for='1H'>1H</label></li></ol></li>";
ptr +="<li class='row row--1'><ol class='set' type='A'><li class='redd'><label for='1A'>Unavailable</label></li><li class='greenn'><label for='1B'>Available</label></li><li class='pinkk'><label for='1C'>Available Near</label><</li></ol></li></ol></div></div></body></html>";
  return ptr;
}

