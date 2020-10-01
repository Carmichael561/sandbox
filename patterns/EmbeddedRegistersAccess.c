//Define base address for particular hardware component:
#define DMA_BASE                 0x10000000UL

//Define descriptor for particular component memory map.
//Members of this descriptor follow special pattern for easy access via define macro COMPONENTNAME_REGISTERNAME_REG
//0x10000000UL DMA descriptor Structure
typedef struct
{
    ___RW uint32_t  DMA_CTRL_REG; // eneble, rx, tx
    ___RW uint32_t  DMA_RESET_IRQ_REG; // 3 irq lines 0, 1, 2
    ___RW uint32_t  DMA_STATUS_P3_REG;
    ___RW uint32_t  DMA_STATUS_P5_REG; // burst, idle, done
    ___RW uint32_t  DMA_CLEAR_P3_REG;  // clear: // burst, idle, done
    ___RW uint32_t  DMA_CLEAR_P5_REG;
} dma_t;


//Declare access types:
#define ___RO volatile const      /*'read only' permissions */
#define ___WO volatile            /*'write only' permissions */
#define ___RW volatile            /*'read / write' permissions */

//Define way of access DMA component:
#define DMACNTR ((dma_t*) DMA_BASE)

//It is an example of usage, read on clear
uint32_t dma_get_status(DMA_PORT port)
{
    switch (port)
    {
    case IMX88_DMA_PORT_3:
        return IMX88_DMA_REG_GET_FIELD(STATUS_P3, DMA_STAT_P3);
    case IMX88_DMA_PORT_5:
        return IMX88_DMA_REG_GET_FIELD(STATUS_P5, DMA_STAT_P5);
    }
}

void dma_clear_status(DMA_PORT port, uint32_t status)
{
    switch (port)
    {
    case IMX88_DMA_PORT_3:
        IMX88_DMA_REG_SET_FIELD(CLEAR_P3, DMA_CLEAR_P3, status);
        break;
    case IMX88_DMA_PORT_5:
        IMX88_DMA_REG_SET_FIELD(CLEAR_P5, DMA_CLEAR_P5, status);
        break;
    }
}



//Define position of bits in a register and mask for this fields in a register.
//Use predefined pattarn for naming convension
COMPONENTNAME_REGISTERNAME_REG_REGISTERFIELDNAME_MASK
COMPONENTNAME_REGISTERNAME_REG_REGISTERFIELDNAME_POS

// DMA_CTRL_REG
// IMX88_DMA_REG_SET_FIELD(CTRL_REG, ENABLE, 1);
#define DMACNTR_DMA_CTRL_REG_ENABLE_POS (0UL)
#define DMACNTR_DMA_CTRL_REG_ENABLE_MASK (0x3UL)

#define DMACNTR_DMA_CTRL_REG_TX_POS (3UL)
#define DMACNTR_DMA_CTRL_REG_TX_MASK (0x8UL)

#define DMACNTR_DMA_CTRL_REG_RX_POS (4UL)
#define DMACNTR_DMA_CTRL_REG_RX_MASK (0x16UL)



// DMA_RESET_IRQ_REG
//IMX88_DMA_REG_GET_FIELD(RESET_IRQ, IRQ1);
//IMX88_DMA_REG_GET_FIELD(RESET_IRQ, IRQ2);
//IMX88_DMA_REG_GET_FIELD(RESET_IRQ, IRQ3);
#define DMACNTR_DMA_RESET_IRQ_REG_IRQ1_POS (0UL)
#define DMACNTR_DMA_RESET_IRQ_REG_IRQ1_MASK (0x00000001UL)

#define DMACNTR_DMA_RESET_IRQ_REG_IRQ2_POS (1UL)
#define DMACNTR_DMA_RESET_IRQ_REG_IRQ2_MASK (0x00000002UL)

#define DMACNTR_DMA_RESET_IRQ_REG_IRQ3_POS (3UL)
#define DMACNTR_DMA_RESET_IRQ_REG_IRQ3_MASK (0x00000004UL)



// DMA_STATUS_P3_REG
//
#define DMACNTR_DMA_STATUS_P3_REG_DMA_STAT_P3_BURST_POS (28UL)
#define DMACNTR_DMA_STATUS_P3_REG_DMA_STAT_P3_BURST_MASK (0xF0000000UL)

#define DMACNTR_DMA_STATUS_P3_REG_DMA_STAT_P3_IDLE_POS (16UL)
#define DMACNTR_DMA_STATUS_P3_REG_DMA_STAT_P3_IDLE_MASK (0x000F0000UL)

#define DMACNTR_DMA_STATUS_P3_REG_DMA_STAT_P3_DONE_POS (4UL)
#define DMACNTR_DMA_STATUS_P3_REG_DMA_STAT_P3_DONE_MASK (0x000000F0UL)



// DMA_CLEAR_P3_REG
//
#define DMACNTR_DMA_CLEAR_P3_REG_DMA_CLR_P3_BURST_POS (28UL)
#define DMACNTR_DMA_CLEAR_P3_REG_DMA_CLR_P3_BURST_MASK (0xF0000000UL)

#define DMACNTR_DMA_CLEAR_P3_REG_DMA_CLR_P3_IDLE_POS (16UL)
#define DMACNTR_DMA_CLEAR_P3_REG_DMA_CLR_P3_IDLE_MASK (0x000F0000UL)

#define DMACNTR_DMA_CLEAR_P3_REG_DMA_CLR_P3_DONE_POS (4UL)
#define DMACNTR_DMA_CLEAR_P3_REG_DMA_CLR_P3_DONE_MASK (0x000000F0UL)




//It is a definition of core methods for access any fields for any register which has descriptor (dma_t)
//reg - is a register name like in descriptor dma_t.
//field - it is a field of some register this field take some bits to encode current status to access it we need MASK and POSITION

#define IMX88_DMA_REG_GET_FIELD(reg, field) \
	((DMACNTR->DMA_##reg##_REG & (DMACNTR_DMA_##reg##_REG_##field##_MASK)) >> (DMACNTR_DMA_##reg##_REG_##field##_POS))


#define IMX88_DMA_REG_SET_FIELD(reg, field, val) \
	DMACNTR->DMA_##reg##_REG = ((DMACNTR->DMA_##reg##_REG & ~(DMACNTR_DMA_##reg##_REG_##field##_MASK)) | \
			((DMACNTR_DMA_##reg##_REG_##field##_MASK) & ((val) << (DMACNTR_DMA_##reg##_REG_##field##_POS))))


/*
 * Compare assembly output with struct-union base pattern
 */
int main()
{
	return 0;
}
