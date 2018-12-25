# Multi-channel Voltage Reader with Arduino Mega 2560

The Arduino Mega 2560 analog input pins are used to read voltage (up to 5.0 volts range, tolerance up to 5.5v), the calibraions parameter is used to calibrate the voltage by a multimeter (this value is diffent for each Mega board).  The voltage recordings are displayed on a 2004A I2C LCD display. A button to pull low the digital pin 2 to trigger writing data to serial port to capture data to a computer. 

## Examples
N/A

## Limitations
Right now I only used 8 analog pins. I plan to use the rest 8 pins to read currents through an opamp. 

## Compatible Hardware

Arduino mega 2560 board and 2004A I2C LCD display.

## License

This code is released under the MIT License.