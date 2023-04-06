/*
 * Copyright (c) 2020 Bitdefender
 * SPDX-License-Identifier: Apache-2.0
 */
#include "include/nd_crt.h"
#include "../inc/bddisasm.h"

// The table definitions.
#include "include/tabledefs.h"

#ifndef UNREFERENCED_PARAMETER
#define UNREFERENCED_PARAMETER(P) ((void)(P))
#endif


static const ND_UINT16 gOperandMap[] =
{
    ND_OPE_D,       // ND_OPT_A
    ND_OPE_V,       // ND_OPT_B
    ND_OPE_R,       // ND_OPT_C
    ND_OPE_R,       // ND_OPT_D
    ND_OPE_M,       // ND_OPT_E
    ND_OPE_S,       // ND_OPT_F
    ND_OPE_R,       // ND_OPT_G
    ND_OPE_V,       // ND_OPT_H
    ND_OPE_I,       // ND_OPT_I
    ND_OPE_D,       // ND_OPT_J
    ND_OPE_S,       // ND_OPT_K
    ND_OPE_L,       // ND_OPT_L
    ND_OPE_M,       // ND_OPT_M
    ND_OPE_M,       // ND_OPT_N
    ND_OPE_D,       // ND_OPT_O
    ND_OPE_R,       // ND_OPT_P
    ND_OPE_M,       // ND_OPT_Q
    ND_OPE_M,       // ND_OPT_R
    ND_OPE_R,       // ND_OPT_S
    ND_OPE_R,       // ND_OPT_T
    ND_OPE_M,       // ND_OPT_U
    ND_OPE_R,       // ND_OPT_V
    ND_OPE_M,       // ND_OPT_W
    ND_OPE_S,       // ND_OPT_X
    ND_OPE_S,       // ND_OPT_Y
    ND_OPE_O,       // ND_OPT_Z
    ND_OPE_R,       // ND_OPT_rB
    ND_OPE_M,       // ND_OPT_mB
    ND_OPE_R,       // ND_OPT_rK
    ND_OPE_V,       // ND_OPT_vK
    ND_OPE_M,       // ND_OPT_mK
    ND_OPE_A,       // ND_OPT_aK
    ND_OPE_R,       // ND_OPT_mR
    ND_OPE_M,       // ND_OPT_mM
    ND_OPE_R,       // ND_OPT_rT
    ND_OPE_M,       // ND_OPT_mT
    ND_OPE_V,       // ND_OPT_vT
    ND_OPE_1,       // ND_OPT_1

    ND_OPE_S,       // ND_OPT_RIP
    ND_OPE_S,       // ND_OPT_MXCSR
    ND_OPE_S,       // ND_OPT_PKRU
    ND_OPE_S,       // ND_OPT_SSP
    ND_OPE_S,       // ND_OPT_UIF

    ND_OPE_S,       // ND_OPT_GPR_AH
    ND_OPE_S,       // ND_OPT_GPR_rAX
    ND_OPE_S,       // ND_OPT_GPR_rCX
    ND_OPE_S,       // ND_OPT_GPR_rDX
    ND_OPE_S,       // ND_OPT_GPR_rBX
    ND_OPE_S,       // ND_OPT_GPR_rSP
    ND_OPE_S,       // ND_OPT_GPR_rBP
    ND_OPE_S,       // ND_OPT_GPR_rSI
    ND_OPE_S,       // ND_OPT_GPR_rDI
    ND_OPE_S,       // ND_OPT_GPR_rR8
    ND_OPE_S,       // ND_OPT_GPR_rR9
    ND_OPE_S,       // ND_OPT_GPR_rR11

    ND_OPE_S,       // ND_OPT_SEG_CS
    ND_OPE_S,       // ND_OPT_SEG_SS
    ND_OPE_S,       // ND_OPT_SEG_DS
    ND_OPE_S,       // ND_OPT_SEG_ES
    ND_OPE_S,       // ND_OPT_SEG_FS
    ND_OPE_S,       // ND_OPT_SEG_GS

    ND_OPE_S,       // ND_OPT_FPU_ST0
    ND_OPE_M,       // ND_OPT_FPU_STX

    ND_OPE_S,       // ND_OPT_SSE_XMM0
    ND_OPE_S,       // ND_OPT_SSE_XMM1
    ND_OPE_S,       // ND_OPT_SSE_XMM2
    ND_OPE_S,       // ND_OPT_SSE_XMM3
    ND_OPE_S,       // ND_OPT_SSE_XMM4
    ND_OPE_S,       // ND_OPT_SSE_XMM5
    ND_OPE_S,       // ND_OPT_SSE_XMM6
    ND_OPE_S,       // ND_OPT_SSE_XMM7

    ND_OPE_S,       // ND_OPT_MEM_rAX (as used by MONITOR, MONITORX and RMPADJUST)
    ND_OPE_S,       // ND_OPT_MEM_rCX (as used by RMPUPDATE)
    ND_OPE_S,       // ND_OPT_MEM_rBX_AL (as used by XLAT)
    ND_OPE_S,       // ND_OPT_MEM_rDI (as used by masked moves)
    ND_OPE_S,       // ND_OPT_MEM_SHS
    ND_OPE_S,       // ND_OPT_MEM_SHSP
    ND_OPE_S,       // ND_OPT_MEM_SHS0
    ND_OPE_S,       // ND_OPT_MEM_SMSRT
    ND_OPE_S,       // ND_OPT_MEM_DMSRT

    ND_OPE_L,       // ND_OPT_Im2z

    ND_OPE_S,       // ND_OPT_CR_0
    ND_OPE_S,       // ND_OPT_IDTR
    ND_OPE_S,       // ND_OPT_GDTR
    ND_OPE_S,       // ND_OPT_LDTR
    ND_OPE_S,       // ND_OPT_TR

    ND_OPE_S,       // ND_OPT_X87_CONTROL
    ND_OPE_S,       // ND_OPT_X87_TAG
    ND_OPE_S,       // ND_OPT_X87_STATUS

    ND_OPE_E,       // ND_OPT_MSR
    ND_OPE_E,       // ND_OPT_XCR
    ND_OPE_S,       // ND_OPT_MSR_TSC
    ND_OPE_S,       // ND_OPT_MSR_TSCAUX
    ND_OPE_S,       // ND_OPT_MSR_SEIP
    ND_OPE_S,       // ND_OPT_MSR_SESP
    ND_OPE_S,       // ND_OPT_MSR_SCS
    ND_OPE_S,       // ND_OPT_MSR_STAR
    ND_OPE_S,       // ND_OPT_MSR_LSTAR
    ND_OPE_S,       // ND_OPT_MSR_FMASK
    ND_OPE_S,       // ND_OPT_MSR_FSBASE
    ND_OPE_S,       // ND_OPT_MSR_GSBASE
    ND_OPE_S,       // ND_OPT_MSR_KGSBASE
    ND_OPE_S,       // ND_OPT_XCR_0
    ND_OPE_S,       // ND_OPT_REG_BANK
    ND_OPE_S,       // Unused.
};


static const ND_UINT8 gDispsizemap16[4][8] =
{
    { 0, 0, 0, 0, 0, 0, 2, 0 },
    { 1, 1, 1, 1, 1, 1, 1, 1 },
    { 2, 2, 2, 2, 2, 2, 2, 2 },
    { 0, 0, 0, 0, 0, 0, 0, 0 },
};

static const ND_UINT8 gDispsizemap[4][8] =
{
    { 0, 0, 0, 0, 0, 4, 0, 0 },
    { 1, 1, 1, 1, 1, 1, 1, 1 },
    { 4, 4, 4, 4, 4, 4, 4, 4 },
    { 0, 0, 0, 0, 0, 0, 0, 0 },
};


//
// NdGetVersion
//
void
NdGetVersion(
    ND_UINT32 *Major,
    ND_UINT32 *Minor,
    ND_UINT32 *Revision,
    char **BuildDate,
    char **BuildTime
    )
{
    if (ND_NULL != Major)
    {
        *Major = DISASM_VERSION_MAJOR;
    }

    if (ND_NULL != Minor)
    {
        *Minor = DISASM_VERSION_MINOR;
    }

    if (ND_NULL != Revision)
    {
        *Revision = DISASM_VERSION_REVISION;
    }

//
// Do not use __TIME__ and __DATE__ macros when compiling against a kernel tree.
//
#if defined(__KERNEL__)

    if (ND_NULL != BuildDate)
    {
        *BuildDate = (char *)ND_NULL;
    }

    if (ND_NULL != BuildTime)
    {
        *BuildTime = (char *)ND_NULL;
    }

#else

    if (ND_NULL != BuildDate)
    {
        *BuildDate = __DATE__;
    }

    if (ND_NULL != BuildTime)
    {
        *BuildTime = __TIME__;
    }

#endif

}



//
// NdFetchData
//
static ND_UINT64
NdFetchData(
    const ND_UINT8 *Buffer,
    ND_UINT8 Size
    )
{
    return (4 == Size) ? ND_FETCH_32(Buffer) :
           (1 == Size) ? ND_FETCH_8(Buffer) :
           (8 == Size) ? ND_FETCH_64(Buffer) :
           (2 == Size) ? ND_FETCH_16(Buffer) :
           0;
}


//
// NdFetchXop
//
static NDSTATUS
NdFetchXop(
    INSTRUX *Instrux,
    const ND_UINT8 *Code,
    ND_UINT8 Offset,
    ND_SIZET Size
    )
{
    // Offset points to the 0x8F XOP prefix.
    // One more byte has to follow, the modrm or the second XOP byte.
    RET_GT((ND_SIZET)Offset + 2, Size, ND_STATUS_BUFFER_TOO_SMALL);

    if (((Code[Offset + 1] & 0x1F) >= 8))
    {
        // XOP found, make sure the third byte is here.
        RET_GT((ND_SIZET)Offset + 3, Size, ND_STATUS_BUFFER_TOO_SMALL);

        // Make sure we don't have any other prefix.
        if (Instrux->HasOpSize || Instrux->HasRepnzXacquireBnd || Instrux->HasRepRepzXrelease || Instrux->HasRex)
        {
            return ND_STATUS_XOP_WITH_PREFIX;
        }

        // Fill in XOP info.
        Instrux->HasXop = ND_TRUE;
        Instrux->EncMode = ND_ENCM_XOP;
        Instrux->Xop.Xop[0] = Code[Offset];
        Instrux->Xop.Xop[1] = Code[Offset + 1];
        Instrux->Xop.Xop[2] = Code[Offset + 2];

        Instrux->Exs.w = Instrux->Xop.w;
        Instrux->Exs.r = ~Instrux->Xop.r;
        Instrux->Exs.x = ~Instrux->Xop.x;
        Instrux->Exs.b = ~Instrux->Xop.b;
        Instrux->Exs.l = Instrux->Xop.l;
        Instrux->Exs.v = ~Instrux->Xop.v;
        Instrux->Exs.m = Instrux->Xop.m;
        Instrux->Exs.p = Instrux->Xop.p;

        // if we are in non 64 bit mode, we must make sure that none of the extended registers are being addressed.
        if (Instrux->DefCode != ND_CODE_64)
        {
            // Xop.R and Xop.X must be 1 (inverted).
            if ((Instrux->Exs.r | Instrux->Exs.x) == 1)
            {
                return ND_STATUS_INVALID_ENCODING_IN_MODE;
            }

            // Xop.V must be less than 8.
            if ((Instrux->Exs.v & 0x8) == 0x8)
            {
                return ND_STATUS_INVALID_ENCODING_IN_MODE;
            }

            // Xop.B is ignored, so we force it to 0.
            Instrux->Exs.b = 0;
        }

        // Update Instrux length & offset, and make sure we don't exceed 15 bytes.
        Instrux->Length += 3;
        if (Instrux->Length > ND_MAX_INSTRUCTION_LENGTH)
        {
            return ND_STATUS_INSTRUCTION_TOO_LONG;
        }
    }

    return ND_STATUS_SUCCESS;
}


//
// NdFetchVex2
//
static NDSTATUS
NdFetchVex2(
    INSTRUX *Instrux,
    const ND_UINT8 *Code,
    ND_UINT8 Offset,
    ND_SIZET Size
    )
{
    // One more byte has to follow, the modrm or the second VEX byte.
    RET_GT((ND_SIZET)Offset + 2, Size, ND_STATUS_BUFFER_TOO_SMALL);

    // VEX is available only in 32 & 64 bit mode.
    if ((ND_CODE_64 == Instrux->DefCode) || ((Code[Offset + 1] & 0xC0) == 0xC0))
    {
        // Make sure we don't have any other prefix.
        if (Instrux->HasOpSize || Instrux->HasRepnzXacquireBnd ||
            Instrux->HasRepRepzXrelease || Instrux->HasRex || Instrux->HasLock)
        {
            return ND_STATUS_VEX_WITH_PREFIX;
        }

        // Fill in VEX2 info.
        Instrux->VexMode = ND_VEXM_2B;
        Instrux->HasVex = ND_TRUE;
        Instrux->EncMode = ND_ENCM_VEX;
        Instrux->Vex2.Vex[0] = Code[Offset];
        Instrux->Vex2.Vex[1] = Code[Offset + 1];

        Instrux->Exs.m = 1; // For VEX2 instructions, always use the second table.
        Instrux->Exs.r = ~Instrux->Vex2.r;
        Instrux->Exs.v = ~Instrux->Vex2.v;
        Instrux->Exs.l = Instrux->Vex2.l;
        Instrux->Exs.p = Instrux->Vex2.p;

        // Update Instrux length & offset, and make sure we don't exceed 15 bytes.
        Instrux->Length += 2;
        if (Instrux->Length > ND_MAX_INSTRUCTION_LENGTH)
        {
            return ND_STATUS_INSTRUCTION_TOO_LONG;
        }
    }

    return ND_STATUS_SUCCESS;
}


//
// NdFetchVex3
//
static NDSTATUS
NdFetchVex3(
    INSTRUX *Instrux,
    const ND_UINT8 *Code,
    ND_UINT8 Offset,
    ND_SIZET Size
    )
{
    // One more byte has to follow, the modrm or the second VEX byte.
    RET_GT((ND_SIZET)Offset + 2, Size, ND_STATUS_BUFFER_TOO_SMALL);

    // VEX is available only in 32 & 64 bit mode.
    if ((ND_CODE_64 == Instrux->DefCode) || ((Code[Offset + 1] & 0xC0) == 0xC0))
    {
        // VEX found, make sure the third byte is here.
        RET_GT((ND_SIZET)Offset + 3, Size, ND_STATUS_BUFFER_TOO_SMALL);

        // Make sure we don't have any other prefix.
        if (Instrux->HasOpSize || Instrux->HasRepnzXacquireBnd ||
            Instrux->HasRepRepzXrelease || Instrux->HasRex || Instrux->HasLock)
        {
            return ND_STATUS_VEX_WITH_PREFIX;
        }

        // Fill in XOP info.
        Instrux->VexMode = ND_VEXM_3B;
        Instrux->HasVex = ND_TRUE;
        Instrux->EncMode = ND_ENCM_VEX;
        Instrux->Vex3.Vex[0] = Code[Offset];
        Instrux->Vex3.Vex[1] = Code[Offset + 1];
        Instrux->Vex3.Vex[2] = Code[Offset + 2];

        Instrux->Exs.r = ~Instrux->Vex3.r;
        Instrux->Exs.x = ~Instrux->Vex3.x;
        Instrux->Exs.b = ~Instrux->Vex3.b;
        Instrux->Exs.m = Instrux->Vex3.m;
        Instrux->Exs.w = Instrux->Vex3.w;
        Instrux->Exs.v = ~Instrux->Vex3.v;
        Instrux->Exs.l = Instrux->Vex3.l;
        Instrux->Exs.p = Instrux->Vex3.p;

        // Do validations in case of VEX outside 64 bits.
        if (Instrux->DefCode != ND_CODE_64)
        {
            // Vex.R and Vex.X have been tested by the initial if.

            // Vex.vvvv must be less than 8.
            Instrux->Exs.v &= 7;

            // Vex.B is ignored, so we force it to 0.
            Instrux->Exs.b = 0;
        }

        // Update Instrux length & offset, and make sure we don't exceed 15 bytes.
        Instrux->Length += 3;
        if (Instrux->Length > ND_MAX_INSTRUCTION_LENGTH)
        {
            return ND_STATUS_INSTRUCTION_TOO_LONG;
        }
    }

    return ND_STATUS_SUCCESS;
}


//
// NdFetchEvex
//
static NDSTATUS
NdFetchEvex(
    INSTRUX *Instrux,
    const ND_UINT8 *Code,
    ND_UINT8 Offset,
    ND_SIZET Size
    )
{
    // One more byte has to follow, the modrm or the second VEX byte.
    RET_GT((ND_SIZET)Offset + 2, Size, ND_STATUS_BUFFER_TOO_SMALL);

    if ((ND_CODE_64 != Instrux->DefCode) && ((Code[Offset + 1] & 0xC0) != 0xC0))
    {
        // BOUND instruction in non-64 bit mode, not EVEX.
        return ND_STATUS_SUCCESS;
    }

    // EVEX found, make sure all the bytes are present. At least 4 bytes in total must be present.
    RET_GT((ND_SIZET)Offset + 4, Size, ND_STATUS_BUFFER_TOO_SMALL);

    // This is EVEX.
    Instrux->HasEvex = ND_TRUE;
    Instrux->EncMode = ND_ENCM_EVEX;
    Instrux->Evex.Evex[0] = Code[Offset + 0];
    Instrux->Evex.Evex[1] = Code[Offset + 1];
    Instrux->Evex.Evex[2] = Code[Offset + 2];
    Instrux->Evex.Evex[3] = Code[Offset + 3];

    // Legacy prefixes are not accepted with EVEX.
    if (Instrux->HasOpSize || Instrux->HasRepnzXacquireBnd || Instrux->HasRepRepzXrelease || Instrux->HasRex)
    {
        return ND_STATUS_EVEX_WITH_PREFIX;
    }

    // Do the opcode independent checks. Opcode dependent checks are done when decoding each instruction.
    if (Instrux->Evex.zero != 0 || Instrux->Evex.one != 1 || Instrux->Evex.m == 0)
    {
        return ND_STATUS_INVALID_ENCODING;
    }

    // Fill in the generic extension bits
    Instrux->Exs.r = ~Instrux->Evex.r;
    Instrux->Exs.x = ~Instrux->Evex.x;
    Instrux->Exs.b = ~Instrux->Evex.b;
    Instrux->Exs.rp = ~Instrux->Evex.rp;
    Instrux->Exs.m = Instrux->Evex.m;
    Instrux->Exs.w = Instrux->Evex.w;
    Instrux->Exs.v = ~Instrux->Evex.v;
    Instrux->Exs.vp = ~Instrux->Evex.vp;
    Instrux->Exs.p = Instrux->Evex.p;
    Instrux->Exs.z = Instrux->Evex.z;
    Instrux->Exs.l = Instrux->Evex.l;
    Instrux->Exs.bm = Instrux->Evex.bm;
    Instrux->Exs.k = Instrux->Evex.a;

    // Do EVEX validations outside 64 bits mode.
    if (ND_CODE_64 != Instrux->DefCode)
    {
        // Evex.R and Evex.X must be 1. If they're not, we have BOUND instruction. This is checked in the
        // first if. Note that they are inverted inside the Evex prefix.
        Instrux->Exs.r = 0;
        Instrux->Exs.x = 0;

        // Evex.B is ignored, so we force it to 0.
        Instrux->Exs.b = 0;

        // Evex.R' is ignored, so we force it to 0.
        Instrux->Exs.rp = 0;

        // High bit inside Evex.VVVV is ignored, so we force it to 0.
        Instrux->Exs.v &= 0x7;

        // Evex.V' must be 1 (negated to 0) in 32-bit mode.
        if (Instrux->Exs.vp == 1)
        {
            return ND_STATUS_BAD_EVEX_V_PRIME;
        }
    }

    // Update Instrux length & offset, and make sure we don't exceed 15 bytes.
    Instrux->Length += 4;
    if (Instrux->Length > ND_MAX_INSTRUCTION_LENGTH)
    {
        return ND_STATUS_INSTRUCTION_TOO_LONG;
    }

    return ND_STATUS_SUCCESS;
}


