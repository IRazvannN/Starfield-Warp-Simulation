# ESP32-S3 3D Starfield Warp Simulation

A lightweight, high-performance 3D perspective projection starfield simulator optimized for the ESP32-S3 architecture and a 128x32 SSD1306 OLED display over a non-standard I2C bus mapping.

## Hardware Demonstration
Below is a live recording of the simulation rendering at 40 frames per second on the 128x32 OLED panel layout:

<video src="demo.mp4" width="100%" controls muted autoplay loop></video>

## Hardware Specifications
- **Microcontroller:** ESP32-S3
- **Display Module:** SSD1306 128x32 OLED Panel
- **I2C Data Line (SDA):** GPIO 47
- **I2C Clock Line (SCL):** GPIO 48

## Technical Implementation
The simulation utilizes basic 3D-to-2D matrix perspective transformations. Each star point possesses a three-dimensional coordinate vector $(X, Y, Z)$. 

Depth velocity is simulated by decrementing the $Z$ coordinate on every frame. Spatial projection is achieved by dividing the horizontal and vertical vectors by the depth element:

$$x_{screen} = \left(\frac{X}{Z} \times \text{Scale}\right) + \text{CenterOffset}_{X}$$
$$y_{screen} = \left(\frac{Y}{Z} \times \text{Scale}\right) + \text{CenterOffset}_{Y}$$

Level-of-Detail (LoD) handling is included to scale pixel coordinates into 2x2 primitives as proximity parameters cross specified depth thresholds.

## Software Dependencies
- Arduino IDE (ESP32 Board Package v2.x or later)
- Adafruit GFX Library
- Adafruit SSD1306 Library

## Installation and Deployment
1. Verify target pin routing corresponds to the custom motherboard schematic (GPIO 47/48).
2. Install the necessary Adafruit display driver libraries via the Arduino Library Manager.
3. Compile and flash the project binary using the selected ESP32-S3 development module configuration.
