# gbprinter

Game Boy Printer test ROM

![alt text](https://raw.githubusercontent.com/mmuszkow/gbprinter/master/screenshots/rom.png)
![alt text](https://raw.githubusercontent.com/mmuszkow/gbprinter/master/screenshots/print.png)
![alt text](https://raw.githubusercontent.com/mmuszkow/gbprinter/master/screenshots/test_pattern.png)

Tested on SameBoy & mGBA, not on real hardware - feel free to contact me if you would like to donate it ;)

# Control keys

- arrows: move cursor
- A: add character
- B: backspace
- Start: print
- Select: caps lock

# Test pattern

If you want to print a test pattern instead of on-screen text, type `PAT` and press Start.

# Errors

Printing process in progress is indicated by the letter `P` on the left of the screen.
The communication errors will be reported by letter `E` and number of the stage on which printing failed, followed by the returned status code. `FF` status code can mean timeout.
On successfully completed print the preview screen will be cleared.

# Protocol

The protocol is well documented at [https://gbdev.io/pandocs/Gameboy_Printer.html](https://gbdev.io/pandocs/Gameboy_Printer.html).
RLE compression is disabled as most of the emulators don't support it.