//
// NdFetchPrefixes
//
static NDSTATUS
NdFetchPrefixes(
    INSTRUX *Instrux,
    const ND_UINT8 *Code,
    ND_UINT8 Offset,
    ND_SIZET Size
    )
{
    NDSTATUS status;
    ND_BOOL morePrefixes;
    ND_UINT8 prefix;

    morePrefixes = ND_TRUE;

    while (morePrefixes)
    {
        morePrefixes = ND_FALSE;

        RET_GT((ND_SIZET)Offset + 1, Size, ND_STATUS_BUFFER_TOO_SMALL);

        prefix = Code[Offset];

        // Speedup: if the current byte is not a prefix of any kind, leave now. This will be the case most of the times.
        if (ND_PREF_CODE_NONE == gPrefixesMap[prefix])
        {
            status = ND_STATUS_SUCCESS;
            goto done_prefixes;
        }

        if (ND_PREF_CODE_STANDARD == gPrefixesMap[prefix])
        {
            switch (prefix)
            {
            case ND_PREFIX_G0_LOCK:
                Instrux->HasLock = ND_TRUE;
                morePrefixes = ND_TRUE;
                break;
            case ND_PREFIX_G1_REPE_REPZ:
                Instrux->Rep = ND_PREFIX_G1_REPE_REPZ;
                Instrux->HasRepRepzXrelease = ND_TRUE;
                morePrefixes = ND_TRUE;
                break;
            case ND_PREFIX_G1_REPNE_REPNZ:
                Instrux->Rep = ND_PREFIX_G1_REPNE_REPNZ;
                Instrux->HasRepnzXacquireBnd = ND_TRUE;
                morePrefixes = ND_TRUE;
                break;
            case ND_PREFIX_G2_SEG_CS:
            case ND_PREFIX_G2_SEG_SS:
            case ND_PREFIX_G2_SEG_DS:
            case ND_PREFIX_G2_SEG_ES:
            case ND_PREFIX_G2_SEG_FS:
            case ND_PREFIX_G2_SEG_GS:
                if (ND_CODE_64 == Instrux->DefCode)
                {
                    if (prefix == ND_PREFIX_G2_SEG_FS || 
                        prefix == ND_PREFIX_G2_SEG_GS)
                    {
                        // The last FS/GS is always used, if present.
                        Instrux->Seg = prefix;
                        Instrux->HasSeg = ND_TRUE;
                    }
                    else if (prefix == ND_PREFIX_G2_NO_TRACK && 
                        Instrux->Seg != ND_PREFIX_G2_SEG_FS &&
                        Instrux->Seg != ND_PREFIX_G2_SEG_GS)
                    {
                        // The Do Not Track prefix is considered only if there isn't a FS/GS prefix.
                        Instrux->Seg = prefix;
                        Instrux->HasSeg = ND_TRUE;
                    }
                    else if (Instrux->Seg != ND_PREFIX_G2_SEG_FS && 
                        Instrux->Seg != ND_PREFIX_G2_SEG_GS &&
                        Instrux->Seg != ND_PREFIX_G2_NO_TRACK)
                    {
                        // All other prefixes are considered if Do Not Track, FS, GS are not present.
                        Instrux->Seg = prefix;
                        Instrux->HasSeg = ND_TRUE;
                    }
                }
                else
                {
                    Instrux->Seg = prefix;
                    Instrux->HasSeg = ND_TRUE;
                }
                morePrefixes = ND_TRUE;
                break;
            case ND_PREFIX_G3_OPERAND_SIZE:
                Instrux->HasOpSize = ND_TRUE;
                morePrefixes = ND_TRUE;
                break;
            case ND_PREFIX_G4_ADDR_SIZE:
                Instrux->HasAddrSize = ND_TRUE;
                morePrefixes = ND_TRUE;
                break;
            default:
                break;
            }
        }

        // REX must precede the opcode byte. However, if one or more other prefixes are present, the instruction
        // will still decode & execute properly, but REX will be ignored.
        if (morePrefixes && Instrux->HasRex)
        {
            Instrux->HasRex = ND_FALSE;
            Instrux->Rex.Rex = 0;
            Instrux->Exs.w = 0;
            Instrux->Exs.r = 0;
            Instrux->Exs.x = 0;
            Instrux->Exs.b = 0;
        }

        // Check for REX.
        if ((ND_CODE_64 == Instrux->DefCode) && (ND_PREF_CODE_REX == gPrefixesMap[prefix]))
        {
            Instrux->HasRex = ND_TRUE;
            Instrux->Rex.Rex = prefix;
            Instrux->Exs.w = Instrux->Rex.w;
            Instrux->Exs.r = Instrux->Rex.r;
            Instrux->Exs.x = Instrux->Rex.x;
            Instrux->Exs.b = Instrux->Rex.b;
            morePrefixes = ND_TRUE;
        }

        // We have found prefixes, update the instruction length and the current offset.
        if (morePrefixes)
        {
            Instrux->Length++, Offset++;
            if (Instrux->Length > ND_MAX_INSTRUCTION_LENGTH)
            {
                return ND_STATUS_INSTRUCTION_TOO_LONG;
            }
        }
    }

    // We must have at least one more free byte after the prefixes, which will be either the opcode, either
    // XOP/VEX/EVEX/MVEX prefix.
    RET_GT((ND_SIZET)Offset + 1, Size, ND_STATUS_BUFFER_TOO_SMALL);

    // Try to match a XOP/VEX/EVEX/MVEX prefix.
    if (ND_PREF_CODE_EX == gPrefixesMap[Code[Offset]])
    {
        // Check for XOP
        if (Code[Offset] == ND_PREFIX_XOP)
        {
            status = NdFetchXop(Instrux, Code, Offset, Size);
            if (!ND_SUCCESS(status))
            {
                return status;
            }
        }
        else if (Code[Offset] == ND_PREFIX_VEX_2B)
        {
            status = NdFetchVex2(Instrux, Code, Offset, Size);
            if (!ND_SUCCESS(status))
            {
                return status;
            }
        }
        else if (Code[Offset] == ND_PREFIX_VEX_3B)
        {
            status = NdFetchVex3(Instrux, Code, Offset, Size);
            if (!ND_SUCCESS(status))
            {
                return status;
            }
        }
        else if (Code[Offset] == ND_PREFIX_EVEX)
        {
            status = NdFetchEvex(Instrux, Code, Offset, Size);
            if (!ND_SUCCESS(status))
            {
                return status;
            }
        }
        else
        {
            return ND_STATUS_INVALID_INSTRUX;
        }
    }
    else
    {
        Instrux->EncMode = ND_ENCM_LEGACY;
    }

done_prefixes:
    // The total length of the instruction is the total length of the prefixes right now.
    Instrux->PrefLength = Instrux->OpOffset = Instrux->Length;

    return ND_STATUS_SUCCESS;
}


//
// NdFetchOpcode
//
static NDSTATUS
NdFetchOpcode(
    INSTRUX *Instrux,
    const ND_UINT8 *Code,
    ND_UINT8 Offset,
    ND_SIZET Size
    )
{
    // At least one byte must be available, for the fetched opcode.
    RET_GT((ND_SIZET)Offset + 1, Size, ND_STATUS_BUFFER_TOO_SMALL);

    Instrux->OpCodeBytes[Instrux->OpLength++] = Code[Offset];

    Instrux->Length++;
    if (Instrux->Length > ND_MAX_INSTRUCTION_LENGTH)
    {
        return ND_STATUS_INSTRUCTION_TOO_LONG;
    }

    return ND_STATUS_SUCCESS;
}


//
// NdFetchModrm
//
static NDSTATUS
NdFetchModrm(
    INSTRUX *Instrux,
    const ND_UINT8 *Code,
    ND_UINT8 Offset,
    ND_SIZET Size
    )
{
    // At least one byte must be available, for the modrm byte.
    RET_GT((ND_SIZET)Offset + 1, Size, ND_STATUS_BUFFER_TOO_SMALL);

    // If we get called, we assume we have ModRM.
    Instrux->HasModRm = ND_TRUE;

    // Fetch the ModRM byte & update the offset and the instruction length.
    Instrux->ModRm.ModRm = Code[Offset];
    Instrux->ModRmOffset = Offset;

    Instrux->Length++, Offset++;

    // Make sure we don't exceed the maximum instruction length.
    if (Instrux->Length > ND_MAX_INSTRUCTION_LENGTH)
    {
        return ND_STATUS_INSTRUCTION_TOO_LONG;
    }

    return ND_STATUS_SUCCESS;
}


//
// NdFetchModrmAndSib
//
static NDSTATUS
NdFetchModrmAndSib(
    INSTRUX *Instrux,
    const ND_UINT8 *Code,
    ND_UINT8 Offset,
    ND_SIZET Size
    )
{
    // At least one byte must be available, for the modrm byte.
    RET_GT((ND_SIZET)Offset + 1, Size, ND_STATUS_BUFFER_TOO_SMALL);

    // If we get called, we assume we have ModRM.
    Instrux->HasModRm = ND_TRUE;

    // Fetch the ModRM byte & update the offset and the instruction length.
    Instrux->ModRm.ModRm = Code[Offset];
    Instrux->ModRmOffset = Offset;

    Instrux->Length++, Offset++;

    // Make sure we don't exceed the maximum instruction length.
    if (Instrux->Length > ND_MAX_INSTRUCTION_LENGTH)
    {
        return ND_STATUS_INSTRUCTION_TOO_LONG;
    }

    // If needed, fetch the SIB.
    if ((Instrux->ModRm.rm == NDR_RSP) && (Instrux->ModRm.mod != 3) && (Instrux->AddrMode != ND_ADDR_16))
    {
        // At least one more byte must be available, for the sib.
        RET_GT((ND_SIZET)Offset + 1, Size, ND_STATUS_BUFFER_TOO_SMALL);

        // SIB present.
        Instrux->HasSib = ND_TRUE;

        Instrux->Sib.Sib = Code[Offset];
        Instrux->Length++;

        // Make sure we don't exceed the maximum instruction length.
        if (Instrux->Length > ND_MAX_INSTRUCTION_LENGTH)
        {
            return ND_STATUS_INSTRUCTION_TOO_LONG;
        }
    }

    return ND_STATUS_SUCCESS;
}


//
// NdFetchDisplacement
//
static NDSTATUS
NdFetchDisplacement(
    INSTRUX *Instrux,
    const ND_UINT8 *Code,
    ND_UINT8 Offset,
    ND_SIZET Size
    )
//
// Will decode the displacement from the instruction. Will fill in extracted information in Instrux,
// and will update the instruction length.
//
{
    ND_UINT8 displSize;

    displSize = 0;

    if (ND_ADDR_16 == Instrux->AddrMode)
    {
        displSize = gDispsizemap16[Instrux->ModRm.mod][Instrux->ModRm.rm];
    }
    else
    {
        displSize = gDispsizemap[Instrux->ModRm.mod][Instrux->HasSib ? Instrux->Sib.base : Instrux->ModRm.rm];
    }

    if (0 != displSize)
    {
        static const ND_UINT32 signMask[4] = { 0x80, 0x8000, 0, 0x80000000 };

        // Make sure enough buffer space is available.
        RET_GT((ND_SIZET)Offset + displSize, Size, ND_STATUS_BUFFER_TOO_SMALL);

        // If we get here, we have displacement.
        Instrux->HasDisp = ND_TRUE;

        Instrux->Displacement = (ND_UINT32)NdFetchData(Code + Offset, displSize);
        Instrux->SignDisp = (Instrux->Displacement & signMask[displSize - 1]) ? ND_TRUE : ND_FALSE;

        // Fill in displacement info.
        Instrux->DispLength = displSize;
        Instrux->DispOffset = Offset;
        Instrux->Length += displSize;
        if (Instrux->Length > ND_MAX_INSTRUCTION_LENGTH)
        {
            return ND_STATUS_INSTRUCTION_TOO_LONG;
        }
    }

    return ND_STATUS_SUCCESS;
}


//
// NdFetchAddress
//
static NDSTATUS
NdFetchAddress(
    INSTRUX *Instrux,
    const ND_UINT8 *Code,
    ND_UINT8 Offset,
    ND_SIZET Size,
    ND_UINT8 AddressSize
    )
{
    //. Make sure the
    RET_GT((ND_SIZET)Offset + AddressSize, Size, ND_STATUS_BUFFER_TOO_SMALL);

    Instrux->HasAddr = ND_TRUE;
    Instrux->AddrLength = AddressSize;
    Instrux->AddrOffset = Offset;

    Instrux->Address.Ip = (ND_UINT32)NdFetchData(Code + Offset, Instrux->AddrLength - 2);
    Instrux->Address.Cs = (ND_UINT16)NdFetchData(Code + Offset + Instrux->AddrLength - 2, 2);

    Instrux->Length += Instrux->AddrLength;
    if (Instrux->Length > ND_MAX_INSTRUCTION_LENGTH)
    {
        return ND_STATUS_INSTRUCTION_TOO_LONG;
    }

    return ND_STATUS_SUCCESS;
}


//
// NdFetchImmediate
//
static NDSTATUS
NdFetchImmediate(
    INSTRUX *Instrux,
    const ND_UINT8 *Code,
    ND_UINT8 Offset,
    ND_SIZET Size,
    ND_UINT8 ImmediateSize
    )
{
    ND_UINT64 imm;

    RET_GT((ND_SIZET)Offset + ImmediateSize, Size, ND_STATUS_BUFFER_TOO_SMALL);

    imm = NdFetchData(Code + Offset, ImmediateSize);

    if (Instrux->HasImm2)
    {
        Instrux->HasImm3 = ND_TRUE;
        Instrux->Imm3Length = ImmediateSize;
        Instrux->Imm3Offset = Offset;
        Instrux->Immediate3 = (ND_UINT8)imm;
    }
    else if (Instrux->HasImm1)
    {
        Instrux->HasImm2 = ND_TRUE;
        Instrux->Imm2Length = ImmediateSize;
        Instrux->Imm2Offset = Offset;
        Instrux->Immediate2 = (ND_UINT8)imm;
    }
    else
    {
        Instrux->HasImm1 = ND_TRUE;
        Instrux->Imm1Length = ImmediateSize;
        Instrux->Imm1Offset = Offset;
        Instrux->Immediate1 = imm;
    }

    Instrux->Length += ImmediateSize;
    if (Instrux->Length > ND_MAX_INSTRUCTION_LENGTH)
    {
        return ND_STATUS_INSTRUCTION_TOO_LONG;
    }

    return ND_STATUS_SUCCESS;
}


//
// NdFetchRelativeOffset
//
static NDSTATUS
NdFetchRelativeOffset(
    INSTRUX *Instrux,
    const ND_UINT8 *Code,
    ND_UINT8 Offset,
    ND_SIZET Size,
    ND_UINT8 RelOffsetSize
    )
{
    // Make sure we don't outrun the buffer.
    RET_GT((ND_SIZET)Offset + RelOffsetSize, Size, ND_STATUS_BUFFER_TOO_SMALL);

    Instrux->HasRelOffs = ND_TRUE;
    Instrux->RelOffsLength = RelOffsetSize;
    Instrux->RelOffsOffset = Offset;

    Instrux->RelativeOffset = (ND_UINT32)NdFetchData(Code + Offset, RelOffsetSize);

    Instrux->Length += RelOffsetSize;
    if (Instrux->Length > ND_MAX_INSTRUCTION_LENGTH)
    {
        return ND_STATUS_INSTRUCTION_TOO_LONG;
    }

    return ND_STATUS_SUCCESS;
}


//
// NdFetchMoffset
//
static NDSTATUS
NdFetchMoffset(
    INSTRUX *Instrux,
    const ND_UINT8 *Code,
    ND_UINT8 Offset,
    ND_SIZET Size,
    ND_UINT8 MoffsetSize
    )
{
    RET_GT((ND_SIZET)Offset + MoffsetSize, Size, ND_STATUS_BUFFER_TOO_SMALL);

    Instrux->HasMoffset = ND_TRUE;
    Instrux->MoffsetLength = MoffsetSize;
    Instrux->MoffsetOffset = Offset;

    Instrux->Moffset = NdFetchData(Code + Offset, MoffsetSize);

    Instrux->Length += MoffsetSize;
    if (Instrux->Length > ND_MAX_INSTRUCTION_LENGTH)
    {
        return ND_STATUS_INSTRUCTION_TOO_LONG;
    }

    return ND_STATUS_SUCCESS;
}


//
// NdFetchSseImmediate
//
static NDSTATUS
NdFetchSseImmediate(
    INSTRUX *Instrux,
    const ND_UINT8 *Code,
    ND_UINT8 Offset,
    ND_SIZET Size,
    ND_UINT8 SseImmSize
    )
{
    RET_GT((ND_SIZET)Offset + SseImmSize, Size, ND_STATUS_BUFFER_TOO_SMALL);

    Instrux->HasSseImm = ND_TRUE;
    Instrux->SseImmOffset = Offset;
    Instrux->SseImmediate = *(Code + Offset);

    Instrux->Length += SseImmSize;
    if (Instrux->Length > ND_MAX_INSTRUCTION_LENGTH)
    {
        return ND_STATUS_INSTRUCTION_TOO_LONG;
    }

    return ND_STATUS_SUCCESS;
}


//
// NdGetSegOverride
//
static ND_UINT8
NdGetSegOverride(
    INSTRUX *Instrux,
    ND_UINT8 DefaultSeg
    )
{
    // In 64 bit mode, the segment override is ignored, except for FS and GS.
    if ((Instrux->DefCode == ND_CODE_64) &&
        (Instrux->Seg != ND_PREFIX_G2_SEG_FS) &&
        (Instrux->Seg != ND_PREFIX_G2_SEG_GS))
    {
        return DefaultSeg;
    }

    switch (Instrux->Seg)
    {
    case ND_PREFIX_G2_SEG_CS:
        return NDR_CS;
    case ND_PREFIX_G2_SEG_DS:
        return NDR_DS;
    case ND_PREFIX_G2_SEG_ES:
        return NDR_ES;
    case ND_PREFIX_G2_SEG_SS:
        return NDR_SS;
    case ND_PREFIX_G2_SEG_FS:
        return NDR_FS;
    case ND_PREFIX_G2_SEG_GS:
        return NDR_GS;
    default:
        return DefaultSeg;
    }
}


