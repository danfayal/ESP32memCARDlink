# ESP32memCARDlink

A wireless interface to access your classic PS1 memory card data, using the memCARDuino project by ShendoXT.

# Main Objective

The goal of this project is to use the amazing memCARDuino by ShendoXT through a simple web application. It leverages the standard Web Bluetooth API and an ESP32 board acting as a BLE UART device, making it compatible with Android devices. It's an alternative to Python scripts and the incredible MemcardRex by Shendo.

# Purposes

People might want to retrieve their old save files from original PlayStation memory cards—or maybe upload saves to those cards. With this "tool," you can do it using almost any device with internet access.

To get started, you’ll need:

- An ESP32 board to create the BLE UART interface.

- An Arduino board to upload the firmware from the memCARDuino project, developed by ShendoXT (check out Shendo’s repository—the links are below).

You can run the web app in most modern browsers. Just save the index.html file anywhere on your Android device and open it in your favorite browser.

Once you've uploaded the ESP32 and Arduino code, open the web app and connect to the device. Then choose an action (write, read, or format). After that, just wait... and let the magic happen.


You can tweak the delay for writing or reading data. I usually go with 110 ms for writing and 50 ms for reading — works fine for me!


# Limitations

- You can only select a single .mcr or .bin file, with a maximum size of 128 KB.

- Other common save formats are not supported.

- You cannot edit save files directly.

- PocketStation? Seriously? I can barely handle basic memory card operations. Forget it!
- 

# Connections

ESP32 TX2 pin → Arduino RX0 pin


ESP32 RX2 pin → Arduino TX0 pin


To see how to connect the Arduino to the memory card, please refer to the memCARDuino repository.



# Write Function

Simply select a .bin or .mcr save file and click the "Write Memory Card" button. Then wait for the process to finish.


# Read Function

Click the "Read Memory Card" button. That’s it—just wait, as with the writing process. Once the memory card backup image is saved, you can use any format converter to make the saves compatible with your emulator, for example.


# Format Function

Click the "Format Memory Card" button. Done. Irreversible operation!


# Does it work with a PlayStation 2 Memory Card?

NOOOOOOOOOOOO!!!!!!!!!!!!!!!!!

# Does it work with a common third-party PlayStation 1 Memory Card?

YEEEEEEEEEEES!!!!!!!!!!!!!!!!!

# Does it work with the PSXMemCard or PocketStation?

I DON'T KNOOOOOWWWWW!!!!!!!!

P.S.: I honestly have no idea about PSXMemCard or PocketStation. I can be kinda lazy sometimes, you know? So if you decide to try it… well, do it at your own risk. I’m not responsible for any damage to your device (especially since those things are insanely expensive!).

# TODO (maybe)

- Add a metadata interface (HEEEEEELLLLPPPPP!!!!)

- Design a 3D printed case—just for aesthetics (Oh come on, dude! Don’t dream too big!)

# SPECIAL THANKS

To Shendo, a great developer.

https://github.com/ShendoXT

https://github.com/ShendoXT/memcarduino

