/* 
 * File:   external_interrupt.c
 * Author: peter
 *
 * Created on July 29, 2024, 4:44 AM
 */

#include "external_interrupt.h"

static void (*INT0_InterruptHandler)(void) = NULL;
static void (*INT1_InterruptHandler)(void) = NULL;
static void (*INT2_InterruptHandler)(void) = NULL;

static void (*RB4_InterruptHandler)(void) = NULL;
static void (*RB5_InterruptHandler)(void) = NULL;
static void (*RB6_InterruptHandler)(void) = NULL;
static void (*RB7_InterruptHandler)(void) = NULL;

static STD_ReturnType Interrupt_INTx_Enable(const interrupt_INTx *_interrupt_INTx);
static STD_ReturnType Interrupt_INTx_Disable(const interrupt_INTx *_interrupt_INTx);
static STD_ReturnType Interrupt_INTx_Priority_init(const interrupt_INTx *_interrupt_INTx);
static STD_ReturnType Interrupt_INTx_Edge_init(const interrupt_INTx *_interrupt_INTx);
static STD_ReturnType Interrupt_INTx_Pin_init(const interrupt_INTx *_interrupt_INTx);
static STD_ReturnType Interrupt_INTx_Clear_Flag(const interrupt_INTx *_interrupt_INTx);

static STD_ReturnType Interrupt_RBx_Enable(const interrupt_RBx *_interrupt_RBx);
static STD_ReturnType Interrupt_RBx_Disable(const interrupt_RBx *_interrupt_RBx);
static STD_ReturnType Interrupt_RBx_Priority_init(const interrupt_RBx *_interrupt_RBx);
static STD_ReturnType Interrupt_RBx_Pin_init(const interrupt_RBx *_interrupt_RBx);
static STD_ReturnType Interrupt_RBx_Clear_Flag(const interrupt_RBx *_interrupt_RBx);

static STD_ReturnType INT0_Interrupt_Handler(void (*Interrupt_Handler)(void));
static STD_ReturnType INT1_Interrupt_Handler(void (*Interrupt_Handler)(void));
static STD_ReturnType INT2_Interrupt_Handler(void (*Interrupt_Handler)(void));

static STD_ReturnType INTx_Set_Interrupt_Handler(const interrupt_INTx *_interrupt_INTx);

void INT0_ISR(void);
void INT1_ISR(void);
void INT2_ISR(void);

void RB4_ISR(void);
void RB5_ISR(void);
void RB6_ISR(void);
void RB7_ISR(void);


/**
 * 
 * @param _interrupt_INTx
 * @return 
 */
STD_ReturnType Interrupt_INTx_init(const interrupt_INTx *_interrupt_INTx)
{
    STD_ReturnType ret = E_OK;
    
    if(NULL == _interrupt_INTx)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* -------------------- disable the external interrupt -------------------- */
        ret = Interrupt_INTx_Disable(_interrupt_INTx);
        
        /* -------------------- clear the interrupt flag -------------------- */
        ret = Interrupt_INTx_Clear_Flag(_interrupt_INTx);
        
        /* -------------------- configure external interrupt edge -------------------- */
        ret = Interrupt_INTx_Edge_init(_interrupt_INTx);
        
        /* -------------------- configure external interrupt priority -------------------- */
        ret = Interrupt_INTx_Priority_init(_interrupt_INTx);

        /* -------------------- configure external interrupt pin -------------------- */
        ret = Interrupt_INTx_Pin_init(_interrupt_INTx);
        
        /* -------------------- configure default interrupt callback -------------------- */
        ret = INTx_Set_Interrupt_Handler(_interrupt_INTx);
        
        /* -------------------- enable the external interrupt -------------------- */
        ret = Interrupt_INTx_Enable(_interrupt_INTx);
    }
    return ret;
}

/**
 * 
 * @param _interrupt_INTx
 * @return 
 */
STD_ReturnType Interrupt_INTx_deinit(const interrupt_INTx *_interrupt_INTx)
{
    STD_ReturnType ret = E_OK;
    
    if(NULL == _interrupt_INTx)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = Interrupt_INTx_Disable(_interrupt_INTx);
    }
    return ret;
}

/**
 * 
 * @param _interrupt_RBx
 * @return 
 */
