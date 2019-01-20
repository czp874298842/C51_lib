/**
* @file
* @brief Public QV-nano interface.
* @ingroup qvn
* @cond
******************************************************************************
* Last updated for version 6.1.1
* Last updated on  2018-02-18
*
*                    Q u a n t u m     L e a P s
*                    ---------------------------
*                    innovating embedded systems
*
* Copyright (C) Quantum Leaps, LLC. All rights reserved.
*
* This program is open source software: you can redistribute it and/or
* modify it under the terms of the GNU General Public License as published
* by the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* Alternatively, this program may be distributed and modified under the
* terms of Quantum Leaps commercial licenses, which expressly supersede
* the GNU General Public License and are specifically designed for
* licensees interested in retaining the proprietary status of their code.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*
* Contact information:
* https://www.state-machine.com
* mailto:info@state-machine.com

******************************************************************************
* @endcond
*/
#ifndef qvn_h
#define qvn_h

/****************************************************************************/
/*! Ready set of QV-nano. */
extern uint_fast8_t volatile QV_readySet_;

/*! QV idle callback (customized in BSPs for QK)
*
* QV_onIdle() is called continuously by the QV-nano scheduler. This callback
* gives the application an opportunity to enter a power-saving CPU mode,
* or perform some other idle processing.
*
* @note QV_onIdle() is invoked with interrupts disabled, but must return
* with interrupts enabled. This is in contrast to the callback QK_onIdle(),
* which is used by the preemptive QK-nano scheduler.
*/
void QV_onIdle(void) ;

#endif /* qvn_h */
