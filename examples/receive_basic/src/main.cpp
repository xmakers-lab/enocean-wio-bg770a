#include <Arduino.h>
#include <Adafruit_TinyUSB.h>
#include <WioCellular.h>

// EnOcean モジュール(TCM410J)との UART 通信設定
#define ENOCEAN_SERIAL    Serial1   // Grove UART は Serial1 に接続
#define ENOCEAN_BAUD      57600     // TCM410J の固定ボーレート

// 受信バイト間のギャップがこの時間(ms)を超えたら1パケット終端とみなす
#define PACKET_TIMEOUT_MS 20

void setup() {
    // USB CDC シリアルモニター初期化（最大3秒待機）
    Serial.begin(115200);
    while (!Serial && millis() < 3000) {}

    Serial.println("=== EnOcean Receiver (Wio BG770A + TCM410J) ===");

    // Grove コネクタへの電源供給を有効化
    WioCellular.begin();
    WioCellular.enableGrovePower();
    delay(100);  // 電源安定待ち

    // EnOcean モジュールとの UART 通信開始
    ENOCEAN_SERIAL.begin(ENOCEAN_BAUD);

    Serial.println("Waiting for EnOcean data...");
    Serial.println();
}

void loop() {
    static uint32_t lastByteAt = 0;  // 最後にバイトを受信した時刻
    static bool     receiving  = false;

    // 受信バッファにデータがある間、1バイトずつ16進数で出力
    while (ENOCEAN_SERIAL.available()) {
        uint8_t b = (uint8_t)ENOCEAN_SERIAL.read();
        if (b < 0x10) Serial.print('0');  // ゼロパディング（例: 0x05 → "05"）
        Serial.print(b, HEX);
        Serial.print(' ');
        lastByteAt = millis();
        receiving  = true;
    }

    // 一定時間バイトが来なければパケット終端と判断して改行
    if (receiving && millis() - lastByteAt > PACKET_TIMEOUT_MS) {
        Serial.println();
        receiving = false;
    }
}