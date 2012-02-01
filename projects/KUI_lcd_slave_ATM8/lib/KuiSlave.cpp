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

// Constructors ////////////////////////////////////////////////////////////////

KuiSlave::KuiSlave(uint8_t nAddress)
{
	m_nError = 0;
	twi_setAddress(nAddress);
  	twi_attachSlaveRxEvent(OnReceive);
	twi_attachSlaveTxEvent(OnRequest);
	twi_init();
}


// Public Methods //////////////////////////////////////////////////////////////

void KuiSlave::OnReceive(uint8_t* nnBytes, int nBytes)
{
	if(!m_pEventReceive) 
	{
		//m_nError = 1; 
		return;
	}
	if(nBytes < 3) 
	{
		//m_nError = 2; 
		return;
	}
	uint8_t uPort = nnBytes[0];
	uint8_t uCmd = nnBytes[1];
    uint8_t uLength = nnBytes[2];
	//	if((uint8_t) nBytes - nLength != 3) 
	//	{
	//		//m_nError = 3; 
	//		return;
	//	}
	uint8_t* uuData;
    uuData = (uint8_t*) calloc(nBytes, sizeof(uint8_t));
	for(uint8_t n = 0; n < nBytes; n++)
	{
		uuData[n] = nnBytes[n + 4];    
	}

	if(uCmd < 255)
		m_pEventReceive(uPort, uCmd, uuData, nBytes - 4);
	else
		OnCall(uPort, uCmd, uuData, nBytes - 4);

	free(uuData);
}

void KuiSlave::OnRequest(void)
{
	m_EventRequest(m_uCallPort, m_uCallCmd, m_uuCallArg);
	
		
}

void KuiSlave::OnCall(uint8_t uPort, uint8_t uCmd, uint8_t* uuData, uint8_t uLength)
{
	m_uCallPort = uPort;
	m_uCallCmd = uuData[0];
	if(uLength > 0) m_uCallCmd = uuData[0];
	if(uLength > 1) m_uuCallArg[0] = uuData[1];
	if(uLength > 2) m_uuCallArg[1] = uuData[2];
	if(uLength > 3) m_uuCallArg[2] = uuData[3];
}


void KuiSlave::SetEventReceive( void (*pFunction)(uint8_t, uint8_t, uint8_t*, uint8_t) )
{
	m_pEventReceive = pFunction;
}

void KuiSlave::SetEventRequest( void (*pFunction)(void) )
{
	m_pEventRequest = pFunction;
}

// Private Methods //////////////////////////////////////////////////////////////

void (*KuiSlave::m_pEventReceive)(uint8_t, uint8_t, uint8_t*, uint8_t);
void (*KuiSlave::m_pEventRequest)(void);




