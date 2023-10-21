// DEFS_877 
// 
// Standard definitions for PIC16F877 
// 
// Copyright, Peter H. Anderson, Baltimore, MD, June, '99 
 
//#define byte int 

//#byte PORTD = 0x08
//#bit INTF = 0xb.1

/*
	Alterado por Maria Edivânia Neres de Sousa, acadêmica de Engenharia Elétrica na UFPI.
	25/05/2022, Teresina - PI.
*/

#nolist 
 
//#define FALSE 0 
//#define TRUE !FALSE 
 
 
#byte PCL    = 0x02 
#byte STATUS = 0x03 
#byte FSR    = 0x04 

#byte PORTA = 0x05
	#bit RA5 = PORTA.5 
	#bit RA4 = PORTA.4 
	#bit RA3 = PORTA.3 
	#bit RA2 = PORTA.2 
	#bit RA1 = PORTA.1 
	#bit RA0 = PORTA.0  
#byte PORTB = 0x06 
	#bit RB7 = PORTB.7 
	#bit RB6 = PORTB.6 
	#bit RB5 = PORTB.5 
	#bit RB4 = PORTB.4 
	#bit RB3 = PORTB.3 
	#bit RB2 = PORTB.2 
	#bit RB1 = PORTB.1 
	#bit RB0 = PORTB.0 
#byte PORTC = 0x07 
	#bit RC7 = PORTC.7 
	#bit RC6 = PORTC.6 
	#bit RC5 = PORTC.5 
	#bit RC4 = PORTC.4 
	#bit RC3 = PORTC.3 
	#bit RC2 = PORTC.2 
	#bit RC1 = PORTC.1 
	#bit RC0 = PORTC.0 
#byte PORTD = 0x08 
	#bit RD7 = PORTD.7 
	#bit RD6 = PORTD.6 
	#bit RD5 = PORTD.5 
	#bit RD4 = PORTD.4 
	#bit RD3 = PORTD.3 
	#bit RD2 = PORTD.2 
	#bit RD1 = PORTD.1 
	#bit RD0 = PORTD.0 
#byte PORTE = 0x09
	#bit RE2 = PORTE.2 
	#bit RE1 = PORTE.1 
	#bit RE0 = PORTE.0 


#byte TRISA = 0x85 
	#bit TRISA5 = TRISA.5 
	#bit TRISA4 = TRISA.4 
	#bit TRISA3 = TRISA.3 
	#bit TRISA2 = TRISA.2 
	#bit TRISA1 = TRISA.1 
	#bit TRISA0 = TRISA.0
#byte TRISB = 0x86
	#bit TRISB7 = TRISB.7 
	#bit TRISB6 = TRISB.6 
	#bit TRISB5 = TRISB.5 
	#bit TRISB4 = TRISB.4 
	#bit TRISB3 = TRISB.3 
	#bit TRISB2 = TRISB.2 
	#bit TRISB1 = TRISB.1 
	#bit TRISB0 = TRISB.0 
#byte TRISC = 0x87 
	#bit trisc7 = TRISC.7 
	#bit trisc6 = TRISC.6 
	#bit trisc5 = TRISC.5 
	#bit trisc4 = TRISC.4 
	#bit trisc3 = TRISC.3 
	#bit trisc2 = TRISC.2 
	#bit trisc1 = TRISC.1 
	#bit trisc0 = TRISC.0  
#byte TRISD = 0x88 
	#bit trisd7 = TRISD.7 
	#bit trisd6 = TRISD.6 
	#bit trisd5 = TRISD.5 
	#bit trisd4 = TRISD.4 
	#bit trisd3 = TRISD.3 
	#bit trisd2 = TRISD.2 
	#bit trisd1 = TRISD.1 
	#bit trisd0 = TRISD.0  
#byte TRISE = 0x89
	#bit ibf    = TRISE.7 
	#bit obf    = TRISE.6 
	#bit ibov   = TRISE.5 
	#bit pspmode = TRISE.4 
	#bit trise2 = TRISE.2 
	#bit trise1 = TRISE.1 
	#bit trise0 = TRISE.0

		  ////////////
		  // TIMER0 //
//////////////////////////////////
#byte TMR0 	 = 0x01
#byte OPTION_REG = 0x81 
	// OPTION bits // 
	#bit NOT_RBPU = OPTION_REG.7 
	#bit INTEDG   = OPTION_REG.6 
	#bit T0CS	  = OPTION_REG.5 
	#bit T0SE 	  = OPTION_REG.4 
	#bit PSA 	  = OPTION_REG.3 
	#bit PS2 	  = OPTION_REG.2 
	#bit PS1 	  = OPTION_REG.1 
	#bit PS0 	  = OPTION_REG.0 
