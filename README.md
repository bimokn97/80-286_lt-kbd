# 286_lt Mechanical Keyboard
A mechanical keyboard from old laptop called Goldstar GPC-4013B, soldered with STM32F401 blackpill board, with additional serial output SN74HC595.

# choose firmware
  * Diy arduino firmware
      download the .ino file, and open it using arduino software, than flash it.

  * [QMK Firmware](https://github.com/qmk/qmk_firmware.git) 
    * clone the repository: `git clone https://github.com/bimokn97/qmk_firmware.git`
    * cd to directory     : `cd qmk_firmware`
    * build it            : `make 286_lt:default` or `make 286_lt:via` for costumable layout by [via](https://caniusevia.com)

# pcb layout and schematic
  * on the way
