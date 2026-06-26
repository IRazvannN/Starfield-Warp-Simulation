/**************************************************************************
 * @file starfield_warp.ino
 * @brief 3D Perspective Starfield Simulation for ESP32-S3 and SSD1306 OLED
 * * Hardware Configuration:
 * - MCU: ESP32-S3
 * - Display: SSD1306 128x32 OLED
 * - SDA: GPIO 47
 * - SCL: GPIO 48
 **************************************************************************/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32

#define I2C_SDA 47
#define I2C_SCL 48

#define OLED_RESET     -1 
#define SCREEN_ADDRESS 0x3C 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Simulation Configuration
const int MAX_STARS = 50;   
const float SPEED = 1.8;    

// 3D Coordinate Vectors
float starX[MAX_STARS];
float starY[MAX_STARS];
float starZ[MAX_STARS];

void initStar(int i);

void setup() {
  Serial.begin(115200);

  Wire.begin(I2C_SDA, I2C_SCL);
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("ERROR: SSD1306 allocation failed. Check I2C wiring."));
    for(;;); 
  }

  randomSeed(analogRead(0));

  for (int i = 0; i < MAX_STARS; i++) {
    initStar(i);
    starZ[i] = random(1, SCREEN_WIDTH);
  }

  display.clearDisplay();
}

void loop() {
  display.clearDisplay();

  for (int i = 0; i < MAX_STARS; i++) {
    starZ[i] -= SPEED;

    if (starZ[i] <= 0) {
      initStar(i);
    }

    // 3D to 2D Perspective Projection Transformation
    int screenX = (int)((starX[i] / starZ[i]) * 100.0) + (SCREEN_WIDTH / 2);
    int screenY = (int)((starY[i] / starZ[i]) * 100.0) + (SCREEN_HEIGHT / 2);

    // Boundary Validation and Dynamic Level-of-Detail Rendering
    if (screenX >= 0 && screenX < SCREEN_WIDTH && screenY >= 0 && screenY < SCREEN_HEIGHT) {
      if (starZ[i] > 30) {
        display.drawPixel(screenX, screenY, SSD1306_WHITE);
      } else {
        display.fillRect(screenX, screenY, 2, 2, SSD1306_WHITE);
      }
    } else {
      initStar(i);
    }
  }

  display.display();
  delay(25); 
}

/**
 * @brief Initializes a star coordinate vector at the maximum depth boundary.
 * @param i Index of the target star array element.
 */
void initStar(int i) {
  starX[i] = random(-SCREEN_WIDTH, SCREEN_WIDTH);
  starY[i] = random(-SCREEN_HEIGHT, SCREEN_HEIGHT);
  starZ[i] = SCREEN_WIDTH;
}