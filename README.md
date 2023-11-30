# UK Student Accommodation Heater Keeper
The simple project based on Arduino UNO is for those whose room's heater automatically turn off with a timer. It can work as a external controller to make your heater keep workking and perform better.

# Introduction
In some UK student accommodations, to save the cost, the renter may set a compulsory timer to the heater in your room. This makes your winter so cold. Compared with violent disassembly and illegal circuit modification, adding a low-cost external controller to your heater is a wise choice. This simple project is based on the Arduino UNO and is great for beginners.

Especially good for STIEBEL ELTRON Heater (e.g. iQ student accommodation).

# Required components
All the things you need:
- Arduino UNO * 1
- Servo sg90 180 degre * 1
- DHT 11 Temperature and Humidity Sensor * 1
- SSD1306 0.96 inch OLED Display Module * 1 (optional)
- Button * 4 (optional)
- Breadboard * 1 (optional)
- DuPont male-to-male wires * several
- Double Sided Adhesive Tape * 1

# Default Settings:
Heater Stop Time: 15min (which means the heater in your room will automatically turn off after 15 mins)
Setpoint: 20 C (when indoor temperature is below than this value, the Keeper will turn on the heater)

# Buttons Functions:
- Manually increase the heater degree
- Manually decrease the heater degree
- increase the setpoint
- decrease the setpoint

# Comment
The PID function is just for exploring. For now it's useless in the code.

# Assemble
![image](https://github.com/ShirunK/UK-Student-Accommodation-Heater-Keeper/blob/main/DEMO/1.jpg)
![image](https://github.com/ShirunK/UK-Student-Accommodation-Heater-Keeper/blob/main/DEMO/2.jpg)
![image](https://github.com/ShirunK/UK-Student-Accommodation-Heater-Keeper/blob/main/DEMO/3.jpg)
