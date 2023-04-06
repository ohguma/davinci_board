// Davinci Controller
// スイッチテスト
// 2023-04 ohguma

// ストロベリーリナックス
// ダ・ヴィンチ32U with Arduino Bootloader
// https://strawberry-linux.com/catalog/items?code=25001

// ■ピン設定
// スタートスイッチ
// D7に直結してあり、INPUT_PULLUPモードで使用する。
//
// Davinci
// ━━━━━━┓
// D7  (30ピン)┠──SW──GND
const int PIN_SW_START = 7;  //D7 (Davinci 30ピン)

void setup() {
  Serial.begin(9600);
  // オンボードLED 出力設定（LED_BUILTINは定義済定数。値は13）
  pinMode(LED_BUILTIN, OUTPUT);
  // スタートスイッチ プルアップ入力設定
  pinMode(PIN_SW_START, INPUT_PULLUP);
}

void loop() {
  // スタートスイッチが押されるとINPUT_PULLUPモードの
  // digitalRead()はLOWになる。
  if (digitalRead(PIN_SW_START) == LOW) {
    // スタートスイッチを押している時、オンボードLED：消灯
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.println("START SW pressed.");
  } else {
    // スタートスイッチが離された時、オンボードLED：点灯
    digitalWrite(LED_BUILTIN, LOW);
    Serial.println("START SW released.");
  }
  // 少し待つ。delay()で指定する単位はミリ秒（1000分の1秒）
  delay(100);
}