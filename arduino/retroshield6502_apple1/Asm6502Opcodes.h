

/**************************************
 * Experimental macro's 
 *************************************/

.macro STA.ZPX immVal:req, regName
.byte 0xEA, 0xEA, 0xEA
.ifb \regName
  .byte 0xEB, \immVal, 0xEC
.else
   .ifc "\regName","X"
      .byte 0xED, \immVal, 0xEE
    .else
      .byte 0xEF, \immVal, 0xEF
   .endif
.endif
.byte 0xEA, 0xEA, 0xEA
.endm
 

.macro STA.ZPA addrVal:req
.byte 0xEA, 0xEA, 0xEA
.ifle \addrVal - 0xff
  .byte 0xEE, \addrVal, 0xEE
.else
  .byte 0xEF, lo8(\addrVal), hi8(\addrVal), 0xEF
.endif
.byte 0xEA, 0xEA, 0xEA
.endm
 
.macro STA.HASH immVal
.fail immVal
.endm


/**************************************
 * Initialize RAM section variables 
 *************************************/
 
.set ROM_SECTION_ORIGIN, .
.set ROM_BASE_ADDR, 0x0000

/********************************
 * Start opcode definitions 
 *******************************/


// STA   Absolute  8D
.macro STA.ABS2 absAddr
    //.byte 0x8D, lo8(\absAddr - rom_bin), hi8(\absAddr - rom_bin)
    .byte 0x8D, lo8(\absAddr - ROM_SECTION_ORIGIN  + ROM_BASE_ADDR), hi8(\absAddr - ROM_SECTION_ORIGIN  + ROM_BASE_ADDR)  
//    .byte 0x8D, lo8(\absAddr - rom_bin  + 0xFF00), hi8(\absAddr - rom_bin  + 0xFF00)  
//    .byte 0x8D, (lo8(\absAddr) + lo8(\romBase)) 
    //.byte 0x8D, lo8(origin1), hi8(\absAddr) 
.endm



/*******************************
 * Addressing mode macro's 
 ******************************/

// Implied addressing (IMP)
.macro  OPCODE_IMP opcode
    .byte lo8(\opcode)
.endm

// Accumulator addressing (IMP-ACC)
.macro OPCODE_ACC opcode
    .byte lo8(\opcode)  
.endm

// Immediate addressing (IMM)
.macro OPCODE_IMM opcode, immVal
    .byte lo8(\opcode), lo8(\immVal)  
.endm

// Relative addressing (REL)
.macro OPCODE_REL opcode, relAddr
    .byte lo8(\opcode), lo8(\relAddr - 1f )
  1:
.endm

// Zero-Page addressing (ZP)
.macro OPCODE_ZP opcode, zpAddr
    .byte lo8(\opcode), lo8(\zpAddr)  
.endm

// Zero-Page, X-indexed addressing (ZPX)
.macro OPCODE_ZP_X opcode, zpAddr
    OPCODE_ZP \opcode, \zpAddr  
.endm

// Zero-Page, Y-indexed addressing (ZPY)
.macro OPCODE_ZP_Y opcode, zpAddr
    OPCODE_ZP \opcode, \zpAddr  
.endm

// Absolute addressing (ABS)
.macro OPCODE_ABS opcode, absAddr
    .byte \opcode, lo8(\absAddr), hi8(\absAddr)  
.endm

// Absolute ROM addressing (ROM)
.macro OPCODE_ROM opcode, absAddr
    .byte \opcode, lo8(\absAddr - ROM_SECTION_ORIGIN  + ROM_BASE_ADDR), hi8(\absAddr - ROM_SECTION_ORIGIN  + ROM_BASE_ADDR)  
.endm

// Absolute, X-indexed addressing (ABX)
.macro OPCODE_ABS_X opcode, absAddr
    OPCODE_ABS \opcode, \absAddr
.endm

