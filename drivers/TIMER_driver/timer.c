# include "timer.h"

void init_timer() {
    TA1CTL = TACLR;             // Clear timer
    TA1CTL = TASSEL__SMCLK      // Clock Source = SMCLK
            | ID__8             // Input divider / 8
            | MC__CONTINUOUS    // Continuous mode
            | TACLR;            // Clear timer again
}
