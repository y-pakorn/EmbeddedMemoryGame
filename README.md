# Brain Activity Improvement Using Memory Game By Embedded Device 

## Objective

Dementia and Alzheimer's disease affect ten to thirty percent of the existing population over the age of 65.

So, using Arduino Mega 320 and other embedded electronics, we designed a memory stimulating recognition game to help avoid these diseases while also having fun.

![S__84967459](https://user-images.githubusercontent.com/48324733/166116418-2ec3306a-9a32-4107-ad58-3c3e0a8afe46.jpeg)


## Parts

|Part  |Amount  |
|--|--|
|Arduino Mega 320  |1  |
|LED 5mm|3|
|220kΩ Resistor|3|
|1kΩ Resistor|3|
|Matrix Keypad Module|3|
|I2C 16x2 LCD Display|1|
|Tact Switch|4|
|Temp & Humidity Switch|1|
|Buzzer|1|
|RFID Reader Module|1|
|RFID Tag Card|1|
|RFID Tag Keychain|1|

## Instructions

After the device is started, the LCD screen will show 2 varaints of information stream.

- Current user and highscore
- Temperature and humidity

User's may correlate between current temperature and humidity and scores that user got in that period of time to determine whethere temperature and humidity have the effect to the user's brain or not.

Then to play the game, press the top left button of the matrix keypad module (labeled with `s1`)

The device's LCD will show the proceeding instruction to play the game.

In short, user will need to watch the LED light blub blink in specific order and memorize those patterns. Then the device will prompt the user to press the button that tied to the LED light blub in pattern that the light shown before.

Then finally the device will show current score that user got and back to the main menu with highscore.

## Usage

The compilable source code is in `./project.ino` file. Dependencies that are required and modifiable settings are listed below.

### Dependencies

- <https://github.com/fdebrabander/Arduino-LiquidCrystal-I2C-library>
- <https://www.brainy-bits.com/post/how-to-use-the-dht11-temperature-and-humidity-sensor-with-an-arduino> (Download link is at the bottom of the article)
- <https://github.com/miguelbalboa/rfid>
- <https://www.arduinoall.net/arduino-tutor/code/Keypad.rar>

### Settings

The modifiable settings are

- Numbers of pattern to memories, default to 6
  - Adjustable by changing the `rSize` value in line `39` to desired value. More than 10 will be too hard and overkill.
- Delays between each blinking, default to 500ms
  - Adjustable by changing the `delay` function parameters in line `154` and `156` (in milliseconds). Less than 200ms will be too fast.a

