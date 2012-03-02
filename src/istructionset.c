#define ADD(reg) \
    if(0xFF - REG_A < reg) REG_F = F_CARRY; \
    if(0x0F - (REG_A & 0x0F) < (reg & 0x0F)) REG_F |= F_HALFCARRY; \
    REG_A += reg; \
    REG_F |= (REG_A) ? 0 : F_ZERO; \
    REG_F |= F_U_SUBTRACT;

#define ADC(reg) \
    if(0x0F - (REG_A & 0x0F) < (REG_F & (F_CARRY | 0x0F) ) REG_F = F_HALFCARRY; \
    if(0xFF - REG_A < REG_F & F_CARRY ) REG_F |= F_CARRY; \
    REG_A = REG_A + reg + (REG_F & F_CARRY) ? 0 : 1; \
    if(0x0F - (REG_A & 0x0F) < (reg & 0x0F)) REG_F |= F_HALFCARRY; \
    if(0xFF - REG_A < reg) REG_F |= F_CARRY; \
    REG_F |= (REG_A) ? 0 : F_ZERO; \
    REG_F |= F_U_SUBTRACT;
    
#define SUB(reg) \
    if(REG_A < reg) REG_F = F_CARRY; \
    if((REG_A & 0x0F) < (reg & 0X0F)) REG_F |= F_HALFCARRY; \
    REG_A += reg; \
    REG_F |= (REG_A) ? 0 : F_ZERO; \
    REG_F |= F_SUBTRACT;

#define SBC(reg) \
    if(REG_A < REG_F & F_CARRY) REG_F = F_CARRY; \
    if((REG_A & 0x0F) < (REG_F & (F_CARRY | 0x0F) REG_F |= F_HALFCARRY; \
    if(REG_A - (REG_F & F_CARRY) < reg) REG_F |= F_CARRY; \
    if(((REG_A - (REG_F & F_CARRY)) & 0x0F) < (reg & 0x0F)) REG_F |= F_HALFCARRY; \
    REG_A = REG_A - (REG_F & F_CARRY) - reg; \
    REG_F |= (REG_A) ? 0 : F_ZERO; \
    REG_F |= F_SUBTRACT;

#define INC(reg) \
    reg++; \
    if(!(reg & 0x0F)) REG_F = F_HALFCARRY; \
    REG_F |= (reg) ? 0 : F_ZERO; \
    REG_F |= F_U_SUBTRACT;

#define DEC(reg) \
    reg--; \
    if((reg & 0x0F) == 0x0F) REG_F = F_HALFCARRY; \
    REG_F |= (reg) ? 0 : F_ZERO; \
    REG_F |= F_SUBTRACT;

#define AND(reg) \
    REG_A &= reg; \
    REG_F = (REG_A) ? F_HALFCARRY : F_ZERO | F_HALFCARRY;

#define xOR(reg) \
    REG_A ^= reg; \
    REG_F = (REG_A) ? 0 : F_ZERO;

#define OR(reg) \
    REG_A |= reg; \
    REG_F = (REG_A) ? 0 : F_ZERO;

#define CP(reg) \
    if(REG_A < reg) REG_F = F_CARRY; \
    if((REG_A & 0x0F) < (reg & 0X0F)) REG_F |= F_HALFCARRY; \
    REG_F |= (REG_A + reg) ? 0 : F_ZERO; \
    REG_F |= F_SUBTRACT;

#define SWAP(reg) \
    byte temp = reg; \
    reg = ((temp & 0xF0) >> 4) | ((temp & 0x0F) << 4); \
    REG_F = (reg == 0) ? F_ZERO : 0;
    

/**
 * opcode 00
 * istruction NOP
 */
void NOP() {
    CLOCK_M = 1;
}
/**
 * opcode 01
 * istruction LD BC d16
 * load immediate word to BC
 */
void LD_BC_d16() {
    REG_BC = readw(REG_PC);
    REG_PC += 2;
    CLOCK_M = 3;
}
/**
 * opcode 02
 * istruction LD (BC) A
 * load register A in memory pointed by BC
 */
void LD_BCm_A() {
    writeb(readb(REG_BC), REG_A);
    CLOCK_M = 2;
}
/**
 * opcode 03
 * istruction INC BC
 * increment the value of register BC
 */
void INC_BC() {
    REG_BC++;
    CLOCK_M = 2;
}
/**
 * opcode 04
 * istruction INC B
 * increment the value of register B
 */
void INC_b() {
    INC(REG_B);
    CLOCK_M = 1;
}
/**
 * opcode 05
 * istruction DEC B
 * decrement the value of register B
 */
void DEC_b() {
    DEC(REG_B);
    CLOCK_M = 1;
}
/**
 * opcode 06
 * istruction LD B d8
 * load immediate halfword to B
 */
void LD_b_d8() {
    REG_B = readb(REG_PC);
    REG_PC++;
    CLOCK_M = 2;
}
/**
 * opcode 07
 * istruction RLCA
 * ?
 */
void RLCA() {
    REG_F = ((REG_A & 0x80) >> 7) ? F_CARRY : 0;
    REG_A = (REG_A << 1) + (REG_F & F_CARRY);
    REG_F |= F_ZERO;
    CLOCK_M = 1;
}
/**
 * opcode 08
 * istruction LD (PC) SP
 * load SP register in memory pointed by PC
 */
void LD_m16_SP() {
    writew(readw(REG_PC), REG_SP);
    REG_PC += 2;
    CLOCK_M = 5;
}
/**
 * opcode 09
 * istruction ADD HL BC
 * Add HL and BC to HL
 */
void ADD_HL_BC() {
    REG_HL += REG_BC;
    REG_F = (REG_HL == 0) ? REG_F | F_CARRY : REG_F & F_U_CARRY;
    CLOCK_M = 3;
}
/**
 * opcode 0A
 * istruction LD A (BC)
 * load halfword pointed by BC in A
 */
void LD_A_BCm() {
    REG_A = rb(REG_BC);
    CLOCK_M = 2;
}
/**
 * opcode 0B
 * istruction DEC BC
 * decrement BC register
 */
void DEC_BC() {
    REG_BC--;
    CLOCK_M = 2;
}
/**
 * opcode 0C
 * istruction INC C
 * increment C register
 */
void INC_c() {
    INC(REG_C);
    CLOCK_M = 1;
}
/**
 * opcode 0D
 * istruction DEC C
 * decrement C register
 */
void DEC_c() {
    DEC(REG_C);
    CLOCK_M = 1;
}
/**
 * opcode 0E
 * istruction LD C (PC)
 * load halfword pointed by PC in C register
 */
void LD_c_d8() {
    REG_C = readb(REG_PC);
    REG_PC++;
    CLOCK_M = 2;
}
/**
 * opcode 0F
 * istruction RRCA
 * ?
 */
void RRCA() {
    byte ci = REG_A & 1 ? 0x80 : 0;
    byte co = REG_A & 1 ? 0x10 : 0;
    REG_A = (REG_A >> 1) + ci;
    REG_F = (REG_F & F_U_CARRY) + co;
    CLOCK_M = 1;
}
/**
 * opcode 10
 * istruction STOP
 * stop the processor ?
 */
void STOP() {
    _stop = 1;
    CLOCK_M = 1;
}
/**
 * opcode 11
 * istruction LD DE (PC)
 * load word pointed in PC in DE register
 */
void LD_DE_d16() {
    REG_DE = readw(REG_PC);
    REG_PC += 2;
    CLOCK_M = 3;
}
/**
 * opcode 12
 * istruction LD (DE) A
 * write A register in memory pointed by DE
 */
void LD_DEm_A() {
    writeb(REG_DE, REG_A);
    CLOCK_M = 2;
}
/**
 * opcode 13
 * istruction INC DE
 * increment DE register
 */
void INC_DE() {
    REG_DE++;
    CLOCK_M = 2;
}
/**
 * opcode 14
 * istruction INC D
 * increment D register
 */
void INC_d() {
    INC(REG_D);
    CLOCK_M = 1;
}
/**
 * opcode 15
 * istruction DEC D
 * decrement D register
 */
void DEC_d() {
    DEC(REG_D);
    CLOCK_M = 1;
}
/**
 * opcode 16
 * istruction LD D (PC)
 * load halfword pointed by PC in D register
 */
void LD_d_d8() {
    REG_D = readb(REG_PC);
    REG_PC++;
    CLOCK_M = 2;
}
/**
 * opcode 17
 * istruction RLA
 * ?
 */
void RLA() {
    byte ci = (REG_F & 0x10) ? 0x01 : 0;
    byte co = (REG_A & 0x80) ? 0x10 : 0;
    REG_A = (REG_A << 1) + ci;
    REG_F = (REG_F & F_U_CARRY) + co;
    CLOCK_M = 1;
}
/**
 * opcode 18
 * istruction JR (PC)
 * jump to istruction pointed by memory pointed by PC
 */
void JR_r8() {
    byte i = readb(REG_PC);
    if( i > 127)
        i = -((~i + 1) & 255);
    REG_PC++;
    CLOCK_M = 2;
    REG_PC += i;
    CLOCK_M++;
}
/**
 * opcode 19
 * istruction ADD HL DE
 * Add HL and DE in HL
 */
void ADD_HL_DE() {
    REG_HL += REG_DE;
    REG_F = (REG_HL == 0) ? REG_F | F_CARRY : REG_F & F_U_CARRY;
    CLOCK_M = 3;
}
/**
 * opcode 1A
 * istruction LD A (DE)
 */
void LD_A_DEm() {
    REG_A = rb(REG_DE);
    CLOCK_M = 2;
}
/**
 * opcode 1B
 * istruction DEC DE
 */
void DEC_DE() {
    REG_DE--;
    CLOCK_M = 2;
}
/**
 * opcode 1C
 * istruction INC E
 */
void INC_e() {
    INC(REG_E);
    CLOCK_M = 1;
}
/**
 * opcode 1D
 * istruction DEC E
 */
void DEC_e() {
    DEC(REG_E);
    CLOCK_M = 1;
}
/**
 * opcode 1E
 * istruction LD E (PC)
 */
void LD_e_d8() {
    REG_E = rb(REG_PC);
    REG_PC++;
    CLOCK_M = 2;
}
/**
 * opcode 1F
 * istruction RRA
 */
void RRA() {
    byte ci = (REG_F & 0x10) ? 0x80 : 0;
    byte co = (REG_A & 0x01) ? 0x10 : 0;
    REG_A = (REG_A >> 1) + ci;
    REG_F = (REG_F & F_U_CARRY) + co;
    CLOCK_M = 1;
}
//0x20
void JR_NZ_r8() {
    byte i = rb(REG_PC);
    if( i > 127)
        i = -((~i+1)&255);
    REG_PC++;
    CLOCK_M = 2;
    if((REG_F & F_ZERO) == 0x00) {
        REG_PC += i;
        CLOCK_M++;
    }
}
//0x21
void LD_HL_d16() {
    REG_HL = rw(REG_PC);
    REG_PC += 2;
    CLOCK_M = 3;
}
//0x22
void LDI_HLm_A() {
    wb(REG_HL, REG_A);
    REG_HL++;
    CLOCK_M = 2;
}
//0x23
void INC_HL() {
    REG_HL++;
    CLOCK_M = 2;
}
//0x24
void INC_h() {
    INC(REG_H);
    CLOCK_M = 1;
}
//0x25
void DEC_h() {
    DEC(REG_H);
    CLOCK_M = 1;
}
//0x26
void LD_h_d8() {
    REG_H = rb(REG_PC);
    REG_PC++;
    CLOCK_M = 2;
}
//0x27
void DAA() {
    byte a = REG_A;
    if((REG_F & F_HALFCARRY) || ((REG_A & 15) > 9))
        REG_A += 6;
    REG_F &= F_U_CARRY;
    if((REG_F & F_HALFCARRY) || (a > 0x99)) {
        REG_A += 0x60;
        REG_F |= F_CARRY;
    }
    CLOCK_M = 1;
}
//0x28
void JR_Z_r8() {
    byte i = rb(REG_PC);
    if( i > 127)
        i = -((~i + 1) & 255);
    REG_PC++;
    CLOCK_M = 2;
    if((REG_F & F_ZERO) == 0x80) {
        REG_PC += i;
        CLOCK_M++;
    }
}
//0x29
void ADD_HL_HL() {
    REG_HL += REG_HL
    REG_F = (REG_HL) ? REG_F | F_CARRY : REG_F & F_U_CARRY;
    CLOCK_M = 3;
}
//0x2A
void LDI_A_HLm() {
    REG_A = rb(REG_HL);
    REG_HL++;
    CLOCK_M = 2;
}
//0x2B
void DEC_HL() {
    REG_HL--;
    CLOCK_M = 2;
}
//0x2C
void INC_l() {
    REG_L++;
    REG_F = (REG_L) ? 0 : F_ZERO;
    CLOCK_M = 1;
}
//0x2D
void DEC_l() {
    REG_L--;
    REG_F = (REG_L) ? 0 : F_ZERO;
    CLOCK_M = 1;
}
//0x2E
void LD_l_d8() {
    REG_L = rb(REG_PC);
    REG_PC++;
    CLOCK_M = 2;
}
//0x2F
void CPL() {
    REG_A ^= 0xFF;
    REG_F = (REG_A) ? 0 : F_ZERO;
    CLOCK_M = 1;
}
//0x30
void JR_NC_r8() {
    byte i = rb(REG_PC);
    if( i > 127)
        i = -((~i + 1) & 255);
    REG_PC++;
    CLOCK_M = 2;
    if((REG_F & F_CARRY) == 0x00) {
        REG_PC += i;
        CLOCK_M++;
    }
}
//0x31
void LD_SP_d16() {
    REG_SP = rw(REG_PC);
    REG_PC += 2;
    CLOCK_M = 3;
}
//0x32
void LDD_HLm_A() {
    wb(REG_HL, REG_A);
    REG_HL--;
    CLOCK_M = 2;
}
//0x33
void INC_SP() {
    REG_SP++;
    CLOCK_M = 1;
}
//0x34
void INC_HLm() {
    byte i = rb(REG_HL) + 1;
    wb(REG_HL, i);
    REG_F = (i) ? 0 : F_ZERO;
    CLOCK_M = 3;
}
//0x35
void DEC_HLm() {
    byte i = rb(REG_HL) - 1;
    wb(REG_HL, i);
    REG_F = (i) ? 0 : F_ZERO;
    CLOCK_M = 3;
}
//0x36
void LD_HLm_d8() {
    wb(REG_HL, rb(REG_PC));
    REG_PC++;
    CLOCK_M = 3;
}
//0x37
void SCF() {
    REG_F = REG_F | F_CARRY | F_U_HALFCARRY | F_U_SUBTRACT;
    CLOCK_M = 1;
}
//0x38
void JR_C_r8() {
    byte i = rb(REG_PC);
    if( i > 127)
        I = -((~i+1)&255);
    REG_PC++;
    CLOCK_M = 2;
    if((REG_F & F_CARRY) == 0x10) {
        REG_PC += i;
        CLOCK_M++;
    }
}
//0x39
void ADD_HL_SP() {
    word HL = (REG_H << 8) + REG_L;
    HL += REG_SP;
    REG_F = (HL > 0xFFFF) ? REG_F | F_CARRY : REG_F & F_U_CARRY;
    REG_H = (HL >> 8) & 255;
    REG_L = HL & 255;
    CLOCK_M = 3;
}
//0x3A
void LDD_A_HLm() {
    REG_A = rb(REG_HL);
    REG_HL--;
    CLOCK_M = 2;
}
//0x3B
void DEC_SP() {
    REG_SP--;
    CLOCK_M = 1;
}
//0x3C
void INC_a() {
    REG_A++;
    REG_F = (REG_A) ? 0 : F_ZERO;
    CLOCK_M = 1;
}
//0x3D
void DEC_a() {
    REG_A--;
    REG_F = (REG_A) ? 0 : F_ZERO;
    CLOCK_M = 1;
}
//0x3E
void LD_a_d8() {
    REG_A = rb(REG_PC);
    REG_PC++;
    CLOCK_M = 2;
}
//0x3F
void CCF() {
    REG_F = (REG_F & F_CARRY) ? 0 : F_CARRY;
    CLOCK_M = 1;
}
//0x40
void LD_b_b() {
    REG_B = REG_B;
    CLOCK_M = 1;
}
//0x41
void LD_b_c() {
    REG_B = REG_C;
    CLOCK_M = 1;
}
//0x42
void LD_b_d() {
    REG_B = REG_D;
    CLOCK_M = 1;
}
//0x43
void LD_b_e() {
    REG_B = REG_E;
    CLOCK_M = 1;
}
//0x44
void LD_b_h() {
    REG_B = REG_H;
    CLOCK_M = 1;
}
//0x45
void LD_b_l() {
    REG_B = REG_L;
    CLOCK_M = 1;
}
//0x46
void LD_b_HLm() {
    REG_B = rb(REG_HL);
    CLOCK_M = 2;
}
//0x47
void LD_b_a() {
    REG_B = REG_A;
    CLOCK_M = 1;
}
//0x48
void LD_c_b() {
    REG_C = REG_B;
    CLOCK_M = 1;
}
//0x49
void LD_c_c() {
    REG_C = REG_C;
    CLOCK_M = 1;
}
//0x4A
void LD_c_d() {
    REG_C = REG_D;
    CLOCK_M = 1;
}
//0x4B
void LD_c_e() {
    REG_C = REG_E;
    CLOCK_M = 1;
}
//0x4C
void LD_c_h() {
    REG_C = REG_H;
    CLOCK_M = 1;
}
//0x4D
void LD_c_l() {
    REG_C = REG_L;
    CLOCK_M = 1;
}
//0x4E
void LD_c_HLm() {
    REG_C = rb(REG_HL);
    CLOCK_M = 2;
}
//0x4F
void LD_c_a() {
    REG_C = REG_A;
    CLOCK_M = 1;
}
//0x50
void LD_d_b() {
    REG_D = REG_B;
    CLOCK_M = 1;
}
//0x51
void LDrr_dc() {
    REG_D = REG_C;
    CLOCK_M = 1;
}
//0x52
void LD_d_d() {
    REG_D = REG_D;
    CLOCK_M = 1;
}
//0x53
void LD_d_e() {
    REG_D = REG_E;
    CLOCK_M = 1;
}
//0x54
void LD_d_h() {
    REG_D = REG_H;
    CLOCK_M = 1;
}
//0x55
void LD_d_l() {
    REG_D = REG_L;
    CLOCK_M = 1;
}
//0x56
void LD_d_HLm() {
    REG_D = rb(REG_HL);
    CLOCK_M = 2;
}
//0x57
void LD_d_a() {
    REG_D = REG_A;
    CLOCK_M = 1;
}
//0x58
void LD_e_b() {
    REG_E = REG_B;
    CLOCK_M = 1;
}
//0x59
void LD_e_c() {
    REG_E = REG_C;
    CLOCK_M = 1;
}
//0x5A
void LD_e_d() {
    REG_E = REG_D;
    CLOCK_M = 1;
}
//0x5B
void LD_e_e() {
    REG_E = REG_E;
    CLOCK_M = 1;
}
//0x5C
void LD_e_h() {
    REG_E = REG_H;
    CLOCK_M = 1;
}
//0x5D
void LD_e_l() {
    REG_E = REG_L;
    CLOCK_M = 1;
}
//0x5E
void LD_e_HLm() {
    REG_E = readb(REG_HL);
    CLOCK_M = 2;
}
//0x5F
void LD_e_a() {
    REG_E = REG_A;
    CLOCK_M = 1;
}
//0x60
void LD_h_b() {
    REG_H = REG_B;
    CLOCK_M = 1;
}
//0x61
void LD_h_c() {
    REG_H = REG_C;
    CLOCK_M = 1;
}
//0x62
void LD_h_d() {
    REG_H = REG_D;
    CLOCK_M = 1;
}
//0x63
void LD_h_e() {
    REG_H = REG_E;
    CLOCK_M = 1;
}
//0x64
void LD_h_h() {
    REG_H = REG_H;
    CLOCK_M = 1;
}
//0x65
void LD_h_l() {
    REG_H = REG_L;
    CLOCK_M = 1;
}
//0x66
void LD_h_HLm() {
    REG_H = readb(REG_HL);
    CLOCK_M = 2;
}
//0x67
void LD_h_a() {
    REG_H = REG_A;
    CLOCK_M = 1;
}
//0x68
void LD_l_b() {
    REG_L = REG_B;
    CLOCK_M = 1;
}
//0x69
void LD_l_c() {
    REG_L = REG_C;
    CLOCK_M = 1;
}
//0x6A
void LD_l_d() {
    REG_L = REG_D;
    CLOCK_M = 1;
}
//0x6B
void LD_l_e() {
    REG_L = REG_E;
    CLOCK_M = 1;
}
//0x6C
void LD_l_h() {
    REG_L = REG_H;
    CLOCK_M = 1;
}
//0x6D
void LD_l_l() {
    REG_L = REG_L;
    CLOCK_M = 1;
}
//0x6E
void LD_l_HLm() {
    REG_L = readb(REG_HL);
    CLOCK_M = 2;
}
//0x6F
void LD_l_a() {
    REG_L = REG_A;
    CLOCK_M = 1;
}
//0x70
void LD_HLm_b() {
    writeb(REG_HL, REG_B);
    CLOCK_M = 2;
}
//0x71
void LD_HLm_c() {
    writeb(REG_HL, REG_C);
    CLOCK_M = 2;
}
//0x72
void LD_HLm_d() {
    writeb(REG_HL, REG_D);
    CLOCK_M = 2;
}
//0x73
void LD_HLm_e() {
    writeb(REG_HL, REG_E);
    CLOCK_M = 2;
}
//0x74
void LD_HLm_h() {
    writeb(REG_HL, REG_H);
    CLOCK_M = 2;
}
//0x75
void LD_HLm_l() {
    writeb(REG_HL, REG_L);
    CLOCK_M = 2;
}
//0x76
void HALT() {
    _halt = 1;
    CLOCK_M = 1;
}
//0x77
void LD_HLm_a() {
    writeb(REG_HL, REG_A);
    CLOCK_M = 2;
}
//0x78
void LD_a_b() {
    REG_A = REG_B;
    CLOCK_M = 1;
}
//0x79
void LD_a_c() {
    REG_A = REG_C;
    CLOCK_M = 1;
}
//0x7A
void LD_a_d() {
    REG_A = REG_D;
    CLOCK_M = 1;
}
//0x7B
void LD_a_e() {
    REG_A = REG_E;
    CLOCK_M = 1;
}
//0x7C
void LD_a_h() {
    REG_A = REG_H;
    CLOCK_M = 1;
}
//0x7D
void LD_a_l() {
    REG_A = REG_L;
    CLOCK_M = 1;
}
//0x7E
void LD_a_HLm() {
    REG_A = readb(REG_HL);
    CLOCK_M = 2;
}
//0x7F
void LD_a_a() {
    REG_A = REG_A;
    CLOCK_M = 1;
}
//0x80
void ADD_b() {
    ADD(REG_B);
    CLOCK_M = 1;
}
//0x81
void ADD_c() {
    ADD(REG_C);
    CLOCK_M = 1;
}
//0x82
void ADD_d() {
    ADD(REG_D);
    CLOCK_M = 1;
}
//0x83
void ADD_e() {
    ADD(REG_E);
    CLOCK_M = 1;
}
//0x84
void ADD_h() {
    ADD(REG_H);
    CLOCK_M = 1;
}
//0x85
void ADD_l() {
    ADD(REG_L);
    CLOCK_M = 1;
}
//0x86
void ADD_HLm() {
    ADD(readb(REG_HL));
    CLOCK_M = 2;
}
//0x87
void ADD_a() {
    ADD(REG_A);
    CLOCK_M = 1;
}
//0x88
void ADC_b() {
    ADC(REG_B);
    CLOCK_M = 1;
}
//0x89
void ADC_c() {
    ADC(REG_C);
    CLOCK_M = 1;
}
//0x8A
void ADC_d() {
    ADC(REG_D);
    CLOCK_M = 1;
}
//0x8B
void ADC_e() {
    ADC(REG_E);
    CLOCK_M = 1;
}
//0x8C
void ADC_h() {
    ADC(REG_H);
    CLOCK_M = 1;
}
//0x8D
void ADC_l() {
    ADC(REG_L);
    CLOCK_M = 1;
}
//0x8E
void ADC_HLm() {
    ADC(readb(HL));
    CLOCK_M = 2;
}
//0x8F
void ADC_a() {
    ADC(REG_A);
    CLOCK_M = 1;
}
//0x90
void SUB_b() {
    SUB(REG_B);
    CLOCK_M = 1;
}
//0x91
void SUB_c() {
    SUB(REG_C);
    CLOCK_M = 1;
}
//0x92
void SUB_d() {
    SUB(REG_D);
    CLOCK_M = 1;
}
//0x93
void SUB_e() {
    SUB(REG_E);
    CLOCK_M = 1;
}
//0x94
void SUB_h() {
    SUB(REG_H);
    CLOCK_M = 1;
}
//0x95
void SUB_l() {
    SUB(REG_L);
    CLOCK_M = 1;
}
//0x96
void SUB_HLm() {
    SUB(readb(REG_HL));//controllare bisognerebbe riscrivere in memoria
    CLOCK_M = 2;
}
//0x97
void SUB_a() {
    SUB(REG_A);
    CLOCK_M = 1;
}
//0x98
void SBC_b() {
    SBC(REG_B);
    CLOCK_M = 1;
}
//0x99
void SBC_c() {
    SBC(REG_C);
    CLOCK_M = 1;
}
//0x9A
void SBC_d() {
    SBC(REG_D);
    CLOCK_M = 1;
}
//0x9B
void SBC_e() {
    SBC(REG_E);
    CLOCK_M = 1;
}
//0x9C
void SBC_h() {
    SBC(REG_H);
    CLOCK_M = 1;
}
//0x9D
void SBC_l() {
    SBC(REG_L);
    CLOCK_M = 1;
}
//0x9E
void SBC_HLm() {
    SBC(readb(REG_HL));//controllare bisognerebbe riscrivere in memoria
    CLOCK_M = 2;
}
//0x9F
void SBC_a() {
    SBC(REG_A);
    CLOCK_M = 1;
}
//0xA0
void AND_b() {
    AND(REG_B);
    CLOCK_M = 1;
}
//0xA1
void AND_c() {
    AND(REG_C);
    CLOCK_M = 1;
}
//0xA2
void AND_d() {
    AND(REG_D);
    CLOCK_M = 1;
}
//0xA3
void AND_e() {
    AND(REG_E);
    CLOCK_M = 1;
}
//0xA4
void AND_h() {
    AND(REG_H);
    CLOCK_M = 1;
}
//0xA5
void AND_l() {
    AND(REG_L);
    CLOCK_M = 1;
}
//0xA6
void AND_HLm() {
    AND(readb(REG_HL));
    CLOCK_M = 2;
}
//0xA7
void AND_a() {
    AND(REG_A);
    CLOCK_M = 1;
}
//0xA8
void XOR_b() {
    XOR(REG_B);
    CLOCK_M = 1;
}
//0xA9
void XOR_c() {
    XOR(REG_C);
    CLOCK_M = 1;
}
//0xAA
void XOR_d() {
    XOR(REG_D);
    CLOCK_M = 1;
}
//0xAB
void XOR_e() {
    XOR(REG_E);
    CLOCK_M = 1;
}
//0xAC
void XOR_h() {
    XOR(REG_H);
    CLOCK_M = 1;
}
//0xAD
void XOR_l() {
    XOR(REG_L);
    CLOCK_M = 1;
}
//0xAE
void XOR_HLm() {
    XOR(readb(REG_HL));
    CLOCK_M = 2;
}
//0xAF
void XOR_a() {
    XOR(REG_A);
    CLOCK_M = 1;
}
//0xB0
void OR_b() {
    OR(REG_B);
    CLOCK_M = 1;
}
//0xB1
void OR_c() {
    OR(REG_C);
    CLOCK_M = 1;
}
//0xB2
void OR_d() {
    OR(REG_D);
    CLOCK_M = 1;
}
//0xB3
void OR_e() {
    OR(REG_E);
    CLOCK_M = 1;
}
//0xB4
void OR_h() {
    OR(REG_H);
    CLOCK_M = 1;
}
//0xB5
void OR_l() {
    OR(REG_L);
    CLOCK_M = 1;
}
//0xB6
void OR_HLm() {
    OR(readb(REG_HL));
    CLOCK_M = 2;
}
//0xB7
void OR_a() {
    OR(REG_A);
    CLOCK_M = 1;
}
//0xB8
void CP_b() {
    CP(REG_B);
    CLOCK_M = 1;
}
//0xB9
void CP_c() {
    CP(REG_C);
    CLOCK_M = 1;
}
//0xBA
void CP_d() {
    CP(REG_D);
    CLOCK_M = 1;
}
//0xBB
void CP_e() {
    CP(REG_E);
    CLOCK_M = 1;
}
//0xBC
void CP_h() {
    CP(REG_H);
    CLOCK_M = 1;
}
//0xBD
void CP_l() {
    CP(REG_L);
    CLOCK_M = 1;
}
//0xBE
void CP_HLm() {
    CP(readb(REG_HL));
    CLOCK_M = 2;
}
//0xBF
void CP_a() {
    CP(REG_A);
    CLOCK_M = 1;
}
//0xC0
void RET_NZ() {
    CLOCK_M = 1;
    if((REG_F & F_ZERO) == 0x00) {
        REG_PC = readw(REG_SP);
        REG_SP += 2;
        CLOCK_M += 2;
    }
}
//0xC1
void POP_BC() {
    REG_C = readb(REG_SP);
    REG_SP++;
    REG_B = readb(REG_SP);
    REG_SP++;
    CLOCK_M = 3;
}
//0xC2
void JP_NZ_a16() {
    CLOCK_M = 3;
    if((REG_F & F_ZERO) == 0x00) {
        REG_PC = readw(REG_PC);
        CLOCK_M++;
    } else {
        REG_PC += 2;
    }
}
//0xC3
void JP_a16() {
    REG_PC = readw(REG_PC);
    CLOCK_M = 3;
}
//0xC4
void CALL_NZ_a16() {
    CLOCK_M = 3;
    if((REG_F & F_ZERO) == 0x00) {
        REG_SP -= 2;
        writew(REG_SP, REG_PC + 2);
        REG_PC = readw(REG_PC);
        CLOCK_M += 2;
    } else {
        REG_PC += 2;
    }
}
//0xC5
void PUSH_BC() {
    REG_SP--;
    writeb(REG_SP, REG_B);
    REG_SP--;
    writeb(REG_SP, REG_C);
    CLOCK_M = 3;
}
//0xC6
void ADD_d8() {
    byte a = ;
    byte m = readb(REG_PC);
     += m;
    REG_PC++;
    REG_F = ( > 255) ? F_CARRY : 0;
     &= 255;
    if(!) REG_F |= F_ZERO;
    if((^a^m) & 0x10) REG_F |= F_HALFCARRY;
    CLOCK_M = 2;
}
//0xC7
void RST_00h() {
    
}
//0xC8
void RET_Z() {
    CLOCK_M = 1;
    if((REG_F & F_ZERO) == F_ZERO) {
        REG_PC = readw(REG_SP);
        REG_SP += 2;
        CLOCK_M += 2;
    }
}
//0xC9
void RET() {
    REG_PC = readw(REG_SP);
    REG_SP += 2;
    CLOCK_M = 3;
}
//0xCA
void JP_Z_a16() {
    CLOCK_M = 3;
    if((REG_F & F_ZERO) == F_ZERO) {
        REG_PC = readw(REG_PC);
        CLOCK_M++;
    } else {
        REG_PC += 2;
    }
}
//0xCB
void prefix_CB() {
    REG_PC+1;
    //richiamo dalla mappa
}
//0xCC
void CALL_Z_a16() {
    CLOCK_M = 3;
    if((REG_F & F_ZERO) == F_ZERO) {
        REG_SP -= 2;
        writew(REG_SP, REG_PC + 2);
        REG_PC = readw(REG_PC);
        CLOCK_M += 2;
    } else {
        REG_PC += 2;
    }
}
//0xCD
void CALL_a16() {
    REG_SP -= 2;
    writew(REG_SP, REG_PC + 2);
    REG_PC = readw(REG_PC);
    CLOCK_M = 5;
}
//0xCE
void ADC_d8() {
    byte a = ;
    byte m = readb(REG_PC);
     += m;
    REG_PC++;
     += (REG_F & F_CARRY) ? 1 : 0;
    REG_F = ( > 255) ? F_CARRY : 0;
     &= 255;
    if(!) REG_F |= F_ZERO;
    if((^m^a) & 0x10) REG_F |= F_HALFCARRY;
    CLOCK_M = 2;
}
//0xCF
void RST_08h() {
    
}
//0xD0
void RET_NC() {
    CLOCK_M = 1;
    if((REG_F & F_CARRY) == 0x00) {
        REG_PC = readw(REG_SP);
        REG_SP += 2;
        CLOCK_M += 2;
    }
}
//0xD1
void POP_DE() {
    REG_E = readb(REG_SP);
    REG_SP++;
    REG_D = readb(REG_SP);
    REG_SP++;
    CLOCK_M = 3;
}
//0xD2
void JP_NC_a16() {
    CLOCK_M = 3;
    if((REG_F & F_CARRY) == 0x00) {
        REG_PC = readw(REG_PC);
        CLOCK_M++;
    } else {
        REG_PC += 2;
    }
}
//0xD3 non esiste
//0xD4
void CALL_NZ_r16() {
    CLOCK_M = 3;
    if((REG_F & F_ZERO) == 0x00) {
        REG_SP -= 2;
        writew(REG_SP, REG_PC + 2);
        REG_PC = readw(REG_PC);
        CLOCK_M += 2;
    } else {
        REG_PC += 2;
    }
}
//0xD5
void PUSH_DE() {
    REG_SP--;
    writeb(REG_SP, REG_D);
    REG_SP--;
    writeb(REG_SP, REG_E);
    CLOCK_M = 3;
}
//0xD6
void SUB_d8() {
    byte a = ;
    byte m = readb(REG_PC);
     -= m;
    REG_PC++;
    REG_F = ( < 0) ? F_CARRY | F_SUBTRACT : F_SUBTRACT;
     &= 255;
    if(!) REG_F |= F_ZERO;
    if((^m^a) & 0x10) REG_F |= F_HALFCARRY;
    CLOCK_M = 2;
}
//0xD7
void RST_10h() {
    
}
//0xD8
void RET_C() {
    CLOCK_M = 1;
    if((REG_F & F_CARRY) == F_CARRY) {
        REG_PC = readw(REG_SP);
        REG_SP += 2;
        CLOCK_M += 2;
    }
}
//0xD9
void RETI() {
    REG_PC = readw(REG_SP);
    REG_SP += 2;
    CLOCK_M = 3;
}
//0xDA
void JP_C_a16() {
    CLOCK_M = 3;
    if((REG_F & F_CARRY) == F_CARRY) {
        REG_PC = readw(REG_PC);
        CLOCK_M++;
    } else {
        REG_PC += 2;
    }
}
//0xDB non esiste
//0xDC
void CALL_C_a16() {
    CLOCK_M = 3;
    if((REG_F & F_CARRY) == F_CARRY) {
        REG_SP -= 2;
        writew(REG_SP, REG_PC + 2);
        REG_PC = readw(REG_PC);
        CLOCK_M += 2;
    } else {
        REG_PC += 2;
    }
}
//0xDD non esiste
//0xDE
void SBC_d8() {
    byte a = ;
    byte m = readb(REG_PC);
     -= m;
    REG_PC++;
     -= (REG_F & F_CARRY) ? 1 : 0;
    REG_F = ( < 0) ? F_CARRY | F_SUBTRACT : F_SUBTRACT;
     &= 255;
    if(!) REG_F |= F_ZERO;
    if((^m^a) & 0x10) REG_F |= F_HALFCARRY;
    CLOCK_M = 2;
    
}
//0xDF
void RST_18h() {
    
}
//0xE0
void LDH_d8_A() {
    writeb(0xFF00 + readb(REG_PC), REG_A);
    REG_PC++;
    CLOCK_M = 3;
}
//0xE1
void POP_HL() {
    REG_L = rb(REG_SP);
    REG_SP++;
    REG_H = rb(REG_SP);
    REG_SP++;
    CLOCK_M = 3;
    
}
//0xE2
void LD_Cm_A() {
    writeb(0xFF00 + REG_C, REG_A);
    CLOCK_M = 2;
}
//0xE3 non esiste
//0xE4 non esiste
//0xE5
void PUSH_HL() {
    REG_SP--;
    wb(REG_SP, REG_H);
    REG_SP--;
    wb(REG_SP, REG_L);
    CLOCK_M = 3;
}
//0xE6
void AND_d8() {
     &= rb(REG_PC);
    REG_PC++;
     &= 255;
    REG_F = () ? 0 : F_ZERO;
    CLOCK_M = 2;
}
//0xE7
void RST_20h() {
    
}
//0xE8
void ADD_SP_r8() {
    byte i = readb(_r,pc);
    if(i > 127)
        i=-((~i + 1) & 255);
    REG_PC++;
    REG_SP += i;
    CLOCK_M = 4;
}
//0xE9
void JP_HLm() {
    REG_PC = REG_HL;
    CLOCK_M = 1;
}
//0xEA
void LD_m8_A() {
    writeb(readw(REG_PC), REG_A);
    REG_PC += 2;
    CLOCK_M = 4;
}
//0xEB non esiste
//0xEC non esiste
//0xED non esiste
//0xEE
void XOR_d8() {
     ^= rb(REG_PC);
    REG_PC++;
     &= 255;
    REG_F = () ? 0 : F_ZERO;
    CLOCK_M = 2;
}
//F_U_CARRY
void RST_28h() {
    
}
//0xF0
void LDH_A_d8() {
    REG_A = readb(0xFF00 + readb(REG_PC));
    REG_PC++;
    CLOCK_M = 3;
}
//0xF1
void POP_AF() {
    REG_AF = readw(REG_SP);
    REG_SP += 2;
    CLOCK_M = 3;
}
//0xF2
void LD_A_Cm() {
    REG_A = readb(0xFF00 + REG_C);
    CLOCK_M = 2;
}
//0xF3
void DI() {
    REG_IME = 0;
    CLOCK_M = 1;
}
//0xF4 //non presente
//0xF5
void PUSH_AF() {
    REG_SP -= 2;
    writew(REG_SP, REG_AF);
    CLOCK_M = 3;
}
//0xF6
void OR_d8() {
    REG_A |= readb(REG_PC);
    REG_PC++;
    REG_A &= 255;
    REG_F = () ? 0 : F_ZERO;
    CLOCK_M = 2;
}
//0xF7
void RST_30h() {
    
}
//0xF8
void LD_HL_SP() {
    byte i = readb(REG_PC);
    if(i > 127) i = -((~i + 1) & 255);
    REG_PC++;
    i += REG_SP;
    REG_HL = i;
    CLOCK_M = 3;
}//da controllare
//0xF9
void LD_SP_HL() {
    
}
//0xFA
void LD_A_m8() {
    REG_A = readb(readw(REG_PC));
    REG_PC += 2;
    CLOCK_M = 4;
}
//0xFB
void EI() {
    REG_IME = 1;
    CLOCK_M = 1;
}
//0xFC non esiste
//0xFD non esiste
//0xFE
void CP_d8() {
    byte i = ;
    byte m = readb(REG_PC);
    REG_PC++;
    i -= m;
    REG_F = (i < 0) ? F_CARRY | F_SUBTRACT : F_SUBTRACT;
    i &= 255;
    if(!i) REG_F |= F_ZERO;
    if((^m^i) & 0x10) REG_F |= F_HALFCARRY;
    CLOCK_M = 2;
}
//0xFE
void RST_38h() {
    
}


void LD_HLm_m16() {
    word addr = readw(REG_PC);
    REG_PC += 2;
    REG_HL = readw(addr);
    CLOCK_M = 5;
};

void LD_m16_HLm() {
    word addr = readw(REG_PC);
    REG_PC += 2;
    writew(addr, REG_HL);
    CLOCK_M = 5;
}



//part of CB
//0x30
void SWAP_b() {
    SWAP(REG_B);
    CLOCK_M = 1;
}
//0x31
void SWAP_c() {
    SWAP(REG_C);
    CLOCK_M = 1;
}
//0x32
void SWAP_d() {
    SWAP(REG_D);
    CLOCK_M = 1;
}
//0x33
void SWAP_e() {
    SWAP(REG_E);
    CLOCK_M = 1;
}
//0x34
void SWAP_h() {
    SWAP(REG_H);
    CLOCK_M = 1;
}
//0x35
void SWAP_l() {
    SWAP(REG_L);
    CLOCK_M = 1;
}
//0x36
void SWAP_HLm() {
    byte m = readb(REG_HL);
    byte tr = m;
    m = (tr & 0x0F) << 4) | ((tr & 0xF0) >> 4);
    writeb(REG_HL, m);
    REG_F = (m) ? 0 : F_ZERO;
    CLOCK_M = 1;
}
//0x37
void SWAP_a() {
    SWAP(REG_A);
    CLOCK_M = 1;
}