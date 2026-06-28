# ServoSwitch

以 ESP32-C3 (LoLin C3 Mini) 為基礎的 BLE 伺服馬達開關控制專案。

## 硬體

- 開發板：LoLin C3 Mini (ESP32-C3)
- 伺服馬達：SG90 (接 GPIO 4)
- 通訊：BLE（低功耗藍牙）

## 功能

- 透過 BLE 接收 `PRESS` 指令，驅動伺服馬達旋轉至 35° 後返回 0°（模擬按壓開關）
- 透過 Serial (115200 baud) 直接輸入角度數值控制伺服馬達

## BLE 服務

| 項目 | UUID |
|------|------|
| Service | `12345678-1234-1234-1234-1234567890ab` |
| Characteristic | `abcdefab-1234-5678-1234-abcdefabcdef`（Write） |

## 開發

使用 [PlatformIO](https://platformio.org/) 建置與上傳。

```bash
pio run -t upload
pio device monitor
```
