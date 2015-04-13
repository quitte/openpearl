#include "chip.h"
/* System oscillator rate and RTC oscillator rate */
const uint32_t OscRateIn = 12000000;
const uint32_t RTCOscRateIn = 32768;

static void pllfeed(int pllnum) {
	LPC_SYSCON->PLL[pllnum].PLLFEED = 0xAA;
	LPC_SYSCON->PLL[pllnum].PLLFEED = 0x55;
}

static void ClockInit() {
	/* Sets the CPU clock to 100Mhz from the external 12Mhz
	 * crystal, following the instructions of the NXP UM10360
	 * Manual, 4.5.13 */

	/* Disconnect the Main PLL if it is connected already
	 * Which is the same as enabling, disconnected PLL for
	 * all intents and purposes*/
	LPC_SYSCON->PLL[0].PLLCON = (1<<1);pllfeed(0);
	/* Disable the PLL*/
	LPC_SYSCON->PLL[0].PLLCON = 0;pllfeed(0);
	/* CPU Clock divider = 1 to improve speed */
	LPC_SYSCON->CCLKSEL = 0;
	/* Enable the crystal, wait for lock*/
	LPC_SYSCON->SCS=(1<<5);
	while(!(LPC_SYSCON->SCS&(1<<6)));
	/* Pick the external Oscillator */
	LPC_SYSCON->CLKSRCSEL = (1<<0);
	/* FCCO = ((24+1) * 2 * (12MHz/2)) = 300MHz */
	LPC_SYSCON->PLL[0].PLLCFG = (1<<16)|(24<<0);pllfeed(0);
	/* Enable the PLL */
	LPC_SYSCON->PLL[0].PLLCON = (1<<0);pllfeed(0);
	/*Wait for PLL lock*/
	while (!(LPC_SYSCON->PLL[0].PLLSTAT&(1<<26))) {} /* Wait for the PLL to Lock */
	/* CPUClock Divider: 300Mhz/3=100Mhz */
	LPC_SYSCON->CCLKSEL = 2;
	/*Connect the PLL*/
	LPC_SYSCON->PLL[0].PLLCON = (1<<0)|(1<<1);pllfeed(0);

	/* Put all the peripheral clocks to their CCLK/4 reset value */
	LPC_SYSCON->PCLKSEL[0] = 0;
	LPC_SYSCON->PCLKSEL[1] = 0;

	/* Make timer0 run at CCLK */
	LPC_SYSCON->PCLKSEL[0] = (1<<2);
}

static void USBClockInit(){
	/* Disconnect and disable PLL*/
	LPC_SYSCON->PLL[1].PLLCON = 0;pllfeed(1);
	/* USBClock M=4, P=2  */
	LPC_SYSCON->PLL[1].PLLCFG = (2<<5)|(4<<0);pllfeed(1);
	/* Enable and connect the PLL */
	LPC_SYSCON->PLL[1].PLLCON = (1<<0)|(1<<1);pllfeed(1);
	/*Wait for PLL lock*/
	while (!(LPC_SYSCON->PLL[1].PLLSTAT&(1<<10))) {} /* Wait for the PLL to Lock */
}

static void PowerInit(){
	/* Set Peripheral Power to the Reset value */
	LPC_SYSCON->PCONP = 0x3BE;
}

void SystemInit() {
	ClockInit();
//	PowerInit();
	SystemCoreClockUpdate();
}

