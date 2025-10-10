/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    TIMER_private.h   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author : Abdallah Abdelmoemen Shehawey
 *  Layer  : MCAL
 *  SWC    : TIMER
 *
 */

#ifndef TIMER_PRIVATE_H_
#define TIMER_PRIVATE_H_

#define TIMSK                  *((volatile uint8_t *)0X59)
/*  TMISK Bits */
#define TIMSK_TOIE0            0
#define TIMSK_OCIE0            1
#define TIMSK_TOIE1            2
#define TIMSK_OCIE1B           3
#define TIMSK_OCIE1A           4
#define TIMSK_TICIE1           5
#define TIMSK_TOIE2            6
#define TIMSK_OCIE2            7

#define TIFR                   *((volatile uint8_t *)0X58)
/* TIFR BITS */
#define TIFR_TOV0              0
#define TIFR_OCF0              1
#define TIFR_TOV1              2
#define TIFR_OCF1B             3
#define TIFR_OCF1A             4
#define TIFR_ICF1              5
#define TIFR_TOV2              6
#define TIFR_OCV2              7

/*___________________________________________________________________________________________________________________*/

/* Timer0 Register*/
#define TCCR0                  *((volatile uint8_t *)0X53)
#define TCNT0                  *((volatile uint8_t *)0X52)
#define OCR0                   *((volatile uint8_t *)0X5C)

/*Timer0 BITS*/
#define TCCR0_FOC0             7
#define TCCR0_WGM00            6
#define TCCR0_COM01            5
#define TCCR0_COM00            4
#define TCCR0_WGM01            3
#define TCCR0_CS02             2
#define TCCR0_CS01             1
#define TCCR0_CS00             0

#endif /* TIMER_PRIVATE_H_ */
