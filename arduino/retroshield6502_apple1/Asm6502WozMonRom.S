/**
 * ROM code for 6502 Monitor for Apple 1 by Steve Wozniak.
 * ROM base must be 0xFF00, size is exactly 255 bytes.
 */
 
#include   "Asm6502Opcodes.h"

; Page 0 Variables

.equ  XAML,         0x24           ;  Last "opened" location Low
.equ  XAMH,         0x25           ;  Last "opened" location High
.equ  STL,          0x26           ;  Store address Low
.equ  STH,          0x27           ;  Store address High
.equ  L,            0x28           ;  Hex value parsing Low
.equ  H,            0x29           ;  Hex value parsing High
.equ  YSAV,         0x2A           ;  Used to see if hex value is given
.equ  MODE,         0x2B           ;  $00=XAM, $7F=STOR, $AE=BLOCK XAM


; Other Variables

.equ  IN,           0x0200         ;  Input buffer to $027F
.equ  KBD,          0xD010         ;  PIA.A keyboard input
.equ  KBDCR,        0xD011         ;  PIA.A keyboard control register
.equ  DSP,          0xD012         ;  PIA.B display output register
.equ  DSPCR,        0xD013         ;  PIA.B display control register


  // Define ROM area symbol name for extern C linkage
  .global code_rom_apple1_woz_mon

code_rom_apple1_woz_mon:

  // Set ROM origin base address  
  .set ROM_SECTION_ORIGIN, code_rom_apple1_woz_mon
  .set ROM_BASE_ADDR, 0xFF00

  .section  .text
  .align  1
   
RESET:
    CLD               ; Clear decimal arithmetic mode.
    //D8
    
    CLI
    //58
    
    LDY.IMM 0x7F        ; Mask for DSP data direction register.
    //A0
    //7F
    
    STY.ABS DSP         ; Set it up.
    //8C
    //12
    //D0

    LDA.IMM 0xA7        ; KBD and DSP control register mask.
    //A9
    //A7
    
    STA.ABS KBDCR       ; Enable interrupts, set CA1, CB1, for
    //8D
    //11
    //D0

    STA.ABS DSPCR        ; positive edge sense/output mode.
    //8D
    //13
    //D0

NOTCR:
    CMP.IMM '_' + 0x80    ; "_"?
    //C9
    //DF

    BEQ.REL BACKSPACE     ; Yes.
    //F0
    //13
    
    CMP.IMM 0x9B          ; ESC?
    //C9
    //9B
    
    BEQ.REL ESCAPE        ; Yes.
    //F0
    //03

    INY                   ; Advance text index.
    //C8

    BPL.REL NEXTCHAR      ; Auto ESC if > 127.
    //10
    //0F

ESCAPE:

    LDA.IMM '\\' + 0x80        ; "\".
    //A9
    //DC

    JSR.ROM ECHO              ; Output it
    //20
    //EF
    //FF

GETLINE:
    LDA.IMM 0x8D              ; CR
    //A9
    //8D

    JSR.ROM ECHO              ; Output it
    //20
    //EF
    //FF

    LDY.IMM 0x01              ; Initialize text index.
    //A0
    //01

BACKSPACE:
    DEY                       ; Back up text index.
    //88

    BMI.REL GETLINE           ; Beyond start of line, reinitialize.
    //30
    //F6

NEXTCHAR:    
    LDA.ABS KBDCR       ; Key ready?
    //AD
    //11
    //D0
    
    BPL.REL NEXTCHAR    ; Loop until ready.
    //10
    //FB
    
    LDA.ABS KBD         ; Load character. B7 should be ‘1’.
    //AD
    //10
    //D0
    
    STA.ABS.Y IN        ; Add to text buffer.
    //99
    //00
    //02
    
    JSR.ROM ECHO        ; Display character.
    //20
    //EF
    //FF
    
    CMP.IMM 0x8D        ; CR?
    //C9
    //8D
    
    BNE.REL NOTCR       ; No.
    //D0
    //D4

    LDY.IMM 0xFF        ; Reset text index.
    //A0
    //FF
    
    LDA.IMM 0x00        ; For XAM mode.
    //A9
    //00
    
    TAX             ; 0->X.
    //AA

SETSTOR:
    ASL.ACC             ; Leaves $7B if setting STOR mode.
    //0A
    
