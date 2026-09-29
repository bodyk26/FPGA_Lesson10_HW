#include "xparameters.h"
#include "xgpio.h"
#include "xtmrctr.h"
#include "xil_printf.h"

#define LED_GPIO_ID   XPAR_AXI_GPIO_0_BASEADDR    /* GPIO со светодиодами */
#define BTN_GPIO_ID   XPAR_AXI_GPIO_6_BASEADDR    /* GPIO с кнопками      */
#define TMR_ID        XPAR_AXI_TIMER_0_BASEADDR
                     
#define TMR_FREQ_HZ   XPAR_AXI_TIMER_0_CLOCK_FREQUENCY
#define TMR_NUM       0

#define GPIO_CH       1

/* Кнопки (биты) */
#define BTN_PAUSE     (1u << 0)
#define BTN_DIR       (1u << 1)
#define BTN_FASTER    (1u << 2)
#define BTN_SLOWER    (1u << 3)

#define BTN_ACTIVE_LOW 0

/* Временные параметры */
#define TICK_MS          10     /* шаг главного цикла              */
#define DEBOUNCE_TICKS   3      /* 3 x 10 мс = 30 мс стабильности  */
#define PERIOD_MIN_MS    50
#define PERIOD_MAX_MS    2000
#define PERIOD_STEP_MS   50
#define PERIOD_START_MS  300

static XGpio   leds, btns;
static XTmrCtr tmr;

/* ---------- Таймер ---------- */
static int timer_init(void)
{
    if (XTmrCtr_Initialize(&tmr, TMR_ID) != XST_SUCCESS)
        return XST_FAILURE;
    XTmrCtr_SetOptions(&tmr, TMR_NUM, XTC_DOWN_COUNT_OPTION);
    return XST_SUCCESS;
}

static void timer_delay_us(u32 us)
{
    u32 ticks = (u32)((u64)us * TMR_FREQ_HZ / 1000000u);

    XTmrCtr_SetResetValue(&tmr, TMR_NUM, ticks);
    XTmrCtr_Reset(&tmr, TMR_NUM);
    XTmrCtr_Start(&tmr, TMR_NUM);
    while (!XTmrCtr_IsExpired(&tmr, TMR_NUM))
        ;
    XTmrCtr_Stop(&tmr, TMR_NUM);
}


static u32 buttons_poll(void)
{
    static u32 last_raw  = 0;
    static u32 stable    = 0;
    static u32 prev      = 0;
    static u32 cnt       = 0;

    u32 raw = XGpio_DiscreteRead(&btns, GPIO_CH) & 0xF;
#if BTN_ACTIVE_LOW
    raw = ~raw & 0xF;
#endif

    if (raw == last_raw) {
        if (cnt < DEBOUNCE_TICKS) cnt++;
        else stable = raw;          
    } else {
        cnt = 0;
        last_raw = raw;
    }

    u32 pressed = stable & ~prev;   
    prev = stable;
    return pressed;
}


static u32 led_step(u32 led, int dir_left)
{
    if (dir_left)
        return ((led << 1) | (led >> 3)) & 0xF;
    else
        return ((led >> 1) | (led << 3)) & 0xF;
}

int main(void)
{
    if (XGpio_Initialize(&leds, LED_GPIO_ID) != XST_SUCCESS ||
        XGpio_Initialize(&btns, BTN_GPIO_ID) != XST_SUCCESS ||
        timer_init() != XST_SUCCESS) {
        xil_printf("Init failed\r\n");
        return -1;
    }

    XGpio_SetDataDirection(&leds, GPIO_CH, 0x0);  /* выходы */
    XGpio_SetDataDirection(&btns, GPIO_CH, 0xF);  /* входы  */

    u32 led       = 0x1;
    int paused    = 0;
    int dir_left  = 1;
    u32 period_ms = PERIOD_START_MS;
    u32 elapsed   = 0;

    XGpio_DiscreteWrite(&leds, GPIO_CH, led);
    xil_printf("Running, period %d ms\r\n", period_ms);

    while (1) {
        timer_delay_us(TICK_MS * 1000);

        u32 pressed = buttons_poll();

        if (pressed & BTN_PAUSE) {
            paused = !paused;
            xil_printf(paused ? "Pause\r\n" : "Resume\r\n");
        }
        if (pressed & BTN_DIR) {
            dir_left = !dir_left;
            xil_printf("Direction: %s\r\n", dir_left ? "left" : "right");
        }
        if ((pressed & BTN_FASTER) && period_ms > PERIOD_MIN_MS) {
            period_ms -= PERIOD_STEP_MS;
            xil_printf("Period %d ms\r\n", period_ms);
        }
        if ((pressed & BTN_SLOWER) && period_ms < PERIOD_MAX_MS) {
            period_ms += PERIOD_STEP_MS;
            xil_printf("Period %d ms\r\n", period_ms);
        }

        if (paused)
            continue;               /* текущий светодиод остаётся гореть */

        elapsed += TICK_MS;
        if (elapsed >= period_ms) {
            elapsed = 0;
            led = led_step(led, dir_left);
            XGpio_DiscreteWrite(&leds, GPIO_CH, led);
        }
    }
}