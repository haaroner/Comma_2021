//#include "usart.h"

//extern "C"
//{
//	
////	void USART1_IRQHandler(void)
////	{
////		volatile uint8_t data = USART1->SR;
////		if(data & USART_SR_RXNE)
////		{
////			usart1::rx[usart1::_rxCnt] = USART1->DR;
////			usart1::_rxCnt++;
////			if(usart1::_rxCnt == 8)
////			{
////				usart1::_rxCnt = 0;
////			}
////		}
////		if(data &USART_SR_TC)
////		{
////			USART_ClearITPendingBit(USART1, USART_IT_TC);
////			if(usart1::_txCnt != 0)
////			{
////				(USART1->DR) = usart1::tx[usart1::_sendCnt];
////				usart1::_sendCnt++;
////				if(usart1::_sendCnt == 8)
////				{
////					usart1::_sendCnt = 0;
////				}
////			}
////			else
////			{
////				usart1::flag = 1;
////			}
////		}
////		if(USART1->SR & USART_SR_ORE)
////		{
////			uint8_t a = USART1 -> DR;
////			(void)a;
////		}
////	}
////	
////	void USART2_IRQHandler(void)
////	{
////		volatile uint8_t data = USART2->SR;
////		if(data & USART_SR_RXNE)
////		{
////			usart2::rx[usart2::_rxCnt] = USART2->DR;
////			usart2::_rxCnt++;
////			if(usart2::_rxCnt == 8)
////			{
////				usart2::_rxCnt = 0;
////			}
////		}
////		if(data &USART_SR_TC)
////		{
////			USART_ClearITPendingBit(USART2, USART_IT_TC);
////			if(usart2::_txCnt != 0)
////			{
////				(USART2->DR) = usart2::tx[usart2::_sendCnt];
////				usart2::_sendCnt++;
////				if(usart2::_sendCnt == 8)
////				{
////					usart2::_sendCnt = 0;
////				}
////			}
////			else
////			{
////				usart2::flag = 1;
////			}
////		}
////		if(USART2->SR & USART_SR_ORE)
////		{
////			uint8_t a = USART2 -> DR;
////			(void)a;
////		}
////	}
//	
//	void USART3_IRQHandler(void)
//	{
//		volatile uint8_t data = USART3->SR;
//		if(data & USART_SR_RXNE)
//		{
//			usart3::rx[usart3::_rxCnt] = USART3->DR;
//			usart3::_rxCnt++;
//			if(usart3::_rxCnt == 8)
//			{
//				usart3::_rxCnt = 0;
//			}
//		}
//		if(data &USART_SR_TC)
//		{
//			USART_ClearITPendingBit(USART3, USART_IT_TC);
//			if(usart3::_txCnt != 0)
//			{
//				(USART3->DR) = usart3::tx[usart3::_sendCnt];
//				usart3::_sendCnt++;
//				if(usart3::_sendCnt == 8)
//				{
//					usart3::_sendCnt = 0;
//				}
//			}
//			else
//			{
//				usart3::flag = 1;
//			}
//		}
//		if(USART3->SR & USART_SR_ORE)
//		{
//			uint8_t a = USART3 -> DR;
//			(void)a;
//		}
//	}
//	
////	void UART4_IRQHandler(void)
////	{
////		volatile uint8_t data = UART4->SR;
////		if(data & USART_SR_RXNE)
////		{
////			usart4::rx[usart4::_rxCnt] = UART4->DR;
////			usart4::_rxCnt++;
////			if(usart4::_rxCnt == 8)
////			{
////				usart4::_rxCnt = 0;
////			}
////		}
////		if(data &USART_SR_TC)
////		{
////			USART_ClearITPendingBit(UART4, USART_IT_TC);
////			if(usart1::_txCnt != 0)
////			{
////				(UART4->DR) = usart4::tx[usart4::_sendCnt];
////				usart4::_sendCnt++;
////				if(usart4::_sendCnt == 8)
////				{
////					usart4::_sendCnt = 0;
////				}
////			}
////			else
////			{
////				usart4::flag = 1;
////			}
////		}
////		if(UART4->SR & USART_SR_ORE)
////		{
////			uint8_t a = UART4 -> DR;
////			(void)a;
////		}
////	}
////	
////	void UART5_IRQHandler(void)
////	{
////		volatile uint8_t data = UART5->SR;
////		if(data & USART_SR_RXNE)
////		{
////			usart5::rx[usart5::_rxCnt] = UART5->DR;
////			usart5::_rxCnt++;
////			if(usart5::_rxCnt == 8)
////			{
////				usart5::_rxCnt = 0;
////			}
////		}
////		if(data &USART_SR_TC)
////		{
////			USART_ClearITPendingBit(UART5, USART_IT_TC);
////			if(usart5::_txCnt != 0)
////			{
////				(UART5->DR) = usart5::tx[usart5::_sendCnt];
////				usart5::_sendCnt++;
////				if(usart5::_sendCnt == 8)
////				{
////					usart5::_sendCnt = 0;
////				}
////			}
////			else
////			{
////				usart5::flag = 1;
////			}
////		}
////		if(UART5->SR & USART_SR_ORE)
////		{
////			uint8_t a = UART5 -> DR;
////			(void)a;
////		}
////	}
//	
//	void USART6_IRQHandler(void)
//	{
//		volatile uint8_t data = USART6->SR;
//		if(data & USART_SR_RXNE)
//		{
//			usart6::rx[usart6::_rxCnt] = USART6->DR;
//			usart6::_rxCnt++;
//			if(usart6::_rxCnt == 8)
//			{
//				usart6::_rxCnt = 0;
//			}
//		}
//		if(data &USART_SR_TC)
//		{
//			USART_ClearITPendingBit(USART6, USART_IT_TC);
//			if(usart6::_txCnt != 0)
//			{
//				(USART6->DR) = usart6::tx[usart6::_sendCnt];
//				usart6::_sendCnt++;
//				if(usart6::_sendCnt == 8)
//				{
//					usart6::_sendCnt = 0;
//				}
//			}
//			else
//			{
//				usart6::flag = 1;
//			}
//		}
//		if(USART6->SR & USART_SR_ORE)
//		{
//			uint8_t a = USART6 -> DR;
//			(void)a;
//		}
//	}
//}