// Absolute, Y-indexed addressing (ABY)
.macro OPCODE_ABS_Y opcode, absAddr
    OPCODE_ABS \opcode, \absAddr
.endm

// Indirect absolute addressing (IND)
.macro OPCODE_IND opcode, absAddr
    OPCODE_ABS \opcode, \absAddr
.endm

// Indirect, Zero_page, X-indexed addressing (IZX)
.macro OPCODE_IND_X opcode, zpAddr
    OPCODE_ZP \opcode, \zpAddr  
.endm

// Indirect, , Zero_page, Y-indexed addressing (IZY)
.macro OPCODE_IND_Y opcode, zpAddr
    OPCODE_ZP \opcode, \zpAddr  
.endm

/********************************
 * ADC   Immediate   69
 * ADC   Zero Page   65
 * ADC   Zero Page, X  75
 * ADC   Absolute  6D
 * ADC   Absolute, X   7D
 * ADC   Absolute, Y   79
 * ADC   (Indirect, X    61
 * ADC   (Indirect , Y   71
 *******************************/

// ADC   Immediate   69
.macro ADC.IMM immVal
    OPCODE_IMM 0x69, \immVal  
.endm

// ADC   Zero Page   65
.macro ADC.ZP zpAddr
    OPCODE_ZP 0x65, \zpAddr  
.endm

// ADC   Zero Page, X  75
.macro ADC.ZP.X zpAddr
    OPCODE_ZP_X 0x75, \zpAddr  
.endm

// ADC   Absolute  6D
.macro ADC.ABS absAddr
    OPCODE_ABS 0x6D, \absAddr  
.endm

// ADC   Absolute, X   7D
.macro ADC.ABS.X absAddr
    OPCODE_ABS_X 0x7D, \absAddr 
.endm

// ADC   Absolute, Y   79
.macro ADC.ABS.Y absAddr
    OPCODE_ABS_Y 0x79, \absAddr  
.endm

// ADC   (Indirect, X    61
.macro ADC.IND.X absAddr
    OPCODE_IND_X 0x61, \absAddr  
.endm

// ADC   (Indirect , Y   71
.macro ADC.IND.Y absAddr
    OPCODE_IND_Y 0x71, \absAddr  
.endm

/********************************
 * AND   Immediate   29
 * AND   Zero Page   25
 * AND   Zero Page, X  35
 * AND   Absolute  2D
 * AND   Absolute, X   3D
 * AND   Absolute, Y   39
 * AND   (Indirect, X    21
 * AND   (Indirect , Y   31
 *******************************/

// AND   Immediate   29
.macro AND.IMM immVal
    OPCODE_IMM 0x29, \immVal  
.endm

// AND   Zero Page   25
.macro AND.ZP zpAddr
    OPCODE_ZP 0x25, \zpAddr  
.endm

// AND   Zero Page, X  35
.macro AND.ZP.X zpAddr
    OPCODE_ZP_X 0x35, \zpAddr  
.endm

// AND   Absolute  2D
.macro AND.ABS absAddr
    OPCODE_ABS 0x2D, \absAddr  
.endm

// AND   Absolute, X   3D
.macro AND.ABS.X absAddr
    OPCODE_ABS_X 0x3D, \absAddr 
.endm

// AND   Absolute, Y   39
.macro AND.ABS.Y absAddr
    OPCODE_ABS_Y 0x39, \absAddr  
.endm

// AND   (Indirect, X    21
.macro AND.IND.X absAddr
    OPCODE_IND_X 0x21, \absAddr  
.endm

// AND   (Indirect , Y   31
.macro AND.IND.Y absAddr
    OPCODE_IND_Y 0x31, \absAddr  
.endm


/********************************
 * ASL   Accumulator   0A
 * ASL   Zero Page   06
 * ASL   Zero Page, X  16
 * ASL   Absolute  0E
 * ASL   Absolute, X   1E
 *******************************/


// ASL   Accumulator   0A
.macro ASL.ACC 
    OPCODE_ACC 0x0A  
