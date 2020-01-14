/*
 * Intel ACPI Component Architecture
 * AML/ASL+ Disassembler version 20190509 (64-bit version)
 * Copyright (c) 2000 - 2019 Intel Corporation
 * 
 * Disassembling to symbolic ASL+ operators
 *
 * Disassembly of iASLokM6gi.aml, Tue Jan 14 17:18:48 2020
 *
 * Original Table Header:
 *     Signature        "SSDT"
 *     Length           0x00000437 (1079)
 *     Revision         0x02
 *     Checksum         0xD9
 *     OEM ID           "hack"
 *     OEM Table ID     "_FANQ"
 *     OEM Revision     0x00000000 (0)
 *     Compiler ID      "INTL"
 *     Compiler Version 0x20190509 (538510601)
 */
DefinitionBlock ("", "SSDT", 2, "hack", "_FANQ", 0x00000000)
{
    External (_SB_.PCI0.LPCB.EC__, DeviceObj)
    External (_SB_.PCI0.LPCB.EC__.SCM0, DeviceObj)
    External (_SB_.PCI0.LPCB.EC__.SCM0.TD72, FieldUnitObj)
    External (_SB_.PCI0.LPCB.EC__.SCM0.TD73, FieldUnitObj)
    External (_SB_.PCI0.LPCB.EC__.SCM0.TD74, FieldUnitObj)
    External (_SB_.PCI0.LPCB.EC__.SCM0.TD75, FieldUnitObj)
    External (_SB_.PCI0.LPCB.EC__.SCM0.TD76, FieldUnitObj)
    External (_SB_.PCI0.LPCB.EC__.SCM0.TD77, FieldUnitObj)
    External (_SB_.PCI0.LPCB.EC__.SCM0.TD8A, FieldUnitObj)
    External (_SB_.PCI0.LPCB.EC__.SCM0.TD8B, FieldUnitObj)
    External (_SB_.PCI0.LPCB.EC__.SCM0.TD8C, FieldUnitObj)
    External (_SB_.PCI0.LPCB.EC__.SCM0.TD8D, FieldUnitObj)
    External (_SB_.PCI0.LPCB.EC__.SCM0.TD8E, FieldUnitObj)
    External (_SB_.PCI0.LPCB.EC__.SCM0.TD8F, FieldUnitObj)
    External (_SB_.PCI0.LPCB.EC__.SCM0.TDCD, FieldUnitObj)
    External (_SB_.PCI0.LPCB.EC__.SCM0.TDF4, FieldUnitObj)

    Scope (_SB.PCI0.LPCB.EC)
    {
        Device (SMCD)
        {
            Name (_HID, "FAN00000")  // _HID: Hardware ID
            Name (_CID, "XFAN0000")  // _CID: Compatible ID
            Name (TACH, Package (0x02)
            {
                "System Fan", 
                "FAN0"
            })
            Method (FAN0, 0, Serialized)
            {
                Local0 = \_SB.PCI0.LPCB.EC.SCM0.TDCD /* External reference */
                If ((Local0 <= Zero))
                {
                    Return (Zero)
                }

                Local0 *= 0x96
                Return (Local0)
            }

            Method (CPUF, 6, NotSerialized)
            {
                \_SB.PCI0.LPCB.EC.SCM0.TDF4 = 0x8C
                \_SB.PCI0.LPCB.EC.SCM0.TD72 = Arg0
                \_SB.PCI0.LPCB.EC.SCM0.TD73 = Arg1
                \_SB.PCI0.LPCB.EC.SCM0.TD74 = Arg2
                \_SB.PCI0.LPCB.EC.SCM0.TD75 = Arg3
                \_SB.PCI0.LPCB.EC.SCM0.TD76 = Arg4
                \_SB.PCI0.LPCB.EC.SCM0.TD77 = Arg5
                \_SB.PCI0.LPCB.EC.SCM0.TD8A = Zero
                \_SB.PCI0.LPCB.EC.SCM0.TD8B = Zero
                \_SB.PCI0.LPCB.EC.SCM0.TD8C = 0x1E
                \_SB.PCI0.LPCB.EC.SCM0.TD8D = 0x32
                \_SB.PCI0.LPCB.EC.SCM0.TD8E = 0x50
                \_SB.PCI0.LPCB.EC.SCM0.TD8F = 0x64
            }

            Method (XFAN, 6, Serialized)
            {
                CPUF (Arg0, Arg1, Arg2, Arg3, Arg4, Arg5)
            }

            Method (_STA, 0, NotSerialized)  // _STA: Status
            {
                If (_OSI ("Darwin"))
                {
                    Return (0x0F)
                }
                Else
                {
                    Return (Zero)
                }
            }
        }
    }
}

