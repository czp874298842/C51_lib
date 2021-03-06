
#include "InfraRed.h"

//
static int InfraRed_RX_NEC_Calculate(IR_TypeDef *pIR_Obj);
	
//
const IR_BufTypeDef IR_NEC_Head[] = {
	{9000, IR_PIN_HIGH},
	{4500, IR_PIN_LOW},
};

const IR_BufTypeDef IR_NEC_One[] = {
	{560,	 IR_PIN_HIGH},
	{1685, IR_PIN_LOW},
};

const IR_BufTypeDef IR_NEC_Zero[] = {
	{560, IR_PIN_HIGH},
	{560, IR_PIN_LOW},
};

const IR_BufTypeDef IR_NEC_Repeat[] = {
	{9000, IR_PIN_HIGH},
	{2250, IR_PIN_LOW},
	{560, IR_PIN_HIGH},
};


//
int InfraRed_RX_NEC_Init(IR_TypeDef *pIR_Obj)
{
	pIR_Obj->pHead = IR_NEC_Head;
	pIR_Obj->protocol_size = 66;
	pIR_Obj->state = CAPTURE_STAT_IDLE;
	pIR_Obj->pInfraRed_RX_Calculate = InfraRed_RX_NEC_Calculate;
	return 0;
}

//
int InfraRed_RX_NEC_Calculate(IR_TypeDef *pIR_Obj)
{
	uint8_t idx = 0, byte = 0, _bit = 0x01;
	uint16_t min0, max0, min1, max1;
	uint8_t val[4] = {0};
	
	min0 = IR_NEC_Zero[1].timer - IR_NEC_Zero[1].timer/5;
	max0 = IR_NEC_Zero[1].timer + IR_NEC_Zero[1].timer/5;
	min1 = IR_NEC_One[1].timer - IR_NEC_One[1].timer/5;
	max1 = IR_NEC_One[1].timer + IR_NEC_One[1].timer/5;
	
	if(pIR_Obj->len != 0)
	{
		for(idx=sizeof(IR_NEC_Head)/sizeof(IR_NEC_Head[0])+1; idx<pIR_Obj->len; idx+=2)
		{			
			if((pIR_Obj->rx_buf[idx].timer >= min0) && (pIR_Obj->rx_buf[idx].timer <= max0))
			{
				
			}
			else if((pIR_Obj->rx_buf[idx].timer >= min1) && (pIR_Obj->rx_buf[idx].timer <= max1))
			{
				val[byte] |= _bit; 
			}
			else
			{
				break;
			}
			_bit <<= 1;
			
			if(_bit == 0)
			{
				_bit = 0x01;
				byte++;
			}
		}
		
		if(idx >= pIR_Obj->protocol_size)
		{
			if( 0xFF == (val[2]|val[3]))
			{
				pIR_Obj->value.address = val[0]<<8 | val[1];
				pIR_Obj->value.command = val[2];
				pIR_Obj->value.command_check = val[3];
			}		
		}
		IR_Obj.state = CAPTURE_STAT_IDLE;
		pIR_Obj->len = 0;
	}	
	
	return 0;
}