.endm

// ASL   Zero Page   06
.macro ASL.ZP zpAddr
    OPCODE_ZP 0x06, \zpAddr  
.endm

// ASL   Zero Page, X  16
.macro ASL.ZP.X zpAddr
    OPCODE_ZP_X 0x16, \zpAddr  
.endm

// ASL   Absolute  0E
.macro ASL.ABS absAddr
    OPCODE_ABS 0x0E, \absAddr  
.endm

// ASL   Absolute, X   1E
.macro ASL.ABS.X absAddr
    OPCODE_ABS_X 0x1E, \absAddr 
.endm


/********************************
 * Branching 
 * BCC     90
 * BCS     B0
 * BEQ     F0
 * BMI     30
 * BNE     D0
 * BPL     10
 * BVC     50
 * BVS     70
 *******************************/

// BCC     90
.macro BCC.REL relAddr
    OPCODE_REL 0x90, \relAddr 
.endm

// BCS     B0
.macro BCS.REL relAddr
    OPCODE_REL 0xB0, \relAddr 
.endm

// BEQ     F0
.macro BEQ.REL relAddr
    OPCODE_REL 0xF0, \relAddr 
.endm

// BMI     30
.macro BMI.REL relAddr
    OPCODE_REL 0x30, \relAddr 
.endm

// BNE     D0
.macro BNE.REL relAddr
    OPCODE_REL 0xD0, \relAddr 
.endm

// BPL     10
.macro BPL.REL relAddr
    OPCODE_REL 0x10, \relAddr 
.endm

// BVC     50
.macro BVC.REL relAddr
    OPCODE_REL 0x50, \relAddr 
.endm

// BVS     70
.macro BVS.REL relAddr
    OPCODE_REL 0x70, \relAddr 
.endm

/********************************
 * BIT   Zero Page   24
 * BIT   Absolute  2C
 *******************************/

// BIT   Zero Page   24
.macro BIT.ZP zpAddr
    OPCODE_ZP 0x24, \zpAddr  
.endm

// BIT   Absolute  2C
.macro BIT.ABS absAddr
    OPCODE_ABS 0x2C, \absAddr  
.endm

/********************************
 * BRK     00
 *******************************/

// BRK     00
.macro BRK relAddr
     OPCODE_IMP 0x00 
.endm

/********************************
 * Clear flags 
 * CLC    18
 * CLD    D8
 * CLI    58
 * CLV    B8
 *******************************/

// CLC     18
.macro CLC
     OPCODE_IMP 0x18 
.endm

// CLD     D8
.macro CLD
     OPCODE_IMP 0xD8 
.endm

// CLI     58
.macro CLI
     OPCODE_IMP 0x58 
.endm

// CLV     B8
.macro CLV
     OPCODE_IMP 0xB8 
.endm

/********************************
 * CMP  Immediate   C9
 * CMP  Zero Page   C5
 * CMP  Zero Page, X  D5
 * CMP  Absolute  CD
 * CMP  Absolute, X   DD
 * CMP  Absolute, Y   D9
 * CMP  (Indirect, X    C1
 * CMP  (Indirect , Y   D1
 *******************************/

// CMP   Immediate   C9
.macro CMP.IMM immVal
    OPCODE_IMM 0xC9, \immVal  
.endm

// CMP   Zero Page   C5
.macro CMP.ZP zpAddr
    OPCODE_ZP 0xC5, \zpAddr  
.endm

// CMP   Zero Page, X  D5
.macro CMP.ZP.X zpAddr
    OPCODE_ZP_X 0xD5, \zpAddr  
.endm

// CMP   Absolute  CD
.macro CMP.ABS absAddr
    OPCODE_ABS 0xCD, \absAddr  
.endm

// CMP   Absolute, X   DD
.macro CMP.ABS.X absAddr
    OPCODE_ABS_X 0xDD, \absAddr 
.endm