//
// NdGetCompDispSize
//
static ND_UINT8
NdGetCompDispSize(
    const INSTRUX *Instrux,
    ND_UINT32 MemSize
    )
{
    static const ND_UINT8 fvszLut[4] = { 16, 32, 64, 0 };
    static const ND_UINT8 hvszLut[4] = { 8, 16, 32, 0 };
    static const ND_UINT8 qvszLut[4] = { 4, 8, 16, 0 };
    static const ND_UINT8 dupszLut[4] = { 8, 32, 64, 0 };
    static const ND_UINT8 fvmszLut[4] = { 16, 32, 64, 0 };
    static const ND_UINT8 hvmszLut[4] = { 8, 16, 32, 0 };
    static const ND_UINT8 qvmszLut[4] = { 4, 8, 16, 0 };
    static const ND_UINT8 ovmszLut[4] = { 2, 4, 8, 0 };

    if (Instrux->HasBroadcast)
    {
        // If the instruction uses broadcast, then compressed displacement will use the size of the element as scale:
        // - 2 when broadcasting 16 bit
        // - 4 when broadcasting 32 bit
        // - 8 when broadcasting 64 bit
        return (ND_UINT8)MemSize;
    }

    switch (Instrux->TupleType)
    {
    case ND_TUPLE_FV:
        return fvszLut[Instrux->Exs.l];
    case ND_TUPLE_HV:
        return hvszLut[Instrux->Exs.l];
    case ND_TUPLE_QV:
        return qvszLut[Instrux->Exs.l];
    case ND_TUPLE_DUP:
        return dupszLut[Instrux->Exs.l];
    case ND_TUPLE_FVM:
        return fvmszLut[Instrux->Exs.l];
    case ND_TUPLE_HVM:
        return hvmszLut[Instrux->Exs.l];
    case ND_TUPLE_QVM:
        return qvmszLut[Instrux->Exs.l];
    case ND_TUPLE_OVM:
        return ovmszLut[Instrux->Exs.l];
    case ND_TUPLE_M128:
        return 16;
    case ND_TUPLE_T1S8:
        return 1;
    case ND_TUPLE_T1S16:
        return 2;
    case ND_TUPLE_T1S:
        return !!(Instrux->Attributes & ND_FLAG_WIG) ? 4 : Instrux->Exs.w ? 8 : 4;
    case ND_TUPLE_T1F:
        return (ND_UINT8)MemSize;
    case ND_TUPLE_T2:
        return Instrux->Exs.w ? 16 : 8;
    case ND_TUPLE_T4:
        return Instrux->Exs.w ? 32 : 16;
    case ND_TUPLE_T8:
        return 32;
    case ND_TUPLE_T1_4X:
        return 16;
    default:
        // Default - we assume byte granularity for memory accesses, therefore, no scaling will be done.
        return 1;
    }
}


