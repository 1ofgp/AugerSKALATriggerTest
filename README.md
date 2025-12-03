# Structure
- `src/testBoard.cpp` -- code for the Test Board (Teensy + Tx board + Rx board + TFT Screen)
- `src/onlyTx.cpp` -- code for Teensy to be used ONLY as a "Trigger Generator" 
- `src/onlyRx.cpp` -- code for Teensy to be used ONLY as a "Trigger Receiver/Printer" 
- `src/TxPeriodArray` -- code for Teensy to be used ONLY as a "Trigger Generator" with predefined periods from `src\period....c` files;
- `doTimestamps.py` -- to be used to study triggers info  produced by either Test Board or Teensy in "Trigger Receiver/Printer" mode

Source file to compile is defined in `platformio.ini`
```
build_src_filter = +<testBoard.cpp>
```

# Jumpers
- `pin 29 - 28` -- Tx OFF
- `pin 29 - 30` -- Tx ON
- `pin 31 - 30` -- Screen Print ON
- `pin 31 - 32` -- Screen Print OFF

The trigger info will be printed over serial port regardless of the Screen Print Status. Turning Screen Print OFF allows to do perform more detailed (the difference is not significant though) timing studies, since the lags related to screen update are not present. By default it is recommended to use Screen Print ON.

# IOs

- `Rx Board ST connector` -- Optical Trigger IN
- `SMA connector under the TFT screen` -- Electrical Trigger IN 
- `Tx Board ST connector` -- optical trigger OUT (only when Tx is ON)   

Optical and Electrical Trigger can be connected at the same time, interrupts are attached to both pins.