// CMP   Absolute, Y   D9
.macro CMP.ABS.Y absAddr
    OPCODE_ABS_Y 0xD9, \absAddr  
.endm

// CMP   (Indirect, X    C1
.macro CMP.IND.X absAddr
    OPCODE_IND_X 0xC1, \absAddr  
.endm

// CMP   (Indirect , Y   D1
.macro CMP.IND.Y absAddr
    OPCODE_IND_Y 0xD1, \absAddr  
.endm

/********************************
 * CPX  Immediate   E0
 * CPX  Zero Page   E4
 * CPX  Absolute  EC
 *******************************/

// CPX   Immediate   E0
.macro CPX.IMM immVal
    OPCODE_IMM 0xE0, \immVal  
.endm

// CPX   Zero Page   E4
.macro CPX.ZP zpAddr
    OPCODE_ZP 0xE4, \zpAddr  
.endm

// CPX   Absolute  EC
.macro CPX.ABS absAddr
    OPCODE_ABS 0xEC, \absAddr  
.endm


/********************************
 * CPY  Immediate   C0
 * CPY  Zero Page   C4
 * CPY  Absolute  CC
 *******************************/

// CPY   Immediate   C0
.macro CPY.IMM immVal
    OPCODE_IMM 0xC0, \immVal  
.endm

// CPY   Zero Page   C4
.macro CPY.ZP zpAddr
    OPCODE_ZP 0xC4, \zpAddr  
.endm

// CPY   Absolute  CC
.macro CPY.ABS absAddr
    OPCODE_ABS 0xCC, \absAddr  
.endm

/********************************
 * DEC  Zero Page   C6
 * DEC  Zero Page, X  D6
 * DEC  Absolute  CE
 * DEC  Absolute, X   DE
 *******************************/

// DEC   Zero Page   C6
.macro DEC.ZP zpAddr
    OPCODE_ZP 0xC6, \zpAddr  
.endm

// DEC   Zero Page, X  D6
.macro DEC.ZP.X zpAddr
    OPCODE_ZP_X 0xD6, \zpAddr  
.endm

// DEC   Absolute  CE
.macro DEC.ABS absAddr
    OPCODE_ABS 0xCE, \absAddr  
.endm

// DEC   Absolute, X   DE
.macro DEC.ABS.X absAddr
    OPCODE_ABS_X 0xDE, \absAddr 
.endm

/********************************
 * DEX    CA
 * DEY    88
 *******************************/

// DEX     CA
.macro DEX
     OPCODE_IMP 0xCA 
.endm

// DEY     88
.macro DEY
     OPCODE_IMP 0x88 
.endm

/********************************
 * EOR  Immediate   49
 * EOR  Zero Page   45
 * EOR  Zero Page, X  55
 * EOR  Absolute  4D
 * EOR  Absolute, X   5D
 * EOR  Absolute, Y   59
 * EOR  (Indirect, X    41
 * EOR  (Indirect , Y   51
 *******************************/

// EOR   Immediate   49
.macro EOR.IMM immVal
    OPCODE_IMM 0x49, \immVal  
.endm

// EOR   Zero Page   45
.macro EOR.ZP zpAddr
    OPCODE_ZP 0x45, \zpAddr  
.endm

// EOR   Zero Page, X  55
.macro EOR.ZP.X zpAddr
    OPCODE_ZP_X 0x55, \zpAddr  
.endm

// EOR   Absolute  4D
.macro EOR.ABS absAddr
    OPCODE_ABS 0x4D, \absAddr  
.endm

// EOR   Absolute, X   5D
.macro EOR.ABS.X absAddr
    OPCODE_ABS_X 0x5D, \absAddr 
.endm

// EOR   Absolute, Y   59
.macro EOR.ABS.Y absAddr
    OPCODE_ABS_Y 0x59, \absAddr  
.endm

// EOR   (Indirect, X    41
.macro EOR.IND.X absAddr
    OPCODE_IND_X 0x41, \absAddr  
.endm