//
// NdParseOperand
//
static NDSTATUS
NdParseOperand(
    INSTRUX *Instrux,
    const ND_UINT8 *Code,
    ND_UINT8 Offset,
    ND_SIZET Size,
    ND_UINT32 Index,
    ND_UINT64 Specifier
    )
{
    NDSTATUS status;
    PND_OPERAND operand;
    ND_UINT8 opt, ops, opf, opa, opd, opb;
    ND_REG_SIZE vsibRegSize;
    ND_UINT8 vsibIndexSize, vsibIndexCount;
    ND_OPERAND_SIZE size, bcstSize;
    ND_BOOL width;

    // pre-init
    status = ND_STATUS_SUCCESS;
    vsibRegSize = 0;
    vsibIndexSize = vsibIndexCount = 0;
    size = bcstSize = 0;

    // Get actual width.
    width = Instrux->Exs.w && !(Instrux->Attributes & ND_FLAG_WIG);

    // Get operand components.
    opt = ND_OP_TYPE(Specifier);
    ops = ND_OP_SIZE(Specifier);
    opf = ND_OP_FLAGS(Specifier);
    opa = ND_OP_ACCESS(Specifier);
    opd = ND_OP_DECORATORS(Specifier);
    opb = ND_OP_BLOCK(Specifier);

    // Get a pointer to our op.
    operand = &Instrux->Operands[Index];

    // Fill in the flags.
    operand->Flags.Flags = opf;

    // Store operand access modes.
    operand->Access.Access = opa;


    //
    // Fill in operand size.
    //
    switch (ops)
    {
    case ND_OPS_asz:
        // Size given by the address mode.
        size = 2 << Instrux->AddrMode;
        break;

    case ND_OPS_ssz:
        // Size given by the stack mode.
        size = 2 << Instrux->DefStack;
        break;

    case ND_OPS_0:
        // No memory access. 0 operand size.
        size = 0;
        break;

    case ND_OPS_b:
        // Byte, regardless of operand-size attribute.
        size = ND_SIZE_8BIT;
        break;

    case ND_OPS_w:
        // Word, regardless of operand-size attribute.
        size = ND_SIZE_16BIT;
        break;

    case ND_OPS_d:
        // Dword, regardless of operand-size attribute.
        size = ND_SIZE_32BIT;
        break;

    case ND_OPS_q:
        // Qword, regardless of operand-size attribute.
        size = ND_SIZE_64BIT;
        break;

    case ND_OPS_dq:
        // Double-Qword, regardless of operand-size attribute.
        size = ND_SIZE_128BIT;
        break;

    case ND_OPS_qq:
        // Quad-Quadword (256-bits), regardless of operand-size attribute.
        size = ND_SIZE_256BIT;
        break;

    case ND_OPS_oq:
        // Octo-Quadword (512-bits), regardless of operand-size attribute.
        size = ND_SIZE_512BIT;
        break;

    case ND_OPS_fa:
        // 80 bits packed BCD.
        size = ND_SIZE_80BIT;
        break;

    case ND_OPS_fw:
        // 16 bits real number.
        size = ND_SIZE_16BIT;
        break;

    case ND_OPS_fd:
        // 32 bit real number.
        size = ND_SIZE_32BIT;
        break;

    case ND_OPS_fq:
        // 64 bit real number.
        size = ND_SIZE_64BIT;
        break;

    case ND_OPS_ft:
        // 80 bit real number.
        size = ND_SIZE_80BIT;
        break;

    case ND_OPS_fe:
        // 14 bytes or 28 bytes FPU environment.
        size = (Instrux->EfOpMode == ND_OPSZ_16) ? ND_SIZE_112BIT : ND_SIZE_224BIT;
        break;

    case ND_OPS_fs:
        // 94 bytes or 108 bytes FPU state.
        size = (Instrux->EfOpMode == ND_OPSZ_16) ? ND_SIZE_752BIT : ND_SIZE_864BIT;
        break;

    case ND_OPS_rx:
        // 512 bytes extended state.
        size = ND_SIZE_4096BIT;
        break;

    case ND_OPS_cl:
        // The size of one cache line.
        size = ND_SIZE_CACHE_LINE;
        break;

    case ND_OPS_v:
        // Word, doubleword or quadword (in 64-bit mode), depending on operand-size attribute.
        {
            static const ND_UINT8 szLut[3] = { ND_SIZE_16BIT, ND_SIZE_32BIT, ND_SIZE_64BIT };

            size = szLut[Instrux->EfOpMode];
        }
        break;

    case ND_OPS_y:
        // Doubleword or quadword (in 64-bit mode), depending on operand-size attribute.
        {
            static const ND_UINT8 szLut[3] = { ND_SIZE_32BIT, ND_SIZE_32BIT, ND_SIZE_64BIT };

            size = szLut[Instrux->EfOpMode];
        }
        break;

    case ND_OPS_yf:
        // Always ND_UINT64 in 64 bit mode and ND_UINT32 in 16/32 bit mode.
        {
            static const ND_UINT8 szLut[3] = { ND_SIZE_32BIT, ND_SIZE_32BIT, ND_SIZE_64BIT };

            size = szLut[Instrux->DefCode];
        }
        break;

    case ND_OPS_z:
        // Word for 16-bit operand-size or double word for 32 or 64-bit operand-size.
        {
            static const ND_UINT8 szLut[3] = { ND_SIZE_16BIT, ND_SIZE_32BIT, ND_SIZE_32BIT };

            size = szLut[Instrux->EfOpMode];
        }
        break;

    case ND_OPS_a:
        // Two one-word operands in memory or two double-word operands in memory,
        // depending on operand-size attribute (used only by the BOUND instruction).
        {
            static const ND_UINT8 szLut[3] = { ND_SIZE_16BIT * 2, ND_SIZE_32BIT * 2, 0 };

            if (Instrux->DefCode > ND_CODE_32)
            {
                return ND_STATUS_INVALID_INSTRUX;
            }

            size = szLut[Instrux->EfOpMode];
        }
        break;

    case ND_OPS_c:
        // Byte or word, depending on operand-size attribute.
        switch (Instrux->DefCode)
        {
        case ND_CODE_16:
            size = Instrux->HasOpSize ? ND_SIZE_16BIT : ND_SIZE_8BIT;
            break;
        case ND_CODE_32:
            size = Instrux->HasOpSize ? ND_SIZE_16BIT : ND_SIZE_32BIT;
            break;
        case ND_CODE_64:
            size = ND_SIZE_64BIT;
            break;
        default:
            return ND_STATUS_INVALID_INSTRUX;
        }
        break;

    case ND_OPS_p:
        // 32-bit, 48-bit, or 80-bit pointer, depending on operand-size attribute.
        {
            static const ND_UINT8 szLut[3] = { ND_SIZE_32BIT, ND_SIZE_48BIT, ND_SIZE_80BIT };

            size = szLut[Instrux->EfOpMode];
        }
        break;

    case ND_OPS_s:
        // 6-byte or 10-byte pseudo-descriptor.
        {
            static const ND_UINT8 szLut[3] = { ND_SIZE_48BIT, ND_SIZE_48BIT, ND_SIZE_80BIT };

            size = szLut[Instrux->DefCode];
        }
        break;

    case ND_OPS_l:
        // 64 bit in 16 or 32 bit mode, 128 bit in long mode. Used by BNDMOV instruction.
        {
            static const ND_UINT8 szLut[3] = { ND_SIZE_64BIT, ND_SIZE_64BIT, ND_SIZE_128BIT };

            size = szLut[Instrux->DefCode];
        }
        break;

    case ND_OPS_x:
        // dq, qq or oq based on the operand-size attribute.
        {
            static const ND_UINT8 szLut[3] = { ND_SIZE_128BIT, ND_SIZE_256BIT, ND_SIZE_512BIT };

            size = szLut[Instrux->EfVecMode];
        }
        break;

    case ND_OPS_n:
        // 128, 256 or 512 bit, depending on vector length.
        {
            static const ND_UINT8 szLut[3] = { ND_SIZE_128BIT, ND_SIZE_256BIT, ND_SIZE_512BIT };

            size = szLut[Instrux->EfVecMode];
        }
        break;

    case ND_OPS_u:
        // 256 or 512 bit, depending on vector length.
        {
            static const ND_UINT8 szLut[3] = { 0, ND_SIZE_256BIT, ND_SIZE_512BIT };

            if (ND_VECM_128 == Instrux->EfVecMode)
            {
                return ND_STATUS_INVALID_INSTRUX;
            }

            size = szLut[Instrux->EfVecMode];
        }
        break;

    case ND_OPS_e:
        // eighth = word or dword or qword
        {
            static const ND_UINT8 szLut[3] = { ND_SIZE_16BIT, ND_SIZE_32BIT, ND_SIZE_64BIT };

            size = szLut[Instrux->EfVecMode];
        }
        break;

    case ND_OPS_f:
        // fourth = dword or qword or oword
        {
            static const ND_UINT8 szLut[3] = { ND_SIZE_32BIT, ND_SIZE_64BIT, ND_SIZE_128BIT };

            size = szLut[Instrux->EfVecMode];
        }
        break;

    case ND_OPS_h:
        // half = qword or oword or yword
        {
            static const ND_UINT8 szLut[3] = { ND_SIZE_64BIT, ND_SIZE_128BIT, ND_SIZE_256BIT };

            size = szLut[Instrux->EfVecMode];
        }
        break;

    case ND_OPS_pd:
    case ND_OPS_ps:
    case ND_OPS_ph:
        // packed double or packed single or packed FP16 values.
        {
            static const ND_UINT8 szLut[3] = { ND_SIZE_128BIT, ND_SIZE_256BIT, ND_SIZE_512BIT };

            size = szLut[Instrux->EfVecMode];
        }
        break;

    case ND_OPS_sd:
        // Scalar double.
        size = ND_SIZE_64BIT;
        break;

    case ND_OPS_ss:
        // Scalar single.
        size = ND_SIZE_32BIT;
        break;

    case ND_OPS_sh:
        // Scalar FP16.
        size = ND_SIZE_16BIT;
        break;

    case ND_OPS_mib:
        // MIB addressing, used by MPX instructions.
        size = 0;
        break;

    case ND_OPS_vm32x:
    case ND_OPS_vm32y:
    case ND_OPS_vm32z:
        // 32 bit indexes from XMM, YMM or ZMM register.
        vsibIndexSize  = ND_SIZE_32BIT;
        vsibIndexCount = (Instrux->Exs.l == 0) ? 4 : ((Instrux->Exs.l == 1) ? 8 : 16);
        vsibRegSize = (ops == ND_OPS_vm32x) ? ND_SIZE_128BIT :
                      (ops == ND_OPS_vm32y) ? ND_SIZE_256BIT :
                                              ND_SIZE_512BIT;
        size = vsibIndexCount * (width ? ND_SIZE_64BIT : ND_SIZE_32BIT);
        break;

    case ND_OPS_vm32h:
        // 32 bit indexes from XMM or YMM.
        vsibIndexSize = ND_SIZE_32BIT;
        vsibIndexCount = (Instrux->Exs.l == 0) ? 2 : ((Instrux->Exs.l == 1) ? 4 : 8);
        vsibRegSize = (Instrux->Exs.l == 0) ? ND_SIZE_128BIT :
                      (Instrux->Exs.l == 1) ? ND_SIZE_128BIT :
                                              ND_SIZE_256BIT;
        size = vsibIndexCount * (width ? ND_SIZE_64BIT : ND_SIZE_32BIT);
        break;

    case ND_OPS_vm32n:
        // 32 bit indexes from XMM, YMM or ZMM register.
        vsibIndexSize = ND_SIZE_32BIT;
        vsibIndexCount = (Instrux->Exs.l == 0) ? 4 : ((Instrux->Exs.l == 1) ? 8 : 16);
        vsibRegSize = (Instrux->Exs.l == 0) ? ND_SIZE_128BIT :
                      (Instrux->Exs.l == 1) ? ND_SIZE_256BIT :
                                              ND_SIZE_512BIT;
        size = vsibIndexCount * (width ? ND_SIZE_64BIT : ND_SIZE_32BIT);
        break;

    case ND_OPS_vm64x:
    case ND_OPS_vm64y:
    case ND_OPS_vm64z:
        // 64 bit indexes from XMM, YMM or ZMM register.
        vsibIndexSize = ND_SIZE_64BIT;
        vsibIndexCount = (Instrux->Exs.l == 0) ? 2 : ((Instrux->Exs.l == 1) ? 4 : 8);
        vsibRegSize = (ops == ND_OPS_vm64x) ? ND_SIZE_128BIT :
                      (ops == ND_OPS_vm64y) ? ND_SIZE_256BIT :
                                              ND_SIZE_512BIT;
        size = vsibIndexCount * (width ? ND_SIZE_64BIT : ND_SIZE_32BIT);
        break;

    case ND_OPS_vm64h:
        // 64 bit indexes from XMM or YMM.
        vsibIndexSize = ND_SIZE_64BIT;
        vsibIndexCount = (Instrux->Exs.l == 0) ? 1 : ((Instrux->Exs.l == 1) ? 2 : 4);
        vsibRegSize = (Instrux->Exs.l == 0) ? ND_SIZE_128BIT :
                      (Instrux->Exs.l == 1) ? ND_SIZE_128BIT :
                                              ND_SIZE_256BIT;
        size = vsibIndexCount * (width ? ND_SIZE_64BIT : ND_SIZE_32BIT);
        break;

    case ND_OPS_vm64n:
        // 64 bit indexes from XMM, YMM or ZMM register.
        vsibIndexSize = ND_SIZE_64BIT;
        vsibIndexCount = (Instrux->Exs.l == 0) ? 2 : ((Instrux->Exs.l == 1) ? 4 : 8);
        vsibRegSize = (Instrux->Exs.l == 0) ? ND_SIZE_128BIT :
                      (Instrux->Exs.l == 1) ? ND_SIZE_256BIT :
                                              ND_SIZE_512BIT;
        size = vsibIndexCount * (width ? ND_SIZE_64BIT : ND_SIZE_32BIT);
        break;

    case ND_OPS_v2:
    case ND_OPS_v3:
    case ND_OPS_v4:
    case ND_OPS_v5:
    case ND_OPS_v8:
        // Multiple words accessed.
        {
            static const ND_UINT8 szLut[3] = { ND_SIZE_16BIT, ND_SIZE_32BIT, ND_SIZE_64BIT };
            ND_UINT8 scale = 1;

            scale = (ops == ND_OPS_v2) ? 2 : 
                    (ops == ND_OPS_v3) ? 3 : 
                    (ops == ND_OPS_v4) ? 4 : 
                    (ops == ND_OPS_v5) ? 5 : 8;

            size =  scale * szLut[Instrux->EfOpMode];
        }
        break;

    case ND_OPS_12:
        // SAVPREVSSP instruction reads/writes 4 + 8 bytes from the shadow stack.
        size = 12;
        break;

    case ND_OPS_t:
        // Tile register. The actual size depends on how the TILECFG register has been programmed, but it can be 
        // up to 1K in size.
        size = ND_SIZE_1KB;
        break;

    case ND_OPS_384:
        // 384 bit Key Locker handle.
        size = ND_SIZE_384BIT;
        break;

    case ND_OPS_512:
        // 512 bit Key Locker handle.
        size = ND_SIZE_512BIT;
        break;

    case ND_OPS_4096:
        // 64 entries x 64 bit per entry = 4096 bit MSR address/value list.
        size = ND_SIZE_4096BIT;
        break;

    case ND_OPS_unknown:
        size = ND_SIZE_UNKNOWN;
        break;

    default:
        return ND_STATUS_INVALID_INSTRUX;
    }

    // Store operand info.
    operand->Size = operand->RawSize = bcstSize = size;

    //
    // Fill in the operand type.
    //
    switch (opt)
    {
    case ND_OPT_CONST_1:
        // operand is an implicit constant (used by shift/rotate instruction).
        operand->Type = ND_OP_CONST;
        operand->Info.Constant.Const = 1;
        break;

    case ND_OPT_RIP:
        // The operand is the instruction pointer.
        operand->Type = ND_OP_REG;
        operand->Info.Register.Type = ND_REG_RIP;
        operand->Info.Register.Size = (ND_REG_SIZE)size;
        operand->Info.Register.Reg = 0;
        Instrux->RipAccess |= operand->Access.Access;
        break;

    case ND_OPT_GPR_rAX:
        // Operator is the accumulator.
        operand->Type = ND_OP_REG;
        operand->Info.Register.Type = ND_REG_GPR;
        operand->Info.Register.Size = (ND_REG_SIZE)size;
        operand->Info.Register.Reg = NDR_RAX;
        break;

    case ND_OPT_GPR_AH:
        // Operator is the accumulator.
        operand->Type = ND_OP_REG;
        operand->Info.Register.Type = ND_REG_GPR;
        operand->Info.Register.Size = ND_SIZE_8BIT;
        operand->Info.Register.Reg = NDR_AH;
        operand->Info.Register.IsHigh8 = ND_TRUE;
        break;

    case ND_OPT_GPR_rCX:
        // Operator is the counter register.
        operand->Type = ND_OP_REG;
        operand->Info.Register.Type = ND_REG_GPR;
        operand->Info.Register.Size = (ND_REG_SIZE)size;
        operand->Info.Register.Reg = NDR_RCX;
        break;

    case ND_OPT_GPR_rDX:
        // Operator is rDX.
        operand->Type = ND_OP_REG;
        operand->Info.Register.Type = ND_REG_GPR;
        operand->Info.Register.Size = (ND_REG_SIZE)size;
        operand->Info.Register.Reg = NDR_RDX;
        break;

    case ND_OPT_GPR_rBX:
        // Operator is BX.
        operand->Type = ND_OP_REG;
        operand->Info.Register.Type = ND_REG_GPR;
        operand->Info.Register.Size = (ND_REG_SIZE)size;
        operand->Info.Register.Reg = NDR_RBX;
        break;

    case ND_OPT_GPR_rBP:
        // Operand is rBP.
        operand->Type = ND_OP_REG;
        operand->Info.Register.Type = ND_REG_GPR;
        operand->Info.Register.Size = (ND_REG_SIZE)size;
        operand->Info.Register.Reg = NDR_RBP;
        break;

    case ND_OPT_GPR_rSP:
        // Operand is rSP.
        operand->Type = ND_OP_REG;
        operand->Info.Register.Type = ND_REG_GPR;
        operand->Info.Register.Size = (ND_REG_SIZE)size;
        operand->Info.Register.Reg = NDR_RSP;
        break;

    case ND_OPT_GPR_rSI:
        // Operand is rSI.
        operand->Type = ND_OP_REG;
        operand->Info.Register.Type = ND_REG_GPR;
        operand->Info.Register.Size = (ND_REG_SIZE)size;
        operand->Info.Register.Reg = NDR_RSI;
        break;

    case ND_OPT_GPR_rDI:
        // Operand is rDI.
        operand->Type = ND_OP_REG;
        operand->Info.Register.Type = ND_REG_GPR;
        operand->Info.Register.Size = (ND_REG_SIZE)size;
        operand->Info.Register.Reg = NDR_RDI;
        break;

    case ND_OPT_GPR_rR8:
        // Operand is R8.
        operand->Type = ND_OP_REG;
        operand->Info.Register.Type = ND_REG_GPR;
        operand->Info.Register.Size = (ND_REG_SIZE)size;
        operand->Info.Register.Reg = NDR_R8;
        break;

    case ND_OPT_GPR_rR9:
        // Operand is R9.
        operand->Type = ND_OP_REG;
        operand->Info.Register.Type = ND_REG_GPR;
        operand->Info.Register.Size = (ND_REG_SIZE)size;
        operand->Info.Register.Reg = NDR_R9;
        break;

    case ND_OPT_GPR_rR11:
        // Operand is R11.
        operand->Type = ND_OP_REG;
        operand->Info.Register.Type = ND_REG_GPR;
        operand->Info.Register.Size = (ND_REG_SIZE)size;
        operand->Info.Register.Reg = NDR_R11;
        break;

    case ND_OPT_SEG_CS:
        // Operand is the CS register.
        operand->Type = ND_OP_REG;
        operand->Info.Register.Type = ND_REG_SEG;
        operand->Info.Register.Size = (ND_REG_SIZE)size;
        operand->Info.Register.Reg = NDR_CS;
        Instrux->CsAccess |= operand->Access.Access;
        break;

    case ND_OPT_SEG_SS:
        // Operand is the SS register.
        operand->Type = ND_OP_REG;
        operand->Info.Register.Type = ND_REG_SEG;
        operand->Info.Register.Size = (ND_REG_SIZE)size;
        operand->Info.Register.Reg = NDR_SS;
        break;

    case ND_OPT_SEG_DS:
        // Operand is the DS register.
        operand->Type = ND_OP_REG;
        operand->Info.Register.Type = ND_REG_SEG;
        operand->Info.Register.Size = (ND_REG_SIZE)size;
        operand->Info.Register.Reg = NDR_DS;
        break;

    case ND_OPT_SEG_ES:
        // Operand is the ES register.
        operand->Type = ND_OP_REG;
        operand->Info.Register.Type = ND_REG_SEG;
        operand->Info.Register.Size = (ND_REG_SIZE)size;
        operand->Info.Register.Reg = NDR_ES;
        break;

    case ND_OPT_SEG_FS:
        // Operand is the FS register.
        operand->Type = ND_OP_REG;
        operand->Info.Register.Type = ND_REG_SEG;
        operand->Info.Register.Size = (ND_REG_SIZE)size;
        operand->Info.Register.Reg = NDR_FS;
        break;

    case ND_OPT_SEG_GS:
        // Operand is the GS register.
        operand->Type = ND_OP_REG;
        operand->Info.Register.Type = ND_REG_SEG;
        operand->Info.Register.Size = (ND_REG_SIZE)size;
        operand->Info.Register.Reg = NDR_GS;
        break;

    case ND_OPT_FPU_ST0:
        // Operand is the ST(0) register.
        operand->Type = ND_OP_REG;
        operand->Info.Register.Type = ND_REG_FPU;
        operand->Info.Register.Size = ND_SIZE_80BIT;
        operand->Info.Register.Reg = 0;
        break;

    case ND_OPT_FPU_STX:
        // Operand is the ST(i) register.
        operand->Type = ND_OP_REG;
        operand->Info.Register.Type = ND_REG_FPU;
        operand->Info.Register.Size = ND_SIZE_80BIT;
        operand->Info.Register.Reg = Instrux->ModRm.rm;
        break;

    case ND_OPT_SSE_XMM0:
    case ND_OPT_SSE_XMM1:
    case ND_OPT_SSE_XMM2:
    case ND_OPT_SSE_XMM3:
    case ND_OPT_SSE_XMM4:
    case ND_OPT_SSE_XMM5:
    case ND_OPT_SSE_XMM6:
    case ND_OPT_SSE_XMM7:
        // Operand is a hard-coded XMM register.
        operand->Type = ND_OP_REG;
        operand->Info.Register.Type = ND_REG_SSE;
        operand->Info.Register.Size = ND_SIZE_128BIT;
        operand->Info.Register.Reg = opt - ND_OPT_SSE_XMM0;
        break;

    // Special operands. These are always implicit, and can't be encoded inside the instruction.
    case ND_OPT_CR_0:
        // The operand is implicit and is control register 0.
        operand->Type = ND_OP_REG;
        operand->Info.Register.Type = ND_REG_CR;
        operand->Info.Register.Size = (ND_REG_SIZE)size;
        operand->Info.Register.Reg = NDR_CR0;
        break;

    case ND_OPT_SYS_GDTR:
        // The operand is implicit and is the global descriptor table register.
        operand->Type = ND_OP_REG;
        operand->Info.Register.Type = ND_REG_SYS;
        operand->Info.Register.Size = (ND_REG_SIZE)size;
        operand->Info.Register.Reg = NDR_GDTR;
        break;

    case ND_OPT_SYS_IDTR:
        // The operand is implicit and is the interrupt descriptor table register.
        operand->Type = ND_OP_REG;
        operand->Info.Register.Type = ND_REG_SYS;
        operand->Info.Register.Size = (ND_REG_SIZE)size;
        operand->Info.Register.Reg = NDR_IDTR;
        break;

    case ND_OPT_SYS_LDTR:
        // The operand is implicit and is the local descriptor table register.
        operand->Type = ND_OP_REG;
        operand->Info.Register.Type = ND_REG_SYS;
        operand->Info.Register.Size = (ND_REG_SIZE)size;
        operand->Info.Register.Reg = NDR_LDTR;
        break;

    case ND_OPT_SYS_TR:
        // The operand is implicit and is the task register.
        operand->Type = ND_OP_REG;
        operand->Info.Register.Type = ND_REG_SYS;
        operand->Info.Register.Size = (ND_REG_SIZE)size;
        operand->Info.Register.Reg = NDR_TR;
        break;

    case ND_OPT_X87_CONTROL:
        // The operand is implicit and is the x87 control word.
        operand->Type = ND_OP_REG;
        operand->Info.Register.Type = ND_REG_SYS;
        operand->Info.Register.Size = ND_SIZE_16BIT;
        operand->Info.Register.Reg = NDR_X87_CONTROL;
        break;

    case ND_OPT_X87_TAG:
        // The operand is implicit and is the x87 tag word.
        operand->Type = ND_OP_REG;
        operand->Info.Register.Type = ND_REG_SYS;
        operand->Info.Register.Size = ND_SIZE_16BIT;
        operand->Info.Register.Reg = NDR_X87_TAG;
        break;

    case ND_OPT_X87_STATUS:
        // The operand is implicit and is the x87 status word.
        operand->Type = ND_OP_REG;
        operand->Info.Register.Type = ND_REG_SYS;
        operand->Info.Register.Size = ND_SIZE_16BIT;
        operand->Info.Register.Reg = NDR_X87_STATUS;
        break;

    case ND_OPT_MXCSR:
        // The operand is implicit and is the MXCSR.
        operand->Type = ND_OP_REG;
        operand->Info.Register.Type = ND_REG_MXCSR;
        operand->Info.Register.Size = ND_SIZE_32BIT;
        operand->Info.Register.Reg = 0;
        break;

    case ND_OPT_PKRU:
        // The operand is the PKRU register.
        operand->Type = ND_OP_REG;
        operand->Info.Register.Type = ND_REG_PKRU;
        operand->Info.Register.Size = ND_SIZE_32BIT;
        operand->Info.Register.Reg = 0;
        break;

    case ND_OPT_SSP:
        // The operand is the SSP register.
        operand->Type = ND_OP_REG;
        operand->Info.Register.Type = ND_REG_SSP;
        operand->Info.Register.Size = operand->Size;
        operand->Info.Register.Reg = 0;
        break;

    case ND_OPT_UIF:
        // The operand is the User Interrupt Flag.
        operand->Type = ND_OP_REG;
        operand->Info.Register.Type = ND_REG_UIF;
        operand->Info.Register.Size = ND_SIZE_8BIT; // 1 bit, in fact, but there is no size defined for one bit.
        operand->Info.Register.Reg = 0;
        break;

    case ND_OPT_MSR:
        // The operand is implicit and is a MSR (usually selected by the ECX register).
        operand->Type = ND_OP_REG;
        operand->Info.Register.Type = ND_REG_MSR;
        operand->Info.Register.Size = ND_SIZE_64BIT;
        operand->Info.Register.Reg = 0xFFFFFFFF;
        break;

    case ND_OPT_MSR_TSC:
        // The operand is implicit and is the IA32_TSC.
        operand->Type = ND_OP_REG;
        operand->Info.Register.Type = ND_REG_MSR;
        operand->Info.Register.Size = ND_SIZE_64BIT;
        operand->Info.Register.Reg = NDR_IA32_TSC;
        break;

    case ND_OPT_MSR_TSCAUX:
        // The operand is implicit and is the IA32_TSCAUX.
        operand->Type = ND_OP_REG;
        operand->Info.Register.Type = ND_REG_MSR;
        operand->Info.Register.Size = ND_SIZE_64BIT;
        operand->Info.Register.Reg = NDR_IA32_TSC_AUX;
        break;

    case ND_OPT_MSR_SCS:
        // The operand is implicit and is the IA32_SYSENTER_CS.
        operand->Type = ND_OP_REG;
        operand->Info.Register.Type = ND_REG_MSR;
        operand->Info.Register.Size = ND_SIZE_64BIT;
        operand->Info.Register.Reg = NDR_IA32_SYSENTER_CS;
        break;

    case ND_OPT_MSR_SESP:
        // The operand is implicit and is the IA32_SYSENTER_ESP.
        operand->Type = ND_OP_REG;
        operand->Info.Register.Type = ND_REG_MSR;
        operand->Info.Register.Size = ND_SIZE_64BIT;
        operand->Info.Register.Reg = NDR_IA32_SYSENTER_ESP;
        break;

    case ND_OPT_MSR_SEIP:
        // The operand is implicit and is the IA32_SYSENTER_EIP.
        operand->Type = ND_OP_REG;
        operand->Info.Register.Type = ND_REG_MSR;
        operand->Info.Register.Size = ND_SIZE_64BIT;
        operand->Info.Register.Reg = NDR_IA32_SYSENTER_EIP;
        break;

    case ND_OPT_MSR_STAR:
        // The operand is implicit and is the IA32_STAR.
        operand->Type = ND_OP_REG;
        operand->Info.Register.Type = ND_REG_MSR;
        operand->Info.Register.Size = ND_SIZE_64BIT;
        operand->Info.Register.Reg = NDR_IA32_STAR;
        break;

    case ND_OPT_MSR_LSTAR:
        // The operand is implicit and is the IA32_STAR.
        operand->Type = ND_OP_REG;
        operand->Info.Register.Type = ND_REG_MSR;
        operand->Info.Register.Size = ND_SIZE_64BIT;
        operand->Info.Register.Reg = NDR_IA32_LSTAR;
        break;

    case ND_OPT_MSR_FMASK:
        // The operand is implicit and is the IA32_FMASK.
        operand->Type = ND_OP_REG;
        operand->Info.Register.Type = ND_REG_MSR;
        operand->Info.Register.Size = ND_SIZE_64BIT;
        operand->Info.Register.Reg = NDR_IA32_FMASK;
        break;

    case ND_OPT_MSR_FSBASE:
        // The operand is implicit and is the IA32_FS_BASE MSR.
        operand->Type = ND_OP_REG;
        operand->Info.Register.Type = ND_REG_MSR;
        operand->Info.Register.Size = ND_SIZE_64BIT;
        operand->Info.Register.Reg = NDR_IA32_FS_BASE;
        break;

    case ND_OPT_MSR_GSBASE:
        // The operand is implicit and is the IA32_GS_BASE MSR.
        operand->Type = ND_OP_REG;
        operand->Info.Register.Type = ND_REG_MSR;
        operand->Info.Register.Size = ND_SIZE_64BIT;
        operand->Info.Register.Reg = NDR_IA32_GS_BASE;
        break;

    case ND_OPT_MSR_KGSBASE:
        // The operand is implicit and is the IA32_KERNEL_GS_BASE MSR.
        operand->Type = ND_OP_REG;
        operand->Info.Register.Type = ND_REG_MSR;
        operand->Info.Register.Size = ND_SIZE_64BIT;
        operand->Info.Register.Reg = NDR_IA32_KERNEL_GS_BASE;
        break;

    case ND_OPT_XCR:
        // The operand is implicit and is an extended control register (usually selected by ECX register).
        operand->Type = ND_OP_REG;
        operand->Info.Register.Type = ND_REG_XCR;
        operand->Info.Register.Size = ND_SIZE_64BIT;
        operand->Info.Register.Reg = 0xFF;
        break;

    case ND_OPT_XCR_0:
        // The operand is implicit and is XCR0.
        operand->Type = ND_OP_REG;
        operand->Info.Register.Type = ND_REG_XCR;
        operand->Info.Register.Size = ND_SIZE_64BIT;
        operand->Info.Register.Reg = 0;
        break;

    case ND_OPT_REG_BANK:
        // Multiple registers are accessed.
        if ((Instrux->Instruction == ND_INS_PUSHA) || (Instrux->Instruction == ND_INS_POPA))
        {
            operand->Type = ND_OP_REG;
            operand->Size = operand->RawSize = Instrux->WordLength;
            operand->Info.Register.Type = ND_REG_GPR;
            operand->Info.Register.Size = Instrux->WordLength;
            operand->Info.Register.Reg = NDR_EAX;
            operand->Info.Register.Count = 8;
            operand->Info.Register.IsBlock = ND_TRUE;
        }
        else
        {
            operand->Type = ND_OP_BANK;
        }
        break;

    case ND_OPT_A:
        // Fetch the address. NOTE: The size can't be larger than 8 bytes.
        status = NdFetchAddress(Instrux, Code, Offset, Size, (ND_UINT8)size);
        if (!ND_SUCCESS(status))
        {
            return status;
        }

        // Fill in operand info.
        operand->Type = ND_OP_ADDR;
        operand->Info.Address.BaseSeg = Instrux->Address.Cs;
        operand->Info.Address.Offset = Instrux->Address.Ip;
        break;

    case ND_OPT_B:
        // General purpose register encoded in VEX.vvvv field.
        operand->Type = ND_OP_REG;
        operand->Info.Register.Type = ND_REG_GPR;
        operand->Info.Register.Size = (ND_REG_SIZE)size;

        // EVEX.V' must be 0, if a GPR is encoded using EVEX encoding.
        if (Instrux->Exs.vp != 0)
        {
            return ND_STATUS_INVALID_REGISTER_IN_INSTRUCTION;
        }

        operand->Info.Register.Reg = (ND_UINT8)Instrux->Exs.v;
        break;

    case ND_OPT_C:
        // Control register, encoded in modrm.reg.
        operand->Type = ND_OP_REG;
        operand->Info.Register.Type = ND_REG_CR;
        operand->Info.Register.Size = (ND_REG_SIZE)size;
        operand->Info.Register.Reg = (ND_UINT8)((Instrux->Exs.r << 3) | Instrux->ModRm.reg);
        // On some AMD processors, the presence of the LOCK prefix before MOV to/from control registers allows accessing
        // higher 8 control registers.
        if ((ND_CODE_64 != Instrux->DefCode) && (Instrux->HasLock))
        {
            operand->Info.Register.Reg |= 0x8;
        }

        // Only CR0, CR2, CR3, CR4 & CR8 valid.
        if (operand->Info.Register.Reg != 0 &&
            operand->Info.Register.Reg != 2 &&
            operand->Info.Register.Reg != 3 &&
            operand->Info.Register.Reg != 4 &&
            operand->Info.Register.Reg != 8)
        {
            return ND_STATUS_INVALID_REGISTER_IN_INSTRUCTION;
        }

        break;

    case ND_OPT_D:
        // Debug register, encoded in modrm.reg.
        operand->Type = ND_OP_REG;
        operand->Info.Register.Type = ND_REG_DR;
        operand->Info.Register.Size = (ND_REG_SIZE)size;
        operand->Info.Register.Reg = (ND_UINT8)((Instrux->Exs.r << 3) | Instrux->ModRm.reg);

        // Only DR0-DR7 valid.
        if (operand->Info.Register.Reg >= 8)
        {
            return ND_STATUS_INVALID_REGISTER_IN_INSTRUCTION;
        }

        break;

    case ND_OPT_T:
        // Test register, encoded in modrm.reg.
        operand->Type = ND_OP_REG;
        operand->Info.Register.Type = ND_REG_TR;
        operand->Info.Register.Size = (ND_REG_SIZE)size;
        operand->Info.Register.Reg = (ND_UINT8)((Instrux->Exs.r << 3) | Instrux->ModRm.reg);

        // Only TR0-TR7 valid, only on 486.
        if (operand->Info.Register.Reg >= 8)
        {
            return ND_STATUS_INVALID_REGISTER_IN_INSTRUCTION;
        }

        break;

    case ND_OPT_S:
        // Segment register, encoded in modrm.reg.
        operand->Type = ND_OP_REG;
        operand->Info.Register.Type = ND_REG_SEG;
        operand->Info.Register.Size = (ND_REG_SIZE)size;
        operand->Info.Register.Reg = Instrux->ModRm.reg;

        // Only ES, CS, SS, DS, FS, GS valid.
        if (operand->Info.Register.Reg >= 6)
        {
            return ND_STATUS_INVALID_REGISTER_IN_INSTRUCTION;
        }

        // If CS is loaded - #UD.
        if ((operand->Info.Register.Reg == NDR_CS) && operand->Access.Write)
        {
            return ND_STATUS_CS_LOAD;
        }

        break;

    case ND_OPT_E:
        // General purpose register or memory, encoded in modrm.rm.
        if (Instrux->ModRm.mod == 3)
        {
            operand->Type = ND_OP_REG;
            operand->Info.Register.Type = ND_REG_GPR;
            operand->Info.Register.Size = (ND_REG_SIZE)size;
            operand->Info.Register.Reg = (ND_UINT8)((Instrux->Exs.b << 3) | Instrux->ModRm.rm);
            operand->Info.Register.IsHigh8 = (operand->Info.Register.Size == 1) &&
                                             (operand->Info.Register.Reg  >= 4) &&
                                             (ND_ENCM_LEGACY == Instrux->EncMode) &&
                                             !Instrux->HasRex;
        }
        else
        {
            goto memory;
        }
        break;

    case ND_OPT_F:
        // The flags register.
        operand->Type = ND_OP_REG;
        operand->Info.Register.Type = ND_REG_FLG;
        operand->Info.Register.Size = (ND_REG_SIZE)size;
        operand->Info.Register.Reg = 0;
        Instrux->FlagsAccess.RegAccess |= operand->Access.Access;
        break;

    case ND_OPT_K:
        // The operand is the stack.
        {
            static const ND_UINT8 szLut[3] = { ND_SIZE_16BIT, ND_SIZE_32BIT, ND_SIZE_64BIT };

            Instrux->MemoryAccess |= operand->Access.Access;
            operand->Type = ND_OP_MEM;
            operand->Info.Memory.IsStack = ND_TRUE;
            operand->Info.Memory.HasBase = ND_TRUE;
            operand->Info.Memory.Base = NDR_RSP;
            operand->Info.Memory.BaseSize = szLut[Instrux->DefStack];
            operand->Info.Memory.HasSeg = ND_TRUE;
            operand->Info.Memory.Seg = NDR_SS;
            Instrux->StackWords = (ND_UINT8)(operand->Size / Instrux->WordLength);
            Instrux->StackAccess |= operand->Access.Access;
        }
        break;

    case ND_OPT_G:
        // General purpose register encoded in modrm.reg.
        operand->Type = ND_OP_REG;
        operand->Info.Register.Type = ND_REG_GPR;
        operand->Info.Register.Size = (ND_REG_SIZE)size;

        // EVEX.R' must be 0 if a GPR is encoded.
        if (Instrux->Exs.rp != 0)
        {
            return ND_STATUS_INVALID_REGISTER_IN_INSTRUCTION;
        }

        operand->Info.Register.Reg = (ND_UINT8)((Instrux->Exs.r << 3) | Instrux->ModRm.reg);
        operand->Info.Register.IsHigh8 = (operand->Info.Register.Size == 1) &&
                                         (operand->Info.Register.Reg >= 4) &&
                                         (ND_ENCM_LEGACY == Instrux->EncMode) &&
                                         !Instrux->HasRex;
        break;

    case ND_OPT_R:
        // General purpose register encoded in modrm.rm.
        if ((Instrux->ModRm.mod == 3) || (0 != (Instrux->Attributes & ND_FLAG_MFR)))
        {
            operand->Type = ND_OP_REG;
            operand->Info.Register.Type = ND_REG_GPR;
            operand->Info.Register.Size = (ND_REG_SIZE)size;
            operand->Info.Register.Reg = (ND_UINT8)((Instrux->Exs.b << 3) | Instrux->ModRm.rm);
            operand->Info.Register.IsHigh8 = (operand->Info.Register.Size == 1) &&
                                             (operand->Info.Register.Reg >= 4) &&
                                             (ND_ENCM_LEGACY == Instrux->EncMode) &&
                                             !Instrux->HasRex;
        }
        else
        {
            return ND_STATUS_INVALID_ENCODING;
        }
        break;

    case ND_OPT_I:
        // Immediate, encoded in instructon bytes.
        {
            ND_UINT64 imm;

            // Fetch the immediate. NOTE: The size won't exceed 8 bytes.
            status = NdFetchImmediate(Instrux, Code, Offset, Size, (ND_UINT8)size);
            if (!ND_SUCCESS(status))
            {
                return status;
            }

            // Get the last immediate.
            if (Instrux->HasImm3)
            {
                imm = Instrux->Immediate3;
            }
            else if (Instrux->HasImm2)
            {
                imm = Instrux->Immediate2;
            }
            else
            {
                imm = Instrux->Immediate1;
            }

            operand->Type = ND_OP_IMM;

            if (operand->Flags.SignExtendedDws)
            {
                static const ND_UINT8 wszLut[3] = { ND_SIZE_16BIT, ND_SIZE_32BIT, ND_SIZE_64BIT };

                // Get the default word size: the immediate is sign extended to the default word size.
                operand->Size = wszLut[Instrux->EfOpMode];

                operand->Info.Immediate.Imm = ND_SIGN_EX(size, imm);
            }
            else if (operand->Flags.SignExtendedOp1)
            {
                // The immediate is sign extended to the size of the first operand.
                operand->Size = Instrux->Operands[0].Size;

                operand->Info.Immediate.Imm = ND_SIGN_EX(size, imm);
            }
            else
            {
                operand->Info.Immediate.Imm = imm;
            }
        }
        break;

    case ND_OPT_Im2z:
        {
            operand->Type = ND_OP_IMM;
            operand->Info.Immediate.Imm = Instrux->SseImmediate & 3;
        }
        break;

    case ND_OPT_J:
        // Fetch the relative offset. NOTE: The size of the relative can't exceed 4 bytes.
        status = NdFetchRelativeOffset(Instrux, Code, Offset, Size, (ND_UINT8)size);
        if (!ND_SUCCESS(status))
        {
            return status;
        }

        // The instruction is RIP relative.
        Instrux->IsRipRelative = ND_TRUE;

        operand->Type = ND_OP_OFFS;
        // The relative offset is forced to the default word length. Care must be taken with the 32 bit
        // branches that have 0x66 prefix (in 32 bit mode)!
        operand->Size = Instrux->WordLength;
        operand->Info.RelativeOffset.Rel = ND_SIGN_EX(size, Instrux->RelativeOffset);

        break;

    case ND_OPT_N:
        // The R/M field of the ModR/M byte selects a packed-quadword, MMX technology register.
        if (Instrux->ModRm.mod != 3)
        {
            return ND_STATUS_INVALID_ENCODING;
        }

        operand->Type = ND_OP_REG;
        operand->Info.Register.Type = ND_REG_MMX;
        operand->Info.Register.Size = ND_SIZE_64BIT;
        operand->Info.Register.Reg = Instrux->ModRm.rm;
        break;

    case ND_OPT_P:
        // The reg field of the ModR/M byte selects a packed quadword MMX technology register.
        operand->Type = ND_OP_REG;
        operand->Info.Register.Type = ND_REG_MMX;
        operand->Info.Register.Size = ND_SIZE_64BIT;
        operand->Info.Register.Reg = Instrux->ModRm.reg;
        break;

    case ND_OPT_Q:
        // A ModR/M byte follows the opcode and specifies the operand. The operand is either an MMX technology
        // register or a memory address. If it is a memory address, the address is computed from a segment register
        // and any of the following values: a base register, an index register, a scaling factor, and a displacement
        if (Instrux->ModRm.mod == 3)
        {
            operand->Type = ND_OP_REG;
            operand->Info.Register.Type = ND_REG_MMX;
            operand->Info.Register.Size = ND_SIZE_64BIT;
            operand->Info.Register.Reg = Instrux->ModRm.rm;
        }
        else
        {
            goto memory;
        }
        break;

    case ND_OPT_O:
        // Absolute address, encoded in instruction bytes.
        {
            // NOTE: The moffset len can't exceed 8 bytes.
            status = NdFetchMoffset(Instrux, Code, Offset, Size, 2 << Instrux->AddrMode);
            if (!ND_SUCCESS(status))
            {
                return status;
            }

            // operand info.
            Instrux->MemoryAccess |= operand->Access.Access;
            operand->Type = ND_OP_MEM;
            operand->Info.Memory.HasDisp = ND_TRUE;
            operand->Info.Memory.IsDirect = ND_TRUE;
            operand->Info.Memory.DispSize = Instrux->MoffsetLength;
            operand->Info.Memory.Disp = Instrux->Moffset;
            operand->Info.Memory.HasSeg = ND_TRUE;
            operand->Info.Memory.Seg = NdGetSegOverride(Instrux, NDR_DS);
        }
        break;

    case ND_OPT_M:
        // Modrm based memory addressing.
        if (Instrux->ModRm.mod == 3)
        {
            return ND_STATUS_INVALID_ENCODING;
        }

memory:
        Instrux->MemoryAccess |= operand->Access.Access;
        operand->Type = ND_OP_MEM;
        operand->Info.Memory.HasSeg = ND_TRUE;

        if (ND_ADDR_16 == Instrux->AddrMode)
        {
            // 16 bit addressing, make sure the instruction supports this.
            if (!!(Instrux->Attributes & ND_FLAG_NOA16))
            {
                return ND_STATUS_16_BIT_ADDRESSING_NOT_SUPPORTED;
            }

            switch (Instrux->ModRm.rm)
            {
            case 0:
                // [bx + si]
                operand->Info.Memory.HasBase = ND_TRUE;
                operand->Info.Memory.HasIndex = ND_TRUE;
                operand->Info.Memory.Scale = 1;
                operand->Info.Memory.Base = NDR_BX;
                operand->Info.Memory.Index = NDR_SI;
                operand->Info.Memory.BaseSize = ND_SIZE_16BIT;
                operand->Info.Memory.IndexSize = ND_SIZE_16BIT;
                operand->Info.Memory.Seg = NDR_DS;
                break;
            case 1:
                // [bx + di]
                operand->Info.Memory.HasBase = ND_TRUE;
                operand->Info.Memory.HasIndex = ND_TRUE;
                operand->Info.Memory.Scale = 1;
                operand->Info.Memory.Base = NDR_BX;
                operand->Info.Memory.Index = NDR_DI;
                operand->Info.Memory.BaseSize = ND_SIZE_16BIT;
                operand->Info.Memory.IndexSize = ND_SIZE_16BIT;
                operand->Info.Memory.Seg = NDR_DS;
                break;
            case 2:
                // [bp + si]
                operand->Info.Memory.HasBase = ND_TRUE;
                operand->Info.Memory.HasIndex = ND_TRUE;
                operand->Info.Memory.Scale = 1;
                operand->Info.Memory.Base = NDR_BP;
                operand->Info.Memory.Index = NDR_SI;
                operand->Info.Memory.BaseSize = ND_SIZE_16BIT;
                operand->Info.Memory.IndexSize = ND_SIZE_16BIT;
                operand->Info.Memory.Seg = NDR_SS;
                break;
            case 3:
                // [bp + di]
                operand->Info.Memory.HasBase = ND_TRUE;
                operand->Info.Memory.HasIndex = ND_TRUE;
                operand->Info.Memory.Scale = 1;
                operand->Info.Memory.Base = NDR_BP;
                operand->Info.Memory.Index = NDR_DI;
                operand->Info.Memory.BaseSize = ND_SIZE_16BIT;
                operand->Info.Memory.IndexSize = ND_SIZE_16BIT;
                operand->Info.Memory.Seg = NDR_SS;
                break;
            case 4:
                // [si]
                operand->Info.Memory.HasBase = ND_TRUE;
                operand->Info.Memory.Base = NDR_SI;
                operand->Info.Memory.BaseSize = ND_SIZE_16BIT;
                operand->Info.Memory.Seg = NDR_DS;
                break;
            case 5:
                // [di]
                operand->Info.Memory.HasBase = ND_TRUE;
                operand->Info.Memory.Base = NDR_DI;
                operand->Info.Memory.BaseSize = ND_SIZE_16BIT;
                operand->Info.Memory.Seg = NDR_DS;
                break;
            case 6:
                // [bp]
                if (Instrux->ModRm.mod != 0)
                {
                    // If mod is not zero, than we have "[bp + displacement]".
                    operand->Info.Memory.HasBase = ND_TRUE;
                    operand->Info.Memory.Base = NDR_BP;
                    operand->Info.Memory.BaseSize = ND_SIZE_16BIT;
                    operand->Info.Memory.Seg = NDR_SS;
                }
                else
                {
                    // If mod is zero, than we only have a displacement that is used to directly address mem.
                    operand->Info.Memory.Seg = NDR_DS;
                }
                break;
            case 7:
                // [bx]
                operand->Info.Memory.HasBase = ND_TRUE;
                operand->Info.Memory.Base = NDR_BX;
                operand->Info.Memory.BaseSize = ND_SIZE_16BIT;
                operand->Info.Memory.Seg = NDR_DS;
                break;
            }

            // Store the displacement.
            operand->Info.Memory.HasDisp = !!Instrux->HasDisp;
            operand->Info.Memory.DispSize = Instrux->DispLength;
            operand->Info.Memory.Disp = ND_SIGN_EX(Instrux->DispLength, Instrux->Displacement);
        }
        else
        {
            ND_UINT8 defsize = (Instrux->AddrMode == ND_ADDR_32 ? ND_SIZE_32BIT : ND_SIZE_64BIT);

            // Implicit segment is DS.
            operand->Info.Memory.Seg = NDR_DS;

            if (Instrux->HasSib)
            {
                // Check for base.
                if ((Instrux->ModRm.mod == 0) && (Instrux->Sib.base == NDR_RBP))
                {
                    // Mod is mem without displacement and base reg is RBP -> no base reg used.
                    // Note that this addressing mode is not RIP relative.
                }
                else
                {
                    operand->Info.Memory.HasBase = ND_TRUE;
                    operand->Info.Memory.BaseSize = defsize;
                    operand->Info.Memory.Base = (ND_UINT8)((Instrux->Exs.b << 3) | Instrux->Sib.base);

                    if ((operand->Info.Memory.Base == NDR_RSP) || (operand->Info.Memory.Base == NDR_RBP))
                    {
                        operand->Info.Memory.Seg = NDR_SS;
                    }
                }

                // Check for index.
                if ((((Instrux->Exs.x << 3) | Instrux->Sib.index) != NDR_RSP) || ND_HAS_VSIB(Instrux))
                {
                    // Index * Scale is present.
                    operand->Info.Memory.HasIndex = ND_TRUE;
                    operand->Info.Memory.IndexSize = defsize;
                    operand->Info.Memory.Index = (ND_UINT8)((Instrux->Exs.x << 3) | Instrux->Sib.index);

                    if (ND_HAS_VSIB(Instrux))
                    {
                        operand->Info.Memory.IndexSize = vsibRegSize;
                        operand->Info.Memory.Index |= Instrux->Exs.vp << 4;
                    }

                    operand->Info.Memory.Scale = 1 << Instrux->Sib.scale;
                }
            }
            else
            {
                if ((Instrux->ModRm.mod == 0) && (Instrux->ModRm.rm == NDR_RBP))
                {
                    //
                    // RIP relative addressing addresses a memory region relative to the current RIP; However,
                    // the current RIP, when executing the current instruction, is already updated and points
                    // to the next instruction, therefore, we must add the instruction length also to the final
                    // address. Note that RIP relative addressing is used even if the instruction uses 32 bit
                    // addressing, as long as we're in long mode.
                    //
                    operand->Info.Memory.IsRipRel = Instrux->IsRipRelative = (Instrux->DefCode == ND_CODE_64);

                    // Some instructions (example: MPX) don't support RIP relative addressing.
                    if (operand->Info.Memory.IsRipRel && !!(Instrux->Attributes & ND_FLAG_NO_RIP_REL))
                    {
                        return ND_STATUS_RIP_REL_ADDRESSING_NOT_SUPPORTED;
                    }
                }
                else
                {
                    operand->Info.Memory.HasBase = ND_TRUE;
                    operand->Info.Memory.BaseSize = defsize;
                    operand->Info.Memory.Base = (ND_UINT8)((Instrux->Exs.b << 3) | Instrux->ModRm.rm);

                    if ((operand->Info.Memory.Base == NDR_RSP) || (operand->Info.Memory.Base == NDR_RBP))
                    {
                        operand->Info.Memory.Seg = NDR_SS;
                    }
                }
            }

            operand->Info.Memory.HasDisp = Instrux->HasDisp;
            operand->Info.Memory.DispSize = Instrux->DispLength;
            operand->Info.Memory.Disp = ND_SIGN_EX(Instrux->DispLength, Instrux->Displacement);
        }

        // Get the segment. Note that in long mode, segment prefixes are ignored, except for FS and GS.
        if (Instrux->HasSeg)
        {
            operand->Info.Memory.Seg = NdGetSegOverride(Instrux, operand->Info.Memory.Seg);
        }

        // Handle VSIB addressing.
        if (ND_HAS_VSIB(Instrux))
        {
            // VSIB requires SIB.
            if (!Instrux->HasSib)
            {
                return ND_STATUS_VSIB_WITHOUT_SIB;
            }

            operand->Info.Memory.IsVsib = ND_TRUE;

            operand->Info.Memory.Vsib.IndexSize = vsibIndexSize;
            operand->Info.Memory.Vsib.ElemCount = vsibIndexCount;
            operand->Info.Memory.Vsib.ElemSize = (ND_UINT8)(size / vsibIndexCount);
        }

        // Handle sibmem addressing, as used by Intel AMX instructions.
        if (ND_HAS_SIBMEM(Instrux))
        {
            // sibmem requires SIB to be present.
            if (!Instrux->HasSib)
            {
                return ND_STATUS_SIBMEM_WITHOUT_SIB;
            }

            operand->Info.Memory.IsSibMem = ND_TRUE;
        }

        // If we have broadcast, the operand size is fixed to either 16, 32 or 64 bit, depending on bcast size.
        // Therefore, we will override the rawSize with either 16, 32 or 64 bits. Note that bcstSize will save the 
        // total size of the access, and it will be used to compute the number of broadcasted elements: 
        // bcstSize / rawSize.
        if (Instrux->HasBroadcast)
        {
            operand->Info.Memory.HasBroadcast = ND_TRUE;

            if (opd & ND_OPD_B32)
            {
                size = ND_SIZE_32BIT;
            }
            else if (opd & ND_OPD_B64)
            {
                size = ND_SIZE_64BIT;
            }
            else if (opd & ND_OPD_B16)
            {
                size = ND_SIZE_16BIT;
            }
            else
            {
                size = width ? ND_SIZE_64BIT : ND_SIZE_32BIT;
            }

            // Override operand size.
            operand->Size = operand->RawSize = size;
        }

        // Handle compressed displacement, if any. Note that most EVEX instructions with 8 bit displacement
        // use compressed displacement addressing.
        if (Instrux->HasCompDisp)
        {
            operand->Info.Memory.HasCompDisp = ND_TRUE;
            operand->Info.Memory.CompDispSize = NdGetCompDispSize(Instrux, operand->Size);
        }

        // MIB, if any. Used by some MPX instructions.
        operand->Info.Memory.IsMib = ND_HAS_MIB(Instrux);

        // Bitbase, if any. Used by BT* instructions when the first op is mem and the second one reg.
        operand->Info.Memory.IsBitbase = ND_HAS_BITBASE(Instrux);

        // AG, if this is the case.
        if (ND_HAS_AG(Instrux))
        {
            operand->Info.Memory.IsAG = ND_TRUE;

            // Address generation instructions ignore the segment prefixes. Examples are LEA and MPX instructions.
            operand->Info.Memory.HasSeg = ND_FALSE;
            operand->Info.Memory.Seg = 0;
        }

        // Shadow Stack Access, if this is the case.
        if (ND_HAS_SHS(Instrux))
        {
            operand->Info.Memory.IsShadowStack = ND_TRUE;
            operand->Info.Memory.ShStkType = ND_SHSTK_EXPLICIT;
        }

        break;


    case ND_OPT_H:
        // Vector register, encoded in VEX/EVEX.vvvv.
        if (ND_ENCM_LEGACY == Instrux->EncMode)
        {
            return ND_STATUS_HINT_OPERAND_NOT_USED;
        }
        else
        {
            operand->Type = ND_OP_REG;
            operand->Info.Register.Type = ND_REG_SSE;
            operand->Info.Register.Size = (ND_REG_SIZE)(size < ND_SIZE_128BIT ? ND_SIZE_128BIT : size);
            operand->Info.Register.Reg = (ND_UINT8)((Instrux->Exs.vp << 4) | Instrux->Exs.v);
        }
        break;

    case ND_OPT_L:
        // Vector register, encoded in immediate.
        status = NdFetchSseImmediate(Instrux, Code, Offset, Size, 1);
        if (!ND_SUCCESS(status))
        {
            return status;
        }

        operand->Type = ND_OP_REG;
        operand->Info.Register.Type = ND_REG_SSE;
        operand->Info.Register.Size = (ND_REG_SIZE)(size < ND_SIZE_128BIT ? ND_SIZE_128BIT : size);
        operand->Info.Register.Reg = (Instrux->SseImmediate >> 4) & 0xF;

        if (Instrux->DefCode != ND_CODE_64)
        {
            operand->Info.Register.Reg &= 0x7;
        }

        break;

    case ND_OPT_U:
        // Vector register encoded in modrm.rm.
        if (Instrux->ModRm.mod != 3)
        {
            return ND_STATUS_INVALID_ENCODING;
        }

        operand->Type = ND_OP_REG;
        operand->Info.Register.Type = ND_REG_SSE;
        operand->Info.Register.Size = (ND_REG_SIZE)(size < ND_SIZE_128BIT ? ND_SIZE_128BIT : size);
        operand->Info.Register.Reg = (ND_UINT8)((Instrux->Exs.b << 3) | Instrux->ModRm.rm);
        if (Instrux->HasEvex || Instrux->HasMvex)
        {
            operand->Info.Register.Reg |= Instrux->Exs.x << 4;
        }
        break;

    case ND_OPT_V:
        // Vector register encoded in modrm.reg.
        operand->Type = ND_OP_REG;
        operand->Info.Register.Type = ND_REG_SSE;
        operand->Info.Register.Size = (ND_REG_SIZE)(size < ND_SIZE_128BIT ? ND_SIZE_128BIT : size);
        operand->Info.Register.Reg = (ND_UINT8)((Instrux->Exs.r << 3) | Instrux->ModRm.reg);
        if (Instrux->HasEvex || Instrux->HasMvex)
        {
            operand->Info.Register.Reg |= Instrux->Exs.rp << 4;
        }
        break;

    case ND_OPT_W:
        // Vector register or memory encoded in modrm.rm.
        if (Instrux->ModRm.mod == 3)
        {
            operand->Type = ND_OP_REG;
            operand->Info.Register.Type = ND_REG_SSE;
            operand->Info.Register.Size = (ND_REG_SIZE)(size < ND_SIZE_128BIT ? ND_SIZE_128BIT : size);
            operand->Info.Register.Reg = (ND_UINT8)((Instrux->Exs.b << 3) | Instrux->ModRm.rm);
            if (Instrux->HasEvex || Instrux->HasMvex)
            {
                operand->Info.Register.Reg |= Instrux->Exs.x << 4;
            }
        }
        else
        {
            goto memory;
        }
        break;

    case ND_OPT_X:
    case ND_OPT_Y:
    case ND_OPT_MEM_rDI:
        // RSI/RDI based addressing, as used by string instructions.
        Instrux->MemoryAccess |= operand->Access.Access;
        operand->Type = ND_OP_MEM;
        operand->Info.Memory.HasBase = ND_TRUE;
        operand->Info.Memory.BaseSize = 2 << Instrux->AddrMode;
        operand->Info.Memory.HasSeg = ND_TRUE;
        operand->Info.Memory.Base = (ND_UINT8)(((opt == ND_OPT_X) ? NDR_RSI : NDR_RDI));
        operand->Info.Memory.IsString = (ND_OPT_X == opt || ND_OPT_Y == opt);
        // DS:rSI supports segment overriding. ES:rDI does not.
        if (opt == ND_OPT_Y)
        {
            operand->Info.Memory.Seg = NDR_ES;
        }
        else
        {
            operand->Info.Memory.Seg = NdGetSegOverride(Instrux, NDR_DS);
        }
        break;

    case ND_OPT_MEM_rBX_AL:
        // [rBX + AL], used by XLAT.
        Instrux->MemoryAccess |= operand->Access.Access;
        operand->Type = ND_OP_MEM;
        operand->Info.Memory.HasBase = ND_TRUE;
        operand->Info.Memory.HasIndex = ND_TRUE;
        operand->Info.Memory.BaseSize = 2 << Instrux->AddrMode;
        operand->Info.Memory.IndexSize = ND_SIZE_8BIT;  // Always 1 Byte.
        operand->Info.Memory.Base = NDR_RBX;            // Always rBX.
        operand->Info.Memory.Index = NDR_AL;            // Always AL.
        operand->Info.Memory.Scale = 1;                 // Always 1.
        operand->Info.Memory.HasSeg = ND_TRUE;
        operand->Info.Memory.Seg = NdGetSegOverride(Instrux, NDR_DS);
        break;

    case ND_OPT_MEM_rAX:
        // [rAX], used implicitly by MONITOR, MONITORX and RMPADJUST instructions.
        Instrux->MemoryAccess |= operand->Access.Access;
        operand->Type = ND_OP_MEM;
        operand->Info.Memory.HasBase = ND_TRUE;
        operand->Info.Memory.BaseSize = 2 << Instrux->AddrMode;
        operand->Info.Memory.Base = NDR_RAX;            // Always rAX.
        operand->Info.Memory.HasSeg = ND_TRUE;
        operand->Info.Memory.Seg = NdGetSegOverride(Instrux, NDR_DS);
        break;

    case ND_OPT_MEM_rCX:
        // [rCX], used implicitly by RMPUPDATE.
        Instrux->MemoryAccess |= operand->Access.Access;
        operand->Type = ND_OP_MEM;
        operand->Info.Memory.HasBase = ND_TRUE;
        operand->Info.Memory.BaseSize = 2 << Instrux->AddrMode;
        operand->Info.Memory.Base = NDR_RCX;            // Always rCX.
        operand->Info.Memory.HasSeg = ND_TRUE;
        operand->Info.Memory.Seg = NdGetSegOverride(Instrux, NDR_DS);
        break;

    case ND_OPT_MEM_SHS:
        // Shadow stack access using the current SSP.
        Instrux->MemoryAccess |= operand->Access.Access;
        operand->Type = ND_OP_MEM;
        operand->Info.Memory.IsShadowStack = ND_TRUE;
        operand->Info.Memory.ShStkType = ND_SHSTK_SSP_LD_ST;
        break;

    case ND_OPT_MEM_SHS0:
        // Shadow stack access using the IA32_PL0_SSP.
        Instrux->MemoryAccess |= operand->Access.Access;
        operand->Type = ND_OP_MEM;
        operand->Info.Memory.IsShadowStack = ND_TRUE;
        operand->Info.Memory.ShStkType = ND_SHSTK_PL0_SSP;
        break;

    case ND_OPT_MEM_SMSRT:
        // Table of MSR addresses, encoded in [RSI].
        Instrux->MemoryAccess |= operand->Access.Access;
        operand->Type = ND_OP_MEM;
        operand->Info.Memory.HasBase = ND_TRUE;
        operand->Info.Memory.BaseSize = 2 << Instrux->AddrMode;
        operand->Info.Memory.Base = NDR_RSI;            // Always rSI.
        operand->Info.Memory.HasSeg = ND_FALSE;         // Linear Address directly, only useable in 64 bit mode.
        break;

    case ND_OPT_MEM_DMSRT:
        // Table of MSR addresses, encoded in [RDI].
        Instrux->MemoryAccess |= operand->Access.Access;
        operand->Type = ND_OP_MEM;
        operand->Info.Memory.HasBase = ND_TRUE;
        operand->Info.Memory.BaseSize = 2 << Instrux->AddrMode;
        operand->Info.Memory.Base = NDR_RDI;            // Always rDI.
        operand->Info.Memory.HasSeg = ND_FALSE;         // Linear Address directly, only useable in 64 bit mode.
        break;

    case ND_OPT_MEM_SHSP:
        // Shadow stack push/pop access.
        Instrux->MemoryAccess |= operand->Access.Access;
        operand->Type = ND_OP_MEM;
        operand->Info.Memory.IsShadowStack = ND_TRUE;
        operand->Info.Memory.ShStkType = ND_SHSTK_SSP_PUSH_POP;
        break;

    case ND_OPT_Z:
        // A GPR Register is selected by the low 3 bits inside the opcode. REX.B can be used to extend it.
        operand->Type = ND_OP_REG;
        operand->Info.Register.Type = ND_REG_GPR;
        operand->Info.Register.Size = (ND_REG_SIZE)size;
        operand->Info.Register.Reg = (ND_UINT8)((Instrux->Exs.b << 3) | (Instrux->PrimaryOpCode & 0x7));
        operand->Info.Register.IsHigh8 = (operand->Info.Register.Size == 1) &&
                                         (operand->Info.Register.Reg >= 4) &&
                                         (ND_ENCM_LEGACY == Instrux->EncMode) &&
                                         !Instrux->HasRex;
        break;

    case ND_OPT_rB:
        // reg inside modrm selects a BND register.
        operand->Type = ND_OP_REG;
        operand->Info.Register.Type = ND_REG_BND;
        operand->Info.Register.Size = (ND_REG_SIZE)size;
        operand->Info.Register.Reg = (ND_UINT8)((Instrux->Exs.r << 3) | Instrux->ModRm.reg);
        if (operand->Info.Register.Reg >= 4)
        {
            return ND_STATUS_INVALID_REGISTER_IN_INSTRUCTION;
        }
        break;

    case ND_OPT_mB:
        // rm inside modrm selects either a BND register, either memory.
        if (Instrux->ModRm.mod == 3)
        {
            operand->Type = ND_OP_REG;
            operand->Info.Register.Type = ND_REG_BND;
            operand->Info.Register.Size = (ND_REG_SIZE)size;
            operand->Info.Register.Reg = (ND_UINT8)((Instrux->Exs.b << 3) | Instrux->ModRm.rm);
            if (operand->Info.Register.Reg >= 4)
            {
                return ND_STATUS_INVALID_REGISTER_IN_INSTRUCTION;
            }
        }
        else
        {
            goto memory;
        }
        break;

    case ND_OPT_rK:
        // reg inside modrm selects a mask register.
        operand->Type = ND_OP_REG;
        operand->Info.Register.Type = ND_REG_MSK;

        // Opcode dependent #UD, R and R' must be zero (1 actually, but they're inverted).
        if ((Instrux->Exs.r != 0) || (Instrux->Exs.rp != 0))
        {
            return ND_STATUS_INVALID_REGISTER_IN_INSTRUCTION;
        }

        operand->Info.Register.Size = ND_SIZE_64BIT;
        operand->Info.Register.Reg = (ND_UINT8)(Instrux->ModRm.reg);

        break;

    case ND_OPT_vK:
        // vex.vvvv selects a mask register.
        operand->Type = ND_OP_REG;
        operand->Info.Register.Type = ND_REG_MSK;
        operand->Info.Register.Size = ND_SIZE_64BIT;
        operand->Info.Register.Reg = (ND_UINT8)Instrux->Exs.v;
        if (operand->Info.Register.Reg >= 8)
        {
            return ND_STATUS_INVALID_REGISTER_IN_INSTRUCTION;
        }
        break;

    case ND_OPT_mK:
        // rm inside modrm selects either a mask register, either memory.
        if (Instrux->ModRm.mod == 3)
        {
            operand->Type = ND_OP_REG;
            operand->Info.Register.Type = ND_REG_MSK;
            operand->Info.Register.Size = ND_SIZE_64BIT;
            // X and B are ignored when Msk registers are being addressed.
            operand->Info.Register.Reg = Instrux->ModRm.rm;
        }
        else
        {
            goto memory;
        }
        break;

    case ND_OPT_aK:
        // aaa inside evex selects either a mask register, which is used for masking a destination operand.
        operand->Type = ND_OP_REG;
        operand->Info.Register.Type = ND_REG_MSK;
        operand->Info.Register.Size = ND_SIZE_64BIT;
        operand->Info.Register.Reg = Instrux->Exs.k;
        break;

    case ND_OPT_rM:
        // Sigh. reg field inside mod r/m encodes memory. This encoding is used by MOVDIR64b and ENQCMD instructions.
        // When the ModR/M.reg field is used to select a memory operand, the following apply:
        // - The ES segment register is used as a base
        // - The ES segment register cannot be overridden
        // - The size of the base register is selected by the address size, not the operand size.
        operand->Type = ND_OP_MEM;
        operand->Info.Memory.HasBase = ND_TRUE;
        operand->Info.Memory.Base = (ND_UINT8)((Instrux->Exs.r << 3) | Instrux->ModRm.reg);
        operand->Info.Memory.BaseSize = 2 << Instrux->AddrMode;
        operand->Info.Memory.HasSeg = ND_TRUE;
        operand->Info.Memory.Seg = NDR_ES;
        break;

    case ND_OPT_mM:
        // Sigh. rm field inside mod r/m encodes memory, even if mod is 3.
        operand->Type = ND_OP_MEM;
        operand->Info.Memory.HasBase = ND_TRUE;
        operand->Info.Memory.Base = (ND_UINT8)((Instrux->Exs.m << 3) | Instrux->ModRm.rm);
        operand->Info.Memory.BaseSize = 2 << Instrux->AddrMode;
        operand->Info.Memory.HasSeg = ND_TRUE;
        operand->Info.Memory.Seg = NdGetSegOverride(Instrux, NDR_DS);
        break;

    case ND_OPT_rT:
        // Tile register encoded in ModR/M.reg field.
        operand->Type = ND_OP_REG;
        operand->Info.Register.Type = ND_REG_TILE;
        operand->Info.Register.Size = size;
        operand->Info.Register.Reg = Instrux->ModRm.reg;

        // #UD if a tile register > 7 is encoded.
        if (Instrux->Exs.r != 0)
        {
            return ND_STATUS_INVALID_REGISTER_IN_INSTRUCTION;
        }

        break;

    case ND_OPT_mT:
        // Tile register encoded in ModR/M.rm field.
        operand->Type = ND_OP_REG;
        operand->Info.Register.Type = ND_REG_TILE;
        operand->Info.Register.Size = size;
        operand->Info.Register.Reg = Instrux->ModRm.rm;

        // #UD if a tile register > 7 is encoded.
        if (Instrux->Exs.b != 0)
        {
            return ND_STATUS_INVALID_REGISTER_IN_INSTRUCTION;
        }

        break;

    case ND_OPT_vT:
        // Tile register encoded in vex.vvvv field.
        operand->Type = ND_OP_REG;
        operand->Info.Register.Type = ND_REG_TILE;
        operand->Info.Register.Size = size;
        operand->Info.Register.Reg = Instrux->Exs.v;

        // #UD if a tile register > 7 is encoded.
        if (operand->Info.Register.Reg > 7)
        {
            return ND_STATUS_INVALID_REGISTER_IN_INSTRUCTION;
        }

        break;

    default:
        return ND_STATUS_INVALID_INSTRUX;
    }

    // Handle block addressing - used by AVX512_4FMAPS and AVX512_4VNNIW instructions. Also used by VP2INTERSECTD/Q
    // instructions. Also note that in block addressing, the base of the block is masked using the size of the block;
    // for example, for a block size of 1, the first register must be even; For a block size of 4, the first register
    // must be divisible by 4.
    if (operand->Type == ND_OP_REG)
    {
        if (opb != 0)
        {
            operand->Info.Register.Count = opb;
            operand->Info.Register.Reg &= ~(opb - 1);
            operand->Info.Register.IsBlock = ND_TRUE;
        }
        else
        {
            operand->Info.Register.Count = 1;
        }
    }

    // Store the operand encoding inside the bitmap.
    Instrux->OperandsEncodingMap |= (1 << gOperandMap[opt]);

    operand->Encoding = (ND_OPERAND_ENCODING)gOperandMap[opt];

    // Handle decorators.
    if (0 != opd)
    {
        // Check for mask register. Mask if present only if the operand supports masking and if the
        // mask register is not k0 (which implies "no masking").
        if ((opd & ND_OPD_MASK) && (Instrux->HasMask))
        {
            operand->Decorator.HasMask = ND_TRUE;
            operand->Decorator.Mask.Msk = (ND_UINT8)Instrux->Exs.k;
        }

        // Check for zeroing. The operand must support zeroing and the z bit inside evex3 must be set. Note that
        // zeroing is allowed only for register destinations, and NOT for memory.
        if ((opd & ND_OPD_Z) && (Instrux->HasZero))
        {
            if (operand->Type == ND_OP_MEM)
            {
                return ND_STATUS_ZEROING_ON_MEMORY;
            }

            operand->Decorator.HasZero = ND_TRUE;
        }

        // Check for broadcast again. We've already filled the broadcast size before parsing the op size.
        if ((opd & ND_OPD_BCAST) && (Instrux->HasBroadcast))
        {
            operand->Decorator.HasBroadcast = ND_TRUE;
            operand->Decorator.Broadcast.Size = (ND_UINT8)operand->Size;
            operand->Decorator.Broadcast.Count = (ND_UINT8)(bcstSize / operand->Size);
        }

        if (opd & ND_OPD_SAE)
        {
            operand->Decorator.HasSae = Instrux->HasSae;
        }

        if (opd & ND_OPD_ER)
        {
            operand->Decorator.HasEr = Instrux->HasEr;
        }
    }

    return status;
}


