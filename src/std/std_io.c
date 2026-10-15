#include "nitro/mi.h"
#include "nitro/std.h"
#include "stdarg.h"

#define STD_FMT_FLAG_0x1 0x1
#define STD_FMT_FLAG_POSITIVE 0x2
#define STD_FMT_FLAG_0x4 0x4
#define STD_FMT_FLAG_NEGATIVE 0x8
#define STD_FMT_FLAG_0x10 0x10
#define STD_FMT_FLAG_LONGLONG 0x20
#define STD_FMT_FLAG_CHAR 0x40
#define STD_FMT_FLAG_LONG 0x80
#define STD_FMT_FLAG_SHORT 0x100
#define STD_FMT_FLAG_UNSIGNED 0x1000
#define STD_FMT_FLAG_NO_ASSIGN 0x2000

typedef struct STDString {
    /* 00 */ u32 space;
    /* 04 */ char *end;
    /* 08 */ char *start;
    /* 0c */
} STDString;

static BOOL STDi_IsSpace(u32 ch);
static void STDi_FillBitset(u32 *bitset, u32 start, u32 end);
static inline void STDi_SetBitset(u32 *bitset, u8 ch);
static inline BOOL STDi_GetBitset(u32 *bitset, u8 ch);
static void string_put_char(STDString *dst, char ch);
static void string_fill_char(STDString *dst, char ch, s32 count);
static void string_put_string(STDString *dst, const char *src, s32 count);

void STD_TSScanf(char *buffer, char *format, ...) {
    va_list args = NULL;
    va_start(args, format);

    STD_TVSScanf(buffer, format, args);

    va_end(args);
}

// https://decomp.me/scratch/3XJR4
static BOOL STDi_IsSpace(u32 ch) {
    u32 var_r0;
    s32 mask;
    BOOL result;

    var_r0 = ch - 9;
    result = false;
    if (var_r0 <= ' ' - 9) {
        mask = 1;
        mask <<= var_r0;
        if (0x80001f & mask) {
            result = true;
        }
    }
    return result;
}

static void STDi_FillBitset(u32 *bitset, u32 start, u32 end) {
    s32 mask;
    u32 wordPos;
    u32 bitPos;
    u32 bitsPerWord;

    bitsPerWord = 8 * sizeof(*bitset);
    for (bitPos = start; bitPos < end;) {
        wordPos = bitPos / bitsPerWord;
        mask    = -1 << (bitPos & (bitsPerWord - 1));
        bitPos  = (wordPos + 1) * bitsPerWord;
        if (bitPos > end) {
            mask &= (1 << (0x1F & end)) - 1;
        }
        bitset[wordPos] |= mask;
    }
}

static inline void STDi_SetBitset(u32 *bitset, u8 ch) {
    bitset[ch / (8 * sizeof(*bitset))] |= 1 << (ch & 0x1f);
}

static inline BOOL STDi_GetBitset(u32 *bitset, u8 ch) {
    return (bitset[ch / (8 * sizeof(*bitset))] >> (ch & 0x1f)) & 1;
}

