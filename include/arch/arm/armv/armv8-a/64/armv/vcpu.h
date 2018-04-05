/*
 * Copyright 2018, Data61
 * Commonwealth Scientific and Industrial Research Organisation (CSIRO)
 * ABN 41 687 119 230.
 *
 * This software may be distributed and modified according to the terms of
 * the GNU General Public License version 2. Note that NO WARRANTY is provided.
 * See "LICENSE_GPLv2.txt" for details.
 *
 * @TAG(DATA61_GPL)
 */

#ifndef __ARCH_ARMV_VCPU_H_
#define __ARCH_ARMV_VCPU_H_

#include <config.h>

#ifdef CONFIG_ARM_HYPERVISOR_SUPPORT

#include <arch/object/vcpu.h>

/* Note that the HCR_DC for ARMv8 disables S1 translation if enabled */
/* Trap WFI/WFE/SMC and override CPSR.AIF */
#define HCR_COMMON ( HCR_TWI | HCR_TWE | HCR_VM | HCR_RW | HCR_AMO | HCR_IMO | HCR_FMO )

/* Allow native tasks to run at EL0, but restrict access */
#define HCR_NATIVE ( HCR_COMMON | HCR_TGE | HCR_TVM | HCR_TTLB | HCR_DC \
                   | HCR_TAC | HCR_SWIO |  HCR_TSC | HCR_IMO | HCR_FMO | HCR_AMO)
#define HCR_VCPU   ( HCR_COMMON)

#define SCTLR_EL1_UCI   BIT(26)     /* Enable EL0 access to DC CVAU, DC CIVAC, DC CVAC,
                                       and IC IVAU in AArch64 state   */
#define SCTLR_EL1_C     BIT(2)      /* Enable data and unified caches */
#define SCTLR_EL1_I     BIT(12)     /* Enable instruction cache       */
/* Disable MMU, SP alignment check, and alignment check */
/* A57 default value */
#define SCTLR_EL1_NATIVE   (0x34d58820 | SCTLR_EL1_C | SCTLR_EL1_I | SCTLR_EL1_UCI)
#define SCTLR_EL1_VM       0x34d58820
#define SCTLR_DEFAULT      SCTLR_EL1_NATIVE

/* for EL1 SCTLR */
static inline word_t
getSCTLR(void)
{
    return readSystemControlRegister();
}

static inline void
setSCTLR(word_t sctlr)
{
    writeSystemControlRegister(sctlr);
}

static inline word_t
readTTBR0(void)
{
    word_t reg;
    MRS("ttbr0_el1", reg);
    return reg;
}

static inline void
writeTTBR0(word_t reg)
{
    MSR("ttbr0_el1", reg);
}

static inline word_t
readTTBR1(void)
{
    word_t reg;
    MRS("ttbr1_el1", reg);
    return reg;
}

static inline void
writeTTBR1(word_t reg)
{
    MSR("ttbr1_el1", reg);
}

static inline word_t
readTCR(void)
{
    word_t reg;
    MRS("tcr_el1", reg);
    return reg;
}

static inline void
writeTCR(word_t reg)
{
    MSR("tcr_el1", reg);
}

static inline word_t
readMAIR(void)
{
    word_t reg;
    MRS("mair_el1", reg);
    return reg;
}

static inline void
writeMAIR(word_t reg)
{
    MSR("mair_el1", reg);
}

static inline word_t
readAMAIR(void)
{
    word_t reg;
    MRS("amair_el1", reg);
    return reg;
}

static inline void
writeAMAIR(word_t reg)
{
    MSR("amair_el1", reg);
}

static inline word_t
readCIDR(void)
{
    uint32_t reg;
    MRS("contextidr_el1", reg);
    return (word_t)reg;
}

static inline void
writeCIDR(word_t reg)
{
    MSR("contextidr_el1", (uint32_t)reg);
}

static inline word_t
readACTLR(void)
{
    word_t reg;
    MRS("actlr_el1", reg);
    return reg;
}

static inline void
writeACTLR(word_t reg)
{
    MSR("actlr_el1", reg);
}

static inline word_t
readAFSR0(void)
{
    uint32_t reg;
    MRS("afsr0_el1", reg);
    return (word_t)reg;
}

