

#ifndef		__INFRA_RED_H__   
#define		__INFRA_RED_H__ 

#include "common.h"

sbit IR_RX_PIN = P1^4;

typedef enum _IRType_e
{
	IRType_NONE = 0,
	IRType_NEC,
	IRType_RC5,// PHILIPS
	IRType_RC6,
  IRType_RCA,// THOMSON
  IRType_JVC,
  IRType_TRC,
  IRType_SONY,
  IRType_SHARP,
	IRType_MIT,
	IRType_KONK,
	IRType_MI,
	IRType_NEC_WB,
	IRType_TOP,
	IRType_SAMSUNG,
	IRType_PANASONIC,

	IRType_MAX,
}IRType_e;

typedef enum _IR_PIN_State
{
	IR_PIN_LOW = 0,
	IR_PIN_HIGH
}IR_PIN_State;

typedef struct _IR_DataTypeDef
{
	u16 address;
	u8 command;
	u8 command_check;
}IR_DataTypeDef;

typedef struct _IR_BufTypeDef
{
	u16 timer;
	u8 pin_state;
}IR_BufTypeDef;

#define	CAPTURE_STAT_IDLE 							(0)
#define	CAPTURE_STAT_CAPTURE_HEAD_FLAG	(1<<6)
#define CAPTURE_STAT_CAPTURE_DONE				(1<<7)
#define CAPTURE_STAT_CAPTURE_TIMES			(0x0f)

#define	IR_RX_PORT			P1
//#define IR_RX_PIN				4
#define	IR_RX_GET_PIN()	IR_RX_PIN
#define	IR_RX_GET_PIN_STATE()	IR_RX_PIN
//#define	IR_RX_OFF()			SETB(LED0_PORT,LED0_PIN)
//#define	IR_RX_GET_PIN()	CLRB(LED0_PORT,LED0_PIN)
//#define	IR_RX_OFF()			SETB(LED0_PORT,LED0_PIN)

typedef struct _IR_TypeDef
{
	 u8 state;   // bit7: 捕获完成标志，bit6：是否捕获到高电平，bit5：捕获到高电平之后的下降沿标志，bit4~0：捕获高电平定时器溢出的次数
	 IR_BufTypeDef rx_buf[100];
	 uint8_t len;
	IR_DataTypeDef value;
	uint16_t carry_freq;
	const IR_BufTypeDef *pHead;
	uint8_t protocol_size;
	uint8_t RepeatInterval;  //ms
	IRType_e IRType;
	int (*pInfraRed_RX_Calculate)(struct _IR_TypeDef *);
}IR_TypeDef;

extern IR_TypeDef IR_Obj;

extern int InfraRed_RX_Init(void);
extern int InfraRed_RX_Calculate(void);




#endif /* __INFRA_RED_H__ */