//
// NdFindInstruction
//
static NDSTATUS
NdFindInstruction(
    INSTRUX *Instrux,
    const ND_UINT8 *Code,
    ND_UINT8 Offset,
    ND_SIZET Size,
    ND_INSTRUCTION **InsDef
    )
{
    NDSTATUS status;
    const ND_TABLE *pTable;
    ND_INSTRUCTION *pIns;
    ND_BOOL stop, redf2, redf3;
    ND_UINT32 nextOpcode, nextIndex;

    UNREFERENCED_PARAMETER(Offset);

    // pre-init
    status = ND_STATUS_SUCCESS;
    pIns = (ND_INSTRUCTION *)ND_NULL;
    stop = ND_FALSE;
    nextOpcode = 0;
    redf2 = redf3 = ND_FALSE;

    switch (Instrux->EncMode)
    {
    case ND_ENCM_LEGACY:
        pTable = (const ND_TABLE *)gRootTable;
        break;
    case ND_ENCM_XOP:
        pTable = (const ND_TABLE *)gXopTable;
        break;
    case ND_ENCM_VEX:
        pTable = (const ND_TABLE *)gVexTable;
        break;
    case ND_ENCM_EVEX:
        pTable = (const ND_TABLE *)gEvexTable;
        break;
    default:
        pTable = (const ND_TABLE *)ND_NULL;
        break;
    }

    while ((!stop) && (ND_NULL != pTable))
    {
        switch (pTable->Type)
        {
        case ND_ILUT_INSTRUCTION:
            // We've found the leaf entry, which is an instruction - we can leave.
            pIns = (ND_INSTRUCTION *)(((ND_TABLE_INSTRUCTION *)pTable)->Instruction);
            stop = ND_TRUE;
            break;

        case ND_ILUT_OPCODE:
            // We need an opcode to keep going.
            status = NdFetchOpcode(Instrux, Code, Instrux->Length, Size);
            if (!ND_SUCCESS(status))
            {
                stop = ND_TRUE;
                break;
            }
            pTable = (const ND_TABLE *)pTable->Table[Instrux->OpCodeBytes[nextOpcode++]];
            break;

        case ND_ILUT_OPCODE_3DNOW:
            // We need an opcode to select the next table, but the opcode is AFTER the modrm/sib/displacement.
            if (!Instrux->HasModRm)
            {
                // Fetch modrm
                status = NdFetchModrmAndSib(Instrux, Code, Instrux->Length, Size);
                if (!ND_SUCCESS(status))
                {
                    stop = ND_TRUE;
                    break;
                }

                // Fetch displacement.
                status = NdFetchDisplacement(Instrux, Code, Instrux->Length, Size);
                if (!ND_SUCCESS(status))
                {
                    stop = ND_TRUE;
                    break;
                }
            }

            // Fetch the opcode, which is after the modrm and displacement.
            status = NdFetchOpcode(Instrux, Code, Instrux->Length, Size);
            if (!ND_SUCCESS(status))
            {
                stop = ND_TRUE;
                break;
            }

            pTable = (const ND_TABLE *)pTable->Table[Instrux->OpCodeBytes[nextOpcode++]];
            break;

        case ND_ILUT_MODRM_MOD:
            // We need modrm.mod to select the next table.
            if (!Instrux->HasModRm)
            {
                // Fetch modrm
                status = NdFetchModrmAndSib(Instrux, Code, Instrux->Length, Size);
                if (!ND_SUCCESS(status))
                {
                    stop = ND_TRUE;
                    break;
                }

                // Fetch displacement.
                status = NdFetchDisplacement(Instrux, Code, Instrux->Length, Size);
                if (!ND_SUCCESS(status))
                {
                    stop = ND_TRUE;
                    break;
                }
            }

            // Next index is either 0 (mem) or 1 (reg)
            pTable = (const ND_TABLE *)pTable->Table[Instrux->ModRm.mod == 3 ? 1 : 0];
            break;

        case ND_ILUT_MODRM_REG:
            // We need modrm.reg to select the next table.
            if (!Instrux->HasModRm)
            {
                // Fetch modrm
                status = NdFetchModrmAndSib(Instrux, Code, Instrux->Length, Size);
                if (!ND_SUCCESS(status))
                {
                    stop = ND_TRUE;
                    break;
                }

                // Fetch displacement.
                status = NdFetchDisplacement(Instrux, Code, Instrux->Length, Size);
                if (!ND_SUCCESS(status))
                {
                    stop = ND_TRUE;
                    break;
                }
            }

            // Next index is the reg.
            pTable = (const ND_TABLE *)pTable->Table[Instrux->ModRm.reg];
            break;

        case ND_ILUT_MODRM_RM:
            // We need modrm.rm to select the next table.
            if (!Instrux->HasModRm)
            {
                // Fetch modrm
                status = NdFetchModrmAndSib(Instrux, Code, Instrux->Length, Size);
                if (!ND_SUCCESS(status))
                {
                    stop = ND_TRUE;
                    break;
                }

                // Fetch displacement.
                status = NdFetchDisplacement(Instrux, Code, Instrux->Length, Size);
                if (!ND_SUCCESS(status))
                {
                    stop = ND_TRUE;
                    break;
                }
            }

            // Next index is the rm.
            pTable = (const ND_TABLE *)pTable->Table[Instrux->ModRm.rm];
            break;

        case ND_ILUT_MAN_PREFIX:
            // We have mandatory prefixes.
            if ((Instrux->Rep == 0xF2) && !redf2)
            {
                // We can only redirect once through one mandatory prefix, otherwise we may
                // enter an infinite loop (see CRC32 Gw Eb -> 0x66 0xF2 0x0F ...)
                redf2 = ND_TRUE;
                nextIndex = ND_ILUT_INDEX_MAN_PREF_F2;
                Instrux->HasMandatoryF2 = ND_TRUE;
            }
            else if ((Instrux->Rep == 0xF3) && !redf3)
            {
                redf3 = ND_TRUE;
                nextIndex = ND_ILUT_INDEX_MAN_PREF_F3;
                Instrux->HasMandatoryF3 = ND_TRUE;
            }
            else if (Instrux->HasOpSize)
            {
                nextIndex = ND_ILUT_INDEX_MAN_PREF_66;
                Instrux->HasMandatory66 = ND_TRUE;
            }
            else
            {
                nextIndex = ND_ILUT_INDEX_MAN_PREF_NONE;
            }
            pTable = (const ND_TABLE *)pTable->Table[nextIndex];
            break;

        case ND_ILUT_MODE:
            {
                static const ND_UINT8 indexes[3] =
                {
                    ND_ILUT_INDEX_MODE_16, ND_ILUT_INDEX_MODE_32, ND_ILUT_INDEX_MODE_64
                };

                nextIndex = ND_ILUT_INDEX_MODE_NONE;

                if (ND_NULL != pTable->Table[indexes[Instrux->DefCode]])
                {
                    nextIndex = indexes[Instrux->DefCode];
                }

                pTable = (const ND_TABLE *)pTable->Table[nextIndex];
            }
            break;

        case ND_ILUT_DSIZE:
            {
                static const ND_UINT8 indexes[3] =
                {
                    ND_ILUT_INDEX_DSIZE_16, ND_ILUT_INDEX_DSIZE_32, ND_ILUT_INDEX_DSIZE_64
                };

                nextIndex = ND_ILUT_INDEX_DSIZE_NONE;

                if (ND_NULL != pTable->Table[indexes[Instrux->OpMode]])
                {
                    nextIndex = indexes[Instrux->OpMode];
                }

                // Handle default/forced redirections in 64 bit mode.
                if (ND_CODE_64 == Instrux->DefCode)
                {
                    if ((ND_NULL != pTable->Table[4]) && (!Instrux->HasOpSize || Instrux->Exs.w))
                    {
                        nextIndex = 4;
                    }
                    else if (ND_NULL != pTable->Table[5])
                    {
                        nextIndex = 5;
                    }
                }

                pTable = (const ND_TABLE *)pTable->Table[nextIndex];
            }
            break;

        case ND_ILUT_ASIZE:
            {
                static const ND_UINT8 indexes[3] = {ND_ILUT_INDEX_ASIZE_16, ND_ILUT_INDEX_ASIZE_32, ND_ILUT_INDEX_ASIZE_64};

                nextIndex = ND_ILUT_INDEX_ASIZE_NONE;

                if (ND_NULL != pTable->Table[indexes[Instrux->AddrMode]])
                {
                    nextIndex = indexes[Instrux->AddrMode];
                }

                pTable = (const ND_TABLE *)pTable->Table[nextIndex];
            }
            break;

        case ND_ILUT_AUXILIARY:
            // Auxiliary redirection. Default to table[0] if nothing matches.
            if (Instrux->HasRex && Instrux->Rex.b && (ND_NULL != pTable->Table[ND_ILUT_INDEX_AUX_REXB]))
            {
                nextIndex = ND_ILUT_INDEX_AUX_REXB;
            }
            else if (Instrux->HasRex && Instrux->Rex.w && (ND_NULL != pTable->Table[ND_ILUT_INDEX_AUX_REXW]))
            {
                nextIndex = ND_ILUT_INDEX_AUX_REXW;
            }
            else if ((Instrux->DefCode == ND_CODE_64) && (ND_NULL != pTable->Table[ND_ILUT_INDEX_AUX_O64]))
            {
                nextIndex = ND_ILUT_INDEX_AUX_O64;
            }
            else if (Instrux->Rep == ND_PREFIX_G1_REPE_REPZ && (ND_NULL != pTable->Table[ND_ILUT_INDEX_AUX_F3]))
            {
                nextIndex = ND_ILUT_INDEX_AUX_F3;
            }
            else if ((Instrux->Rep != 0) && (ND_NULL != pTable->Table[ND_ILUT_INDEX_AUX_REP]))
            {
                nextIndex = ND_ILUT_INDEX_AUX_REP;
            }
            else if (Instrux->DefCode == ND_CODE_64 && Instrux->HasModRm && 
                Instrux->ModRm.mod == 0 && Instrux->ModRm.rm == NDR_RBP && 
                ND_NULL != pTable->Table[ND_ILUT_INDEX_AUX_RIPREL])
            {
                nextIndex = ND_ILUT_INDEX_AUX_RIPREL;
            }
            else
            {
                nextIndex = ND_ILUT_INDEX_AUX_NONE;
            }
            pTable = (const ND_TABLE *)pTable->Table[nextIndex];
            break;

        case ND_ILUT_VENDOR:
            // Vendor redirection. Go to the vendor specific entry.
            if (ND_NULL != pTable->Table[Instrux->VendMode])
            {
                pTable = (const ND_TABLE *)pTable->Table[Instrux->VendMode];
            }
            else
            {
                pTable = (const ND_TABLE *)pTable->Table[ND_VEND_ANY];
            }
            break;

        case ND_ILUT_FEATURE:
            // Feature redirection. Normally NOP if feature is not set, but may be something else if feature is set.
            if ((ND_NULL != pTable->Table[ND_ILUT_FEATURE_MPX]) && !!(Instrux->FeatMode & ND_FEAT_MPX))
            {
                pTable = (const ND_TABLE *)pTable->Table[ND_ILUT_FEATURE_MPX];
            }
            else if ((ND_NULL != pTable->Table[ND_ILUT_FEATURE_CET]) && !!(Instrux->FeatMode & ND_FEAT_CET))
            {
                pTable = (const ND_TABLE *)pTable->Table[ND_ILUT_FEATURE_CET];
            }
            else if ((ND_NULL != pTable->Table[ND_ILUT_FEATURE_CLDEMOTE]) && !!(Instrux->FeatMode & ND_FEAT_CLDEMOTE))
            {
                pTable = (const ND_TABLE *)pTable->Table[ND_ILUT_FEATURE_CLDEMOTE];
            }
            else if ((ND_NULL != pTable->Table[ND_ILUT_FEATURE_PITI]) && !!(Instrux->FeatMode & ND_FEAT_PITI))
            {
                pTable = (const ND_TABLE *)pTable->Table[ND_ILUT_FEATURE_PITI];
            }
            else
            {
                pTable = (const ND_TABLE *)pTable->Table[ND_ILUT_FEATURE_NONE];
            }
            break;

        case ND_ILUT_VEX_MMMMM:
            pTable = (const ND_TABLE *)pTable->Table[Instrux->Exs.m];
            break;

        case ND_ILUT_VEX_PP:
            pTable = (const ND_TABLE *)pTable->Table[Instrux->Exs.p];
            break;

        case ND_ILUT_VEX_L:
            if (Instrux->HasEvex && Instrux->Exs.bm)
            {
                // We have evex; we need to fetch the modrm now, because we have to make sure we don't have SAE or ER;
                // if we do have SAE or ER, we have to check the modrm byte and see if it is a reg-reg form (mod = 3),
                // in which case L'L is forced to the maximum vector length of the instruction. We know for sure that
                // all EVEX instructions have modrm.
                if (!Instrux->HasModRm)
                {
                    // Fetch modrm
                    status = NdFetchModrmAndSib(Instrux, Code, Instrux->Length, Size);
                    if (!ND_SUCCESS(status))
                    {
                        stop = ND_TRUE;
                        break;
                    }

                    // Fetch displacement.
                    status = NdFetchDisplacement(Instrux, Code, Instrux->Length, Size);
                    if (!ND_SUCCESS(status))
                    {
                        stop = ND_TRUE;
                        break;
                    }
                }

                if (3 == Instrux->ModRm.mod)
                {
                    // We use the maximum vector length of the instruction. If the instruction does not support
                    // SAE or ER, a #UD would be generated. We check for this later.
                    if (ND_NULL != pTable->Table[2])
                    {
                        pTable = (const ND_TABLE *)pTable->Table[2];
                    }
                    else if (ND_NULL != pTable->Table[1])
                    {
                        pTable = (const ND_TABLE *)pTable->Table[1];
                    }
                    else
                    {
                        pTable = (const ND_TABLE *)pTable->Table[0];
                    }
                }
                else
                {
                    // Mod is mem, we simply use L'L for indexing, as no SAE or ER can be present.
                    pTable = (const ND_TABLE *)pTable->Table[Instrux->Exs.l];
                }
            }
            else
            {
                pTable = (const ND_TABLE *)pTable->Table[Instrux->Exs.l];
            }
            break;

        case ND_ILUT_VEX_W:
            pTable = (const ND_TABLE *)pTable->Table[Instrux->Exs.w];
            break;

        case ND_ILUT_VEX_WI:
            pTable = (const ND_TABLE *)pTable->Table[Instrux->DefCode == ND_CODE_64 ? Instrux->Exs.w : 0];
            break;

        default:
            status = ND_STATUS_INTERNAL_ERROR;
            stop = ND_TRUE;
            break;
        }
    }

    if (!ND_SUCCESS(status))
    {
        goto cleanup_and_exit;
    }

    if (ND_NULL != pIns)
    {
        // Bingo! Valid instruction found for the encoding. If Modrm is needed and we didn't fetch it - do it now.
        if ((pIns->Attributes & ND_FLAG_MODRM) && (!Instrux->HasModRm))
        {
            if (0 == (pIns->Attributes & ND_FLAG_MFR))
            {
                // Fetch Mod R/M and SIB.
                status = NdFetchModrmAndSib(Instrux, Code, Instrux->Length, Size);
                if (!ND_SUCCESS(status))
                {
                    goto cleanup_and_exit;
                }

                // Fetch displacement.
                status = NdFetchDisplacement(Instrux, Code, Instrux->Length, Size);
                if (!ND_SUCCESS(status))
                {
                    goto cleanup_and_exit;
                }
            }
            else
            {
                // Handle special MOV with control and debug registers - the mod is always forced to register. SIB
                // and displacement is ignored.
                status = NdFetchModrm(Instrux, Code, Instrux->Length, Size);
                if (!ND_SUCCESS(status))
                {
                    goto cleanup_and_exit;
                }
            }
        }

        // Store primary opcode.
        Instrux->PrimaryOpCode = Instrux->OpCodeBytes[Instrux->OpLength - 1];

        Instrux->MainOpOffset = ND_IS_3DNOW(Instrux) ?
                                       Instrux->Length - 1 : Instrux->OpOffset + Instrux->OpLength - 1;

        // Make sure the instruction is valid in the given mode.
        if ((ND_CODE_64 == Instrux->DefCode) && (pIns->Attributes & ND_FLAG_I64))
        {
            status = ND_STATUS_INVALID_ENCODING_IN_MODE;
        }

        if ((ND_CODE_64 != Instrux->DefCode) && (pIns->Attributes & ND_FLAG_O64))
        {
            status = ND_STATUS_INVALID_ENCODING_IN_MODE;
        }
    }
    else
    {
        status = ND_STATUS_INVALID_ENCODING;
    }

cleanup_and_exit:
    *InsDef = pIns;

    return status;
}



