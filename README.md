# enocean-wio-bg770a

EnOceanユニットをWioBG770Aで扱います。

---

## 特徴

- Grove接続で簡単に利用可能
- EnOcean無線の受信に対応（TCM410J経由）
- セルラー通信（LTE-M/NB-IoT）でクラウドへのデータ送信が可能

---

## 必要なもの

- Seeed Wio BG770A
- EnOceanユニット

---

## 接続方法

WioBG770AにEnOceanユニットを接続します。

---

## 想定用途

- 温度・湿度センサ
- ドア開閉検知
- 無線スイッチ入力
- セルラー経由でのIoTデータ送信

---

## サンプル

- `examples/receive_basic` — EnOceanパケットを受信してシリアルに16進ダンプする基本サンプル

---

## 関連

- 全体構成（ハブ）  
  https://github.com/xmakers/enocean-iot-modules
