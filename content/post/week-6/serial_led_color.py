from ws2812 import WS2812
import utime
import machine

# Toggle NEOPIXEL_POWER pin on to power the NeoPixel LED
power = machine.Pin(11,machine.Pin.OUT)
power.value(1)

# Define recognized colors
BLACK = (0, 0, 0)
RED = (255, 0, 0)
YELLOW = (255, 150, 0)
GREEN = (0, 255, 0)
CYAN = (0, 255, 255)
BLUE = (0, 0, 255)
PURPLE = (180, 0, 255)
WHITE = (255, 255, 255)

# Map strings to colors
color_dict = {
    "black": BLACK,
    "red": RED,
    "yellow": YELLOW,
    "green": GREEN,
    "cyan": CYAN,
    "blue": BLUE,
    "purple": PURPLE,
    "white": WHITE
}

# Instantiate the WS2812 class with
# pin_num = PIN_NEOPIXEl, led_count = 1 and brightness = 0.01
led = WS2812(12,1,0.01)

# Create an infinite loop for the body of the program
while True:
    # Wait for serial input and convert it to lowercase
    color = input("Name a color: ").lower()
    # If the given color exists in the dictionary,
    # change the LED color to it and print it
    if color in color_dict:
        led.pixels_fill(color_dict[color])
        led.pixels_show()
        print(f"LED color: {color}")
    else:
        print("Color not recognized.")