//
// NdGetVectorLength
//
static __forceinline NDSTATUS
NdGetVectorLength(
    INSTRUX *Instrux
    )
{
    if (Instrux->HasEr || Instrux->HasSae || Instrux->HasIgnEr)
    {
        // Embedded rounding or SAE present, force the vector length to 512 or scalar.
        if ((Instrux->TupleType == ND_TUPLE_T1S) || 
            (Instrux->TupleType == ND_TUPLE_T1S8) ||
            (Instrux->TupleType == ND_TUPLE_T1S16) ||
            (Instrux->TupleType == ND_TUPLE_T1F))
        {
            Instrux->VecMode = Instrux->EfVecMode = ND_VECM_128;
        }
        else
        {
            Instrux->VecMode = Instrux->EfVecMode = ND_VECM_512;
        }

        return ND_STATUS_SUCCESS;
    }

    // Decode EVEX vector length. Also take into consideration the "ignore L" flag.
    switch (Instrux->Exs.l)
    {
    case 0:
        Instrux->VecMode = ND_VECM_128;
        Instrux->EfVecMode = ND_VECM_128;
        break;
    case 1:
        Instrux->VecMode = ND_VECM_256;
        Instrux->EfVecMode = (Instrux->Attributes & ND_FLAG_LIG) ? ND_VECM_128 : ND_VECM_256;
        break;
    case 2:
        Instrux->VecMode = ND_VECM_512;
        Instrux->EfVecMode = (Instrux->Attributes & ND_FLAG_LIG) ? ND_VECM_128 : ND_VECM_512;
        break;
    default:
        return ND_STATUS_BAD_EVEX_LL;
    }

    // Some instructions don't support 128 bit vectors.
    if ((ND_VECM_128 == Instrux->EfVecMode) && (0 != (Instrux->Attributes & ND_FLAG_NOL0)))
    {
        return ND_STATUS_INVALID_ENCODING;
    }

    return ND_STATUS_SUCCESS;
}