SETMODE:
    STA.ZP MODE        ; $00=XAM $7B=STOR $AE=BLOK XAM
    //85
    //2B
    
BLSKIP:
    INY             ; Advance text index.
    //C8

NEXTITEM:
    LDA.ABS.Y IN        ; Get character.
    //B9
    //00
    //02
    
    CMP.IMM 0x8D        ; CR?
    //C9
    //8D
    
    BEQ.REL GETLINE     ; Yes, done this line.
    //F0
    //D4
    
    CMP.IMM '.' + 0x80    ; "."?
    //C9
    //AE
    
    BCC.REL BLSKIP      ; Skip delimiter.
    //90
    //F4
    
    BEQ.REL SETMODE     ; Yes. Set STOR mode.
    //F0
    //F0
    
    CMP.IMM ':' + 0x80    ; ":"?
    //C9
    //BA
    
    BEQ.REL SETSTOR     ; Yes. Set STOR mode.
    //F0
    //EB
    
    CMP.IMM 'R' + 0x80    ; "R"?
    //C9
    //D2

    BEQ.REL RUN         ; Yes. Run user program.
    //F0
    //3B
    
    STX.ZP L           ; $00-> L.
    //86
    //28
    
    STX.ZP H           ; and H.
    //86
    //29
    
    STY.ZP YSAV        ; Save Y for comparison.
    //84
    //2A
                  
NEXTHEX:
    LDA.ABS.Y IN        ; Get character for hex test.
    //B9
    //00
    //02
    
    EOR.IMM 0xB0        ; Map digits to $0-9.
    //49
    //B0
    
    CMP.IMM 0x0A        ; Digit?
    //C9
    //0A
    
    BCC.REL DIG         ; Yes.
    //90
    //06
    
    ADC.IMM 0x88        ; Map letter "A"-"F" to $FA-FF.
    //69
    //88
    
    CMP.IMM 0xFA        ; Hex letter?
    //C9
    //FA
    
    BCC.REL NOTHEX      ; No, character not hex.
    //90
    //11

DIG:
    ASL.ACC
    //0A
    
    ASL.ACC             ; Hex digit to MSD of A.
    //0A
    
    ASL.ACC
    //0A

    ASL.ACC
    //0A
    
    LDX.IMM 0x04        ; Shift count.
    //A2
    //04

HEXSHIFT:       
    ASL.ACC             ; Hex digit left, MSB to carry.
    //0A
    
    ROL.ZP L           ; Rotate into LSD.
    //26
    //28
    
    ROL.ZP H           ;  Rotate into MSD’s.
    //26
    //29
    
    DEX             ; Done 4 shifts?
    //CA
    
    BNE.REL HEXSHIFT    ; No, loop.
    //D0
    //F8
    
    INY             ; Advance text index.
    //C8

    BNE.REL NEXTHEX     ; Always taken. Check next char for hex.
    //D0
    //E0

NOTHEX:
    CPY.ZP YSAV        ; Check if L, H empty (no hex digits).
    //C4
    //2A
    
    BEQ.REL ESCAPE      ; Yes, generate ESC sequence.
    //F0
    //97
    
    BIT.ZP MODE        ; Test MODE byte.
    //24
    //2B
    
    BVC.REL NOTSTOR     ;  B6=0 STOR 1 for XAM & BLOCK XAM
    //50
    //10
    
    LDA.ZP L           ; LSD’s of hex data.
    //A5
    //28
    
    STA.IND.X STL     ; Store at current ‘store index’.
    //81
    //26
    
    INC.ZP STL         ; Increment store index.
    //E6
    //26
    
    BNE.REL NEXTITEM    ; Get next item. (no carry).
    //D0
    //B5
    
    INC.ZP STH         ; Add carry to ‘store index’ high order.                      
    //E6
    //27

TONEXTITEM:
    JMP.ROM NEXTITEM    ; Get next command item.
    //4C
    //44
    //FF
RUN:
    JMP.IND XAML      ; Run at current XAM index.
    //6c
    //24
    //00

NOTSTOR:
    BMI.REL XAMNEXT     ; B7=0 for XAM, 1 for BLOCK XAM.
    //30
    //2B
    
    LDX.IMM 0x02        ; Byte count.
    //A2
    //02
    
