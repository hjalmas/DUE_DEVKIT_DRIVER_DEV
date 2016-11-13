
#ifndef TC_H_INCLUDED
#define TC_H_INCLUDED

/**
 * The Timer Counter (TC) includes several identical 16-bit or 32-bit
 * Timer Counter channels. Each channel can be independently programmed
 * to perform a wide range of functions that includes frequency
 * measurement, event counting, interval measurement, pulse generation,
 * delay timing, and pulse width modulation.
 */


/*
 * -------------------------------------------------------------------
 * 							INCLUDES
 * -------------------------------------------------------------------
 */
#include <stdio.h>
#include <limits.h>
#include <assert.h>
#include "diag/Trace.h"
#include "cmsis_device.h"
#include "sam3x_conf.h"


/*
 * -------------------------------------------------------------------
 * 							PROTOTYPES
 * -------------------------------------------------------------------
 */

void 		tc_init				(Tc *p_tc, uint32_t ul_channel, uint32_t ul_Mode);
void 		tc_sync_trigger		(Tc *p_tc);
void 		tc_set_block_mode	(Tc *p_tc, uint32_t ul_blockmode);

uint32_t 	tc_init_2bit_gray	(Tc *p_tc, uint32_t ul_channel, uint32_t ul_steppermode);

void 		tc_start			(Tc *p_tc, uint32_t ul_channel);
void 		tc_stop				(Tc *p_tc, uint32_t ul_channel);

uint32_t 	tc_read_cv			(Tc *p_tc, uint32_t ul_channel);
uint32_t 	tc_read_ra			(Tc *p_tc, uint32_t ul_channel);
uint32_t 	tc_read_rb			(Tc *p_tc, uint32_t ul_channel);
uint32_t 	tc_read_rc			(Tc *p_tc, uint32_t ul_channel);

void 		tc_write_ra			(Tc *p_tc, uint32_t ul_channel, uint32_t ul_value);
void 		tc_write_rb			(Tc *p_tc, uint32_t ul_channel, uint32_t ul_value);
void 		tc_write_rc			(Tc *p_tc, uint32_t ul_channel, uint32_t ul_value);

uint32_t 	tc_find_mck_divisor	(uint32_t ul_freq, uint32_t ul_mck, uint32_t *p_uldiv, uint32_t *ul_tcclks, uint32_t ul_boardmck);
void 		tc_enable_interrupt	(Tc *p_tc, uint32_t ul_channel,uint32_t ul_sources);
void 		tc_disable_interrupt(Tc *p_tc, uint32_t ul_channel, uint32_t ul_sources);
uint32_t 	tc_get_interrupt_mask(Tc *p_tc, uint32_t ul_channel);
uint32_t 	tc_get_status		(Tc *p_tc, uint32_t ul_channel);
void 		tc_enable_qdec_interrupt(Tc *p_tc, uint32_t ul_sources);
void 		tc_disable_qdec_interrupt(Tc *p_tc, uint32_t ul_sources);
uint32_t 	tc_get_qdec_interrupt_mask(Tc *p_tc);
uint32_t 	tc_get_qdec_interrupt_status(Tc *p_tc);

void 		tc_set_writeprotect(Tc *p_tc, uint32_t ul_enable);

#endif /* TC_H_INCLUDED */