// EOR   (Indirect , Y   51
.macro EOR.IND.Y absAddr
    OPCODE_IND_Y 0x51, \absAddr  
.endm

/********************************
 * INC  Zero Page   E6
 * INC  Zero Page, X  F6
 * INC  Absolute  EE
 * INC  Absolute, X   FE
 *******************************/

// INC   Zero Page   E6
.macro INC.ZP zpAddr
    OPCODE_ZP 0xE6, \zpAddr  
.endm

// INC   Zero Page, X  F6
.macro INC.ZP.X zpAddr
    OPCODE_ZP_X 0xF6, \zpAddr  
.endm

// INC   Absolute  EE
.macro INC.ABS absAddr
    OPCODE_ABS 0xEE, \absAddr  
.endm

// INC   Absolute, X   FE
.macro INC.ABS.X absAddr
    OPCODE_ABS_X 0xFE, \absAddr 
.endm

/********************************
 * INX    E8
 * INY    C8
 *******************************/

// INX     E8
.macro INX
     OPCODE_IMP 0xE8 
.endm

// INY     C8
.macro INY
     OPCODE_IMP 0xC8 
.endm

/********************************
 * JMP  Indirect  6C
 * JMP  Absolute  4C
 *******************************/

// JMP   Indirect  6C
.macro JMP.IND absAddr
    OPCODE_IND 0x6C, \absAddr  
.endm

// JMP   Absolute  4C
.macro JMP.ABSx absAddr
    OPCODE_ABS 0x4C, \absAddr  
.endm

// JMP   Absolute  4C
.macro JMP.ROM absAddr
    OPCODE_ROM 0x4C, \absAddr  
.endm

/********************************
 * JSR    20
 *******************************/
 
// JSR     20
.macro JSR.ABSx absAddr
    OPCODE_ABS 0x20, \absAddr  
.endm

.macro JSR.ROM absAddr
    OPCODE_ROM 0x20, \absAddr  
.endm

/********************************
 * LDA  Immediate   A9
 * LDA  Zero Page   A5
 * LDA  Zero Page, X  B5
 * LDA  Absolute  AD
 * LDA  Absolute, X   BD
 * LDA  Absolute, Y   B9
 * LDA  (Indirect, X    A1
 * LDA  (Indirect , Y   B1
 *******************************/

// LDA   Immediate   A9
.macro LDA.IMM immVal
    OPCODE_IMM 0xA9, \immVal  
.endm

// LDA   Zero Page   A5
.macro LDA.ZP zpAddr
    OPCODE_ZP 0xA5, \zpAddr  
.endm

// LDA   Zero Page, X  B5
.macro LDA.ZP.X zpAddr
    OPCODE_ZP_X 0xB5, \zpAddr  
.endm

// LDA   Absolute  AD
.macro LDA.ABS absAddr
    OPCODE_ABS 0xAD, \absAddr  
.endm

// LDA   Absolute, X   BD
.macro LDA.ABS.X absAddr
    OPCODE_ABS_X 0xBD, \absAddr 
.endm

// LDA   Absolute, Y   B9
.macro LDA.ABS.Y absAddr
    OPCODE_ABS_Y 0xB9, \absAddr  
.endm

// LDA   (Indirect, X    A1
.macro LDA.IND.X absAddr
    OPCODE_IND_X 0xA1, \absAddr  
.endm

// LDA   (Indirect , Y   B1
.macro LDA.IND.Y absAddr
    OPCODE_IND_Y 0xB1, \absAddr  
.endm


/********************************
 * LDX  Zero Page   A6
 * LDX  Zero Page, Y  B6
 * LDX  Absolute  AE
 * LDX  Absolute, Y   BE
 * LDX  Immediate   A2
 *******************************/

// LDX   Immediate   A2
.macro LDX.IMM immVal
    OPCODE_IMM 0xA2, \immVal  
.endm

