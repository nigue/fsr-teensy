#elif defined(USB_DDR)
  #define VENDOR_ID        0x16C0
  #define PRODUCT_ID       0x27DD

  // Necesario para Serial (CDC)
  #define DEVICE_CLASS     0xEF
  #define DEVICE_SUBCLASS  0x02
  #define DEVICE_PROTOCOL  0x01

  #define MANUFACTURER_NAME    {'T','e','e','n','s','y'}
  #define MANUFACTURER_NAME_LEN 6
  #define PRODUCT_NAME         {'S','e','r','i','a','l',' ','+',' ','D','D','R',' ','C','o','n','t','r','o','l','l','e','r'}
  #define PRODUCT_NAME_LEN     23

  #define EP0_SIZE        64

  // Interfaces: CDC (2) + Joystick (1)
  #define NUM_INTERFACE   3
  #define NUM_ENDPOINTS   4

  // --- CDC (Serial) ---
  #define CDC_IAD_DESCRIPTOR  1
  #define CDC_STATUS_INTERFACE 0
  #define CDC_DATA_INTERFACE   1

  #define CDC_ACM_ENDPOINT     2
  #define CDC_RX_ENDPOINT      3
  #define CDC_TX_ENDPOINT      3

  #define CDC_ACM_SIZE         16
  #define CDC_RX_SIZE_480      512
  #define CDC_TX_SIZE_480      512
  #define CDC_RX_SIZE_12       64
  #define CDC_TX_SIZE_12       64

  // --- JOYSTICK ---
  #define JOYSTICK_INTERFACE   2
  #define JOYSTICK_ENDPOINT    4
  #define JOYSTICK_SIZE        1
  #define JOYSTICK_INTERVAL    1

  // --- ENDPOINT CONFIG ---
  #define ENDPOINT2_CONFIG ENDPOINT_RECEIVE_UNUSED + ENDPOINT_TRANSMIT_INTERRUPT
  #define ENDPOINT3_CONFIG ENDPOINT_RECEIVE_BULK + ENDPOINT_TRANSMIT_BULK
  #define ENDPOINT4_CONFIG ENDPOINT_RECEIVE_UNUSED + ENDPOINT_TRANSMIT_INTERRUPT