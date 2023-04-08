// ダ・ヴィンチ32U 拡張基板
// https://github.com/ohguma/davinci_board
//
// モーターテスト 第３弾 前後進
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
//
// ・モータードライバ TOSHIBA TB6612FNG
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
//
// MOTOR1
const int PIN_TB6612_AIN1 = 15;
const int PIN_TB6612_AIN2 = 17;
const int PIN_TB6612_PWMA = 5;

void setup() {
  Serial.begin(9600);
  // オンボードLED 出力設定（LED_BUILTINは定義済定数。値は13）
  pinMode(LED_BUILTIN, OUTPUT);
  // スタートスイッチ プルアップ入力設定
  pinMode(PIN_SW_START, INPUT_PULLUP);
  // MOTOR1
  pinMode(PIN_TB6612_AIN1, OUTPUT);
  pinMode(PIN_TB6612_AIN2, OUTPUT);
  pinMode(PIN_TB6612_PWMA, OUTPUT);

  // スタートスイッチが押されるまで、オンボードLEDを点滅する。
  unsigned long tm = 0;
  // スタートスイッチが押されるとINPUT_PULLUPモードの
  // digitalRead()はLOWになり、whileを終了する。
  Serial.println("Wait until the start switch is pressed.");
  while (digitalRead(PIN_SW_START) == HIGH) {
    // tmは500ミリ秒ごとに0,1,2,3,…となる。
    tm = millis() / 500;
    // 500ミリ秒ごとにLEDをON/OFFする。
    if (tm % 2 == 1) {
      // tmを2で割った余りが1の時、LED：ON
      digitalWrite(LED_BUILTIN, HIGH);
      Serial.print("o");
    } else {
      // tmを2で割った余りが0の時、LED：OFF
      digitalWrite(LED_BUILTIN, LOW);
      Serial.print(".");
    }
    //少し待つ。
    delay(100);
  }
  // オンボードLEDが点灯状態のままループしないよう消しておく。
  digitalWrite(LED_BUILTIN, LOW);
  Serial.print("Start loop.");
}

void loop() {
  // 最大スピード設定の絶対値（％指定）
  int max_speed = 50;
  // スピード設定（-100％～100％で指定、＋は正転、－は逆転）
  int speed = 0;
  // PWM値(0～255)
  int pwm = 0;

  // MOTOR1 前進 加速
  for (speed = 0; speed < max_speed; speed++) {
    digitalWrite(PIN_TB6612_AIN1, HIGH);
    digitalWrite(PIN_TB6612_AIN2, LOW);
    pwm = map(constrain(speed, 0, 100), 0, 100, 0, 255);
    analogWrite(PIN_TB6612_PWMA, pwm);
    Serial.println(speed);
    delay(10);
  }
  // 前進で最大スピード維持
  delay(500);
  for (speed = max_speed - 1; speed >= -max_speed; speed--) {
    // MOTOR1
    if (speed >= 0) {
      // 前進 減速
      digitalWrite(PIN_TB6612_AIN1, HIGH);
      digitalWrite(PIN_TB6612_AIN2, LOW);
    } else {
      // 後進 加速
      digitalWrite(PIN_TB6612_AIN1, LOW);
      digitalWrite(PIN_TB6612_AIN2, HIGH);
    }
    pwm = map(constrain(abs(speed), 0, 100), 0, 100, 0, 255);
    analogWrite(PIN_TB6612_PWMA, pwm);
    Serial.println(speed);
    delay(10);
  }
  // 後進で最大スピード維持
  delay(500);
  // MOTOR 後進 減速
  for (speed = -max_speed; speed < 0; speed++) {
    digitalWrite(PIN_TB6612_AIN1, LOW);
    digitalWrite(PIN_TB6612_AIN2, HIGH);
    pwm = map(constrain(abs(speed), 0, 100), 0, 100, 0, 255);
    analogWrite(PIN_TB6612_PWMA, pwm);
    Serial.println(speed);
    delay(10);
  }
}


//  ■課題
//  (1) シリアルモニタを見ながら、スケッチを実行する。
//  (2) MOTOR1とMOTOR2を同時に同様に動かす。
//  (3) ditiralWrite()とanalogWrite()している箇所を関数化する。
//      関数はupdate_motor
//      関数の戻り値はなし（関数定義の行頭はvoid）
//      引数は整数型(int)が2つ。
//      1番目はモーター番号の指定（1 or 2)
//      2番目はスピード(％指定 -100～100%）
//      スピードが100%(or -100%)の際にanalogWriteで255を指定する。
//      スピードが＋の場合は正転、－の場合は逆転させる。
//  (4) 加減速しているfor文の行は変更せずに、上記関数で同じ動作をさせる。
//