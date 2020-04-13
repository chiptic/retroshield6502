
#include   "Asm6502Opcodes.h"

OPCODE_CHECK_START:
  // 00   BRK   
  BRK
  // 01   ORA   (Indirect, X)
  ORA.IND.X 00
  // 02     
  // 03     
  // 04     
  // 05   ORA   Zero Page
  ORA.ZP 00
  // 06   ASL   Zero Page
  ASL.ZP 00
  // 07     
  // 08   PHP   
  PHP
  // 09   ORA   Immediate
  ORA.IMM 00
  // 0A   ASL   Accumulator
  ASL.ACC
  // 0B     
  // 0C     
  // 0D   ORA   Absolute
  ORA.ABS 0000
  // 0E   ASL   Absolute
  ASL.ABS 0000
  // 0F     
  // 10   BPL   
  BPL.REL   CHECK1
  // 11   ORA   (Indirect), Y
  ORA.IND.Y 00
  // 12     
  // 13     
  // 14     
  // 15   ORA   Zero Page, X
  ORA.ZP.X 00
  // 16   ASL   Zero Page, X
  ASL.ZP.X 00
  // 17     
  // 18   CLC   
  CLC
  // 19   ORA   Absolute, Y
  ORA.ABS.Y 0000
  // 1A     
  // 1B     
  // 1C     
  // 1D   ORA   Absolute, X
  ORA.ABS.X 0000
  // 1E   ASL   Absolute, X
  ASL.ABS.X 0000
  // 1F     
  // 20   JSR   
  JSR.ROM 0000
  // 21   AND   (Indirect, X)
  AND.IND.X 00
  // 22     
  // 23     
  // 24   BIT   Zero Page
  BIT.ZP 00
  // 25   AND   Zero Page
  AND.ZP 00
  // 26   ROL   Zero Page
  ROL.ZP 00
  // 27     
  // 28   PLP   
  PLP 
  // 29   AND   Immediate
  AND.IMM 00
  // 2A   ROL   Accumulator
  ROL.ACC
  // 2B     
  // 2C   BIT   Absolute
  BIT.ABS 0000
  // 2D   AND   Absolute
  AND.ABS 0000
  // 2E   ROL   Absolute
  ROL.ABS 0000
  // 2F     
  // 30   BMI   
  BMI.REL 00
  // 31   AND   (Indirect), Y
  AND.IND.Y 00
  // 32     
  // 33     
  // 34     
  // 35   AND   Zero Page, X
  AND.ZP.X 00
  // 36   ROL   Zero Page, X
  ROL.ZP.X 00
  // 37     
  // 38   SEC   
  SEC
  // 39   AND   Absolute, Y
  AND.ABS.Y 0000
  // 3A     
  // 3B     
  // 3C     
  // 3D   AND   Absolute, X
  AND.ABS.X 0000
  // 3E   ROL   Absolute, X
  ROL.ABS.X 0000
  // 3F     
  // 40   RTI   
  RTI 
  // 41   EOR   (Indirect, X)
  EOR.IND.X 0000
  // 42     
  // 43     
  // 44     
  // 45   EOR   Zero Page
  EOR.ZP 00
  // 46   LSR   Zero Page
  LSR.ZP 00
  // 47     
  // 48   PHA   
  PHA
  // 49   EOR   Immediate
  EOR.IMM 00
  // 4A   LSR   Accumulator
  LSR.ACC
  // 4B     
  // 4C   JMP   Absolute
  JMP.ROM 0000
  // 4D   EOR   Absolute
  EOR.ABS 0000
  // 4E   LSR   Absolute
  LSR.ABS 0000
  // 4F     
  // 50   BVC   
  BVC.REL 00
  // 51   EOR   (Indirect), Y
  EOR.IND.Y 00
  // 52     
  // 53     
  // 54     
  // 55   EOR   Zero Page, X
  EOR.ZP.X 00
  // 56   LSR   Zero Page, X
  LSR.ZP.X 00
  // 57     
  // 58   CLI   
  CLI
  // 59   EOR   Absolute, Y
  EOR.ABS.Y 0000
  // 5A     
  // 5B     
  // 5C     
  // 5D   EOR   Absolute, X
  EOR.ABS.X 0000
  // 5E   LSR   Absolute, X
  LSR.ABS.X 0000
  // 5F     
  // 60   RTS   
  RTS
  // 61   ADC   (Indirect, X)
  ADC.IND.X 00
  // 62     
  // 63     
  // 64     
  // 65   ADC   Zero Page
  ADC.ZP 00
  // 66   ROR   Zero Page
  ROR.ZP 00
  // 67     
  // 68   PLA   
  PLA
  // 69   ADC   Immediate
  ADC.IMM 00
  // 6A   ROR   Accumulator
  ROR.ACC
  // 6B     
  // 6C   JMP   Indirect
  JMP.IND 0000
  // 6D   ADC   Absolute
  ADC.ABS 0000
  // 6E   ROR   Absolute
  ROR.ABS 0000
  // 6F     
  // 70   BVS   
  BVS.REL 00
  // 71   ADC   (Indirect), Y
  ADC.IND.Y 00
  // 72     
  // 73     
  // 74     
  // 75   ADC   Zero Page, X
  ADC.ZP.X 00
  // 76   ROR   Zero Page, X
  ROR.ZP.X 00
  // 77     
  // 78   SEI   
  SEI
  // 79   ADC   Absolute, Y
  ADC.ABS.Y 0000
  // 7A     
  // 7B     
  // 7C     
  // 7D   ADC   Absolute, X
  ADC.ABS.X 00
  // 7E   ROR   Absolute, X
  ROR.ABS.X 0000
  // 7F     
  // 80     
  // 81   STA   (Indirect, X)
  STA.IND.X 00
  // 82     
  // 83     
  // 84   STY   Zero Page
  STY.ZP 00
  // 85   STA   Zero Page
  STA.ZP 00
  // 86   STX   Zero Page
  STX.ZP 00
  // 87     
  // 88   DEY   
  DEY
  // 89     
  // 8A   TXA   
  TXA
  // 8B     
  // 8C   STY   Absolute
  STY.ABS 0000
  // 8D   STA   Absolute
  STA.ABS 0000
  // 8E   STX   Absolute
  STX.ABS 0000
  // 8F     
  // 90   BCC   
  BCC.REL 00
  // 91   STA   (Indirect), Y
  STA.IND.Y 00
  // 92     
  // 93     
  // 94   STY   Zero Page, X
  STY.ZP.X 00
  // 95   STA   Zero Page, X
  STA.ZP.X 00
  // 96   STX   Zero Page, Y
  STX.ZP.Y 00
  // 97     
  // 98   TYA   
  TYA
  // 99   STA   Absolute, Y
  STA.ABS.Y 0000
  // 9A   TXS   
  TXS
  // 9B     
  // 9C     
  // 9D   STA   Absolute, X
  STA.ABS.X 0000
  // 9E     
  // 9F     
  // A0   LDY   Immediate
  LDY.IMM 00
  // A1   LDA   (Indirect, X)
  LDA.IND.X 00
  // A2   LDX   Immediate
  LDX.IMM 00
  // A3     
  // A4   LDY   Zero Page
  LDY.ZP 00
  // A5   LDA   Zero Page
  LDA.ZP 00
  // A6   LDX   Zero Page
  LDX.ZP 00
  // A7     
  // A8   TAY   
  TAY
  // A9   LDA   Immediate
  LDA.IMM 00
  // AA   TAX   
  TAX
  // AB     
  // AC   LDY   Absolute
  LDY.ABS 0000
  // AD   LDA   Absolute
  LDA.ABS 0000
  // AE   LDX   Absolute
  LDX.ABS 0000
  // AF     
  // B0   BCS   
  BCS.REL 00
  // B1   LDA   (Indirect), Y
  LDA.IND.Y 00
  // B2     
  // B3     
  // B4   LDY   Zero Page, X
  LDY.ZP.X 00
  // B5   LDA   Zero Page, X
  LDA.ZP.X 00
  // B6   LDX   Zero Page, Y
  LDX.ZP.Y 00
  // B7     
  // B8   CLV   
  CLV
  // B9   LDA   Absolute, Y
  LDA.ABS.Y 00
  // BA   TSX   
  TSX
  // BB     
  // BC   LDY   Absolute, X
  LDY.ABS.X 0000
  // BD   LDA   Absolute, X
  LDA.ABS.X 0000
  // BE   LDX   Absolute, Y
  LDX.ABS.Y 0000
  // BF     
  // C0   CPY   Immediate
  CPY.IMM 00
  // C1   CMP   (Indirect, X)
  CMP.IND.X 00
  // C2     
  // C3     
  // C4   CPY   Zero Page
  CPY.ZP 00
  // C5   CMP   Zero Page
  CMP.ZP 00
  // C6   DEC   Zero Page
  DEC.ZP 00
  // C7     
  // C8   INY   
  INY
  // C9   CMP   Immediate
  CMP.IMM 00
  // CA   DEX   
  DEX
  // CB     
  // CC   CPY   Absolute
  CPY.ABS 0000
  // CD   CMP   Absolute
  CMP.ABS 0000
  // CE   DEC   Absolute
  DEC.ABS 0000
  // CF     
  // D0   BNE   
  BNE.REL 00
  // D1   CMP   (Indirect), Y
  CMP.IND.Y 00
  // D2     
  // D3     
  // D4     
  // D5   CMP   Zero Page, X
  CMP.ZP.X  00
  // D6   DEC   Zero Page, X
  DEC.ZP.X 00
  // D7     
  // D8   CLD   
  CLD
  // D9   CMP   Absolute, Y
  CMP.ABS.Y 0000
  // DA     
  // DB     
  // DC     
  // DD   CMP   Absolute, X
  CMP.ABS.X 0000
  // DE   DEC   Absolute, X
  DEC.ABS.X 0000
  // DF     
  // E0   CPX   Immediate
  CPX.IMM 00
  // E1   SBC   (Indirect, X)
  SBC.IND.X 00
  // E2     
  // E3     
  // E4   CPX   Zero Page
  CPX.ZP 00
  // E5   SBC   Zero Page
  SBC.ZP 00
  // E6   INC   Zero Page
  INC.ZP 00
  // E7     
  // E8   INX   
  INX
  // E9   SBC   Immediate
  SBC.IMM 00
  // EA   NOP   
  NOP
  // EB     
  // EC   CPX   Absolute
  CPX.ABS 0000
  // ED   SBC   Absolute
  SBC.ABS 0000
  // EE   INC   Absolute
  INC.ABS 0000
  // EF     
  // F0   BEQ   
  BEQ.REL 00
  // F1   SBC   (Indirect), Y
  SBC.IND.Y 00
  // F2     
  // F3     
  // F4     
  // F5   SBC   Zero Page, X
  SBC.ZP.X 00
  // F6   INC   Zero Page, X
  INC.ZP.X 00
  // F7     
  // F8   SED   
  SED
  // F9   SBC   Absolute, Y
  SBC.ABS.Y 0000
  // FA     
  // FB     
  // FC     
  // FD   SBC   Absolute, X
  SBC.ABS.X 0000
  // FE   INC   Absolute, X
  INC.ABS.X 0000
  // FF     
OPCODE_CHECK_END:

  .end