static inline void
writeAFSR0(word_t reg)
{
    MSR("afsr0_el1", (uint32_t)reg);
}

static inline word_t
readAFSR1(void)
{
    uint32_t reg;
    MRS("afsr1_el1", reg);
    return (word_t)reg;
}

static inline void
writeAFSR1(word_t reg)
{
    MSR("afsr1_el1", (uint32_t)reg);
}

static inline word_t
readESR(void)
{
    uint32_t reg;
    MRS("esr_el1", reg);
    return (word_t)reg;
}

static inline void
writeESR(word_t reg)
{
    MSR("esr_el1", (uint32_t)reg);
}

static inline word_t
readFAR(void)
{
    word_t reg;
    MRS("far_el1", reg);
    return reg;
}

static inline void
writeFAR(word_t reg)
{
    MSR("far_el1", (uint32_t)reg);
}

/* ISR is read-only */
static inline word_t
readISR(void)
{
    uint32_t reg;
    MRS("isr_el1", reg);
    return (word_t)reg;
}

static inline word_t
readVBAR(void)
{
    word_t reg;
    MRS("vbar_el1", reg);
    return reg;
}

static inline void
writeVBAR(word_t reg)
{
    MSR("vbar_el1", reg);
}

static inline word_t
readTPIDR_EL0(void)
{
    word_t reg;
    MRS("TPIDR_EL0", reg);
    return reg;
}

static inline void
writeTPIDR_EL0(word_t reg)
{
    MSR("TPIDR_EL0", reg);
}

static inline word_t
readTPIDR_EL1(void)
{
    word_t reg;
    MRS("TPIDR_EL1", reg);
    return reg;
}

static inline void
writeTPIDR_EL1(word_t reg)
{
    MSR("TPIDR_EL1", reg);
}

static inline word_t
readTPIDRRO_EL0(void)
{
    word_t reg;
    MRS("TPIDRRO_EL0", reg);
    return reg;
}

static inline void
writeTPIDRRO_EL0(word_t reg)
{
    MSR("TPIDRRO_EL0", reg);
}

static inline word_t
readSP_EL1(void)
{
    word_t reg;
    MRS("sp_el1", reg);
    return reg;
}

static inline void
writeSP_EL1(word_t reg)
{
    MSR("sp_el1", reg);
}

static inline word_t
readELR_EL1(void)
{
    word_t reg;
    MRS("elr_el1", reg);
    return reg;
}

static inline void
writeELR_EL1(word_t reg)
{
    MRS("elr_el1", reg);
}

static inline word_t
readSPSR_EL1(void)
{
    word_t reg;
    MRS("spsr_el1", reg);
    return reg;
}

static inline void
writeSPSR_EL1(word_t reg)
{
    MSR("spsr_el1", reg);
}

static inline word_t
readCPACR_EL1(void)
{
    word_t reg;
    MRS("cpacr_el1", reg);
    return reg;
}

static inline void
writeCPACR_EL1(word_t reg)
{
    MSR("cpacr_el1", reg);
}

static inline word_t
readCNTV_TVAL_EL0(void)
{
    word_t reg;
    MRS("cntv_tval_el0", reg);
    return reg;
}

static inline void
writeCNTV_TVAL_EL0(word_t reg)
{
    MSR("cntv_tval_el0", reg);
}

static inline word_t
readCNTV_CTL_EL0(void)
{
    word_t reg;
    MRS("cntv_ctl_el0", reg);
    return reg;
}

static inline void
writeCNTV_CTL_EL0(word_t reg)
{
    MSR("cntv_ctl_el0", reg);
}