// https://decomp.me/scratch/fgISI
s32 STD_TVSScanf(const char *buffer, const char *format, va_list args) {
    s32 r2;

    s32 i;
    u32 assignedArgCount;
    s32 maxLength;
    char ch;
    char strCh;
    u8 rangeStart;
    u8 rangeEnd;
    BOOL parsingRange;
    BOOL setInclusive;
    u32 flags;
    u32 sp34;
    u32 digit;
    s32 radix;
    s64 intResult;
    char *strArg;
    const char *start;
    u32 charBitset[8];

    start            = buffer;
    sp34             = 0;
    assignedArgCount = 0;
    for (ch = *format; ch != '\0'; ch = *format) {
        if (STDi_IsSpace(ch)) {
            while (STDi_IsSpace(*format)) {
                ++format;
            }
            while (STDi_IsSpace(*buffer)) {
                ++buffer;
            }
            continue;
        } else if (ch != '%') {
            if (ch == *buffer) {
                if (!STD_CHAR_IS_WIDE(ch) || ch == *++buffer) {
                    ++buffer;
                    ++format;
                    continue;
                }
            }
        } else if (format[1] == '%') {
            if (*buffer == '%') {
                format += 2;
                continue;
            }
        } else {
            r2        = *++format;
            maxLength = 0;
            flags     = 0;
            if (r2 == '*') {
                flags |= STD_FMT_FLAG_NO_ASSIGN;
                r2 = *++format;
            }
            while (r2 >= '0' && r2 <= '9') {
                maxLength = maxLength * 10 + r2 - '0';
                r2        = *++format;
            }
            switch (r2) {
                case 'h':
                    r2 = *++format;
                    if (r2 != 'h') {
                        flags |= STD_FMT_FLAG_CHAR;
                    } else {
                        flags |= STD_FMT_FLAG_SHORT;
                        r2 = *++format;
                    }
                    break;
                case 'l':
                    r2 = *++format;
                    if (r2 != 'l') {
                        flags |= STD_FMT_FLAG_LONGLONG;
                    } else {
                        flags |= STD_FMT_FLAG_LONG;
                        r2 = *++format;
                    }
                    break;
            }
        }
        switch (r2) {
            case 'd':
                radix = 10;
                goto parse_int;
            case 'i':
                radix = -1;
                goto parse_int;
            case 'o':
                radix = 8;
                goto parse_int;
            case 'u':
                radix = 10;
                flags |= STD_FMT_FLAG_UNSIGNED;
                goto parse_int;
            case 'p':
            case 'x':
            case 'X':
                radix = 16;
                flags |= STD_FMT_FLAG_UNSIGNED;
                goto parse_int;
            case 'n':
                if ((flags & STD_FMT_FLAG_NO_ASSIGN) == 0) {
                    --assignedArgCount;
                }
                ++format;
                intResult = buffer - start;
                goto store_int;
            case 'c':
            case 's':
                goto parse_text;
            case '[':
                goto parse_set;
        }
        break;
    parse_int:
        ++format;
        ch = *buffer;
        while (STDi_IsSpace(ch)) {
            ch = *++buffer;
        }
        while (true) {
            if (ch == '+') {
                flags |= STD_FMT_FLAG_POSITIVE;
            } else if (ch == '-') {
                flags |= STD_FMT_FLAG_NEGATIVE;
            } else {
                break;
            }
            ch = *++buffer;
        }
        if (radix == -1) {
            if (ch != '0') {
                radix = 10;
            } else if (buffer[1] == 'x' || buffer[1] == 'X') {
                radix = 16;
            } else {
                radix = 8;
            }
        }
        if (radix == 16 && ch == '0') {
            if (buffer[1] == 'x' || buffer[1] == 'X') {
                buffer += 2;
                ch = *buffer;
            }
        }
        if (maxLength == 0) {
            maxLength = 0x7fffffff;
        }
        for (i = 0; i < maxLength; ++i) {
            digit = ch - '0';
            if (digit >= 10) {
                if (digit - ('a' - '0') < 6) {
                    digit -= 0x27;
                } else {
                    digit -= 'A' - '0';
                    if (digit < 6) {
                        digit += 10;
                    }
                }
            }
            if (digit >= radix) {
                break;
            }
            ch        = *++buffer;
            intResult = intResult * radix + digit;
        }
        if (i == 0) {
            break;
        }
        if (flags & STD_FMT_FLAG_NEGATIVE) {
            intResult = -intResult;
        }
        sp34 = 1;
    store_int:
        if (flags & STD_FMT_FLAG_NO_ASSIGN) {
            continue;
        }
        ++assignedArgCount;
        if (flags & STD_FMT_FLAG_SHORT) {
            *va_arg(args, u8 *) = intResult;
        } else if (flags & STD_FMT_FLAG_CHAR) {
            *va_arg(args, u16 *) = intResult;
        } else if (flags & STD_FMT_FLAG_LONG) {
            *va_arg(args, u64 *) = intResult;
        } else {
            *va_arg(args, u32 *) = intResult;
        }
        continue;
    parse_text:
        sp34   = 1;
        strArg = NULL;
        ++format;
        if ((flags & STD_FMT_FLAG_NO_ASSIGN) == 0) {
            ++assignedArgCount;
            strArg = va_arg(args, char *);
        }
        if (r2 == 's') {
            if (maxLength == 0) {
                maxLength = 0x7fffffff;
            }
            strCh = *buffer;
            while (STDi_IsSpace(strCh)) {
                strCh = *++buffer;
            }
            while (strCh != '\0' && !STDi_IsSpace(strCh) && maxLength > 0) {
                if (strArg != NULL) {
                    *strArg++ = strCh;
                }
                --maxLength;
                strCh = *++buffer;
            }
            if (strArg == NULL) {
                continue;
            }
            *strArg = '\0';
            continue;
        }
        if (maxLength == 0) {
            maxLength = 1;
        }
        for (ch = *buffer; ch != 0 && maxLength > 0; ch = *++buffer, --maxLength) {
            if (strArg != NULL) {
                *strArg++ = ch;
            }
        }
        if (strArg != NULL && maxLength > 0) {
            *strArg = '\0';
        }
        continue;
    parse_set:
        strArg       = NULL;
        parsingRange = false;
        setInclusive = true;
        rangeStart   = '\0';
        ++format;
        MIi_CpuClear32(0, charBitset, sizeof(charBitset));
        if (*format == '^') {
            setInclusive = false;
            ++format;
        }
        if (*format == ']') {
            STDi_SetBitset(charBitset, *format);
            ++format;
        }
        while (true) {
            if (*format == '\0' || *format == ']') {
                if (parsingRange) {
                    STDi_SetBitset(charBitset, rangeStart);
                    STDi_SetBitset(charBitset, '-');
                }
                if (*format == ']') {
                    ++format;
                }
                break;
            } else if (!parsingRange) {
                if (rangeStart != '\0' && *format == '-') {
                    parsingRange = true;
                } else {
                    STDi_SetBitset(charBitset, *format);
                    rangeStart = *format;
                }
            } else {
                rangeEnd = (u8) *format;
                if (rangeStart > rangeEnd) {
                    STDi_SetBitset(charBitset, rangeStart);
                    STDi_SetBitset(charBitset, '-');
                    STDi_SetBitset(charBitset, rangeEnd);
                } else {
                    STDi_FillBitset(charBitset, rangeStart, rangeEnd + 1);
                }
                parsingRange = false;
                rangeStart   = '\0';
            }
            ++format;
        }
        sp34 = 1;
        if ((flags & STD_FMT_FLAG_NO_ASSIGN) == 0) {
            ++assignedArgCount;
            strArg = va_arg(args, char *);
        }
        if (maxLength == 0) {
            maxLength = 0x7fffffff;
        }
        for (ch = *buffer; ch != '\0' && maxLength > 0; ch = *++buffer, --maxLength) {
            if (STDi_GetBitset(charBitset, (u8) ch) != setInclusive) {
                break;
            }
            if (strArg != NULL) {
                *strArg++ = ch;
            }
        }
        if (strArg != NULL) {
            *strArg = '\0';
        }
    }
    if (*buffer == '\0' && sp34 == 0) {
        assignedArgCount = -1;
    }
    return assignedArgCount;
}

