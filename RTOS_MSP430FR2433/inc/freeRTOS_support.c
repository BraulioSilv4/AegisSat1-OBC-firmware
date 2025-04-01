#include "freeRTOS_support.h"

void initialize_clock() {
    // Initialize ACLK using REFO as clock reference
    // CS_initClockSignal(CS_ACLK, CS_REFOCLK_SELECT, CS_CLOCK_DIVIDER_1);
    CS_initClockSignal(CS_ACLK, CS_XT1CLK_SELECT, CS_CLOCK_DIVIDER_1);
}

void vApplicationSetupTimerInterrupt(void) {
    /* Setting up hardware timer for RTOS tick interrupt */
    TA0CTL |= MC_0;          // Halt the timer
    TA0R = 0;                // Reset Count
    TA0CTL |= TACLR;         // Clear Timer_A settings                        
    TA0CCR0 = (configREFOCLK_HZ / configTICK_RATE_HZ) - 1;
    TA0CCTL0 = CCIE;        // Enable interrupt when TA0R == TA0CCR0
    TA0CTL = TASSEL_1 | MC_1 | TACLR;    // TASSEL_1 = ACLK as clock source, MC_1 = Up mode (counts up to TA0CCR0), TACLR = clear settings
}

void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName) {
    /* Overflow hook */
    while(1);
}
