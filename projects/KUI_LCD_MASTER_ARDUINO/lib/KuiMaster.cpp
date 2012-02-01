/*
  KuiMaster.c - TWI/I2C library for iiKUIno project
  Copyright (c) 2011 Andrea Calvia (algedi_kui@ilnaufrago.it).  
  All right reserved.

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

extern "C" 
{
  #include <stdlib.h>
  #include <string.h>
  #include <inttypes.h>
  #include "twi.h"
}

#include "KuiMaster.h"

#define KUI_BUS_LENGTH 32

/////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////// Constructors //
/////////////////////////////////////////////////////////////////////

KuiMaster::KuiMaster()
{
  twi_init();
}

///////////////////////////////////////////////////////////////////// 
/////////////////////////////////////////////////// Public Methods //
/////////////////////////////////////////////////////////////////////

// ********************
// * SetEventReceive  * 
// *****************************************************
// * (uint8_t)  pFunction => pointer callback function *
// *****************************************************

void KuiMaster::SetEventReceive( void (*pFunction)(uint8_t, uint8_t, uint8_t, uint8_t, uint8_t*) )
{
	m_pEventReceive = pFunction;
}

// ****************
// * Call         *
// ***********************************************
// * (unit8_t) uAddress = I2C address device     *
// * (unit8_t) uPort    = port in device         *
// * (unit8_t) uCmd     = command                *
// ***********************************************

int KuiMaster::Call(uint8_t uAddress, uint8_t uPort, uint8_t uCmd)
{
	Send(uAddress, uPort, 255, uCmd);
	Send(127, 1, 1);  							// ???? 

	uint8_t uuBuffer[KUI_BUS_LENGTH + 4];
	uint8_t uuData[KUI_BUS_LENGTH];

	int nLen = twi_readFrom(uAddress, m_uuBuffer, KUI_BUS_LENGTH + 4);

	for(uint8_t n = 0; n < KUI_BUS_LENGTH; n++)
		uuData[n] = uuBuffer[n + 4];

	uint8_t uLen     = uuBuffer[4];
	m_pEventReceive(uAddress, uPort, uCmd, uLen, uuData);
}

    								///////////////// SEND //
									// SECTION //////////////

// ****************
// * Send         *
// ********************************************************
// * (uint8_t)        uAddress = I2C address device       *
// * (uint8_t)        uPort    = number port in device    *
// * (uint8_t)        uCmd     = command                  *
// * (const uint8_t*) uuData   = array - data to send     *
// * (uint8_t)        uLen     = length of data           *
// ********************************************************

void KuiMaster::Send(uint8_t uAddress, uint8_t uPort, uint8_t uCmd, const uint8_t* uuData, uint8_t uLen)
{
	uint8_t uuBuffer[uLen + 4];
	for(uint8_t n = 0; n < uLen; n++)
		uuBuffer[n + 4] = uuData[n];
	uuBuffer[0] = uPort;
	uuBuffer[1] = uCmd;
	uuBuffer[2] = uLen;
	int8_t u = twi_writeTo(uAddress, uuBuffer, uLen + 4, 1);
}

// ****************
// * Send         *
// **************************************************
// * (uint8_t)  uAddress = I2C address device       *
// * (uint8_t)  uPort    = number port in device    *
// * (uint8_t)  uCmd     = command                  *
// * (uint8_t*) uuData   = array - data to send     *
// * (uint8_t)  uLen     = length of data           *
// **************************************************

void KuiMaster::Send(uint8_t uAddress, uint8_t uPort, uint8_t uCmd, uint8_t* uuData, uint8_t uLen)
{
	Send(uAddress, uPort, uCmd, (const uint8_t*) uuData, uLen);
}

// ****************
// * Send         *
// ******************************************************
// * (unit8_t)  uAddress = I2C address device           *
// * (unit8_t)  uPort    = number port in device        *
// * (unit8_t)  uCmd     = command                      *
// * (unit8_t*) uuData   = array to send with /0 to end *
// ******************************************************

void KuiMaster::Send(uint8_t uAddress, uint8_t uPort, uint8_t uCmd, uint8_t* uuData)
{
	uint8_t n = strlen((char*)uuData);
	Send(uAddress, uPort, uCmd, uuData, n);
}

// ****************
// * Send         *
// ************************************************************
// * (unit8_t)  	  uAddress = I2C address device           *
// * (unit8_t)  	  uPort    = number port in device        *
// * (unit8_t) 		  uCmd     = command					  *       
// * (const unit8_t*) uuData   = array to send with /0 to end *
// ************************************************************
void KuiMaster::Send(uint8_t uAddress, uint8_t uPort, uint8_t uCmd, const char* sData)
{
	uint8_t n = strlen(sData);
	Send(uAddress, uPort, uCmd, (const uint8_t*) sData, n);
}

// ****************
// * Send         *
// ****************************************************
// * (unit8_t) uAddress = I2C address device          *
// * (unit8_t) uPort    = number port in device       *
// * (unit8_t) uCmd     = command                     *
// * (unit8_t) uData    = byte to send                *
// ****************************************************

void KuiMaster::Send(uint8_t uAddress, uint8_t uPort, uint8_t uCmd, uint8_t uData)
{
	Send(uAddress, uPort, uCmd, &uData, 1);
}

// ****************
// * Send         *
// ***********************************************
// * (unit8_t) uAddress = I2C address device     *
// * (unit8_t) uPort    = number port in device  *
// * (unit8_t) uCmd     = command                *
// ***********************************************

void KuiMaster::Send(uint8_t uAddress, uint8_t uPort, uint8_t uCmd)
{
	uint8_t uData = 0;
	Send(uAddress, uPort, uCmd, &uData, 0);
}

    								///////////////// GET //
									// SECTION //////////////

// ********************
// * Get              * 
// ***********************************************
// * (uint8_t) uAddress =  I2C address device    *
// * (uint8_t) uPort    =  number port in device *
// * (uint8_t) uCmd     =  command               *
// ***********************************************
// * Return  = (uint8_t) value                   *
// ***********************************************

uint8_t KuiMaster::Get(uint8_t uAddress, uint8_t uPort, uint8_t uCmd)
{
	Send(uAddress, uPort, 255, uCmd);
	Send(127, 1, 1);  // porcheria per aggirare un problema

	uint8_t uuData[KUI_BUS_LENGTH + 4];
	uuData[4] = 100;
	uint8_t uLen = twi_readFrom(uAddress, uuData, KUI_BUS_LENGTH + 4);
	return uuData[4];
}

// ********************
// * Get              * 
// **************************************************
// * (uint8_t)  uAddress  =  I2C address device     *
// * (uint8_t)  uPort     =  number port in device  *
// * (uint8_t)  uCmd      =  command                *
// * (uint8_t*) uuCmd     =  pointer for input data *
// **************************************************
// * Return  = (uint8_t) length data                *
// **************************************************

uint8_t KuiMaster::Get(uint8_t uAddress, uint8_t uPort, uint8_t uCmd, uint8_t* uuData)
{
	Send(uAddress, uPort, 255, uCmd);
	Send(127, 1, 1);  							// ???? 

	uint8_t uuBuffer[KUI_BUS_LENGTH + 4];
	uint8_t uRet = twi_readFrom(uAddress, uuBuffer, KUI_BUS_LENGTH + 4);

	for(int n = 0; n < KUI_BUS_LENGTH + 4; n++)
		uuData[n] = uuBuffer[n + 4];
	
	return uuBuffer[3];
}


/////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////// Private Methods //
/////////////////////////////////////////////////////////////////////////////////

void (*KuiMaster::m_pEventReceive)(uint8_t, uint8_t, uint8_t, uint8_t, uint8_t*);


