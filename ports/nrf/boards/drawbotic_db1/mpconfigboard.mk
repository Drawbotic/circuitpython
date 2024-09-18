USB_VID = 0x1209
USB_PID = 0x0001
USB_PRODUCT = "Drawbotic DB-1"
USB_MANUFACTURER = "Drawbotic"

MCU_CHIP = nrf52840

SPI_FLASH_FILESYSTEM = 1
EXTERNAL_FLASH_DEVICES = "S25FL064L"

CIRCUITPY_BITBANGIO = 1
CIRCUITPY_COUNTIO = 1
CIRCUITPY_BUSDEVICE = 1

FROZEN_MPY_DIRS += $(TOP)/frozen/Adafruit_CircuitPython_NeoPixel
FROZEN_MPY_DIRS += $(TOP)/frozen/Adafruit_CircuitPython_BLE
FROZEN_MPY_DIRS += $(TOP)/frozen/Adafruit_CircuitPython_VL53L0X
FROZEN_MPY_DIRS += $(TOP)/frozen/Adafruit_CircuitPython_Motor
FROZEN_MPY_DIRS += $(TOP)/frozen/Adafruit_CircuitPython_BNO08x
