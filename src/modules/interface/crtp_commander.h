/**
 *    ||          ____  _ __  ______
 * +------+      / __ )(_) /_/ ____/_________ _____  ___
 * | 0xBC |     / __  / / __/ /    / ___/ __ `/_  / / _	\
 * +------+    / /_/ / / /_/ /___ / /  / /_/ / / /_/  __/
 *  ||  ||    /_____/_/\__/\____//_/   \__,_/ /___/\___/
 *
 * Crazyflie control firmware
 *
 * Copyright (C) 2011-2012 Bitcraze AB
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, in version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef CRTP_COMMANDER_H_
#define CRTP_COMMANDER_H_

#include <stdint.h>
#include "stabilizer_types.h"
#include "crtp.h"

void crtpCommanderInit(void);
void crtpCommanderRpytDecodeSetpoint(setpoint_t *setpoint, CRTPPacket *pk);
void crtpCommanderRpytCompactDecodeSetpoint(setpoint_t *setpoint, CRTPPacket *pk);
//void crtpCommanderRpytChanceController(setpoint_t *setpoint, CRTPacket *pk);
void crtpCommanderGenericDecodeSetpoint(setpoint_t *setpoint, CRTPPacket *pk);
void custPowerDistributionTwo(uint16_t m1, uint16_t m2, uint16_t m3, uint16_t m4, uint16_t stamp);

#endif /* CRTP_COMMANDER_H_ */
