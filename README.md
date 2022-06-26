# 286_lt Mechanical Keyboard
A mechanical keyboard from old laptop called Goldstar GPC-4013B, with STM32F401 blackpill board, and additional serial output SN74HC595.

# choose firmware
  * Diy arduino firmware
      [download](https://github.com/bimokn97/80-286_lt-kbd/blob/master/stmduino_kbd/stmduino_kbd.ino) the .ino file, and open it using arduino software, than flash it.

  * [QMK Firmware](https://github.com/qmk/qmk_firmware.git) 
    * clone the repository     : `git clone https://github.com/bimokn97/qmk_firmware.git`
    * cd to directory          : `cd qmk_firmware`
    * switch to develop branch : `git checkout develop`
    * build it                 : `make 286_lt:default` or `make 286_lt:via` for costumable layout by [via](https://caniusevia.com)
   
   * [Vial Firmware](https://github.com/vial_qmk/vial.git)
     * clone the repository     : `git clone https://github.com/bimokn97/vial_qmk.git`
     * cd to directory          : `cd qmk_firmware`
     * switch to develop branch : `git checkout develop`
     * build it                 : `make 286_lt:vial` for costumable layout by [vial]([https://caniusevia.com](https://get.vial.today/))

# pcb layout and schematic
  using [Kicad](https://www.kicad.org/)
  * [keyboard pcb](https://github.com/bimokn97/80-286_lt-kbd/tree/master/schematic_pcb/keyboard)
  * [mcu connector board](https://github.com/bimokn97/80-286_lt-kbd/tree/master/schematic_pcb/mcu_board)
  
    connector FPC 22 pin 1mm pitch
  
  * ![Photo of back keyboard pcb](https://github.com/bimokn97/80-286_lt-kbd/blob/master/schematic_pcb/pcb_back_photo.jpg)