//
// NdGetAddrAndOpMode
//
static __forceinline NDSTATUS
NdGetAddrAndOpMode(
    INSTRUX *Instrux
    )
{
    // Fill in addressing mode & default op size.
    switch (Instrux->DefCode)
    {
    case ND_CODE_16:
        Instrux->AddrMode = Instrux->HasAddrSize ? ND_ADDR_32 : ND_ADDR_16;
        Instrux->OpMode = Instrux->HasOpSize ? ND_OPSZ_32 : ND_OPSZ_16;
        break;
    case ND_CODE_32:
        Instrux->AddrMode = Instrux->HasAddrSize ? ND_ADDR_16 : ND_ADDR_32;
        Instrux->OpMode = Instrux->HasOpSize ? ND_OPSZ_16 : ND_OPSZ_32;
        break;
    case ND_CODE_64:
        Instrux->AddrMode = Instrux->HasAddrSize ? ND_ADDR_32 : ND_ADDR_64;
        Instrux->OpMode = Instrux->Exs.w ? ND_OPSZ_64 : (Instrux->HasOpSize ? ND_OPSZ_16 : ND_OPSZ_32);
        break;
    default:
        return ND_STATUS_INVALID_INSTRUX;
    }

    return ND_STATUS_SUCCESS;
}


//
// NdGetEffectiveOpMode
//
static __forceinline NDSTATUS
NdGetEffectiveOpMode(
    INSTRUX *Instrux
    )
{
    static const ND_UINT8 szLut[3] = { ND_SIZE_16BIT, ND_SIZE_32BIT, ND_SIZE_64BIT };
    ND_BOOL width, f64, d64, has66;

    if ((ND_CODE_64 != Instrux->DefCode) && !!(Instrux->Attributes & ND_FLAG_IWO64))
    {
        // Some instructions ignore VEX/EVEX.W field outside 64 bit mode, and treat it as 0.
        Instrux->Exs.w = 0;
    }

    // Extract the flags.
    width = (0 != Instrux->Exs.w) && !(Instrux->Attributes & ND_FLAG_WIG);
    // In 64 bit mode, the operand is forced to 64 bit. Size-changing prefixes are ignored.
    f64 = 0 != (Instrux->Attributes & ND_FLAG_F64) && (ND_VEND_AMD != Instrux->VendMode);
    // In 64 bit mode, the operand defaults to 64 bit. No 32 bit form of the instruction exists. Note that on AMD,
    // only default 64 bit operands exist, even for branches - no operand is forced to 64 bit.
    d64 = (0 != (Instrux->Attributes & ND_FLAG_D64)) ||
          (0 != (Instrux->Attributes & ND_FLAG_F64) && (ND_VEND_AMD == Instrux->VendMode));
    // Check if 0x66 is indeed interpreted as a size changing prefix. Note that if 0x66 is a mandatory prefix,
    // then it won't be interpreted as a size changing prefix. However, there is an exception: MOVBE and CRC32
    // have mandatory 0xF2, and 0x66 is in fact a size changing prefix.
    has66 = Instrux->HasOpSize && (!Instrux->HasMandatory66 || (Instrux->Attributes & ND_FLAG_S66));

    // Fill in the effective operand size.
    switch (Instrux->DefCode)
    {
    case ND_CODE_16:
        Instrux->EfOpMode = has66 ? ND_OPSZ_32 : ND_OPSZ_16;
        break;
    case ND_CODE_32:
        Instrux->EfOpMode = has66 ? ND_OPSZ_16 : ND_OPSZ_32;
        break;
    case ND_CODE_64:
        Instrux->EfOpMode = (width || f64 || (d64 && !has66)) ? ND_OPSZ_64 : (has66 ? ND_OPSZ_16 : ND_OPSZ_32);
        Instrux->AddrMode = !!(Instrux->Attributes & ND_FLAG_I67) ? ND_ADDR_64 : Instrux->AddrMode;
        break;
    default:
        return ND_STATUS_INVALID_INSTRUX;
    }

    // Fill in the default word length. It can't be more than 8 bytes.
    Instrux->WordLength = szLut[Instrux->EfOpMode];

    return ND_STATUS_SUCCESS;
}


