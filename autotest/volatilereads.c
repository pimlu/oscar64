#include <stdint.h>

uint8_t scr_reg_gamepad1_read(void) { volatile uint8_t *ptr = (volatile uint8_t*) (0x2008); return *ptr; }

uint8_t scr_reg_gamepad2_read(void) { volatile uint8_t *ptr = (volatile uint8_t*) (0x2009); return *ptr; }

// Metadata for volatile read assertions
// Format: [addr_low, addr_high, expected_count], terminated by 0xFFFF
uint8_t __volatile_read_checks[9] = {
    0x08, 0x20, 2,  // gamepad1 (0x2008) should be read 2 times
    0x09, 0x20, 1,  // gamepad2 (0x2009) should be read 1 time
    0xFF, 0xFF, 0   // terminator
};

int main(void)
{
    // Force reference to array using inline assembly to prevent optimization
    __asm volatile {
        lda __volatile_read_checks
    }

    scr_reg_gamepad2_read();

    uint8_t lo = scr_reg_gamepad1_read();
    uint8_t hi = scr_reg_gamepad1_read();
    uint16_t combo = (hi << 8) | lo;

    return combo;
}