////namespace usart1
////{
////  volatile uint8_t tx[8];
////  volatile uint8_t rx[8];
////  volatile uint16_t _rxCnt;
////  volatile uint16_t _txCnt;
////  volatile bool flag;
////  volatile uint16_t _readCnt;
////  volatile uint16_t _sendCnt;
////	
////	void usart1Init(uint32_t _baud_rate, int8_t _word_length, int8_t _stop_bits, bool _parity)
////		{
////		flag = 1;
////		_txCnt = 0;
////		_rxCnt = 0;
////		_readCnt = 0;
////		_sendCnt = 0;

////		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
////		USART_InitTypeDef u;
////		u.USART_BaudRate = 115200;
////		u.USART_WordLength = USART_WordLength_8b;
////		u.USART_StopBits = USART_StopBits_1;
////		u.USART_Parity = USART_Parity_No;
////		u.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
////		u.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
////		USART_Init(USART1, &u);
////		USART_ITConfig(USART1, USART_IT_TC, ENABLE);
////		USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
////		USART_Cmd(USART1, ENABLE);
////		NVIC_SetPriority(USART1_IRQn, 0);
////		NVIC_EnableIRQ(USART1_IRQn);
////	}  
////		 
////	uint16_t read()
////	{  
////		uint16_t dt;
////		ENTER_CRITICAL_SECTION();
////		dt = rx[_readCnt];
////		_readCnt++;
////		if(_readCnt == 8)
////		{
////		 _readCnt = 0;
////		}
////		EXIT_CRITICAL_SECTION();
////		return dt;
////	}  
////		 
////	uint16_t available()
////	{  
////		uint16_t size;
////		ENTER_CRITICAL_SECTION();
////		size = _rxCnt - _readCnt;
////		EXIT_CRITICAL_SECTION();
////		return size;
////	}  
////		 
////	void write(uint8_t _byte)
////	{  
////		ENTER_CRITICAL_SECTION();
////		if(!flag)
////		{
////		 tx[_txCnt] = _byte;
////		 _txCnt++;
////		 if(_txCnt == 8)
////		 {
////		 _txCnt = 0;
////		 }
////		}
////		else
////		{
////		 flag = 0;
////		 (USART1->DR) = _byte;
////		}
////		EXIT_CRITICAL_SECTION();
////	}
////}

