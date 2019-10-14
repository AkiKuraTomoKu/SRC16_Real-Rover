/*
 * Program : analogRead
 * Boards  : Mega,Mega 2560,Mega ADK,Due
 * 2017/10/01 Akitomo Kuraku
 */

void setup(void){
	Serial.begin(115200);
}

void loop(void){
	for(int i=0;i<16;i++){
		Serial.print(analogRead(i));
		Serial.print("\t");
	}
	Serial.println("");
}
