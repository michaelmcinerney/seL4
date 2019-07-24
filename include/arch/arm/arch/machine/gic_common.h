/*
 * Copyright 2019, Data61
 * Commonwealth Scientific and Industrial Research Organisation (CSIRO)
 * ABN 41 687 119 230.
 *
 * This software may be distributed and modified according to the terms of
 * the GNU General Public License version 2. Note that NO WARRANTY is provided.
 * See "LICENSE_GPLv2.txt" for details.
 *
 * @TAG(DATA61_GPL)
 */

#ifndef __ARCH_MACHINE_GIC_COMMON_H
#define __ARCH_MACHINE_GIC_COMMON_H

#include <stdint.h>

/* Shift positions for GICD_SGIR register */
#define GICD_SGIR_SGIINTID_SHIFT          0
#define GICD_SGIR_CPUTARGETLIST_SHIFT     16
#define GICD_SGIR_TARGETLISTFILTER_SHIFT  24

/* Special IRQ's */
#define SPECIAL_IRQ_START 1020u
#define IRQ_NONE          1023u

/* CPU specific IRQ's */
#define SGI_START         0u
#define PPI_START         16u

/* Shared Peripheral Interrupts */
#define SPI_START         32u

/* Setters/getters helpers for hardware irqs */
#define IRQ_REG(IRQ) ((IRQ) >> 5u)
#define IRQ_BIT(IRQ) ((IRQ) & 0x1f)
#define IS_IRQ_VALID(X) (((X) & IRQ_MASK) < SPECIAL_IRQ_START)

typedef uint16_t interrupt_t;
typedef uint16_t irq_t;

enum irqNumbers {
    irqInvalid = (irq_t) - 1
};

/*
 * The only sane way to get an GIC IRQ number that can be properly
 * ACKED later is through the int_ack register. Unfortunately, reading
 * this register changes the interrupt state to pending so future
 * reads will not return the same value For this reason, we have a
 * global variable to store the IRQ number.
 */
extern uint32_t active_irq[CONFIG_MAX_NUM_NODES];

static inline void handleSpuriousIRQ(void)
{
}

void initIRQController(void);


#endif /* __ARCH_MACHINE_GIC_COMMON_H */