////namespace usart2
////{
////  volatile uint8_t tx[8];
////  volatile uint8_t rx[8];
////  volatile uint16_t _rxCnt;
////  volatile uint16_t _txCnt;
////  volatile bool flag;
////  volatile uint16_t _readCnt;
////  volatile uint16_t _sendCnt;
////	
////	void usart2Init(uint32_t _baud_rate, int8_t _word_length, int8_t _stop_bits, bool _parity)
////		{
////		flag = 1;
////		_txCnt = 0;
////		_rxCnt = 0;
////		_readCnt = 0;
////		_sendCnt = 0;

////		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
////		USART_InitTypeDef u;
////		u.USART_BaudRate = _baud_rate;
////			
////		if(_word_length == 9) u.USART_WordLength = USART_WordLength_9b;
////		else u.USART_WordLength = USART_WordLength_8b;
////			
////		if(_stop_bits == 2) u.USART_StopBits = USART_StopBits_2;
////		else u.USART_StopBits = USART_StopBits_1;
////			
////		if(_parity == true) u.USART_Parity = USART_Parity_Even;
////		else u.USART_Parity = USART_Parity_No;
////			
////		u.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
////		u.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
////		USART_Init(USART2, &u);
////		USART_ITConfig(USART2, USART_IT_TC, ENABLE);
////		USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
////		USART_Cmd(USART2, ENABLE);
////		NVIC_SetPriority(USART2_IRQn, 0);
////		NVIC_EnableIRQ(USART2_IRQn);
////	}  
////		 
////	uint16_t read()
////	{  
////		uint16_t dt;
////		ENTER_CRITICAL_SECTION();
////		dt = rx[_readCnt];
////		_readCnt++;
////		if(_readCnt == 8)
////		{
////		 _readCnt = 0;
////		}
////		EXIT_CRITICAL_SECTION();
////		return dt;
////	}  
////		 
////	uint16_t available()
////	{  
////		uint16_t size;
////		ENTER_CRITICAL_SECTION();
////		size = _rxCnt - _readCnt;
////		EXIT_CRITICAL_SECTION();
////		return size;
////	}  
////		 
////	void write(uint8_t _byte)
////	{  
////		ENTER_CRITICAL_SECTION();
////		if(!flag)
////		{
////		 tx[_txCnt] = _byte;
////		 _txCnt++;
////		 if(_txCnt == 8)
////		 {
////		 _txCnt = 0;
////		 }
////		}
////		else
////		{
////		 flag = 0;
////		 (USART2->DR) = _byte;
////		}
////		EXIT_CRITICAL_SECTION();
////	}
////}

//namespace usart3
//{
//  volatile uint8_t tx[8];
//  volatile uint8_t rx[8];
//  volatile uint16_t _rxCnt;
//  volatile uint16_t _txCnt;
//  volatile bool flag;
//  volatile uint16_t _readCnt;
//  volatile uint16_t _sendCnt;
//	
//	void usart3Init()
//		{
//		flag = 1;
//		_txCnt = 0;
//		_rxCnt = 0;
//		_readCnt = 0;
//		_sendCnt = 0;

