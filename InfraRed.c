
/**
  ******************************************************************************
  * @file    InfraRed.c
  * @author  CZP
  * @version V1.0.0
  * @date    29-June-2018
  * @brief   InfraRed protocol
  ******************************************************************************
  * @attention
	* 
  ******************************************************************************
  */
	
/** @addtogroup Template_Project
  * @{
  */ 
	
/*************************************
              include
*************************************/
#include "InfraRed.h"

/*************************************
              define
*************************************/

/**************************************
              typedef
**************************************/
typedef struct _IR_TypeList_t
{
	IRType_e IRType;
	int (*pInfraRed_RX_Init)(struct _IR_TypeDef *);
}IR_FuncList_t;

/*************************************
         function prototypes
*************************************/
extern int InfraRed_RX_NEC_Init(IR_TypeDef *pIR_Obj);
extern int InfraRed_RX_SONY_Init(IR_TypeDef *pIR_Obj);
extern int InfraRed_RX_SAMSUNG_Init(IR_TypeDef *pIR_Obj);
extern int InfraRed_RX_PANASONIC_Init(IR_TypeDef *pIR_Obj);
extern int InfraRed_RX_RC5_Init(IR_TypeDef *pIR_Obj);
extern int InfraRed_RX_RCA_Init(IR_TypeDef *pIR_Obj);

/*************************************
              variable
*************************************/
IR_TypeDef IR_Obj = {0};

/**
 *@brief:	paraments of IR_FuncList_t
 *@{
 */
const IR_FuncList_t IR_FuncList[] = { 	//don't change sequence, add after last
//	{IRType_NONE, 			NULL},
	{IRType_NEC, 				InfraRed_RX_NEC_Init},
	{IRType_RC5, 				InfraRed_RX_RC5_Init},
//	{IRType_RC6, 				NULL},
	{IRType_RCA, 				InfraRed_RX_RCA_Init},
//	{IRType_JVC, 				NULL},
//	{IRType_TRC, 				NULL},
	{IRType_SONY, 			InfraRed_RX_SONY_Init},
//	{IRType_SHARP, 			NULL},
//	{IRType_MIT, 				NULL},
//	{IRType_KONK, 			NULL},
//	{IRType_MI, 				NULL},
//	{IRType_NEC_WB, 		NULL},
//	{IRType_TOP, 				NULL},
	{IRType_SAMSUNG, 		InfraRed_RX_SAMSUNG_Init},
	{IRType_PANASONIC, 	InfraRed_RX_PANASONIC_Init},
	
};
/*
 *@}
 */ /* end of paraments of IR_FuncList_t */

/*************************************
              function
*************************************/

/**
  * @brief  InfraRed_RX_Init
  * @param  
  * @retval 
  */
int InfraRed_RX_Init(void)
{
	uint8_t IR_Typex;
	IR_Obj.IRType = IRType_NEC;
	
	for (IR_Typex=0; IR_Typex<sizeof(IR_FuncList)/sizeof(IR_FuncList[0]); IR_Typex++)
	{
		if(IR_FuncList[IR_Typex].IRType == IR_Obj.IRType)
		{
			IR_FuncList[IR_Typex].pInfraRed_RX_Init(&IR_Obj);
		}
	}
	
	return 0;
}

/**
  * @brief  InfraRed_RX_Calculate
  * @param  
  * @retval 
  */
int InfraRed_RX_Calculate(void)
{
	IR_Obj.pInfraRed_RX_Calculate(&IR_Obj);
	return 0;
}

/**
  * @brief  Input Capture callback in non blocking mode 
  * @param  htim: pointer to a TIM_HandleTypeDef structure that contains
  *                the configuration information for TIM module.
  * @retval None
  */
void CaptureCallback(void)
{
	IR_Obj.rx_buf[IR_Obj.len].timer = (CCAP1H << 8) | CCAP1L;//__HAL_TIM_GET_COMPARE(htim, TIM_CHANNEL_3);			
	IR_Obj.rx_buf[IR_Obj.len].pin_state = (IR_PIN_State)IR_RX_GET_PIN_STATE();
	
	if( (IR_Obj.state == CAPTURE_STAT_IDLE)
			&& (IR_Obj.rx_buf[0].timer > IR_Obj.pHead[0].timer*0.8) 
			&& (IR_Obj.rx_buf[0].timer < IR_Obj.pHead[0].timer*1.2)
			&& (IR_Obj.rx_buf[0].pin_state == IR_Obj.pHead[0].pin_state)
	)
	{
		if (IR_Obj.len == 0)
		{
			IR_Obj.len++;
			IR_Obj.rx_buf[1].timer = 0;
		}	
		else if((IR_Obj.state == CAPTURE_STAT_IDLE)
			&& (IR_Obj.rx_buf[1].timer > IR_Obj.pHead[1].timer*0.8) 
			&& (IR_Obj.rx_buf[1].timer < IR_Obj.pHead[1].timer*1.2)
			&& (IR_Obj.rx_buf[1].pin_state == IR_Obj.pHead[1].pin_state)
		)
		{
			IR_Obj.state |= CAPTURE_STAT_CAPTURE_HEAD_FLAG;
		}	
		else
		{
			IR_Obj.len = 0;
		}
		
	}
	
	if( (IR_Obj.state & CAPTURE_STAT_CAPTURE_HEAD_FLAG) 
	)
	{
		
		IR_Obj.len++;
		if( (IR_Obj.len > IR_Obj.protocol_size)
		)
		{
			IR_Obj.state &= ~CAPTURE_STAT_CAPTURE_HEAD_FLAG;
			IR_Obj.state |= CAPTURE_STAT_CAPTURE_DONE;
		}
	}
	
	if(IR_Obj.len >= 100)
	{
		IR_Obj.len = 0;
		IR_Obj.state = CAPTURE_STAT_IDLE;
	}
	CH = CL = 0;
}/**/

/**
  * @}
  */

/************************ (C) COPYRIGHT chenzhipeng3472 *****END OF FILE****/
