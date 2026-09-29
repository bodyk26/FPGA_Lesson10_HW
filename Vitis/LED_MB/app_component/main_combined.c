#include "xparameters.h"
#include "xgpio.h"
#include "xtmrctr.h"

#define SIM_FAST 

#define LED_BASE XPAR_AXI_GPIO_0_BASEADDR
#define BTN_BASE XPAR_AXI_GPIO_1_BASEADDR
#define TMR_BASE XPAR_AXI_TIMER_0_BASEADDR
#define TMR_FREQ XPAR_AXI_TIMER_0_CLOCK_FREQUENCY

#ifdef SIM_FAST
#define TICK_US 10
#else
#define TICK_US 10000
#endif

XGpio leds, btns;
XTmrCtr tmr;

void delay(u32 ticks)
{
    XTmrCtr_SetResetValue(&tmr, 0, ticks);
    XTmrCtr_Reset(&tmr, 0);
    XTmrCtr_Start(&tmr, 0);
    while (!XTmrCtr_IsExpired(&tmr, 0));
    XTmrCtr_Stop(&tmr, 0);
}

int main(void)
{
    XGpio_Initialize(&leds, LED_BASE);
    XGpio_Initialize(&btns, BTN_BASE);
    XTmrCtr_Initialize(&tmr, TMR_BASE);
    XTmrCtr_SetOptions(&tmr, 0, XTC_DOWN_COUNT_OPTION);

    XGpio_SetDataDirection(&leds, 1, 0x0);
    XGpio_SetDataDirection(&btns, 1, 0xF);

    u32 ticks = (u64)TICK_US * TMR_FREQ / 1000000;
    u32 led = 1, prev = 0, count = 0, period = 30; // period in 10 ms steps
    int paused = 0, left = 1;

    XGpio_DiscreteWrite(&leds, 1, led);

    while (1) {
        delay(ticks);

        u32 cur = XGpio_DiscreteRead(&btns, 1) & 0xF;
        u32 pressed = cur & ~prev;
        prev = cur;

        if (pressed & 1) paused = !paused;
        if (pressed & 2) left = !left;
        if ((pressed & 4) && period > 5) period -= 5;
        if ((pressed & 8) && period < 200) period += 5;

        if (paused) continue;

        if (++count >= period) {
            count = 0;
            if (left) led = ((led << 1) | (led >> 3)) & 0xF;
            else      led = ((led >> 1) | (led << 3)) & 0xF;
            XGpio_DiscreteWrite(&leds, 1, led);
        }
    }
}