//		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
//		USART_InitTypeDef u;
//		u.USART_BaudRate = 115200;
//		u.USART_WordLength = USART_WordLength_8b;
//		u.USART_StopBits = USART_StopBits_1;
//		u.USART_Parity = USART_Parity_No;
//		u.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
//		u.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
//		USART_Init(USART3, &u);
//		USART_ITConfig(USART3, USART_IT_TC, ENABLE);
//		USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
//		USART_Cmd(USART3, ENABLE);
//		NVIC_SetPriority(USART3_IRQn, 0);
//		NVIC_EnableIRQ(USART3_IRQn);
//	}  
//		 
//	uint16_t read()
//	{  
//		uint16_t dt;
//		ENTER_CRITICAL_SECTION();
//		dt = rx[_readCnt];
//		_readCnt++;
//		if(_readCnt == 8)
//		{
//		 _readCnt = 0;
//		}
//		EXIT_CRITICAL_SECTION();
//		return dt;
//	}  
//		 
//	uint16_t available()
//	{  
//		uint16_t size;
//		ENTER_CRITICAL_SECTION();
//		size = _rxCnt - _readCnt;
//		EXIT_CRITICAL_SECTION();
//		return size;
//	}  
//		 
//	void write(uint8_t _byte)
//	{  
//		ENTER_CRITICAL_SECTION();
//		if(!flag)
//		{
//		 tx[_txCnt] = _byte;
//		 _txCnt++;
//		 if(_txCnt == 8)
//		 {
//		 _txCnt = 0;
//		 }
//		}
//		else
//		{
//		 flag = 0;
//		 (USART3->DR) = _byte;
//		}
//		EXIT_CRITICAL_SECTION();
//	}
//}

////namespace usart4
////{
////  volatile uint8_t tx[8];
////  volatile uint8_t rx[8];
////  volatile uint16_t _rxCnt;
////  volatile uint16_t _txCnt;
////  volatile bool flag;
////  volatile uint16_t _readCnt;
////  volatile uint16_t _sendCnt;
////	
////	void usart4Init(uint32_t _baud_rate, int8_t _word_length, int8_t _stop_bits, bool _parity)
////		{
////		flag = 1;
////		_txCnt = 0;
////		_rxCnt = 0;
////		_readCnt = 0;
////		_sendCnt = 0;

////		RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);
////		USART_InitTypeDef u;
////		u.USART_BaudRate = _baud_rate;
////			
////		if(_word_length == 9) u.USART_WordLength = USART_WordLength_9b;
////		else u.USART_WordLength = USART_WordLength_8b;
////			
////		if(_stop_bits == 2) u.USART_StopBits = USART_StopBits_2;
////		else u.USART_StopBits = USART_StopBits_1;
////			
////		if(_parity == true) u.USART_Parity = USART_Parity_Even;
////		else u.USART_Parity = USART_Parity_No;
////			
////		u.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
////		u.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
////		USART_Init(UART4, &u);
////		USART_ITConfig(UART4, USART_IT_TC, ENABLE);
////		USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);
////		USART_Cmd(UART4, ENABLE);
////		NVIC_SetPriority(UART4_IRQn, 0);
////		NVIC_EnableIRQ(UART4_IRQn);
////	}  
////		 
////	uint16_t read()
////	{  
////		uint16_t dt;
////		ENTER_CRITICAL_SECTION();
////		dt = rx[_readCnt];
////		_readCnt++;
////		if(_readCnt == 8)
////		{
////		 _readCnt = 0;
////		}
////		EXIT_CRITICAL_SECTION();
////		return dt;
////	}  
////		 
////	uint16_t available()
////	{  
////		uint16_t size;
////		ENTER_CRITICAL_SECTION();
////		size = _rxCnt - _readCnt;
////		EXIT_CRITICAL_SECTION();
////		return size;
////	}  
////		 
////	void write(uint8_t _byte)
////	{  
////		ENTER_CRITICAL_SECTION();
////		if(!flag)
////		{
////		 tx[_txCnt] = _byte;
////		 _txCnt++;
////		 if(_txCnt == 8)
////		 {
////		 _txCnt = 0;
////		 }
////		}
////		else
////		{
////		 flag = 0;
////		 (UART4->DR) = _byte;
////		}
////		EXIT_CRITICAL_SECTION();
////	}
////}

////namespace usart5
////{
////  volatile uint8_t tx[8];
////  volatile uint8_t rx[8];
////  volatile uint16_t _rxCnt;
////  volatile uint16_t _txCnt;
////  volatile bool flag;
////  volatile uint16_t _readCnt;
////  volatile uint16_t _sendCnt;
////	
////	void usart5Init(uint32_t _baud_rate, int8_t _word_length, int8_t _stop_bits, bool _parity)
////		{
////		flag = 1;
////		_txCnt = 0;
////		_rxCnt = 0;
////		_readCnt = 0;
////		_sendCnt = 0;

