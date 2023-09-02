# penguin

Operation Penguin, build nodejs server and esp32 devices to communicate

## Outline of how it works

Sending a message:

1. The user will press a button on the esp32 device x times (penguin 3d printed)
2. The esp32 device will send a message to the server that the button was pressed x times.
3. The server will receive the message and translate the x times to enum and send the color and shape and store it for the other persons device.

Receiving a message:

1. The esp32 will check the server for a message every x seconds.
2. If there is a message, the esp32 will display the color and shape on the device.

## Physical Supplies and Links

Need to revisit the 3d model as I can only find 8x8 led matrix's and not 3x3 or 5x5 led matrix's.

- ![3d model of the penguin](https://www.thingiverse.com/thing:2418547)
- ![esp32](https://www.digikey.com/en/products/detail/espressif-systems/ESP32-S3-DEVKITC-1-N32R8V/15970965?utm_adgroup=&utm_source=google&utm_medium=cpc&utm_campaign=PMax%20Shopping_Product_Low%20ROAS%20Categories&utm_term=&utm_content=&gclid=Cj0KCQjwusunBhCYARIsAFBsUP9LnaJD9s0TqwgHO65f_HdPA6vvaPaSplHHLiGu4rG288dLipJM4GwaAu0MEALw_wcB)
- ![8x8 flexible led matrix](https://www.amazon.com/gp/product/B0C2C6KF4Y/ref=ppx_yo_dt_b_asin_title_o00_s00?ie=UTF8&th=1)

Pixels: 64Pixels
Size:8cmx8cm(3.15inx3.15in)
Watts:19.2W

## How to run