STD_ReturnType Interrupt_RBx_init(const interrupt_RBx *_interrupt_RBx)
{
    STD_ReturnType ret = E_OK;
    
    if(NULL == _interrupt_RBx)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* -------------------- disable the external interrupt -------------------- */
        ret = Interrupt_RBx_Disable(_interrupt_RBx);
        
        /* -------------------- clear the interrupt flag -------------------- */
        ret = Interrupt_RBx_Clear_Flag(_interrupt_RBx);

        /* -------------------- configure external interrupt priority -------------------- */
        ret = Interrupt_RBx_Priority_init(_interrupt_RBx);

        /* -------------------- configure external interrupt pin -------------------- */
        ret = Interrupt_RBx_Pin_init(_interrupt_RBx);

        /* -------------------- enable the external interrupt -------------------- */
        ret = Interrupt_RBx_Enable(_interrupt_RBx);
    }
    
    return ret;
}

/**
 * 
 * @param _interrupt_RBx
 * @return 
 */
STD_ReturnType Interrupt_RBx_deinit(const interrupt_RBx *_interrupt_RBx)
{
    STD_ReturnType ret = E_OK;
    
    if(NULL == _interrupt_RBx)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = Interrupt_RBx_Disable(_interrupt_RBx);
    }
    return ret;
}


/* --------------------------------- Helper functions --------------------------------- */
/**
 * 
 * @param _interrupt_INTx
 * @return 
 */
static STD_ReturnType Interrupt_INTx_Enable(const interrupt_INTx *_interrupt_INTx) 
{
    STD_ReturnType ret = E_OK;

    if (NULL == _interrupt_INTx) 
    {
        ret = E_NOT_OK;
    } 
    else 
    {
        switch (_interrupt_INTx->INTx) 
        {
            case INTERRUPT_EXTERNAL_INT0:          
#if Interrupt_Priority_level_Enable == Interrupt_Feature_Enable
                INTERRUPT_ENABLE_BRIORITY_INTERRUPT();
                INTERRUPT_ENABLE_GLOBLE_HIGH_BRIORITY_INTERRUPT();
                EXTERNAL_INT0_INTERRUPT_ENABLE();
#else
                INTERRUPT_ENABLE_GLOBLE_INTERRUPT();
                INTERRUPT_ENABLE_PERIPHERAL_INTERRUPT();
#endif
                break;

            case INTERRUPT_EXTERNAL_INT1:
#if Interrupt_Priority_level_Enable == Interrupt_Feature_Enable
                INTERRUPT_ENABLE_BRIORITY_INTERRUPT();
                EXTERNAL_INT1_INTERRUPT_ENABLE();
                switch (_interrupt_INTx->priority) 
                {
                    case INTERRUPT_LOW_PRIORITY:
                        INTERRUPT_ENABLE_GLOBLE_LOW_BRIORITY_INTERRUPT();
                        break;
                    case INTERRUPT_HIGH_PRIORITY:
                        INTERRUPT_ENABLE_GLOBLE_HIGH_BRIORITY_INTERRUPT();
                        break;
                }
                break;
#else
                INTERRUPT_ENABLE_GLOBLE_INTERRUPT();
                INTERRUPT_ENABLE_PERIPHERAL_INTERRUPT();
#endif
                break;

            case INTERRUPT_EXTERNAL_INT2:
#if Interrupt_Priority_level_Enable == Interrupt_Feature_Enable
                INTERRUPT_ENABLE_BRIORITY_INTERRUPT();
                EXTERNAL_INT2_INTERRUPT_ENABLE();
                switch (_interrupt_INTx->priority) 
                {
                    case INTERRUPT_LOW_PRIORITY:
                        INTERRUPT_ENABLE_GLOBLE_LOW_BRIORITY_INTERRUPT();
                        break;
                    case INTERRUPT_HIGH_PRIORITY:
                        INTERRUPT_ENABLE_GLOBLE_HIGH_BRIORITY_INTERRUPT();
                        break;
                }
                break;

#else
                INTERRUPT_ENABLE_GLOBLE_INTERRUPT();
                INTERRUPT_ENABLE_PERIPHERAL_INTERRUPT();
#endif 
                break;

            default:
                ret = E_NOT_OK;
                break;
        }
    }
    return ret;
}

/**
 * 
 * @param _interrupt_INTx
 * @return 
 */
static STD_ReturnType Interrupt_INTx_Disable(const interrupt_INTx *_interrupt_INTx)
{
    STD_ReturnType ret = E_OK;
    
    if(NULL == _interrupt_INTx)
    {
        ret = E_NOT_OK;
    }
    else
    {
        switch(_interrupt_INTx->INTx)
        {
            case INTERRUPT_EXTERNAL_INT0:
                EXTERNAL_INT0_INTERRUPT_DISABLE();
                break;

            case INTERRUPT_EXTERNAL_INT1:
                EXTERNAL_INT1_INTERRUPT_DISABLE();
                break;

            case INTERRUPT_EXTERNAL_INT2:
                EXTERNAL_INT2_INTERRUPT_DISABLE();
                break;
            default:
                ret = E_NOT_OK;
        }
    }
    return ret;
}