////		RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);
////		USART_InitTypeDef u;
////		u.USART_BaudRate = 115200;
////		u.USART_WordLength = USART_WordLength_8b;
////		u.USART_StopBits = USART_StopBits_1;
////		u.USART_Parity = USART_Parity_No;
////		u.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
////		u.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
////		USART_Init(UART5, &u);
////		USART_ITConfig(UART5, USART_IT_TC, ENABLE);
////		USART_ITConfig(UART5, USART_IT_RXNE, ENABLE);
////		USART_Cmd(UART5, ENABLE);
////		NVIC_SetPriority(UART5_IRQn, 0);
////		NVIC_EnableIRQ(UART5_IRQn);
////	}  
////		 
////	uint16_t read()
////	{  
////		uint16_t dt;
////		ENTER_CRITICAL_SECTION();
////		dt = rx[_readCnt];
////		_readCnt++;
////		if(_readCnt == 8)
////		{
////		 _readCnt = 0;
////		}
////		EXIT_CRITICAL_SECTION();
////		return dt;
////	}  
////		 
////	uint16_t available()
////	{  
////		uint16_t size;
////		ENTER_CRITICAL_SECTION();
////		size = _rxCnt - _readCnt;
////		EXIT_CRITICAL_SECTION();
////		return size;
////	}  
////		 
////	void write(uint8_t _byte)
////	{  
////		ENTER_CRITICAL_SECTION();
////		if(!flag)
////		{
////		 tx[_txCnt] = _byte;
////		 _txCnt++;
////		 if(_txCnt == 8)
////		 {
////		 _txCnt = 0;
////		 }
////		}
////		else
////		{
////		 flag = 0;
////		 (UART5->DR) = _byte;
////		}
////		EXIT_CRITICAL_SECTION();
////	}
////}

//namespace usart6
//{
//  volatile uint8_t tx[8];
//  volatile uint8_t rx[8];
//  volatile uint16_t _rxCnt;
//  volatile uint16_t _txCnt;
//  volatile bool flag;
//  volatile uint16_t _readCnt;
//  volatile uint16_t _sendCnt;
//	
//	void usart6Init()
//		{
//		flag = 1;
//		_txCnt = 0;
//		_rxCnt = 0;
//		_readCnt = 0;
//		_sendCnt = 0;

//		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6, ENABLE);
//		USART_InitTypeDef u;
//		u.USART_BaudRate = 115200;
//		u.USART_WordLength = USART_WordLength_8b;
//		u.USART_StopBits = USART_StopBits_1;
//		u.USART_Parity = USART_Parity_No;
//		u.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
//		u.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
//		USART_Init(USART6, &u);
//		USART_ITConfig(USART6, USART_IT_TC, ENABLE);
//		USART_ITConfig(USART6, USART_IT_RXNE, ENABLE);
//		USART_Cmd(USART6, ENABLE);
//		NVIC_SetPriority(USART6_IRQn, 0);
//		NVIC_EnableIRQ(USART6_IRQn);
//	}  
//		 
//	uint16_t read()
//	{  
//		uint16_t dt;
//		ENTER_CRITICAL_SECTION();
//		dt = rx[_readCnt];
//		_readCnt++;
//		if(_readCnt == 8)
//		{
//		 _readCnt = 0;
//		}
//		EXIT_CRITICAL_SECTION();
//		return dt;
//	}  
//		 
//	uint16_t available()
//	{  
//		uint16_t size;
//		ENTER_CRITICAL_SECTION();
//		size = _rxCnt - _readCnt;
//		EXIT_CRITICAL_SECTION();
//		return size;
//	}  
//		 
//	void write(uint8_t _byte)
//	{  
//		ENTER_CRITICAL_SECTION();
//		if(!flag)
//		{
//		 tx[_txCnt] = _byte;
//		 _txCnt++;
//		 if(_txCnt == 8)
//		 {
//		 _txCnt = 0;
//		 }
//		}
//		else
//		{
//		 flag = 0;
//		 (USART6->DR) = _byte;
//		}
//		EXIT_CRITICAL_SECTION();
//	}
//}