// LDX   Zero Page   A6
.macro LDX.ZP zpAddr
    OPCODE_ZP 0xA6, \zpAddr  
.endm

// LDX   Zero Page, Y  B6
.macro LDX.ZP.Y zpAddr
    OPCODE_ZP_Y 0xB6, \zpAddr  
.endm

// LDX   Absolute  AE
.macro LDX.ABS absAddr
    OPCODE_ABS 0xAE, \absAddr  
.endm

// LDX   Absolute, Y   BE
.macro LDX.ABS.Y absAddr
    OPCODE_ABS_Y 0xBE, \absAddr  
.endm



/********************************
 * LDY  Immediate   A0
 * LDY  Zero Page   A4
 * LDY  Zero Page, X  B4
 * LDY  Absolute  AC
 * LDY  Absolute, X   BC
 *******************************/
 
// LDY   Immediate   A0
.macro LDY.IMM immVal
    OPCODE_IMM 0xA0, \immVal 
.endm

// LDY   Zero Page   A4
.macro LDY.ZP zpAddr
    OPCODE_ZP 0xA4, \zpAddr  
.endm

// LDY   Zero Page, X  B4
.macro LDY.ZP.X zpAddr
    OPCODE_ZP_X 0xB4, \zpAddr  
.endm

// LDY   Absolute  AC
.macro LDY.ABS absAddr
    OPCODE_ABS 0xAC, \absAddr  
.endm

// LDY   Absolute, X   BC
.macro LDY.ABS.X absAddr
    OPCODE_ABS_X 0xBC, \absAddr 
.endm

/********************************
 * LSR  Accumulator   4A
 * LSR  Zero Page   46
 * LSR  Zero Page, X  56
 * LSR  Absolute  4E
 * LSR  Absolute, X   5E
 *******************************/

// LSR   Accumulator   4A
.macro LSR.ACC
    OPCODE_ACC 0x4A  
.endm

// LSR   Zero Page   46
.macro LSR.ZP zpAddr
    OPCODE_ZP 0x46, \zpAddr  
.endm

// LSR   Zero Page, X  56
.macro LSR.ZP.X zpAddr
    OPCODE_ZP_X 0x56, \zpAddr  
.endm

// LSR   Absolute  4E
.macro LSR.ABS absAddr
    OPCODE_ABS 0x4E, \absAddr  
.endm

// LSR   Absolute, X   5E
.macro LSR.ABS.X absAddr
    OPCODE_ABS_X 0x5E, \absAddr 
.endm

/********************************
 * NOP     EA
 *******************************/

// NOP     EA
.macro NOP
     OPCODE_IMP 0xEA 
.endm

/********************************
 * ORA  Immediate   09
 * ORA  Zero Page   05
 * ORA  Zero Page, X  15
 * ORA  Absolute  0D
 * ORA  Absolute, X   1D
 * ORA  Absolute, Y   19
 * ORA  (Indirect, X    01
 * ORA  (Indirect , Y   11
 *******************************/

// ORA   Immediate   09
.macro ORA.IMM immVal
    OPCODE_IMM 0x09, \immVal  
.endm

// ORA   Zero Page   05
.macro ORA.ZP zpAddr
    OPCODE_ZP 0x05, \zpAddr  
.endm

// ORA   Zero Page, X  15
.macro ORA.ZP.X zpAddr
    OPCODE_ZP_X 0x15, \zpAddr  
.endm

// ORA   Absolute  0D
.macro ORA.ABS absAddr
    OPCODE_ABS 0x0D, \absAddr  
.endm

// ORA   Absolute, X   1D
.macro ORA.ABS.X absAddr
    OPCODE_ABS_X 0x1D, \absAddr 
.endm

// ORA   Absolute, Y   19
.macro ORA.ABS.Y absAddr
    OPCODE_ABS_Y 0x19, \absAddr  
.endm

// ORA   (Indirect, X    01
.macro ORA.IND.X absAddr
    OPCODE_IND_X 0x01, \absAddr  