SETADR:
    LDA.ZP.X L-1       ; Copy hex data to
    //B5
    //27
    
    STA.ZP.X STL-1     ; ‘store index’.
    //95
    //25
    
    STA.ZP.X XAML-1    ; And to ‘XAM index’.
    //95
    //23
    
    DEX             ; Next of 2 bytes.
    //CA
    
    BNE.REL SETADR      ; Loop unless X=0.
    //D0
    //F7

 NXTPRNT:        
    BNE.REL PRDATA      ; NE means no address to print.
    //D0
    //14
    
    LDA.IMM 0x8D        ; CR.
    //A9
    //8D
    
    JSR.ROM ECHO        ; Output it.
    //20
    //EF
    //FF
    
    LDA.ZP XAMH        ; ‘Examine index’ high-order byte.
    //A5
    //25
    
    JSR.ROM PRBYTE      ; Output it in hex format.
    //20
    //DC
    //FF
    
    LDA.ZP XAML        ; Low-order ‘examine index’ byte.
    //A5
    //24
    
    JSR.ROM PRBYTE      ; Output it in hex format.
    //20
    //DC
    //FF
    
    LDA.IMM ':' + 0x80    ; ":".
    //A9
    //BA
    
    JSR.ROM ECHO        ; Output it.
    //20
    //EF
    //FF

PRDATA:
    LDA.IMM 0xA0        ; Blank.
    //A9
    //A0
    
    JSR.ROM ECHO        ; Output it.
    //20
    //EF
    //FF
    
    LDA.IND.X XAML    ; Get data byte at ‘examine index’.
    //A1
    //24
    
    JSR.ROM PRBYTE      ; Output it in hex format.
    //20
    //DC
    //FF

XAMNEXT:        
    STX.ZP MODE        ; 0->MODE (XAM mode).
    //86
    //2b
    
    LDA.ZP XAML
    //A5
    //24
    
    CMP.ZP L           ; Compare ‘examine index’ to hex data.
    //C5
    //28
    
    LDA.ZP XAMH
    //A5
    //25
    
    SBC.ZP H
    //E5
    //29
    
    BCS.REL TONEXTITEM  ; Not less, so no more data to output.
    //B0
    //C1
    
    INC.ZP XAML
    //E6
    //24
    
    BNE.REL MOD8CHK     ; Increment ‘examine index’.
    //D0
    //02
    
    INC.ZP XAMH              
    //E6
    //25

MOD8CHK:
    LDA.ZP XAML        ; Check low-order ‘examine index’ byte
    //A5
    //24
    
    AND.IMM 0x07        ; For MOD 8=0
    //29
    //07
    
    BPL.REL NXTPRNT     ; Always taken.
    //10
    //C8
    
PRBYTE:
    PHA             ; Save A for LSD.
    //48
    LSR.ACC
    //4A
    LSR.ACC
    //4A
    LSR.ACC             ; MSD to LSD position.
    //4A
    LSR.ACC
    //4A
    
    JSR.ROM PRHEX       ; Output hex digit.
    //20
    //E5
    //FF
    
    PLA             ; Restore A.
    //68

PRHEX:
    AND.IMM 0x0F        ; Mask LSD for hex print.
    //29
    //0F
    
    ORA.IMM '0' + 0x80    ; Add "0".
    //09
    //B0
    
    CMP.IMM 0xBA        ; Digit?
    //C9
    //BA
    
    BCC.REL ECHO        ; Yes, output it.
    //90
    //02
    
    ADC.IMM 0x06        ; Add offset for letter.
    //69
    //06
    
ECHO:
    BIT.ABS DSP         ; bit (B7) cleared yet?
    //2C
    //12
    //D0
    
    BMI.REL ECHO        ; No, wait for display.
    //30
    //FB
    
    STA.ABS DSP         ; Output character. Sets DA.
    //8d
    //12
    //D0
    
    RTS             ; Return.
    //60
    
    BRK             ; unused
    //00
    
    BRK             ; unused
    //00

; Interrupt Vectors

//    .WORD $0F00     ; NMI
    .byte 0x00, 0x0F
    
//    .WORD RESET     ; RESET
    .byte 0x00, 0xFF
    
//    .WORD $0000     ; BRK/IRQ    
    .byte 0x00, 0x00

    .end
  
