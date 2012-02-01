/*
  KuiMaster.c - TWI/I2C library for iiKUIno project
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

#include "KuiMaster.h"

#define KUI_BUS_LENGTH 32

// Constructors ////////////////////////////////////////////////////////////////

KuiMaster::KuiMaster()
{
  m_uuBuffer = (uint8_t*) calloc(KUI_BUS_LENGTH + 4, sizeof(uint8_t));
  twi_init();
}

// Public Methods //////////////////////////////////////////////////////////////

void KuiMaster::Send(uint8_t uAddress, uint8_t uPort, uint8_t uCmd, const uint8_t* uuData, uint8_t uDataLength)
{
	for(uint8_t n = 0; n < uDataLength; n++)
	{
		m_uuBuffer[n + 4] = uuData[n];
	}
//	m_uBufferLength = uDataLength;
	m_uuBuffer[0] = uPort;
	m_uuBuffer[1] = uCmd;
	m_uuBuffer[2] = uDataLength;
	int8_t uRet = twi_writeTo(uAddress, m_uuBuffer, uDataLength + 4, 1);  // return ??
	m_uBufferLength = 0;
	m_zRead = 0;
}

void KuiMaster::Send(uint8_t uAddress, uint8_t uPort, uint8_t uCmd, uint8_t* uuData)
{
	uint8_t n = strlen((char*)uuData);
	Send(uAddress, uPort, uCmd, uuData, n);
}

void KuiMaster::Send(uint8_t uAddress, uint8_t uPort, uint8_t uCmd, const char* sData)
{
	uint8_t n = strlen(sData);
	Send(uAddress, uPort, uCmd, (const uint8_t*) sData, n);
}

void KuiMaster::Send(uint8_t uAddress, uint8_t uPort, uint8_t uCmd, uint8_t uData)
{
	m_uuBuffer[0] = uPort;
	m_uuBuffer[1] = uCmd;
	m_uuBuffer[2] = 1;
	m_uuBuffer[3] = 0;
	m_uuBuffer[4] = uData;
	Send(uAddress, uPort, uCmd, m_uuBuffer, 1);
}

void KuiMaster::Send(uint8_t uAddress, uint8_t uPort, uint8_t uCmd)
{
	if(m_zRead) m_uBufferLength = 0;
	
	m_uuBuffer[0] = uPort;
	m_uuBuffer[1] = uCmd;
	m_uuBuffer[2] = m_uBufferLength;
	Send(uAddress, uPort, uCmd, m_uuBuffer, m_uBufferLength);

	int8_t uRet = twi_writeTo(uAddress, m_uuBuffer, m_uBufferLength + 4, 1);  // return ??
	m_uBufferLength = 0;
	m_zRead = 0;
}

int KuiMaster::Call(uint8_t uAddress, uint8_t uPort, uint8_t uCmd)
{
	Send(uAddress, uPort, 255, uCmd);
	uint8_t m_uLength = twi_readFrom(uAddress, m_uuBuffer + 4, KUI_BUS_LENGTH);
}



