#include "stm32f4xx.h"
#include "stm32f407xx.h"
void delay_ms(uint32_t ms);
extern void SystemInit(void);
int main(void) {
    // Khoi tao clock cho GPIO
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

    // Cấu hình các chân PD12, PD13, PD14, PD15 là output
    GPIOD->MODER &= ~(0xFF << (2 * 12));         // Xoá cấu hình cũ
    GPIOD->MODER |=  (0x55 << (2 * 12));         // Output mode cho PD12..PD15

    // Cấu hình chân PA0 là input
    GPIOA->MODER &= ~(0x3 << 0);                 // Input mode cho PA0

    GPIOD->OTYPER &= ~(0xF << 12);               // Push-pull

    GPIOD->OSPEEDR |= (0xFF << (2 * 12));        // High speed
    GPIOD->PUPDR &= ~(0xFF << (2 * 12));         // No pull-up, pull-down

    GPIOA->PUPDR &= ~(0x3 << 0);                 // Xoá cấu hình cũ
    // GPIOA->PUPDR |=  (0x1 << 0);                 // Pull-up cho PA0

    while (1) {
#ifdef MODE1
        // Nhấn vào nút PA0 làm bát/ tắt LED PD12..PD15, delay 10ms, không nhấn nút PA0 tắt LED PD12..PD15
        if ((GPIOA->IDR & (1 << 0))) {
            GPIOD->ODR |= (0xF << 12); // Bật LED khi nhấn nút
        } else {
            GPIOD->ODR &= ~(0xF << 12); // Tắt LED khi thả nút
        }
        delay_ms(10);
#else
        // Nhấn vào nút PA0 làm bật/ tắt LED PD12..PD15, delay 10ms
        if ((GPIOA->IDR & (1 << 0))) {
            GPIOD->ODR ^= (0xF << 12); // Bật LED khi nhấn nút
        }
        delay_ms(10);
#endif // MODE1
    }
}

// openocd -f interface/stlink.cfg -f target/stm32f4x.cfg -c "program blink.elf verify reset exit"
void delay_ms(uint32_t ms) {
    // Giả sử clock chạy ở 16 MHz từ HSI (hoặc bạn có thể thay đổi tùy theo clock thực tế)
    for (uint32_t i = 0; i < ms * 16000; i++) {
        __NOP();
    }
}