.endm

// ORA   (Indirect , Y   11
.macro ORA.IND.Y absAddr
    OPCODE_IND_Y 0x11, \absAddr  
.endm


/********************************
 * Push and Pull
 * PHA     48
 * PHP    08
 * PLA    68
 * PLP    28
 *******************************/

// PHA     48
.macro PHA
     OPCODE_IMP 0x48 
.endm

// PHP     08
.macro PHP
     OPCODE_IMP 0x08 
.endm

// PLA     68
.macro PLA
     OPCODE_IMP 0x68 
.endm

// PLP     28
.macro PLP
     OPCODE_IMP 0x28 
.endm


/********************************
 * ROL  Accumulator   2A
 * ROL  Zero Page   26
 * ROL  Zero Page, X  36
 * ROL  Absolute  2E
 * ROL  Absolute, X   3E
 *******************************/

// ROL   Accumulator   2A
.macro ROL.ACC
    OPCODE_ACC 0x2A  
.endm

// ROL   Zero Page   26
.macro ROL.ZP zpAddr
    OPCODE_ZP 0x26, \zpAddr  
.endm

// ROL   Zero Page, X  36
.macro ROL.ZP.X zpAddr
    OPCODE_ZP_X 0x36, \zpAddr  
.endm

// ROL   Absolute  2E
.macro ROL.ABS absAddr
    OPCODE_ABS 0x2E, \absAddr  
.endm

// ROL   Absolute, X   3E
.macro ROL.ABS.X absAddr
    OPCODE_ABS_X 0x3E, \absAddr 
.endm


/********************************
 * ROR  Accumulator   6A
 * ROR  Zero Page   66
 * ROR  Zero Page, X  76
 * ROR  Absolute  6E
 * ROR  Absolute, X   7E
 *******************************/

// ROR   Accumulator   6A
.macro ROR.ACC
    OPCODE_ACC 0x6A  
.endm

// ROR   Zero Page   66
.macro ROR.ZP zpAddr
    OPCODE_ZP 0x66, \zpAddr  
.endm

// ROR   Zero Page, X  76
.macro ROR.ZP.X zpAddr
    OPCODE_ZP_X 0x76, \zpAddr  
.endm

// ROR   Absolute  6E
.macro ROR.ABS absAddr
    OPCODE_ABS 0x6E, \absAddr  
.endm

// ROR   Absolute, X   7E
.macro ROR.ABS.X absAddr
    OPCODE_ABS_X 0x7E, \absAddr 
.endm


/********************************
 * RTI    40
 * RTS    60
 *******************************/

// RTI     40
.macro RTI
     OPCODE_IMP 0x40 
.endm

// RTS     60
.macro RTS
     OPCODE_IMP 0x60 
.endm


/********************************
 * SBC  Immediate   E9
 * SBC  Zero Page   E5
 * SBC  Zero Page, X  F5
 * SBC  Absolute  ED
 * SBC  Absolute, X   FD
 * SBC  Absolute, Y   F9
 * SBC  (Indirect, X    E1
 * SBC  (Indirect , Y   F1
 *******************************/

// SBC   Immediate   E9
.macro SBC.IMM immVal
    OPCODE_IMM 0xE9, \immVal  
.endm

// SBC   Zero Page   E5
.macro SBC.ZP zpAddr
    OPCODE_ZP 0xE5, \zpAddr  
.endm

// SBC   Zero Page, X  F5
.macro SBC.ZP.X zpAddr
    OPCODE_ZP_X 0xF5, \zpAddr  
.endm

// SBC   Absolute  ED
.macro SBC.ABS absAddr
    OPCODE_ABS 0xED, \absAddr  
.endm

// SBC   Absolute, X   FD
.macro SBC.ABS.X absAddr
    OPCODE_ABS_X 0xFD, \absAddr 
.endm

// SBC   Absolute, Y   F9
.macro SBC.ABS.Y absAddr
    OPCODE_ABS_Y 0xF9, \absAddr  
