/* IO pin mapping, naming as in schematics diagram */
#define ESP_LED  25
#define ESP_BTN  26
#define EG_RI    35
#define EG_RST   32
#define EG_PWR   33
#define EG_DCD   27
#define EG_CTS   14
#define EG_RTS   12
#define EG_DTR   13
#define RS485_IO  4
#define RS485_PV 15

/* EG95 4G Modem */
#define TINY_GSM_MODEM_BG96
#include <TinyGsmClient.h>
// Modem HW Pins, naming asqTop_BG9X_AXC_ThingsBoard.ino example
#define MODEM_PWR_ON_PIN    EG_PWR
#define MODEM_RESET_PIN     EG_RST

/* WK2312 I2C to dual UART setup */
#include <DFRobot_IICSerial.h>
#define BAUDRATE_EG95 115200   // EG 95 default baudrate is 115200.
#define BAUDRATE_NEXTION 9600  // Nextion display default baudrate is 9600.
#define BAUDRATE_RS485 9600
#define BAUDRATE_RS232 9600
DFRobot_IICSerial UART1(Wire, SUBUART_CHANNEL_1, /*IA1 = */0,/*IA0 = */0 );  // UART1 for Quectel EG95
DFRobot_IICSerial UART2(Wire, SUBUART_CHANNEL_2, /*IA1 = */0,/*IA0 = */0 );  // UART2 for Nextion display
DFRobot_IICSerial UART3(Wire, SUBUART_CHANNEL_1, /*IA1 = */0,/*IA0 = */1 );  // UART3 for RS485
DFRobot_IICSerial UART4(Wire, SUBUART_CHANNEL_2, /*IA1 = */0,/*IA0 = */1 );  // UART4 for RS232

#define DEBUG_EG95 1
#ifdef DEBUG_EG95
  #include <StreamDebugger.h>
  StreamDebugger serialGSM(UART1, Serial);
  TinyGsm modem(serialGSM);
#else
  #define serialGSM UART1
  TinyGsm modem(serialGSM);
#endif
#define serialNextion UART2
#define serialRS485 UART3
#define serialRS232 UART4

// global status variables
bool is_modem_on = false;


void setup() {
  Serial.begin(115200);
  Serial.println("\r\n---- Setup Started ----\r\n");

  pinMode(ESP_LED, OUTPUT);
  pinMode(RS485_IO, OUTPUT);
  digitalWrite(RS485_IO, LOW);  // RS485=LOW : receiving, RS485=HIGH : transmitting

  pinMode(MODEM_PWR_ON_PIN, OUTPUT);
  pinMode(MODEM_RESET_PIN, OUTPUT);
  digitalWrite(MODEM_PWR_ON_PIN, LOW);
  digitalWrite(MODEM_RESET_PIN, LOW);

  // turn on EG95
  Serial.println("[STATUS] turning on EG95 module ...");
  digitalWrite(MODEM_PWR_ON_PIN, HIGH);
  delay(1000);
  digitalWrite(MODEM_PWR_ON_PIN, LOW);
  delay(500);
  digitalWrite(MODEM_RESET_PIN, HIGH);
  delay(1000);
  digitalWrite(MODEM_RESET_PIN, LOW);
  Serial.println("[STATUS] turned on EG95 module.");

  // init seral port for EG95
  int _u1 = UART1.begin(BAUDRATE_EG95);  // serialGSM has no begin attribute when it is set as StreamDebugger
  if (_u1 == 0) {
    Serial.println("[OK] Quad UART initialization success");
  } else {
    Serial.println("[ERROR] UART initialization error");
  }

  // init EG95
  Serial.println("\r\n [STATUS] Modem Initializing...");
  if (modem.begin()) {
    Serial.println("[OK] Modem init success");
    // Get Modem Info
    String modemInfo = modem.getModemInfo();
    Serial.print("Modem: ");
    Serial.println(modemInfo);

    String imei = modem.getIMEI();
    Serial.print("IMEI: ");
    Serial.println(imei);

    String imsi = modem.getIMSI();
    Serial.print("IMSI: ");
    Serial.println(imsi);

    String ccid = modem.getSimCCID();
    Serial.print("CCID: ");
    Serial.println(ccid);

    delay(3000);

    /* GNSS On and Search */
    // gnss_search();

    is_modem_on = true;
  } else {
    Serial.println("[ERROR] No Modem Found");
    is_modem_on = false;
  }

  Serial.println("\r\n---- Setup Done ----");
}

void loop() {
  digitalWrite(ESP_LED, HIGH);
  delay(200);
  digitalWrite(ESP_LED, LOW);
  delay(200);

  digitalWrite(RS485_IO, HIGH);
  serialRS485.println("Hello RS485");
  digitalWrite(RS485_IO, LOW);

  serialRS232.println("Hello RS232");
}
