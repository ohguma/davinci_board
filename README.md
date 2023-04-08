# ダ・ヴィンチ32U 拡張基板

## 概要

+ [ストロベリー・リナックス](http://strawberry-linux.com/)の「[ダ・ヴィンチ32U with Arduino Bootloader](http://strawberry-linux.com/catalog/items?code=25005)」の拡張基板。
  + マイコン　ATMEGA32U4。Arduino Leonard 互換。
    + mini-USB な点に注意 
  + アナログ入力12本（A0～A11）が利用可能。電源は5V。
  + 1つのタクトスイッチ（D7） はINPUT_PULLUPで使用する。
  + 複数のI2C端子はTJ3B互換［SCL,5V,SDA,GND］
+ モータードライバ　TB6612FNGを搭載し、モーター2個を制御可能。
  + [TB6612FNG日本語データシート](https://toshiba.semicon-storage.com/info/datasheet_ja_20141001.pdf?did=10661)
  + VM=15V(Max)、1chあたりIout=1.2A(ave)、3.2A(peak)
  + VMはバッテリー電圧
+ 基板サイズ　78 x 93mm、周囲の穴は3.2mm径、5mm間隔
  + [タミヤ ユニバーサルプレート](https://www.tamiya.com/japan/products/70172/index.html)上に取り付け可能。

----
## サンプルスケッチ

+ [sample/](./sample/)  

## マニュアル
+ [Davinci Controller 2022版マニュアル](./documents/Davinci_controller_2022_manual.pdf)
  + バッテリーは6～15Vとすること。マニュアル、基板シルクの16Vは誤り。

## 実装例

<img src="./documents/board2022.png"><br>
▲2022版（バッテリーは6～15Vとすること。上の図は誤り）

----

## パーツリスト

個数は明記なければ1個。☆は取り付け向きに注意。

+ マイコン
  + [ダ・ヴィンチ32U with Arduino Bootloader](http://strawberry-linux.com/catalog/items?code=25005) ☆
+ 入出力関係 ☆
  - タクトスイッチ　1個（D7用） ☆（向きを90度間違えないこと）
  - XH 2ピン用ポスト　任意（バッテリー、モーター2個、バッテリー外部出力(EXT)用） ☆
  - XH 3ピン用ポスト　任意（A0～A11用） ☆
  - XH 4ピン用ポスト　任意（I2C用） ☆
    - XHポストは基板の裏・表どちらに取り付けても良い。
    - 裏面設置時は表の時の逆向きになる。
+ モータードライバ関係
  - [SparkFun Motor Driver - Dual TB6612FNG (1A)](https://www.sparkfun.com/products/14451)☆
    - ピン配置が同じ互換モジュールでもよい。
  - 電解コンデンサ 10V 10uF 2個☆
  - セラミックコンデンサ 35V 0.1uF (104） 2個

+ 電源関連 各1個
  - タクトスイッチ　リセット用　1個☆
  - 基板用トグルスイッチ 2個
    - 下記FETとモーター(TB6612FNG STBY)のON/OFF用
    - モーター用を省略する場合、適宜ジャンパし、TB6612FNG STBYをHIGHにする。
  - PchパワーMOSFET（30V40A MTP4835I3等）☆
  - 抵抗 10KΩ（茶黒橙金）
  - ポリスイッチ　　短絡等の保護用。不要時はジャンパ接続する。

+ 内部5V電源まわり
  - ショットキーダイオード （40V1A 1S4など。レギュレータへの逆接防止用）☆
  - 5Vレギュレータ（5V1A TA4805S等）☆
  - 電解コンデンサ 10V 33uF ☆
  - セラミックコンデンサ 35V 0.1uF (104）

## 購入先
+ [ストロベリー・リナックス](http://strawberry-linux.com/)
  + [ダ・ヴィンチ32U with Arduino Bootloader](http://strawberry-linux.com/catalog/items?code=25005)  
+ [秋月電子](https://akizukidenshi.com/catalog/)
  + 「[ＴＢ６６１２モータドライバ　ブレークアウトボードキット](https://akizukidenshi.com/catalog/g/gK-16947/)」はピン配置が異なるため使用不可。
+ [スイッチ・サイエンス](https://www.switch-science.com//)
  + 「[TB6612FNG搭載 デュアルモータードライバ](https://www.switch-science.com/products/3587)」が「[SparkFun Motor Driver - Dual TB6612FNG (1A)](https://www.sparkfun.com/products/14451)」そのもの。
+ amazonでも見かけるが、値段や送料がべらぼうに高かったり、DRV8833が届いたなどのレビューもあったので要注意。
+ DRV8833のモジュールはTB6612モジュールとピン互換と書かれているものもあるが、DRV8833はモーター1つを2本のPWMで制御する。1本PWMと2本のHIGH/LOWで回転方向を指定する前提の本基板では利用できない。

----
## 回路図

- モータードライバ周りはデータシートの「Typical Application Diagram」に従った。
  - [SparkFun Motor Driver - Dual TB6612FNG (1A)](https://www.sparkfun.com/products/14451)
  - [TB6612FNG Datasheet](https://www.sparkfun.com/datasheets/Robotics/TB6612FNG.pdf)

<img src="./documents/schema2022.png">

| Davinci | TB6612FNG |
| ---- | ---- |
| D15 (23ピン) | AIN1 |
| D17 (22ピン) | AIN2 |
| D5  (12ピン) | PWMA |
| D16 (24ピン) | BIN1 |
| D14 (25ピン) | BIN2 | 
| D11 (29ピン) | PWMB |

| TB6612FNG |　モーター |
| ---- | ---- |
| A01 |　MT1 - |
| A02 |　MT1 + |
| B01 |　MT2 + |
| B02 |　MT2 - |

----
## 基板作成

+ 基板作成は「[JLCPCB](https://jlcpcb.com/)」を利用した。
  + つや消し黒が安い。
  + 2022-03-19発注、2022-09-29到着、運送便はDHLを選択（配達は直接DHLだった）
  + twitter https://twitter.com/JLCPCB_Japan
+ [Fritzingデータ Davinci_controller_2022.fzz](./pcb/Davinci_controller_2022.fzz)
  + [Fritzing](https://fritzing.org/)で設計し、基板作成まで行った。
  + コネクタは表・裏どちらにも実装し易いよう、両面にシルクを入れた。
  + 参考書　 「[Fritzing入門実習テキスト「Fritzing Basics」#マッハ新書 （ダウンロード商品）](https://booth.pm/ja/items/1414214)」
+ [発注時ガーバーファイル order_Davinci_controller_2022.zip](./pcb/order_Davinci_controller_2022.zip)
  + 床センサー基板と一体化したデータで発注してしまったため、追加料金を取られた。
  + 同一パターンの面付けは別料金にならないが、異なるパターンをまとめるとNG

<img src="./pcb/pcb2022_top.png" width="240px"> <img src="./pcb/pcb2022_bottom.png" width="240px">

----

- 2023-04-08 ohguma 誤記など訂正
- 2023-04-05 ohguma 初版