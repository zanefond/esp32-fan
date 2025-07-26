# ESP32 WiFi Fan Controller

This project turns an ESP32 into a WiFi-controlled fan, allowing you to manage fan speeds through a web interface.

## Features

-   Web-based control panel accessible from any device on the same network.
-   Four fan states: OFF, Speed 1, Speed 2, and Speed 3.
-   Simple HTML and JavaScript interface.
-   Built with PlatformIO and the Arduino framework.

## Hardware Requirements

-   ESP32 Development Board
-   4-Channel Relay Module
-   A fan with multiple speed settings that can be controlled by relays.
-   5V Power Supply

## Pinout

The following GPIO pins are used to control the relays. You can modify these in `src/ESP32_Fan_Control.ino`.

-   **Fan OFF:** GPIO 25
-   **Speed 1:** GPIO 26
-   **Speed 2:** GPIO 27
-   **Speed 3:** GPIO 32

## Setup

1.  **Clone the repository:**
    ```bash
    git clone https://github.com/zanefond/esp32-fan.git
    cd esp32-fan
    ```
2.  **Update WiFi Credentials:**
    Open `src/ESP32_Fan_Control.ino` and replace `"YOUR_SSID"` and `"YOUR_PASSWORD"` with your WiFi network's credentials.
3.  **Build and Upload:**
    Using PlatformIO, build and upload the project to your ESP32.
    ```bash
    pio run --target upload
    ```
4.  **Connect:**
    After uploading, open the Serial Monitor to find the IP address assigned to the ESP32. Access this IP address in your web browser to control the fan.

---

# ESP32 WiFi 风扇控制器

本项目将 ESP32 开发板变成一个通过 WiFi 控制的风扇，你可以通过网页界面来管理风扇的速度。

## 功能

-   可通过同一网络下的任何设备访问的网页控制面板。
-   四种风扇状态：关闭、速度1、速度2、速度3。
-   简洁的 HTML 和 JavaScript 界面。
-   使用 PlatformIO 和 Arduino 框架构建。

## 硬件要求

-   ESP32 开发板
-   4通道继电器模块
-   一个可以通过继电器控制的多速风扇。
-   5V 电源

## 引脚定义

以下 GPIO 引脚用于控制继电器。你可以在 `src/ESP32_Fan_Control.ino` 文件中修改它们。

-   **风扇关闭:** GPIO 25
-   **速度 1:** GPIO 26
-   **速度 2:** GPIO 27
-   **速度 3:** GPIO 32

## 设置步骤

1.  **克隆仓库:**
    ```bash
    git clone https://github.com/zanefond/esp32-fan.git
    cd esp32-fan
    ```
2.  **更新 WiFi 凭据:**
    打开 `src/ESP32_Fan_Control.ino` 文件，将 `"YOUR_SSID"` 和 `"YOUR_PASSWORD"` 替换为你的 WiFi 网络名称和密码。
3.  **编译和上传:**
    使用 PlatformIO 编译项目并上传到你的 ESP32。
    ```bash
    pio run --target upload
    ```
4.  **连接:**
    上传后，打开串口监视器，找到 ESP32 被分配到的 IP 地址。在你的网页浏览器中访问该 IP 地址即可控制风扇。