#byte INTCON = 0x0B
	#bit GIE  	= INTCON.7 
	#bit PEIE 	= INTCON.6 
	#bit TMR0IE = INTCON.5 
	#bit INTE 	= INTCON.4 
	#bit RBIE 	= INTCON.3 
	#bit TMR0IF = INTCON.2 
	#bit INTIF 	= INTCON.1 
	#bit RBIF 	= INTCON.0
///////////////////////////////////


		  ////////////
		  // TIMER1 //
//////////////////////////////////
#byte TMR1L = 0x0E 
#byte TMR1H = 0x0F
#byte T1CON = 0x10
	#bit T1CKPS1 = T1CON.5 
	#bit T1CKPS0 = T1CON.4 
	#bit T1OSCEN = T1CON.3 
	#bit T1SYNC  = T1CON.2 
	#bit TMR1CS  = T1CON.1 
	#bit TMR1ON  = T1CON.0 
#byte PIR1  = 0x0C
	#bit PSPIF 	= PIR1.7 
	#bit ADIF 	= PIR1.6 
	#bit RCIF 	= PIR1.5 
	#bit TXIF 	= PIR1.4 
	#bit SSPIF 	= PIR1.3 
	#bit CCP1IF = PIR1.2 
	#bit TMR2IF = PIR1.1 
	#bit TMR1IF = PIR1.0 
#byte PIE1 = 0x8C
	#bit PSPIE 	= PIE1.7 
	#bit ADIE   = PIE1.6 
	#bit RCIE	= PIE1.5 
	#bit TXIE   = PIE1.4 
	#bit SSPIE  = PIE1.3 
	#bit CCP1IE = PIE1.2 
	#bit TMR2IE = PIE1.1 
	#bit TMR1IE = PIE1.0 
#byte CCPR1L  = 0x15
#byte CCPR1H  = 0x16	
#byte CCP1CON = 0x17
	#bit CCP1X  = CCP1CON.5 
	#bit CCP1Y  = CCP1CON.4 
	#bit CCP1M3 = CCP1CON.3 
	#bit CCP1M2 = CCP1CON.2 
	#bit CCP1M1 = CCP1CON.1 
	#bit CCP1M0 = CCP1CON.0
///////////////////////////////////


		  ////////////
		  // TIMER2 //
//////////////////////////////////
#byte TMR2  = 0x11
#byte T2CON = 0x12
	#bit TOUTPS3 = T2CON.6 
	#bit TOUTPS2 = T2CON.5 
	#bit TOUTPS1 = T2CON.4 
	#bit TOUTPS0 = T2CON.3 
	#bit TMR2ON  = T2CON.2 
	#bit T2CKPS1 = T2CON.1 
	#bit T2CKPS0 = T2CON.0
#byte PIR2  = 0x0D 
	#bit EEIF   = PIR2.4 
	#bit BCLIF  = PIR2.3 
	#bit CCP2IF = PIR2.0
#byte PIE2 = 0x8D
	#bit EEIE   = PIE2.4 
	#bit BCLIE  = PIE2.3 
	#bit CCP2IE = PIE2.0
#byte PR2     = 0x92
#byte CCP2CON = 0x1D
	#bit CCP2X  = CCP2CON.5 
	#bit CCP2Y  = CCP2CON.4 
	#bit CCP2M3 = CCP2CON.3 
	#bit CCP2M2 = CCP2CON.2 
	#bit CCP2M1 = CCP2CON.1 
	#bit CCP2M0 = CCP2CON.0 
#byte CCPR2L  = 0x1B
#byte CCPR2H  = 0x1C 
///////////////////////////////////

		    //////////
		    // MSSP //
//////////////////////////////////
#byte SSPSTAT = 0x94 
	#bit stat_smp = SSPSTAT.7 
	#bit stat_cke = SSPSTAT.6 
	#bit stat_da = SSPSTAT.5 
	#bit stat_p  = SSPSTAT.4 
	#bit stat_s  = SSPSTAT.3 
	#bit stat_rw = SSPSTAT.2 
	#bit stat_ua = SSPSTAT.1 
	#bit stat_bf = SSPSTAT.0
