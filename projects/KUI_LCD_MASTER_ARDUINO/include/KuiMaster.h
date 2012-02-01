/*
  KuiMaster.h - TWI/I2C library for iiKUIno project
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

#ifndef KUIMASTER_H
#define KUIMASTER_H

#include <inttypes.h>

class KuiMaster
{
  private:
	uint8_t* m_uuBuffer;
	uint8_t m_uBufferLength;
	uint8_t m_zRead;			// 1 = read - 2 = write 
	static void (*m_pEventReceive)(uint8_t, uint8_t, uint8_t, uint8_t, uint8_t*);	

  public:
	KuiMaster();

//	void Set(uint8_t* uuData, uint8_t uLength);
//	void Clear(void);
//	void Append(const char);
//	void Append(const char[]);
//	void Append(uint8_t* uuData, uint8_t uLength);
//	uint8_t Get(void);
//	uint8_t GetIndex(uint8_t);
//	uint8_t GetLength(void);

	void Send(uint8_t, uint8_t, uint8_t);						// nAdress, nPort, nCmd
	void Send(uint8_t, uint8_t, uint8_t, uint8_t);				// nAdress, nPort, nCmd, cValue
//	void Send(uint8_t, uint8_t, uint8_t, int);					// nAdress, nPort, nCmd, nValue
 	void Send(uint8_t, uint8_t, uint8_t, uint8_t*);				// nAdress, nPort, nCmd, ccBuffer* (with /0 end string)
	void Send(uint8_t, uint8_t, uint8_t, const char*);			// nAdress, nPort, nCmd, ccBuffer* (with /0 end string)
	void Send(uint8_t, uint8_t, uint8_t, const uint8_t*, uint8_t);    // nAdress, nPort, nCmd, ccBuffer*, nLengthBuffer
	void Send(uint8_t, uint8_t, uint8_t, uint8_t*, uint8_t);    // nAdress, nPort, nCmd, ccBuffer*, nLengthBuffer

	int Call(uint8_t, uint8_t, uint8_t);					// nAdress, nPort, nCmd 			- return byte value
//	int Get(uint8_t, uint8_t, uint8_t);
	uint8_t Get(uint8_t, uint8_t, uint8_t);
	uint8_t Get(uint8_t, uint8_t, uint8_t, uint8_t*);
//	uint8_t Call(uint8_t, uint8_t, uint8_t, uint8_t*);			// nAdress, nPort, nCmd, ccBuffer* 	- return Lemgth
	void SetEventReceive( void (*pFunction)(uint8_t, uint8_t, uint8_t, uint8_t, uint8_t*) );

	uint8_t OnAlert( void (*)(uint8_t, uint8_t, uint8_t));		// pCallBack_function (nAdress, nPort, nCmd)
};

#endif // KUIMASTER_H

