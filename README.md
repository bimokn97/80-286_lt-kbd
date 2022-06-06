# 286_lt Mechanical Keyboard
A mechanical keyboard from old laptop called Goldstar GPC-4013B, with STM32F401 blackpill board, and additional serial output SN74HC595.

# choose firmware
  * Diy arduino firmware
      [download](https://github.com/bimokn97/80-286_lt-kbd/edit/master/README.md) the .ino file, and open it using arduino software, than flash it.

  * [QMK Firmware](https://github.com/qmk/qmk_firmware.git) 
    * clone the repository     : `git clone https://github.com/bimokn97/qmk_firmware.git`
    * cd to directory          : `cd qmk_firmware`
    * switch to develop branch : `git checkout develop`
    * build it                 : `make 286_lt:default` or `make 286_lt:via` for costumable layout by [via](https://caniusevia.com)
   
   * [Vial Firmware](https://github.com/vial_qmk/vial.git)
    * clone the repository: `git clone https://github.com/bimokn97/vial_qmk.git`
    * cd to directory     : `cd qmk_firmware`
    * switch to develop branch : `git checkout develop`
    * build it                 : `make 286_lt:vial` for costumable layout by [vial]([https://caniusevia.com](https://get.vial.today/))

# pcb layout and schematic
  * on the way
