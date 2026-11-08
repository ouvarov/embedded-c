# Traffic light

A pedestrian traffic light on ESP32, written in C with ESP-IDF.

| Phase | Duration |
|---|---|
| Red | 6 s |
| Yellow | 1 s |
| Green | 1 to 3 s, the button ends it early after the first second |
| Yellow | 1 s |

## Wiring

| Part | ESP32 pin |
|---|---|
| Red LED, through 220 Ω | GPIO 25 |
| Yellow LED, through 220 Ω | GPIO 26 |
| Green LED, through 220 Ω | GPIO 27 |
| Push button | GPIO 33 |
| LED cathodes and the other button pin | GND |

The button uses the internal pull-up: released reads 1, pressed reads 0.

## Build

Open this folder in VS Code with the ESP-IDF extension, select the `esp32` target and press Build.

From an ESP-IDF terminal:

```
idf.py build
```

## Simulate

Build first, then in VS Code press `F1` and run `Wokwi: Start Simulator`. The circuit is in `diagram.json`.