static word_t
vcpu_hw_read_reg(word_t reg_index)
{
    word_t reg = 0;
    switch (reg_index) {
    case seL4_VCPUReg_SCTLR:
        return getSCTLR();
    case seL4_VCPUReg_TTBR0:
        return readTTBR0();
    case seL4_VCPUReg_TTBR1:
        return readTTBR1();
    case seL4_VCPUReg_TCR:
        return readTCR();
    case seL4_VCPUReg_MAIR:
        return readMAIR();
    case seL4_VCPUReg_AMAIR:
        return readAMAIR();
    case seL4_VCPUReg_CIDR:
        return readCIDR();
    case seL4_VCPUReg_ACTLR:
        return readACTLR();
    case seL4_VCPUReg_CPACR:
        return readCPACR_EL1();
    case seL4_VCPUReg_AFSR0:
        return readAFSR0();
    case seL4_VCPUReg_AFSR1:
        return readAFSR1();
    case seL4_VCPUReg_ESR:
        return readESR();
    case seL4_VCPUReg_FAR:
        return readFAR();
    case seL4_VCPUReg_ISR:
        return readISR();
    case seL4_VCPUReg_VBAR:
        return readVBAR();
    case seL4_VCPUReg_TPIDR_EL0:
        return readTPIDR_EL0();
    case seL4_VCPUReg_TPIDR_EL1:
        return readTPIDR_EL1();
    case seL4_VCPUReg_TPIDRRO_EL0:
        return readTPIDRRO_EL0();
    case seL4_VCPUReg_CNTV_TVAL:
        return readCNTV_TVAL_EL0();
    case seL4_VCPUReg_CNTV_CTL:
        return readCNTV_CTL_EL0();
    case seL4_VCPUReg_CNTV_CVAL:
        return 0;
    case seL4_VCPUReg_SP_EL1:
        return readSP_EL1();
    case seL4_VCPUReg_ELR_EL1:
        return readELR_EL1();
    case seL4_VCPUReg_SPSR_EL1:
        return readSPSR_EL1();
    default:
        fail("ARM/HYP: Invalid register index");
    }

    return reg;
}

static void
vcpu_hw_write_reg(word_t reg_index, word_t reg)
{
    switch (reg_index) {
    case seL4_VCPUReg_SCTLR:
        return setSCTLR(reg);
    case seL4_VCPUReg_TTBR0:
        return writeTTBR0(reg);
    case seL4_VCPUReg_TTBR1:
        return writeTTBR1(reg);
    case seL4_VCPUReg_TCR:
        return writeTCR(reg);
    case seL4_VCPUReg_MAIR:
        return writeMAIR(reg);
    case seL4_VCPUReg_AMAIR:
        return writeAMAIR(reg);
    case seL4_VCPUReg_CIDR:
        return writeCIDR(reg);
    case seL4_VCPUReg_ACTLR:
        return writeACTLR(reg);
    case seL4_VCPUReg_CPACR:
        return writeCPACR_EL1(reg);
    case seL4_VCPUReg_AFSR0:
        return writeAFSR0(reg);
    case seL4_VCPUReg_AFSR1:
        return writeAFSR1(reg);
    case seL4_VCPUReg_ESR:
        return writeESR(reg);
    case seL4_VCPUReg_FAR:
        return writeFAR(reg);
    case seL4_VCPUReg_ISR:
        /* ISR is read-only */
        return;
    case seL4_VCPUReg_VBAR:
        return writeVBAR(reg);
    case seL4_VCPUReg_TPIDR_EL0:
        return writeTPIDR_EL0(reg);
    case seL4_VCPUReg_TPIDR_EL1:
        return writeTPIDR_EL1(reg);
    case seL4_VCPUReg_TPIDRRO_EL0:
        return writeTPIDRRO_EL0(reg);
    case seL4_VCPUReg_CNTV_TVAL:
        return writeCNTV_TVAL_EL0(reg);
    case seL4_VCPUReg_CNTV_CTL:
        return writeCNTV_CTL_EL0(reg);
    case seL4_VCPUReg_CNTV_CVAL:
        return;
    case seL4_VCPUReg_SP_EL1:
        return writeSP_EL1(reg);
    case seL4_VCPUReg_ELR_EL1:
        return writeELR_EL1(reg);
    case seL4_VCPUReg_SPSR_EL1:
        return writeSPSR_EL1(reg);
    default:
        fail("ARM/HYP: Invalid register index");
    }

    return;
}

static inline void
vcpu_save_reg(vcpu_t *vcpu, word_t reg)
{
    if (reg >= seL4_VCPUReg_Num || vcpu == NULL) {
        fail("ARM/HYP: Invalid register index or NULL VCPU");
        return;
    }
    vcpu->regs[reg] = vcpu_hw_read_reg(reg);
}

