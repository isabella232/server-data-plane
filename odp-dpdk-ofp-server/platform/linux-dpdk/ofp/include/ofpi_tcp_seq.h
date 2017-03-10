/*-
 * Copyright (c) 1982, 1986, 1993, 1995
 *	The Regents of the University of California.
 * Copyright (c) 2015 Nokia Solutions and Networks
 * Copyright (c) 2015 Enea Software AB
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#ifndef _NETINET_TCP_SEQ_H_
#define _NETINET_TCP_SEQ_H_

#include "ofpi_timer.h"

/*
 * TCP sequence numbers are 32 bit integers operated
 * on with modular arithmetic.  These macros can be
 * used to compare such integers.
 */
#define	SEQ_LT(a,b)	((int)((a)-(b)) < 0)
#define	SEQ_LEQ(a,b)	((int)((a)-(b)) <= 0)
#define	SEQ_GT(a,b)	((int)((a)-(b)) > 0)
#define	SEQ_GEQ(a,b)	((int)((a)-(b)) >= 0)

#define	SEQ_MIN(a, b)	((SEQ_LT(a, b)) ? (a) : (b))
#define	SEQ_MAX(a, b)	((SEQ_GT(a, b)) ? (a) : (b))

/* for modulo comparisons of timestamps */
#define TSTMP_LT(a,b)	((int)((a)-(b)) < 0)
#define TSTMP_GT(a,b)	((int)((a)-(b)) > 0)
#define TSTMP_GEQ(a,b)	((int)((a)-(b)) >= 0)

/*
 * Macros to initialize tcp sequence numbers for
 * send and receive from initial send and receive
 * sequence numbers.
 */
#define	tcp_rcvseqinit(tp) \
	(tp)->rcv_adv = (tp)->rcv_nxt = (tp)->irs + 1

#define	tcp_sendseqinit(tp) \
	(tp)->snd_una = (tp)->snd_nxt = (tp)->snd_max = (tp)->snd_up = \
	    (tp)->snd_recover = (tp)->iss

/*
 * Clock macros for RFC 1323 timestamps.
 */
#define	TCP_TS_TO_TICKS(_t)	((_t)*1000 / OFP_TIMER_RESOLUTION_US)

/* Timestamp wrap-around time, 24 days. */
#define TCP_PAWS_IDLE	(24 * 24 * 60 * 60 * 1000)

/*
 * tcp_ts_getticks() in ms, should be 1ms < x < 1000ms according to RFC 1323.
 * We always use 1ms granularity independent of hz.
 */
static __inline uint32_t
tcp_ts_getticks(void)
{
	return (ofp_timer_ticks(0) * (OFP_TIMER_RESOLUTION_US / 1000));
}

#endif /* _NETINET_TCP_SEQ_H_ */