/**
 * 
 * @param _interrupt_INTx
 * @return 
 */
static STD_ReturnType Interrupt_INTx_Priority_init(const interrupt_INTx *_interrupt_INTx)
{
    STD_ReturnType ret = E_OK;
    
    if((NULL == _interrupt_INTx) || (INTCONbits.GIE == 0))
    {
        ret = E_NOT_OK;
    }
    else
    {
        switch (_interrupt_INTx->INTx) 
        {
            case INTERRUPT_EXTERNAL_INT0:
                break;
            case INTERRUPT_EXTERNAL_INT1:
                switch (_interrupt_INTx->priority) 
                {
                    case INTERRUPT_LOW_PRIORITY:
                        EXTERNAL_INT1_LOW_BRIORITY_SET();
                        break;
                    case INTERRUPT_HIGH_PRIORITY:
                        EXTERNAL_INT1_HIGHT_BRIORITY_SET();
                        break;
                }
                break;
                
            case INTERRUPT_EXTERNAL_INT2:
                switch (_interrupt_INTx->edge) 
                {
                    case INTERRUPT_LOW_PRIORITY:
                        EXTERNAL_INT2_LOW_BRIORITY_SET();
                        break;
                    case INTERRUPT_HIGH_PRIORITY:
                        EXTERNAL_INT2_HIGHT_BRIORITY_SET();
                        break;
                }
                break;
                
            default :
                ret = E_NOT_OK;
        }
    }
    return ret;
}


/**
 * 
 * @param _interrupt_INTx
 * @return 
 */
static STD_ReturnType Interrupt_INTx_Edge_init(const interrupt_INTx *_interrupt_INTx)
{
    STD_ReturnType ret = E_OK;
    
    if(NULL == _interrupt_INTx)
    {
        ret = E_NOT_OK;
    }
    else 
    {
        switch (_interrupt_INTx->INTx) 
        {
            case INTERRUPT_EXTERNAL_INT0:
                switch (_interrupt_INTx->edge) 
                {
                    case INTERRUPT_FALLING_EDGE:
                        EXTERNAL_INT0_FALLING_EDGE_SET();
                        break;
                    case INTERRUPT_RISING_EDGE:
                        EXTERNAL_INT0_RISING_EDGE_SET();
                        break;
                }
                break;
                
            case INTERRUPT_EXTERNAL_INT1:
                switch (_interrupt_INTx->edge) 
                {
                    case INTERRUPT_FALLING_EDGE:
                        EXTERNAL_INT1_FALLING_EDGE_SET();
                        break;
                    case INTERRUPT_RISING_EDGE:
                        EXTERNAL_INT1_RISING_EDGE_SET();
                        break;
                }
                break;
            case INTERRUPT_EXTERNAL_INT2:
                switch (_interrupt_INTx->edge) 
                {
                    case INTERRUPT_FALLING_EDGE:
                        EXTERNAL_INT2_FALLING_EDGE_SET();
                        break;
                    case INTERRUPT_RISING_EDGE:
                        EXTERNAL_INT2_RISING_EDGE_SET();
                        break;
                }
                break;
            default:
                ret = E_NOT_OK;
        }

    }
    return ret;
}

/**
 * 
 * @param _interrupt_INTx
 * @return 
 */
static STD_ReturnType Interrupt_INTx_Pin_init(const interrupt_INTx *_interrupt_INTx)
{
    STD_ReturnType ret = E_OK;
    
    if(NULL == _interrupt_INTx)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = gpio_pin_direction_init(&(_interrupt_INTx->interrupt_pin));
    }
    return ret;
}

/**
 * 
 * @param _interrupt_INTx
 * @return 
 */
static STD_ReturnType Interrupt_INTx_Clear_Flag(const interrupt_INTx *_interrupt_INTx)
{
    STD_ReturnType ret = E_OK;
    
    if(NULL == _interrupt_INTx)
    {
        ret = E_NOT_OK;
    }
    else
    {
        switch(_interrupt_INTx->INTx)
        {
            case INTERRUPT_EXTERNAL_INT0:
                EXTERNAL_INT0_INTERRUPT_FLAG_CLEAR();
                break;
            case INTERRUPT_EXTERNAL_INT1:
                EXTERNAL_INT1_INTERRUPT_FLAG_CLEAR();
                break;    
            case INTERRUPT_EXTERNAL_INT2:
                EXTERNAL_INT2_INTERRUPT_FLAG_CLEAR();
                break;
            default:
                ret = E_NOT_OK;
        }
    }
    return ret;
}

