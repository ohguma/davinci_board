// Davinci Controller
// スイッチ・モーターテスト
// 2023-04 ohguma

// ストロベリーリナックス
// ダ・ヴィンチ32U with Arduino Bootloader
// https://strawberry-linux.com/catalog/items?code=25001

// ■ピン設定

// スタートスイッチ
// D7に直結しているでINPUT_PULLUPで使用する。 
//
// Davinci
// ━━━━━━┓
// D7  (30ピン)┠──SW──GND
const int PIN_SW_START = 7;  //D7 (Davinci 30ピン)

// モータードライバ TOSHIBA TB6612FNG
//
// Davinci             TB6612FNG
// ━━━━━━┓      ┏━━━━━┓
// D15 (23ピン)┠───┨AIN1   A01┠─ MT1 -
// D17 (22ピン)┠───┨AIN2   A02┠─ MT1 +
// D5  (12ピン)┠───┨PWMA      ┃
// D16 (24ピン)┠───┨BIN1   B01┠─ MT2 +
// D14 (25ピン)┠───┨BIN2   B02┠─ MT2 - 
// D11 (29ピン)┠───┨PWMB      ┃
//
// IN1  IN2  PWM  動作
// ---- ---- ---- -----------------
// LOW  LOW  HIGH 停止
// HIGH LOW  数値 時計回り
// LOW  HIGH 数値 半時計回り
// HIGH HIGH 任意 ショートブレーキ（モーター端子を短絡した状態）
//   ※数値は0～255で指定する(255指定時が100%)。analogWrite()を使う。
//
// TB6612FNG Hookup Guide
// https://learn.sparkfun.com/tutorials/TB6612fng-hookup-guide/all

// MOTOR1
const int PIN_TB6612_AIN1 = 15;
const int PIN_TB6612_AIN2 = 17;
const int PIN_TB6612_PWMA = 5;

void setup() {
  Serial.begin(9600);
  // MOTOR1
  pinMode(PIN_TB6612_AIN1, OUTPUT);
  pinMode(PIN_TB6612_AIN2, OUTPUT);
  pinMode(PIN_TB6612_PWMA, OUTPUT);
  // オンボードLED 出力設定
  pinMode(LED_BUILTIN, OUTPUT);
  // スタートスイッチ プルアップ入力設定
  pinMode(PIN_SW_START, INPUT_PULLUP);

  unsigned long tm = 0;
  // タクトスイッチが押されていない時はHIGH（押されるとLOW）
  while (digitalRead(PIN_SW_START) == HIGH) {
    // tmは500ミリ秒ごとに0,1,2,3,…となる。
    tm = millis() / 500;
    // 500ミリ秒ごとにLEDをON/OFFする。
    if (tm % 2 == 1) {
      // tmを2で割った余りが1の時、LED：ON
      digitalWrite(LED_BUILTIN, HIGH);
    } else {
      // tmを2で割った余りが0の時、LED：OFF
      digitalWrite(LED_BUILTIN, LOW);
    }
    delay(10);
  }
}

void loop() {
    int speed = 0;

    // トップスピード設定
    int max_speed = 128;

    // 前進
    for (speed = 0; speed < max_speed; speed++) {
      // MOTOR1
      digitalWrite(PIN_TB6612_AIN1, HIGH);
      digitalWrite(PIN_TB6612_AIN2, LOW);
      analogWrite(PIN_TB6612_PWMA, speed);
      delay(10);
    }
    // トップスピードで前進のまま
    delay(500);
    for (speed = max_speed - 1; speed >= 0; speed--) {
      // MOTOR1
      digitalWrite(PIN_TB6612_AIN1, HIGH);
      digitalWrite(PIN_TB6612_AIN2, LOW);
      analogWrite(PIN_TB6612_PWMA, speed);
      delay(10);
    }
    
    // 停止
    digitalWrite(PIN_TB6612_AIN1, LOW);
    digitalWrite(PIN_TB6612_AIN2, LOW);
    digitalWrite(PIN_TB6612_PWMA, HIGH);
    delay(500);

}    