static void string_put_char(STDString *dst, char ch) {
    if (dst->space > 0) {
        *dst->end = ch;
        --dst->space;
    }
    ++dst->end;
}

static void string_fill_char(STDString *dst, char ch, s32 count) {
    u32 i;
    u32 written;

    if (count <= 0) {
        return;
    }
    written = dst->space;
    if (written > count) {
        written = count;
    }
    for (i = 0; i < written; ++i) {
        dst->end[i] = ch;
    }
    dst->space -= written;
    dst->end += count;
}

static void string_put_string(STDString *dst, const char *src, s32 count) {
    u32 i;
    u32 written;

    if (count <= 0) {
        return;
    }
    written = dst->space;
    if (written > count) {
        written = count;
    }
    for (i = 0; i < written; ++i) {
        dst->end[i] = src[i];
    }
    dst->space -= written;
    dst->end = dst->end + count;
}

// https://decomp.me/scratch/cjUzS
s32 STD_TVSNPrintf(char *buffer, s32 bufferLen, char *format, va_list args) {
    char intBuffer[24];
    STDString string;
    char prefix[2];
    s32 prefixLen;
    s32 radix;
    s32 width;
    s32 precision;
    char *sp14;
    s32 flags;
    s32 hexA;
    u32 charsWritten;
    s32 digit;
    s32 temp_r1_15;
    s32 temp_r4;
    s32 intLength;
    char *outStr;
    char ch;
    s8 temp_r1_2;
    s64 outInt;
    s32 n;
    s32 tempDiv32;
    s64 tempDiv;
    s32 sp10;

    string.space = bufferLen;
    string.start = buffer;
    string.end   = buffer;

    n = 0;

    while (*format != '\0') {
        flags = 0;
        ch    = *format;
        if (STD_CHAR_IS_WIDE(ch)) {
            ++format;
            string_put_char(&string, ch);
            temp_r1_2 = *format;
            if (temp_r1_2 != '\0') {
                ++format;
                string_put_char(&string, temp_r1_2);
            }
        } else if (ch != '%') {
            ++format;
            string_put_char(&string, ch);
        } else {
            sp14      = format;
            width     = 0;
            precision = -1;
            radix     = 10;
            hexA      = 'a' - 10;
            while (true) {
                format += 1;
                temp_r1_2 = *format;
                switch (temp_r1_2) {
                    case '+':
                        if (*(format - 1) == ' ') {
                            flags |= STD_FMT_FLAG_POSITIVE;
                            continue;
                        }
                        break;
                    case ' ':
                        flags |= STD_FMT_FLAG_0x1;
                        continue;
                    case '-':
                        flags |= STD_FMT_FLAG_NEGATIVE;
                        continue;
                    case '0':
                        flags |= STD_FMT_FLAG_0x10;
                        continue;
                }
                break;
            }
            if (temp_r1_2 == '*') {
                format += 1;
                width = va_arg(args, s32);
                if (width < 0) {
                    width = -width;
                    flags |= STD_FMT_FLAG_NEGATIVE;
                }
            } else {
                while (*format >= '0' && *format <= '9') {
                    width = 10 * width + *format++ - '0';
                }
            }
            if (*format == '.') {
                format += 1;
                precision = 0;
                if (*format == '*') {
                    format += 1;
                    precision = va_arg(args, s32);
                    if (precision < 0) {
                        precision = -1;
                    }
                } else {
                    while (*format >= '0' && *format <= '9') {
                        precision = 10 * precision + *format++ - '0';
                    }
                }
            }
            switch (*format) {
                case 'h':
                    format += 1;
                    if (*format != 0x68) {
                        flags |= 0x40;
                    } else {
                        format += 1;
                        flags |= STD_FMT_FLAG_SHORT;
                    }
                    break;
                case 'l':
                    format += 1;
                    if (*format != 'l') {
                        flags |= STD_FMT_FLAG_LONGLONG;
                    } else {
                        format += 1;
                        flags |= STD_FMT_FLAG_LONG;
                    }
                    break;
            }
            switch (*format) {
                case 'o':
                    radix = 8;
                    flags |= STD_FMT_FLAG_UNSIGNED;
                    goto print_int;
                case 'u':
                    flags |= STD_FMT_FLAG_UNSIGNED;
                    goto print_int;
                case 'X':
                    hexA = 'A' - 10;
                    goto print_hex;
                case 'p':
                    flags |= STD_FMT_FLAG_0x4;
                    precision = 2 * sizeof(void *);
                    goto print_int;
                case 'c':
                    if (precision >= 0) {
                        break;
                    }
                    temp_r4 = va_arg(args, s32);
                    if (flags & STD_FMT_FLAG_NEGATIVE) {
                        string_put_char(&string, temp_r4);
                        string_fill_char(&string, ' ', width - 1);
                    } else {
                        string_fill_char(&string, flags & STD_FMT_FLAG_0x10 ? '0' : ' ', width - 1);
                        string_put_char(&string, temp_r4);
                    }
                    format += 1;
                    break;
                case 's':
                    outStr = va_arg(args, char *);
                    if (precision < 0) {
                        while (outStr[n] != '\0') {
                            ++n;
                        }
                    } else {
                        while (n < precision && outStr[n] != '\0') {
                            ++n;
                        }
                    }
                    width -= n;
                    if (flags & STD_FMT_FLAG_NEGATIVE) {
                        string_put_string(&string, outStr, n);
                        string_fill_char(&string, ' ', width);
                    } else {
                        if (flags & 0x10) {
                            ch = '0';
                        } else {
                            ch = ' ';
                        }
                        string_fill_char(&string, ch, width);
                        string_put_string(&string, outStr, n);
                    }
                    break;
                case 'n':
                    charsWritten = string.end - string.start;
                    if (!(flags & STD_FMT_FLAG_SHORT)) {
                        if (flags & 0x40) {
                            *va_arg(args, u16 *) = charsWritten;
                        } else if (flags & STD_FMT_FLAG_LONG) {
                            *va_arg(args, u64 *) = charsWritten;
                        } else {
                            *va_arg(args, u32 *) = charsWritten;
                        }
                    }
                    format += 1;
                    break;
                case '%':
                    if ((sp14 + 1) == format) {
                        format += 1;
                        string_put_char(&string, '%');
                    } else {
                        string_put_string(&string, sp14, buffer - sp14);
                    }
                    break;
                case 'x':
                print_hex:
                    radix = 16;
                    flags |= STD_FMT_FLAG_UNSIGNED;
                case 'd':
                case 'i':
                print_int:
                    prefixLen = 0;
                    if (flags & STD_FMT_FLAG_NEGATIVE) {
                        flags &= ~STD_FMT_FLAG_0x10;
                    }
                    if (precision < 0) {
                        precision = 1;
                    } else {
                        flags &= ~STD_FMT_FLAG_0x10;
                    }
                    if (flags & STD_FMT_FLAG_UNSIGNED) {
                        if (flags & STD_FMT_FLAG_SHORT) {
                            outInt = va_arg(args, u8);
                        } else if (flags & STD_FMT_FLAG_CHAR) {
                            outInt = va_arg(args, u16);
                        } else if (flags & STD_FMT_FLAG_LONG) {
                            outInt = va_arg(args, u64);
                        } else {
                            outInt = va_arg(args, u32);
                        }
                        flags &= ~(STD_FMT_FLAG_0x1 | STD_FMT_FLAG_POSITIVE);
                        if (flags & STD_FMT_FLAG_0x4) {
                            if (radix == 16) {
                                if (outInt != 0) {
                                    prefix[0] = (s8) (hexA + 'x' - 'a' + 10);
                                    prefix[1] = '0';
                                    prefixLen = 2;
                                }
                            } else if (radix == 8) {
                                prefix[0] = '0';
                                prefixLen = 1;
                            }
                        }
                    } else {
                        if (flags & STD_FMT_FLAG_SHORT) {
                            outInt = va_arg(args, s8);
                        } else if (flags & STD_FMT_FLAG_CHAR) {
                            outInt = va_arg(args, s16);
                        } else if (flags & STD_FMT_FLAG_LONG) {
                            outInt = va_arg(args, s64);
                        } else {
                            outInt = va_arg(args, s32);
                        }
                        if (outInt < 0) {
                            outInt    = -outInt;
                            prefix[0] = '-';
                        } else if (outInt != 0 || precision != 0) {
                            if (flags & STD_FMT_FLAG_POSITIVE) {
                                prefix[0] = '+';
                                prefixLen = 1;
                            } else if (flags & 1) {
                                prefix[0] = ' ';
                                prefixLen = 1;
                            }
                        }
                    }
                    intLength = 0;
                    switch (radix) {
                        case 8:
                            while (outInt != 0) {
                                intBuffer[intLength] = (outInt & 7) + 0x30;
                                outInt >>= 3;
                                ++intLength;
                            }
                            break;
                        case 10:
                            if ((outInt & 0xffffffff00000000) == 0) {
                                n = (u32) outInt;
                                while (n != 0) {
                                    tempDiv32            = n / 10;
                                    intBuffer[intLength] = n - tempDiv32 * 10 + '0';
                                    n                    = tempDiv32;
                                    ++intLength;
                                }
                            } else {
                                while (outInt != 0) {
                                    tempDiv              = outInt / 10;
                                    intBuffer[intLength] = outInt - tempDiv * 10 + '0';
                                    outInt               = tempDiv;
                                    ++intLength;
                                }
                            }
                            break;
                        case 16:
                            while (outInt != 0) {
                                digit = outInt & 0xf;
                                outInt >>= 4;
                                intBuffer[intLength] = digit + (digit < 10 ? '0' : hexA);
                                ++intLength;
                            }
                            break;
                    }
                    if (prefixLen > 0 && prefix[0] == '0') {
                        prefixLen              = 0;
                        intBuffer[intLength++] = '0';
                    }
                    sp10 = precision - intLength;
                    if (flags & STD_FMT_FLAG_0x10) {
                        temp_r1_15 = (width - intLength) - prefixLen;
                        if (sp10 < temp_r1_15) {
                            sp10 = temp_r1_15;
                        }
                    }
                    if (sp10 > 0) {
                        width -= sp10;
                    }
                    width -= prefixLen + intLength;
                    if (!(flags & STD_FMT_FLAG_NEGATIVE)) {
                        string_fill_char(&string, ' ', width);
                    }
                    while (prefixLen > 0) {
                        string_put_char(&string, prefix[--prefixLen]);
                    }
                    string_fill_char(&string, '0', sp10);
                    while (intLength > 0) {
                        string_put_char(&string, intBuffer[--intLength]);
                    }
                    if (flags & STD_FMT_FLAG_NEGATIVE) {
                        string_fill_char(&string, ' ', width);
                    }
                    ++format;
                    break;
            }
        }
    }
    if (string.space > 0) {
        *string.end = '\0';
    } else if (bufferLen != 0) {
        string.start[bufferLen - 1] = '\0';
    }
    return string.end - string.start;
}