/**
 * 
 * @param _interrupt_RBx
 * @return 
 */

static STD_ReturnType Interrupt_RBx_Enable(const interrupt_RBx *_interrupt_RBx)
{
    STD_ReturnType ret = E_OK;
    
    if(NULL == _interrupt_RBx)
    {
        ret = E_NOT_OK;
    }
    else
    {
        EXTERNAL_RBX_INTERRUPT_ENABLE();

    }
    return ret;
}

/**
 * 
 * @param _interrupt_RBx
 * @return 
 */
static STD_ReturnType Interrupt_RBx_Disable(const interrupt_RBx *_interrupt_RBx)
{
    STD_ReturnType ret = E_OK;
    
    if(NULL == _interrupt_RBx)
    {
        ret = E_NOT_OK;
    }
    else
    {
        EXTERNAL_RBX_INTERRUPT_DISABLE();

    }
    return ret;
}

/**
 * 
 * @param _interrupt_RBx
 * @return 
 */
static STD_ReturnType Interrupt_RBx_Priority_init(const interrupt_RBx *_interrupt_RBx)
{
    STD_ReturnType ret = E_OK;
    
    if(NULL == _interrupt_RBx)
    {
        ret = E_NOT_OK;
    }
    else
    {
#if Interrupt_Priority_level_Enable == Interrupt_Feature_Enable
        INTERRUPT_ENABLE_BRIORITY_INTERRUPT();
        switch (_interrupt_RBx->priority) 
        {
            case INTERRUPT_LOW_PRIORITY:
                INTERRUPT_ENABLE_GLOBLE_LOW_BRIORITY_INTERRUPT();
                EXTERNAL_RBX_LOW_BRIORITY_SET();
                break;
            case INTERRUPT_HIGH_PRIORITY:
                INTERRUPT_ENABLE_GLOBLE_HIGH_BRIORITY_INTERRUPT();
                EXTERNAL_RBX_HIGHT_BRIORITY_SET();
                break;
            default:
                ret = E_NOT_OK;
                break;
        }
#else
        INTERRUPT_ENABLE_GLOBLE_INTERRUPT();
        INTERRUPT_ENABLE_PERIPHERAL_INTERRUPT();
#endif
    }

    return ret;
}

/**
 * 
 * @param _interrupt_RBx
 * @return 
 */
static STD_ReturnType Interrupt_RBx_Pin_init(const interrupt_RBx *_interrupt_RBx)
{
    STD_ReturnType ret = E_OK;
    
    if(NULL == _interrupt_RBx)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = gpio_pin_direction_init(&(_interrupt_RBx->interrupt_pin));

        switch(_interrupt_RBx->interrupt_pin.pin)
        {
            case GPIO_PIN4:
                RB4_InterruptHandler = _interrupt_RBx->EXTERNAL_INTERRUPT_CALLBACK; 
                break;
            case GPIO_PIN5:
                RB5_InterruptHandler = _interrupt_RBx->EXTERNAL_INTERRUPT_CALLBACK;
                break;
            case GPIO_PIN6:
                RB6_InterruptHandler = _interrupt_RBx->EXTERNAL_INTERRUPT_CALLBACK;
                break;
            case GPIO_PIN7:
                RB7_InterruptHandler = _interrupt_RBx->EXTERNAL_INTERRUPT_CALLBACK;
                break;    
            default:
                ret = E_NOT_OK;
                break;
        }
    }
    return ret;
}

/**
 * 
 * @param _interrupt_RBx
 * @return 
 */
static STD_ReturnType Interrupt_RBx_Clear_Flag (const interrupt_RBx *_interrupt_RBx)
{
    STD_ReturnType ret = E_OK;
    
    if(NULL == _interrupt_RBx)
    {
        ret = E_NOT_OK;
    }
    else
    {
        EXTERNAL_RBX_INTERRUPT_FLAG_CLEAR();

    }
    return ret;
}

/**
 * 
 * @param Interrupt_Handler
 * @return 
 */
static STD_ReturnType INT0_Interrupt_Handler(void (*Interrupt_Handler)(void))
{
    STD_ReturnType ret = E_OK;
    
    if(NULL == Interrupt_Handler)
    {
        ret = E_NOT_OK;
    }
    else
    {
        INT0_InterruptHandler = Interrupt_Handler;
    }
    return ret;
}

