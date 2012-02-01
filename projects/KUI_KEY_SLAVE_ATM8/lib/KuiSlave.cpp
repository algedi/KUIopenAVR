/*
  KuiSlave.c - TWI/I2C library for iiKUIno project
  Copyright (c) 2011 Andrea Calvia (algedi_kui@ilnaufrago.it).  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

extern "C" {
  #include <stdlib.h>
  #include <string.h>
  #include <inttypes.h>
  #include "twi.h"
}

#include "KuiSlave.h"

#define KUI_BUS_LENGTH 32

uint8_t KuiSlave::m_uAddress = 0;
uint8_t KuiSlave::m_uCallPort = 0;
uint8_t KuiSlave::m_uCallCmd = 0;


// Constructors ////////////////////////////////////////////////////////////////

KuiSlave::KuiSlave(uint8_t nAddress)
{
	SetAddress(nAddress);

	twi_setAddress(nAddress);
 	twi_attachSlaveRxEvent(OnReceive); // richiede static per OnReceive
	twi_attachSlaveTxEvent(OnRequest); // richiede static per OnRequest
	twi_init();
}


// Public Methods //////////////////////////////////////////////////////////////

void KuiSlave::OnReceive(uint8_t* nnBytes, int nBytes)
{
	if(!m_pEventReceive) return;
	if(nBytes < 4) return;
	uint8_t uPort = nnBytes[0];
	uint8_t uCmd = nnBytes[1];
  	uint8_t uLength = nnBytes[2];

	uint8_t uuData[uLength];
//  	uuData = (uint8_t*) calloc(uLength, sizeof(uint8_t));
	for(uint8_t n = 0; n < uLength; n++)
	{
		uuData[n] = nnBytes[n + 4];    
	}

	if(uCmd < 255)
		m_pEventReceive(uPort, uCmd, uuData, uLength);
	else
		m_uCallPort = uPort;
		m_uCallCmd = uuData[0];
//	free(uuData);
}

void KuiSlave::OnRequest(void)
{
	if(m_uCallPort < 1) return;
	uint8_t uLength = 0;
	uint8_t uuData[KUI_BUS_LENGTH + 4]; 
	uLength = m_pEventRequest(m_uCallPort, m_uCallCmd, uuData + 4);

	uuData[0] = m_uAddress;
	uuData[1] = m_uCallPort;
	uuData[2] = m_uCallCmd;
	uuData[3] = uLength;

	twi_transmit(uuData, KUI_BUS_LENGTH + 4);
	m_uCallPort = 0;
}

//void KuiSlave::OnCall(uint8_t uPort, uint8_t uCmd, uint8_t* uuData, uint8_t uLength)
//{
////	m_uCallPort = uPort;
////	m_uCallCmd = uuData[0];
//////	if(uLength > 0) m_uCallCmd = uuData[0];
////	if(uLength > 1) m_uuCallArg[0] = uuData[1];
////	if(uLength > 2) m_uuCallArg[1] = uuData[2];
////	if(uLength > 3) m_uuCallArg[2] = uuData[3];
//}


void KuiSlave::SetEventReceive( void (*pFunction)(uint8_t, uint8_t, uint8_t*, uint8_t) )
{
	m_pEventReceive = pFunction;
}

void KuiSlave::SetEventRequest( uint8_t (*pFunction)(uint8_t, uint8_t, uint8_t*) )
{
	m_pEventRequest = pFunction;
}

// Private Methods //////////////////////////////////////////////////////////////

void KuiSlave::SetAddress(uint8_t uAddress)
{
	m_uAddress = uAddress;
}

void (*KuiSlave::m_pEventReceive)(uint8_t, uint8_t, uint8_t*, uint8_t);
uint8_t (*KuiSlave::m_pEventRequest)(uint8_t, uint8_t, uint8_t*);




