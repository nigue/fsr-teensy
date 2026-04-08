#if JOYSTICK_SIZE == 1

static uint8_t joystick_report_desc[] = {
    0x05, 0x01,        // Usage Page (Generic Desktop)
    0x09, 0x05,        // Usage (Game Pad)
    0xA1, 0x01,        // Collection (Application)

    0x05, 0x09,        // Usage Page (Button)
    0x19, 0x01,        // Usage Minimum (Button 1)
    0x29, 0x04,        // Usage Maximum (Button 4)

    0x15, 0x00,        // Logical Min (0)
    0x25, 0x01,        // Logical Max (1)

    0x95, 0x04,        // Report Count (4 botones)
    0x75, 0x01,        // Report Size (1 bit por botón)
    0x81, 0x02,        // Input (Data,Var,Abs)

    // Padding hasta completar 1 byte
    0x95, 0x04,        // 4 bits restantes
    0x75, 0x01,
    0x81, 0x03,        // Input (Const,Var,Abs)

    0xC0               // End Collection
};

#elif JOYSTICK_SIZE == 12