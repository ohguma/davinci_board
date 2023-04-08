// ダ・ヴィンチ32U 拡張基板
// https://github.com/ohguma/davinci_board
//
// スイッチテスト
// 2023-04-08 ohguma
//
// ■マイコン情報
// ストロベリーリナックス
// ダ・ヴィンチ32U with Arduino Bootloader
// https://strawberry-linux.com/catalog/items?code=25001
//
// ■ピン設定
// ・スタートスイッチはD7に接続されONでGNDに繋がる。
// ・D7はINPUT_PULLUPモードで使用する。
const int PIN_SW_START = 7;

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
    // スタートスイッチを押している時、オンボードLED：点灯
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.println("START SW pressed.");
  } else {
    // スタートスイッチが離された時、オンボードLED：消灯
    digitalWrite(LED_BUILTIN, LOW);
    Serial.println("START SW released.");
  }
  // 少し待つ。delay()で指定する単位はミリ秒（1000分の1秒）
  delay(100);
}

//  ■課題
//  (1) シリアルモニタを見ながら、スケッチを実行する。
//  (2) スタートスイッチを押したらLED消灯、離したらLED点灯に変更する。
//  (3) Serial.println を Serial.print に置換し、シリアルモニタの表示を確認する。
//