static inline void
vcpu_save_reg_range(vcpu_t *vcpu, word_t start, word_t end)
{
    for (word_t i = start; i <= end; i++) {
        vcpu_save_reg(vcpu, i);
    }
}

static inline void
vcpu_restore_reg(vcpu_t *vcpu, word_t reg)
{
    if (reg >= seL4_VCPUReg_Num || vcpu == NULL) {
        fail("ARM/HYP: Invalid register index or NULL VCPU");
        return;
    }
    vcpu_hw_write_reg(reg, vcpu->regs[reg]);
}

static inline void
vcpu_restore_reg_range(vcpu_t *vcpu, word_t start, word_t end)
{
    for (word_t i = start; i <= end; i++) {
        vcpu_restore_reg(vcpu, i);
    }
}

static inline word_t
vcpu_read_reg(vcpu_t *vcpu, word_t reg)
{
    if (reg >= seL4_VCPUReg_Num || vcpu == NULL) {
        fail("ARM/HYP: Invalid register index or NULL VCPU");
        return 0;
    }
    return vcpu->regs[reg];
}

static inline void
vcpu_write_reg(vcpu_t *vcpu, word_t reg, word_t value)
{
    if (reg >= seL4_VCPUReg_Num || vcpu == NULL) {
        fail("ARM/HYP: Invalid register index or NULL VCPU");
        return;
    }
    vcpu->regs[reg] = value;
}

#define VTCR_EL2_T0SZ(x)    (x)
#define VTCR_EL2_SL0(x)     ((x) << 6)
#define VTCR_EL2_IRGN0(x)   ((x) << 8)
#define VTCR_EL2_ORGN0(x)   ((x) << 10)
#define VTCR_EL2_SH0(x)     ((x) << 12)
#define VTCR_EL2_TG0(x)     ((x) << 14)
#define VTCR_EL2_PS(x)      ((x) << 16)

static inline void
vcpu_init_vtcr(void)
{
    /* Set up the stage-2 translation control register for cores supporting 44-bit PA */
    uint32_t vtcr_el2 = VTCR_EL2_T0SZ(20); // 44-bit input IPA
    vtcr_el2 |= VTCR_EL2_SL0(0b10);        // 4KiB, start at level 0
    vtcr_el2 |= VTCR_EL2_IRGN0(0b01);      // inner normal, write-back, read/write allocate
    vtcr_el2 |= VTCR_EL2_ORGN0(0b01);      // outer normal, write-back, read/write allocate
    vtcr_el2 |= VTCR_EL2_SH0(0b11);        // inner sharable
    vtcr_el2 |= VTCR_EL2_TG0(0);           // 4KiB page size
    vtcr_el2 |= VTCR_EL2_PS(0b100);        // 44-bit PA size
    vtcr_el2 |= BIT(31);                   // reserved as 1

    MSR("vtcr_el2", vtcr_el2);
    isb();
}

static inline void
armv_vcpu_boot_init(void)
{
    word_t hcr_el2 = 0;

    vcpu_init_vtcr();

    hcr_el2 = HCR_NATIVE;
    MSR("hcr_el2", hcr_el2);
    isb();

    /* set the SCTLR_EL1 for running native seL4 threads */
    MSR("sctlr_el1", SCTLR_EL1_NATIVE);
    isb();
}

#define UNKNOWN_FAULT       0x2000000
#define ESR_EC_TFP          0x7         /* Trap instructions that access FPU registers */
#define ESR_EC_CPACR        0x18        /* Trap access to CPACR                        */
#define ESR_EC(x)           (((x) & 0xfc000000) >> 26)

static inline bool_t
armv_handleVCPUFault(word_t hsr)
{
#ifdef CONFIG_HAVE_FPU
    if ((ESR_EC(hsr) == ESR_EC_TFP || ESR_EC(hsr) == ESR_EC_CPACR) && !isFpuEnable()) {
        handleFPUFault();
        setNextPC(NODE_STATE(ksCurThread), getRestartPC(NODE_STATE(ksCurThread)));
        return true;
    }
#endif

    if (hsr == UNKNOWN_FAULT) {
        handleUserLevelFault(0, 0);
        return true;
    }

    return false;
}

#endif /* End of CONFIG_ARM_HYPERVISOR_SUPPORT */

#endif