#byte SSPCON1  = 0x14
	#bit wcol = SSPCON1.7 
	#bit sspov = SSPCON1.6 
	#bit sspen = SSPCON1.5 
	#bit ckp = SSPCON1.4 
	#bit sspm3 = SSPCON1.3 
	#bit sspm2 = SSPCON1.2 
	#bit sspm1 = SSPCON1.1 
	#bit sspm0 = SSPCON1.0 
//////////////////////////////////


#byte PCLATH = 0x0a 
#byte SSPBUF  = 0x13 
#byte RCSTA   = 0x18 
#byte TXREG   = 0x19 
#byte RCREG   = 0x1a 
#byte ADRESH  = 0x1e 
#byte ADCON0  = 0x1f 
#byte PCON    = 0x8e 
#byte SSPCON2 = 0x91 
#byte SSPADD  = 0x93 
#byte TXSTA   = 0x98 
#byte SPBRG   = 0x99 
#byte ADRESL  = 0x9e 
#byte ADCON1  = 0x9f 
#byte EEDATA  = 0x10c 
#byte EEADR   = 0x10d 
#byte EEDATH  = 0x10e 
#byte EEADRH  = 0x10f
#byte EECON1  = 0x18c 
#byte EECON2  = 0x18d 


// STATUS bits 
#define IRP 	8 
#define RP1 	6 
#define RP0     5 
#define TO 		4 
#define PD 		3 
#define ZERO    2 
#define DC      1 
#define C   	0 
 
#define RA5     5 
#define RA4     4 
#define RA3     3 
#define RA2     2 
#define RA1     1 
#define RA0     0 
 
#define RB7     7 
#define RB6     6 
#define RB5     5 
#define RB4     4 
#define RB3     3 
#define RB2     2 
#define RB1     1 
#define RB0     0 
 
#define RC7     7 
#define RC6     6 
#define RC5     5 
#define RC4     4 
#define RC3     3 
#define RC2     2 
#define RC1     1 
#define RC0     0 
 
#define RD7     PIN_D7
#define RD6     PIN_D6
#define RD5     PIN_D5
#define RD4     PIN_D4
#define RD3     PIN_D3
#define RD2     PIN_D2
#define RD1     PIN_D1 
#define RD0     PIN_D0
 
#define RE2     2 
#define RE1     1 
#define RE0     0 


// RCSTA bits 
#bit spen = RCSTA.7 
#bit rx9  = RCSTA.6 
#bit sren = RCSTA.5 
#bit cren = RCSTA.4 
#bit adden = RCSTA.3 
#bit ferr = RCSTA.2 
#bit oerr = RCSTA.1 
#bit rx9d = RCSTA.0 
 
//  ADCON0 bits 
#bit adcs1 = ADCON0.7 
#bit adcs0 = ADCON0.6 
#bit chs2  = ADCON0.5 
#bit chs1  = ADCON0.4 
#bit chs0  = ADCON0.3 
#bit adgo  = ADCON0.2 
 
#bit adon  = ADCON0.0 
 
// PCON bits 
#bit por  = PCON.1 
#bit bor = PCON.0 
 
// SSPCON2 
#bit gcen = SSPCON2.7 
#bit ackstat = SSPCON2.6 
#bit ackdt = SSPCON2.5 
#bit acken = SSPCON2.4 
#bit rcen = SSPCON2.3 
#bit pen = SSPCON2.2 
#bit rsen = SSPCON2.1 
#bit sen = SSPCON2.0 
 
// TXSTA bits 
#bit csrc  = TXSTA.7 
#bit tx9  = TXSTA.6 
#bit txen  = TXSTA.5 
#bit sync  = TXSTA.4 
 
#bit brgh  = TXSTA.2 
#bit trmt  = TXSTA.1 
#bit tx9d  = TXSTA.0 
 
// ADCON1 bits 
#bit adfm = ADCON1.7 
#bit pcfg3 = ADCON1.3 
#bit pcfg2  = ADCON1.2 
#bit pcfg1  = ADCON1.1 
#bit pcfg0 = ADCON1.0 
 
//  EECON1 
#bit eepgd = EECON1.7 
#bit wrerr = EECON1.3 
#bit wren = EECON1.2 
#bit wr = EECON1.1 
#bit rd = EECON1.0 
 
#define CONFIG_ADDR 0x2007 
#define FOSC0  0x01 
#define FOSC1  0x02 
#define WDTE  0x04 
#define PWRTE  0x08 
#define CP0  0x10 
#define CP1  0x20 
 
#list 

