byte readb(word addr) {
    switch (addr) {
        case 0xFF00:
            return REG_P1;
            break;
        case 0xFF01:
            return REG_SB;
            break;
        case 0xFF02:
            return REG_SC;
            break;
        case 0xFF04:
            return REG_DIV;
            break;
        case 0xFF05:
            return REG_TIMA;
            break;
        case 0xFF06:
            return REG_TMA;
            break;
        case 0xFF07:
            return REG_TAC;
            break;
        case 0xFF4D:
            return REG_KEY1;
            break;
        case 0xFF56:
            return REG_RP;
            break;
        case 0xFF70:
            return REG_SVBK;
            break;
        case 0xFF0F:
            return REG_IF;
            break;
        case 0xFFFF:
            return REG_IE;
            break;
        case 0xFF40:
            return REG_LCDC;
            break;
        case 0xFF41:
            return REG_STAT;
            break;
        case 0xFF42:
            return REG_SCY;
            break;
        case 0xFF43:
            return REG_SCX;
            break;
        case 0xFF44:
            return REG_LY;
            break;
        case 0xFF45:
            return REG_LYC;
            break;
        case 0xFF46:
            return REG_DMA;
            break;
        case 0xFF47:
            return REG_BGP;
            break;
        case 0xFF48:
            return REG_OBP0;
            break;
        case 0xFF49:
            return REG_OBP1;
            break;
        case 0xFF4A:
            return REG_WY;
            break;
        case 0xFF4B:
            return REG_WX;
            break;
        case 0xFF4F:
            return REG_VBK;
            break;
        case 0xFF51:
            return REG_HDMA1;
            break;
        case 0xFF52:
            return REG_HDMA2;
            break;
        case 0xFF53:
            return REG_HDMA3;
            break;
        case 0xFF54:
            return REG_HDMA4;
            break;
        case 0xFF55:
            return REG_HDMA5;
            break;
        case 0xFF68:
            return REG_BCPS;
            break;
        case 0xFF69:
            return REG_BCPD;
            break;
        case 0xFF6A:
            return REG_OCPS;
            break;
        case 0xFF6B:
            return REG_OCPD;
            break;
        default:
            break;
    }
}

void writeb(word addr, byte val) {
    switch (addr) {
        case 0xFF00:
            REG_P1 = val;
            break;
        case 0xFF01:
            REG_SB = val;
            break;
        case 0xFF02:
            REG_SC = val;
            break;
        case 0xFF04:
            REG_DIV = val;
            break;
        case 0xFF05:
            REG_TIMA = val;
            break;
        case 0xFF06:
            REG_TMA = val;
            break;
        case 0xFF07:
            REG_TAC = val;
            break;
        case 0xFF4D:
            REG_KEY1 = val;
            break;
        case 0xFF56:
            REG_RP = val;
            break;
        case 0xFF70:
            REG_SVBK = val;
            break;
        case 0xFF0F:
            REG_IF = val;
            break;
        case 0xFFFF:
            REG_IE = val;
            break;
        case 0xFF40:
            REG_LCDC = val;
            break;
        case 0xFF41:
            REG_STAT = val;
            break;
        case 0xFF42:
            REG_SCY = val;
            break;
        case 0xFF43:
            REG_SCX = val;
            break;
        case 0xFF44:
            REG_LY = val;
            break;
        case 0xFF45:
            REG_LYC = val;
            break;
        case 0xFF46:
            REG_DMA = val;
            break;
        case 0xFF47:
            REG_BGP = val;
            break;
        case 0xFF48:
            REG_OBP0 = val;
            break;
        case 0xFF49:
            REG_OBP1 = val;
            break;
        case 0xFF4A:
            REG_WY = val;
            break;
        case 0xFF4B:
            REG_WX = val;
            break;
        case 0xFF4F:
            REG_VBK = val;
            break;
        case 0xFF51:
            REG_HDMA1 = val;
            break;
        case 0xFF52:
            REG_HDMA2 = val;
            break;
        case 0xFF53:
            REG_HDMA3 = val;
            break;
        case 0xFF54:
            REG_HDMA4 = val;
            break;
        case 0xFF55:
            REG_HDMA5 = val;
            break;
        case 0xFF68:
            REG_BCPS = val;
            break;
        case 0xFF69:
            REG_BCPD = val;
            break;
        case 0xFF6A:
            REG_OCPS = val;
            break;
        case 0xFF6B:
            REG_OCPD = val;
            break;
        default:
            break;
    }
}