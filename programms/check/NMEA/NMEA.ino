void setup(void){
	Serial.begin(115200);
	Serial2.begin(9600);
}

void loop(void){
	if(Serial2.available()){
		Serial.print((char)Serial2.read());
	}
}