//
// NdPostProcessEvex
//
static NDSTATUS
NdPostProcessEvex(
    INSTRUX *Instrux
    )
{
    // Handle embedded broadcast/rounding-control.
    if (Instrux->Exs.bm == 1)
    {
        if (Instrux->ModRm.mod == 3)
        {
            // reg form for the instruction, check for ER or SAE support.
            if (Instrux->ValidDecorators.Er)
            {
                Instrux->HasEr = 1;
                Instrux->HasSae = 1;
                Instrux->RoundingMode = (ND_UINT8)Instrux->Exs.l;
            }
            else if (Instrux->ValidDecorators.Sae)
            {
                Instrux->HasSae = 1;
            }
            else if (!!(Instrux->Attributes & ND_FLAG_IER))
            {
                // The encoding behaves as if embedded rounding is enabled, but it is in fact ignored.
                Instrux->HasIgnEr = 1;
            }
            else
            {
                return ND_STATUS_ER_SAE_NOT_SUPPORTED;
            }
        }
        else
        {
            // mem form for the instruction, check for broadcast.
            if (Instrux->ValidDecorators.Broadcast)
            {
                Instrux->HasBroadcast = 1;
            }
            else
            {
                return ND_STATUS_BROADCAST_NOT_SUPPORTED;
            }
        }
    }

    // Handle masking.
    if (Instrux->Exs.k != 0)
    {
        if (Instrux->ValidDecorators.Mask)
        {
            Instrux->HasMask = 1;
        }
        else
        {
            return ND_STATUS_MASK_NOT_SUPPORTED;
        }
    }
    else
    {
        if (!!(Instrux->Attributes & ND_FLAG_MMASK))
        {
            return ND_STATUS_MASK_REQUIRED;
        }
    }

    // Handle zeroing.
    if (Instrux->Exs.z != 0)
    {
        if (Instrux->ValidDecorators.Zero)
        {
            // Zeroing restrictions:
            // - valid with register only;
            // - valid only if masking is also used;
            if (Instrux->HasMask)
            {
                Instrux->HasZero = 1;
            }
            else
            {
                return ND_STATUS_ZEROING_NO_MASK;
            }
        }
        else
        {
            return ND_STATUS_ZEROING_NOT_SUPPORTED;
        }
    }

    // EVEX instructions with 8 bit displacement use compressed displacement addressing, where the displacement
    // is scaled according to the data type accessed by the instruction.
    if (Instrux->HasDisp && Instrux->DispLength == 1)
    {
        Instrux->HasCompDisp = ND_TRUE;
    }

    return ND_STATUS_SUCCESS;
}


//
// NdValidateInstruction
//
static __forceinline NDSTATUS
NdValidateInstruction(
    INSTRUX *Instrux
    )
{
    // If LOCK is present, make sure that the instruction 1. supports LOCKing and 2. the destination is memory.
    // A special case are MOV to/from CRs, on AMD, in 16/32 bit mode.
    if (Instrux->HasLock && (0 == (Instrux->Attributes & ND_FLAG_LOCK_SPECIAL) || (ND_CODE_64 == Instrux->DefCode)) &&
        (!ND_LOCK_SUPPORT(Instrux) || (Instrux->Operands[0].Type != ND_OP_MEM)))
    {
        return ND_STATUS_BAD_LOCK_PREFIX;
    }

    // Some instructions (example: PTWRITE) do not accept the 0x66 prefix.
    if (Instrux->HasOpSize && (0 != (Instrux->Attributes & ND_FLAG_NO66)))
    {
        return ND_STATUS_66_NOT_ACCEPTED;
    }

    // 16 bit addressing is checked when decoding the memory operand (if present).
    // RIP-relative addressing is checked when decoding the memory operand (if present).
    // Register validity is checked when decoding the said register.
    // Memory/register encoding for instructions which don't support it is checked when decoding the operand.

    // VEX/EVEX validations.
    if (ND_ENCM_LEGACY != Instrux->EncMode)
    {
        // Instructions that don't use VEX/XOP/EVEX vvvv field must set it to 1111b/0, otherwise a #UD will be generated.
        if ((0 == (Instrux->OperandsEncodingMap & (1 << ND_OPE_V))) && (0 != Instrux->Exs.v))
        {
            return ND_STATUS_VEX_VVVV_MUST_BE_ZERO;
        }

        // Instruction that don't use EVEX.V' field must set to to 1b/0, otherwise a #UD will be generated.
        if ((0 == (Instrux->OperandsEncodingMap & (1 << ND_OPE_V))) && !ND_HAS_VSIB(Instrux) && (0 != Instrux->Exs.vp))
        {
            return ND_STATUS_BAD_EVEX_V_PRIME;
        }

        // VSIB instructions have a restriction: the same vector register can't be used by more than one operand.
        // The exception is SCATTER*, which can use the VSIB reg as two sources.
        if (ND_HAS_VSIB(Instrux) && Instrux->Category != ND_CAT_SCATTER)
        {
            ND_UINT8 usedVects[32] = { 0 };
            ND_UINT32 i;

            for (i = 0; i < Instrux->OperandsCount; i++)
            {
                if (Instrux->Operands[i].Type == ND_OP_REG && Instrux->Operands[i].Info.Register.Type == ND_REG_SSE)
                {
                    if (++usedVects[Instrux->Operands[i].Info.Register.Reg] > 1)
                    {
                        return ND_STATUS_INVALID_VSIB_REGS;
                    }
                }
                else if (Instrux->Operands[i].Type == ND_OP_MEM)
                {
                    if (++usedVects[Instrux->Operands[i].Info.Memory.Index] > 1)
                    {
                        return ND_STATUS_INVALID_VSIB_REGS;
                    }
                }
            }
        }

        // Handle AMX exception class.
        if (Instrux->ExceptionClass == ND_EXC_AMX)
        {
            if (Instrux->ExceptionType == ND_EXT_AMX_E4)
            {
                // #UD if srcdest == src1, srcdest == src2 or src1 == src2. All three operands are tile regs.
                if (Instrux->Operands[0].Info.Register.Reg == Instrux->Operands[1].Info.Register.Reg ||
                    Instrux->Operands[0].Info.Register.Reg == Instrux->Operands[2].Info.Register.Reg ||
                    Instrux->Operands[1].Info.Register.Reg == Instrux->Operands[2].Info.Register.Reg)
                {
                    return ND_STATUS_INVALID_TILE_REGS;
                }
            }
            else
            {
                // #UD if vex.vvvv is not 0 (0b1111 negated) for all other exception classes, as they do not use it.
                if (Instrux->Exs.v != 0)
                {
                    return ND_STATUS_VEX_VVVV_MUST_BE_ZERO;
                }
            }
        }

        // Handle EVEX exception class.
        if (Instrux->ExceptionClass == ND_EXC_EVEX)
        {
            // If E4* or E10* exception class is used (check out AVX512-FP16 instructions), an additional #UD case
            // exists: if the destination register is equal to either of the source registers.
            if (Instrux->ExceptionType == ND_EXT_E4S || Instrux->ExceptionType == ND_EXT_E10S)
            {
                // Note that operand 0 is the destination, operand 1 is the mask, operand 2 is first source, operand
                // 3 is the second source.

                if (Instrux->Operands[0].Type == ND_OP_REG && Instrux->Operands[2].Type == ND_OP_REG &&
                    Instrux->Operands[0].Info.Register.Reg == Instrux->Operands[2].Info.Register.Reg)
                {
                    return ND_STATUS_INVALID_DEST_REGS;
                }

                
                if (Instrux->Operands[0].Type == ND_OP_REG && Instrux->Operands[3].Type == ND_OP_REG &&
                    Instrux->Operands[0].Info.Register.Reg == Instrux->Operands[3].Info.Register.Reg)
                {
                    return ND_STATUS_INVALID_DEST_REGS;
                }
            }
        }
    }

    return ND_STATUS_SUCCESS;
}


//
// NdDecodeEx2
//
NDSTATUS
NdDecodeEx2(
    INSTRUX *Instrux,
    const ND_UINT8 *Code,
    ND_SIZET Size,
    ND_UINT8 DefCode,
    ND_UINT8 DefData,
    ND_UINT8 DefStack,
    ND_UINT8 Vendor
    )
{
    ND_CONTEXT opt;

    NdInitContext(&opt);

    opt.DefCode = DefCode;
    opt.DefData = DefData;
    opt.DefStack = DefStack;
    opt.VendMode = Vendor;
    opt.FeatMode = ND_FEAT_ALL; // Optimistically decode everything, as if all features are enabled.

    return NdDecodeWithContext(Instrux, Code, Size, &opt);
}


NDSTATUS
NdDecodeWithContext(
    INSTRUX *Instrux,
    const ND_UINT8 *Code,
    ND_SIZET Size,
    ND_CONTEXT *Context
    )
{
    NDSTATUS status;
    PND_INSTRUCTION pIns;
    ND_UINT32 opIndex;
    ND_SIZET i;

    // pre-init
    status = ND_STATUS_SUCCESS;
    pIns = (PND_INSTRUCTION)ND_NULL;
    opIndex = 0;

    // validate
    if (ND_NULL == Instrux)
    {
        return ND_STATUS_INVALID_PARAMETER;
    }

    if (ND_NULL == Code)
    {
        return ND_STATUS_INVALID_PARAMETER;
    }

    if (Size == 0)
    {
        return ND_STATUS_INVALID_PARAMETER;
    }

    if (ND_NULL == Context)
    {
        return ND_STATUS_INVALID_PARAMETER;
    }

    if (ND_CODE_64 < Context->DefCode)
    {
        return ND_STATUS_INVALID_PARAMETER;
    }

    if (ND_DATA_64 < Context->DefData)
    {
        return ND_STATUS_INVALID_PARAMETER;
    }

    if (ND_VEND_CYRIX < Context->VendMode)
    {
        return ND_STATUS_INVALID_PARAMETER;
    }

    // Initialize with zero.
    nd_memzero(Instrux, sizeof(INSTRUX));

    Instrux->DefCode = (ND_UINT8)Context->DefCode;
    Instrux->DefData = (ND_UINT8)Context->DefData;
    Instrux->DefStack = (ND_UINT8)Context->DefStack;
    Instrux->VendMode = (ND_UINT8)Context->VendMode;
    Instrux->FeatMode = (ND_UINT8)Context->FeatMode;

    // Copy the instruction bytes.
    for (opIndex = 0; opIndex < ((Size < ND_MAX_INSTRUCTION_LENGTH) ? Size : ND_MAX_INSTRUCTION_LENGTH); opIndex++)
    {
        Instrux->InstructionBytes[opIndex] = Code[opIndex];
    }

    // Fetch prefixes. We peek at the first byte, if that's not a prefix, there's no need to call the main decoder.
    if (ND_PREF_CODE_NONE != gPrefixesMap[Instrux->InstructionBytes[0]])
    {
        status = NdFetchPrefixes(Instrux, Instrux->InstructionBytes, 0, Size);
        if (!ND_SUCCESS(status))
        {
            return status;
        }
    }

    // Get addressing mode & operand size.
    status = NdGetAddrAndOpMode(Instrux);
    if (!ND_SUCCESS(status))
    {
        return status;
    }

    // Start iterating the tables, in order to extract the instruction entry.
    status = NdFindInstruction(Instrux, Instrux->InstructionBytes, Instrux->Length, Size, &pIns);
    if (!ND_SUCCESS(status))
    {
        return status;
    }

    // Instruction found, copy information inside the Instrux.
    Instrux->Attributes = pIns->Attributes;
    Instrux->Instruction = Instrux->Iclass = (ND_INS_CLASS)pIns->Instruction;
    Instrux->Category = (ND_INS_CATEGORY)pIns->Category;
    Instrux->IsaSet = (ND_INS_SET)pIns->IsaSet;
    Instrux->FlagsAccess.Undefined.Raw = pIns->SetFlags & pIns->ClearedFlags;
    Instrux->FlagsAccess.Tested.Raw = pIns->TestedFlags;
    Instrux->FlagsAccess.Modified.Raw = pIns->ModifiedFlags;
    Instrux->FlagsAccess.Set.Raw = pIns->SetFlags ^ Instrux->FlagsAccess.Undefined.Raw;
    Instrux->FlagsAccess.Cleared.Raw = pIns->ClearedFlags ^ Instrux->FlagsAccess.Undefined.Raw;
    Instrux->CpuidFlag.Flag = pIns->CpuidFlag;
    Instrux->ValidModes.Raw = pIns->ValidModes;
    Instrux->ValidPrefixes.Raw = pIns->ValidPrefixes;
    Instrux->ValidDecorators.Raw = pIns->ValidDecorators;
    *((ND_UINT8*)&Instrux->FpuFlagsAccess) = pIns->FpuFlags;
    // Valid for EVEX, VEX and SSE instructions only. A value of 0 means it's not used.
    Instrux->ExceptionClass = pIns->ExcClass;
    Instrux->ExceptionType = pIns->ExcType;
    // Used only by EVEX instructions.
    Instrux->TupleType = pIns->TupleType;

    // Copy the mnemonic, up until the ND_NULL terminator.
    for (i = 0; i < sizeof(Instrux->Mnemonic); i++)
    {
        Instrux->Mnemonic[i] = gMnemonics[pIns->Mnemonic][i];
        if (Instrux->Mnemonic[i] == 0)
        {
            break;
        }
    }

    // Get effective operand mode.
    status = NdGetEffectiveOpMode(Instrux);
    if (!ND_SUCCESS(status))
    {
        return status;
    }

    if (Instrux->HasEvex)
    {
        // Post-process EVEX encoded instructions. This does two thing:
        // - check and fill in decorator info;
        // - generate error for invalid broadcast/rounding, mask or zeroing bits.
        status = NdPostProcessEvex(Instrux);
        if (!ND_SUCCESS(status))
        {
            return status;
        }
    }

    if (ND_HAS_VECTOR(Instrux))
    {
        // Get vector length.
        status = NdGetVectorLength(Instrux);
        if (!ND_SUCCESS(status))
        {
            return status;
        }
    }

    // Handle condition byte, if present.
    if (ND_HAS_SSE_CONDITION(Instrux))
    {
        Instrux->SseCondition = Instrux->Immediate1 & 0x1F;
    }

    // Handle predicate, if present.
    if (ND_HAS_CONDITION(Instrux))
    {
        Instrux->Condition = Instrux->Predicate = Instrux->PrimaryOpCode & 0xF;
    }

    Instrux->ExpOperandsCount = ND_EXP_OPS_CNT(pIns->OpsCount);
    Instrux->OperandsCount = Instrux->ExpOperandsCount + ND_IMP_OPS_CNT(pIns->OpsCount);

    // And now decode each operand.
    for (opIndex = 0; opIndex < Instrux->OperandsCount; ++opIndex)
    {
        status = NdParseOperand(Instrux, Instrux->InstructionBytes, Instrux->Length, Size, 
                                opIndex, pIns->Operands[opIndex]);
        if (!ND_SUCCESS(status))
        {
            return status;
        }
    }

    // Check if the instruction is XACQUIRE or XRELEASE enabled.
    if ((Instrux->Rep != 0) && (Instrux->HasLock || (!!Instrux->ValidPrefixes.HleNoLock)) &&
        (Instrux->Operands[0].Type == ND_OP_MEM))
    {
        if ((ND_XACQUIRE_SUPPORT(Instrux) || ND_HLE_SUPPORT(Instrux)) && (Instrux->Rep == ND_PREFIX_G1_XACQUIRE))
        {
            Instrux->IsXacquireEnabled = ND_TRUE;
        }
        else if ((ND_XRELEASE_SUPPORT(Instrux) || ND_HLE_SUPPORT(Instrux)) && (Instrux->Rep == ND_PREFIX_G1_XRELEASE))
        {
            Instrux->IsXreleaseEnabled = ND_TRUE;
        }
    }

    // Check if the instruction is REPed.
    Instrux->IsRepeated = ((Instrux->Rep != 0) && (ND_REP_SUPPORT(Instrux) || ND_REPC_SUPPORT(Instrux)));

    // Check if the instruction is CET tracked. The do not track prefix (0x3E) works only for indirect near JMP and CALL
    // instructions. It is always enabled for far JMP and CALL instructions.
    Instrux->IsCetTracked = ND_HAS_CETT(Instrux) && ((!ND_DNT_SUPPORT(Instrux)) ||
                                                     (Instrux->Seg != ND_PREFIX_G2_NO_TRACK));

    // Fill in branch information.
    if (!!(Instrux->RipAccess & ND_ACCESS_ANY_WRITE))
    {
        Instrux->BranchInfo.IsBranch = 1;
        Instrux->BranchInfo.IsConditional = Instrux->Category == ND_CAT_COND_BR;
        // Indirect branches are those which get their target address from a register or memory, including RET familly.
        Instrux->BranchInfo.IsIndirect = ((!Instrux->Operands[0].Flags.IsDefault) && 
            ((Instrux->Operands[0].Type == ND_OP_REG) || (Instrux->Operands[0].Type == ND_OP_MEM))) || 
            (Instrux->Category == ND_CAT_RET);
        Instrux->BranchInfo.IsFar = !!(Instrux->CsAccess & ND_ACCESS_ANY_WRITE);
    }

    // Do instruction validations. These checks are made in order to filter out encodings that would normally
    // be invalid and would generate #UD.
    status = NdValidateInstruction(Instrux);
    if (!ND_SUCCESS(status))
    {
        return status;
    }

    // All done! Instruction successfully decoded!
    return ND_STATUS_SUCCESS;
}


//
// NdDecodeEx
//
NDSTATUS
NdDecodeEx(
    INSTRUX *Instrux,
    const ND_UINT8 *Code,
    ND_SIZET Size,
    ND_UINT8 DefCode,
    ND_UINT8 DefData
    )
{
    return NdDecodeEx2(Instrux, Code, Size, DefCode, DefData, DefCode, ND_VEND_ANY);
}


//
// NdDecode
//
NDSTATUS
NdDecode(
    INSTRUX *Instrux,
    const ND_UINT8 *Code,
    ND_UINT8 DefCode,
    ND_UINT8 DefData
    )
{
    return NdDecodeEx2(Instrux, Code, ND_MAX_INSTRUCTION_LENGTH, DefCode, DefData, DefCode, ND_VEND_ANY);
}


//
// NdInitContext
//
void
NdInitContext(
    ND_CONTEXT *Context
    )
{
    nd_memzero(Context, sizeof(*Context));
}