/**
 * 
 * @param Interrupt_Handler
 * @return 
 */
static STD_ReturnType INT1_Interrupt_Handler(void (*Interrupt_Handler)(void))
{
    STD_ReturnType ret = E_OK;
    
    if(NULL == Interrupt_Handler)
    {
        ret = E_NOT_OK;
    }
    else
    {
        INT1_InterruptHandler = Interrupt_Handler;
    }
    return ret;
}

/**
 * 
 * @param Interrupt_Handler
 * @return 
 */
static STD_ReturnType INT2_Interrupt_Handler(void (*Interrupt_Handler)(void))
{
    STD_ReturnType ret = E_OK;
    
    if(NULL == Interrupt_Handler)
    {
        ret = E_NOT_OK;
    }
    else
    {
        INT2_InterruptHandler = Interrupt_Handler;
    }
    return ret;
}

/**
 * 
 * @param _interrupt_INTx
 * @return 
 */
static STD_ReturnType INTx_Set_Interrupt_Handler(const interrupt_INTx *_interrupt_INTx)
{
    STD_ReturnType ret = E_OK;
    
    if(NULL == _interrupt_INTx)
    {
        ret = E_NOT_OK;
    }
    else
    {
        switch(_interrupt_INTx->INTx)
        {
            case INTERRUPT_EXTERNAL_INT0:
                ret = INT0_Interrupt_Handler(_interrupt_INTx->EXTERNAL_INTERRUPT_CALLBACK);
                break;

            case INTERRUPT_EXTERNAL_INT1:
                ret = INT1_Interrupt_Handler(_interrupt_INTx->EXTERNAL_INTERRUPT_CALLBACK);
                break;

            case INTERRUPT_EXTERNAL_INT2:
                ret = INT2_Interrupt_Handler(_interrupt_INTx->EXTERNAL_INTERRUPT_CALLBACK);
                break;

            default:
                ret = E_NOT_OK;       
        }
    }
    return ret;
}


void INT0_ISR(void)
{
    /* ------------ clear the interrupt flag ------------ */
    EXTERNAL_INT0_INTERRUPT_FLAG_CLEAR();
    
    /* ------------ code ------------ */
    
    /* ------------ callback function ------------ */
    if(INT0_InterruptHandler)
    {
        INT0_InterruptHandler();
    }
}

void INT1_ISR(void)
{
    /* ------------ clear the interrupt flag ------------ */
    EXTERNAL_INT1_INTERRUPT_FLAG_CLEAR();
    
    /* ------------ code ------------ */
    
    /* ------------ callback function ------------ */
    if(INT1_InterruptHandler)
    {
        INT1_InterruptHandler();
    }
}

void INT2_ISR(void)
{
    /* ------------ clear the interrupt flag ------------ */
    EXTERNAL_INT2_INTERRUPT_FLAG_CLEAR();
    
    /* ------------ code ------------ */
    
    /* ------------ callback function ------------ */
    if(INT2_InterruptHandler)
    {
        INT2_InterruptHandler();
    }
}

void RB4_ISR(void)
{
    /* ------------ clear the interrupt flag ------------ */
    EXTERNAL_RBX_INTERRUPT_FLAG_CLEAR();
    
    /* ------------ code ------------ */
    
    /* ------------ callback function ------------ */
    if(RB4_InterruptHandler)
    {
        RB4_InterruptHandler();
    }
}

void RB5_ISR(void)
{
    /* ------------ clear the interrupt flag ------------ */
    EXTERNAL_RBX_INTERRUPT_FLAG_CLEAR();
    
    /* ------------ code ------------ */
    
    /* ------------ callback function ------------ */
    if(RB5_InterruptHandler)
    {
        RB5_InterruptHandler();
    }
    
}

void RB6_ISR(void)
{
    /* ------------ clear the interrupt flag ------------ */
    EXTERNAL_RBX_INTERRUPT_FLAG_CLEAR();
    
    /* ------------ code ------------ */
    
    /* ------------ callback function ------------ */
    if(RB6_InterruptHandler)
    {
        RB6_InterruptHandler();
    }
    
}

void RB7_ISR(void)
{
    /* ------------ clear the interrupt flag ------------ */
    EXTERNAL_RBX_INTERRUPT_FLAG_CLEAR();
    
    /* ------------ code ------------ */
    
    /* ------------ callback function ------------ */
    if(RB7_InterruptHandler)
    {
        RB7_InterruptHandler();
    }
    
}