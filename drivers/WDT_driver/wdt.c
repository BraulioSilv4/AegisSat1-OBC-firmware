#include "wdt.h"

static void WDT_handle_reset() {
    switch (__even_in_range(SYSRSTIV, SYSRSTIV_PMMPW)) {
        case SYSRSTIV_NONE:        /* no reset */           break;
        case SYSRSTIV_BOR:         /* brown‑out reset */    break;
        case SYSRSTIV_PERF:        /* perf fetch error */   break;
        case SYSRSTIV_WDTTO: {     /* watchdog timeout */
            TA0CTL = MC_0;              // Stop Timer_A
            TA0CTL |= TACLR;            // Clear the counter 
            TA0CCTL0 &= ~CCIE;          // Disable Timer_A Interrupt
            TA0CCTL0 &= ~CCIFG;         // Clear the interrupt flag
        }
        case SYSRSTIV_WDTKEY:      /* WDTKEY violation */   break;
        default:                   /* unknown/unhandled */  break;
    }
}

void WDT_init() {
    WDTCTL = WDTPW | WDTHOLD | WDTSSEL__ACLK | WDTIS__32K;        // Stop the watchdog, ACLK as source (32kHz) and interval (2^15/32kHz)
    WDT_handle_reset();
}

void WDT_start() {
    WDTCTL = WDTPW | ((WDTCTL & ~WDTHOLD) & 0xFF);
}

void WDT_reset() {
    WDTCTL = WDTPW | ((WDTCTL | WDTCNTCL) & 0xFF);   
}

void WDT_dead() {
    while(1);
}

