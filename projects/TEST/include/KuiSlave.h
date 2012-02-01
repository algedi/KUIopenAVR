/*
  KuiSlave.h - TWI/I2C library for iiKUIno project
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

#ifndef KUISLAVE_H
#define KUISLAVE_H

#include <inttypes.h>

class KuiSlave
{
  private:
	uint8_t m_nError;
	uint8_t m_ppOnReceive[5]; // 5 PORT MAX
  static void (*m_pEventReceive)(uint8_t, uint8_t, uint8_t*, uint8_t);	
  static void (*m_pEventRequest)(void);
	static void OnReceive(uint8_t*, int);
	static void OnRequest(void);
  public:
	KuiSlave(uint8_t);
	void SetEventReceive( void (*)(uint8_t, uint8_t, uint8_t*, uint8_t) );
	void SetEventRequest( void (*)(void) );
 };

#endif // KUISLAVE_H

