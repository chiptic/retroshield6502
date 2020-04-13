# RetroShield 6502 for Arduino Mega

`k65c02_apple1`: emulates Apple I hardware, includes BIOS and BASIC ROMs.

To run Apple I, you need:
* Arduino Mega
* LCD Display Shield for Arduino

0) Disconnect RetroShield from Arduino Mega.

1) Program Arduino Mega with Apple I code (software/k6502_apple1/).

2) Disconnect Arduino Mega from computer and plug RetroShield 6502.

3) Connect Arduino Mega to computer.

4) Open `Serial Monitor` from Arduino IDE `Tools` menu.

5) Select `115200` for Baud and `Carriage Return` for line endings.

6) Press DOWN buttons to assert CPU RESET.

7) Press UP button to release CPU RESET.

8) You should see prompt `\` in serial monitor now.

9) type `e000.e100` + enter to see memory dump from 0xE000 to 0xE100.

To run BASIC:

1) type `E000R` to run the Apple I Basic ROM.

2) type

```
10 PRINT "HELLO WORLD"
20 END
```

3) type `RUN` to run.

4) for more information about BASIC, see Apple I BASIC Manual.