.endm

// SBC   (Indirect, X    E1
.macro SBC.IND.X absAddr
    OPCODE_IND_X 0xE1, \absAddr  
.endm

// SBC   (Indirect , Y   F1
.macro SBC.IND.Y absAddr
    OPCODE_IND_Y 0xF1, \absAddr  
.endm

/********************************
 * Set flags 
 * SEC     38
 * SED    F8
 * SEI    78
 *******************************/

// SEC     38
.macro SEC
     OPCODE_IMP 0x38 
.endm

// SED     F8
.macro SED
     OPCODE_IMP 0xF8 
.endm

// SEI     78
.macro SEI
     OPCODE_IMP 0x78 
.endm

/********************************
 * STA  Zero Page   85
 * STA  Zero Page, X  95
 * STA  Absolute  8D
 * STA  Absolute, X   9D
 * STA  Absolute, Y   99
 * STA  (Indirect, X    81
 * STA  (Indirect , Y   91
 *******************************/

// STA   Zero Page   85
.macro STA.ZP zpAddr
    OPCODE_ZP 0x85, \zpAddr  
.endm

// STA   Zero Page, X  95
.macro STA.ZP.X zpAddr
    OPCODE_ZP_X 0x95, \zpAddr  
.endm

// STA   Absolute  8D
.macro STA.ABS absAddr
    OPCODE_ABS 0x8D, \absAddr  
.endm

// STA   Absolute, X   9D
.macro STA.ABS.X absAddr
    OPCODE_ABS_X 0x9D, \absAddr 
.endm

// STA   Absolute, Y   99
.macro STA.ABS.Y absAddr
    OPCODE_ABS_Y 0x99, \absAddr  
.endm

// STA   (Indirect, X    81
.macro STA.IND.X absAddr
    OPCODE_IND_X 0x81, \absAddr  
.endm

// STA   (Indirect , Y   91
.macro STA.IND.Y absAddr
    OPCODE_IND_Y 0x91, \absAddr  
.endm



/********************************
 * STX  Zero Page   86
 * STX  Zero Page, Y  96
 * STX  Absolute  8E
 *******************************/
 
// STX   Zero Page   86
.macro STX.ZP zpAddr
    OPCODE_ZP 0x86, \zpAddr  
.endm

// STX   Zero Page, Y  96
.macro STX.ZP.Y zpAddr
    OPCODE_ZP_X 0x96, \zpAddr  
.endm

// STX   Absolute  8E
.macro STX.ABS absAddr
    OPCODE_ABS 0x8E, \absAddr  
.endm

/********************************
 * STY  Zero Page   84
 * STY  Zero Page, X  94
 * STY  Absolute  8C
 *******************************/
 
// STY   Zero Page   84
.macro STY.ZP zpAddr
    OPCODE_ZP 0x84, \zpAddr  
.endm

// STY   Zero Page, X  94
.macro STY.ZP.X zpAddr
    OPCODE_ZP_X 0x94, \zpAddr  
.endm

// STY   Absolute  8C
.macro STY.ABS absAddr
    OPCODE_ABS 0x8C, \absAddr  
.endm


/********************************
 * Transfer register 
 * TAX    AA
 * TAY    A8
 * TSX    BA
 * TXA    8A
 * TXS    9A
 * TYA    98
 *******************************/

// TAX     AA
.macro TAX
     OPCODE_IMP 0xAA 
.endm

// TAY     A8
.macro TAY
     OPCODE_IMP 0xA8 
.endm

// TSX     BA
.macro TSX
     OPCODE_IMP 0xBA 
.endm

// TXA     8A
.macro TXA
     OPCODE_IMP 0x8A 
.endm

// TXS     9A
.macro TXS
     OPCODE_IMP 0x9A 
.endm

// TYA    98
.macro TYA
     OPCODE_IMP 0x98 
.endm


/********************************
 * End opcode definitions 
 *******************************/
