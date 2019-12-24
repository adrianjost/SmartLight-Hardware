# SmartLight Hardware

This Version was designed with the awesome web tool https://easyeda.com. You can find the complete project [here](https://easyeda.com/adrian.aus.berlin/SmartLight-6ff7039580814d20a6c5e83e7830ab1b) and can modify it.

<a href="./Gerber_SmartLight-V3.1.zip" download target="_blank">
  <center>
    <img alt="Download Gerber Files" src="./img/Download.svg" width="50%"/>
  </center>
</a>

## Assembling

The full tutorial can be found at: [https://docs.smartlight.ga](https://docs.smartlight.ga/setup/build-the-hardware).

## Schematic

<center>
  <img alt="Schematic" src="./img/Schematic-V3.1.svg" width="100%" />
</center>

## PCB(s)

<center>
  <img alt="PCB Top Side", src="./img/PCB-V3.1-Top.svg"  width="100%"/>
  <img alt="PCB Bottom Side", src="./img/PCB-V3.1-Bottom.svg" width="100%"/>
</center>

## Known Issues & Workarounds

## ESP is not booting when the MOSFET PCB is connected [#2](https://github.com/adrianjost/SmartLight-Hardware/issues/2)

**Solution:**

1. Power up the ESP without the MOSFET PCB connected and only connect the PCB a couple of seconds later.
2. Remove the R5, R6, R7 resistors.
