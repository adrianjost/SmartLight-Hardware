# SmartLight Hardware

This Version was designed with the awesome web tool https://easyeda.com. You can find the complete project [here](https://easyeda.com/adrian.aus.berlin/SmartLight-6ff7039580814d20a6c5e83e7830ab1b) and can modify it.

<a href="./Gerber_SmartLight-V4.0.zip" download target="_blank">
  <center>
    <img alt="Download Gerber Files" src="./img/Download.svg" width="50%"/>
  </center>
</a>

## Assembling

The full tutorial can be found at: [https://docs.smartlight.ga](https://docs.smart-light.ga/setup/build-the-hardware).

## Schematic

<center>
  <img alt="Schematic" src="./img/Schematic-V4.0.svg" width="100%" />
</center>

## PCB(s)

<center>
  <img alt="PCB Top Side", src="./img/PCB-V4.0-Top.svg"  width="100%"/>
  <img alt="PCB Bottom Side", src="./img/PCB-V4.0-Bottom.svg" width="100%"/>
  <img alt="PCB 3D Preview", src="./img/3D-Preview-V4.0.png" width="100%"/>
</center>

## Known Issues & Workarounds & Learnings

- do not populate `R2`, `R4` and `R5`, those will prevent the ESP from booting and are not required.
- The spacing of `JP1` could be smaller to make soldering easier. Most of the time it's also the default, so in the next version there should be a thin, cuttable trace in between.
- `U2` (`LD1117V33`) get's really hot when converting 12V to 3.3V. I don't know yet why, but when keeping it in contact with a little bit of metal it's fine for now. In future versions an alternative voltage converter should be considered. But Coils are still a no-go because of the occasional coil-wine.
- There are smaller button types that would help to free up some more space for other cool features. I rarely use RESET because of OTA Updates and the setup-button could also be merged with the button hooked up to IO2, which would allow a 3rd output channel to support RGB again.
- The Button labels are switched
