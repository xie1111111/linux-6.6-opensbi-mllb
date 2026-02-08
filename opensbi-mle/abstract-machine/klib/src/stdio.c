#include <am.h>
#include <klib.h>
#include <klib-macros.h>
#include <stdarg.h>

int vsnprintf_internal(char *out, size_t n, const char *fmt, va_list ap);
int vsprintf(char *out, const char *fmt, va_list ap);
#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

inline int isdigit(char c){
    if(c>='0'&&c<='9')
        return 1;
    else
        return 0;
}

void print_float(float val, int width, int precision, int flag) {
    // 将浮点数拆分为整数部分和小数部分
    int integer_part = (int)val;
    float decimal_part = val - integer_part;

    // 处理负数
    if (val < 0) {
        putch('-');
        integer_part = -integer_part;
        decimal_part = -decimal_part;
    }

    // 打印整数部分
    char num[20];
    int i = 0;
    do {
        num[i++] = integer_part % 10 + '0';
        integer_part /= 10;
    } while (integer_part);
    
    while (i > 0) {
        putch(num[--i]);
    }

    // 打印小数部分
    if (precision > 0) {
        putch('.'); // 打印小数点
        while (precision--) {
            decimal_part *= 10;
            int digit = (int)decimal_part;
            putch(digit + '0');
            decimal_part -= digit;
        }
    }
}
int printf(const char *fmt,...){
    va_list args;
    va_start(args, fmt);
    const char *p = fmt;
    while (*p) {
        if (*p != '%') {
            putch(*p++);
            continue;
        }else if(*(p+1) == '%'){
            putch(*p);
            p+=2; //skip %%
            continue;
        }

        p++; // skip '%'

        // ###########FLAG CHAR START#############
        unsigned char flag=0;
        enum{
            AF, // 值应转换为“替代形式” 对于x和X转换，如果结果不为零，则在其前面加上字符串0x（对于X转换，前缀为0X）
            ZF, // 转换后的值在左侧用零而不是空格填充。同时出现0和-标志，则忽略0标志; 值转换指定了精度，则忽略0标志。
            LF, // 转换后的值在字段边界内左对齐。（默认是右对齐。）转换后的值在右侧用空格填充，而不是在左侧用空格或零填充。如果同时指定了LF和ZF，则以LF为准
            SF, // 符号转换产生的数值，总是应在前面放置一个符号（+或-）。默认情况下，只有对于负数会显示符号。如果同时使用了+和空格标志，则以+为准
            PF  // 对于有符号转换（d、i）产生的正数（或空字符串）之前，应留一个空格
        };
        int contiue_loop=1;
        while (*p&&contiue_loop) {
            switch (*p) {
                case '#':flag|=1<<AF;p++;break;
                case '0':flag|=1<<ZF;p++;break;
                case '-':flag|=1<<LF;p++;break;
                case '+':flag|=1<<SF;p++;break;
                case ' ':flag|=1<<PF;p++;break;
                default: contiue_loop=0;break;
            }
        }// ############FLAG CHAR END########

        // ############WIDTH START##########
        contiue_loop=1;
        char width_str[20]={0};
        int i=0;
        while (*p&&contiue_loop) {
            if(isdigit(*p)){
                width_str[i++]=*p;
                p++;
            }else {
                contiue_loop=0;
            }
        }
        int width=atoi(width_str);
        // #############WIDTH END###########
                // ########### Precision handling ##########
        int precision = 6; // 默认精度
        if (*p == '.') {
            p++;
            char precision_str[20] = {0};
            int j = 0;
            while (*p && isdigit(*p)) {
                precision_str[j++] = *p++;
            }
            precision = atoi(precision_str);
        }
        // long type
        bool islong=false;
        if( *p=='l' ) {
            islong=true;
            p++;
        }
        if (*p == 's') {
            const char *s = va_arg(args, const char *);
            while (*s) {
                putch(*s++);
            }
            p++; // skip 's'
        } else if (*p == 'd' || *p == 'i') {
            long d=0;
            if(islong){
                d = va_arg(args, long);
            }else{
                d = va_arg(args, int);
            }
            char num[20]; // assume the max length is 20
            int i = 0;
            if (d < 0) {
                putch('-');
                d = -d;
            }
            do {
                num[i++] = d % 10 + '0';
                d /= 10;
            } while (d);
            while (i > 0) {
                putch(num[--i]);
            }
            p++; // skip 'd'
        } else if (*p == 'x' || *p == 'X') {
            unsigned long d = (unsigned long)va_arg(args, unsigned int);
            if(islong){
                d = (unsigned long)va_arg(args, unsigned long);
            }
            char num[32]; // assume the max length is 20
            int i = 0;
            do {
                unsigned long tmp=d % 16;
                num[i++] = tmp + '0' + ( (tmp>9) ? 7 : 0);
                d /= 16;
            } while (d);

            if (flag&(1<<AF)) {
                putch('0');
                putch(*p);
                // TODO 更多格式化标志支持
            }
            if( (flag&(1<<LF)) == 0){
                if(i+1<=width){
                    int insert_char_num=width-i;
                    char insert_char= flag&(1<<ZF) ? '0' : ' ';

                    while (insert_char_num--) {
                        putch(insert_char);
                    }
                }
            }
            while (i > 0) {
                putch(num[--i]); // 复制数字
            }
            if( (flag&(1<<LF)) != 0){
                if(i+1<=width){
                    int insert_char_num=width-i;
                    char insert_char= flag&(1<<ZF) ? '0' : ' ';

                    while (insert_char_num--) {
                        putch(insert_char);
                    }
                }
            }
            p++; // skip 'd'
        }else if (*p == 'p' || *p == 'P') {
            unsigned long d = (unsigned long)va_arg(args, unsigned long);
            char num[20]; // assume the max length is 20
            int i = 0;
            width=__SIZEOF_POINTER__<<1;
            putch('0');
            putch('x');
            do {
                unsigned long tmp=d % 16;
                num[i++] = tmp + '0' + ( (tmp>9) ? 7 : 0);
                d /= 16;
            } while (d);

            if (flag&(1<<AF)) {
                putch('0');
                putch(*p);
                // TODO 更多格式化标志支持
            }
            if(i+1<=width){
                int insert_char_num=width-i;
                char insert_char= '0';

                while (insert_char_num--) {
                    putch(insert_char);
                }
            }
            while (i > 0) {
                putch(num[--i]); // 复制数字
            }
            p++; // skip 'p'
        }else if (*p == 'f') {
            float f = va_arg(args, double);  // Use double to match the float type in va_arg
            print_float(f, width, precision, flag);
            p++; // Skip 'f'
        } else if (*p=='c'){
            putch((char)va_arg(args, int));
            p++;// skip 'c'
        } else if (*p!=0){
            // Unsupported format specifier, just copy as is
            putch('%');
            putch(*p++);
        }
    }
    // putch('\0'); // null-terminate the string
    va_end(args);
    return 0;
}
int vsprintf(char *out, const char *fmt, va_list ap) {
    char *str = out;
    const char *p = fmt;
    while (*p) {
        if (*p != '%') {
            *str++ = *p++;
            continue;
        }

        p++; // skip '%'

        // ###########FLAG CHAR START#############
        unsigned char flag=0;
        enum{
            AF, // 值应转换为“替代形式” 对于x和X转换，如果结果不为零，则在其前面加上字符串0x（对于X转换，前缀为0X）
            ZF, // 转换后的值在左侧用零而不是空格填充。同时出现0和-标志，则忽略0标志; 值转换指定了精度，则忽略0标志。
            LF, // 转换后的值在字段边界内左对齐。（默认是右对齐。）转换后的值在右侧用空格填充，而不是在左侧用空格或零填充。如果同时指定了LF和ZF，则以LF为准
            SF, // 符号转换产生的数值，总是应在前面放置一个符号（+或-）。默认情况下，只有对于负数会显示符号。如果同时使用了+和空格标志，则以+为准
            PF  // 对于有符号转换（d、i）产生的正数（或空字符串）之前，应留一个空格
        };
        int contiue_loop=1;
        while (*p&&contiue_loop) {
            switch (*p) {
                case '#':flag|=1<<AF;p++;break;
                case '0':flag|=1<<ZF;p++;break;
                case '-':flag|=1<<LF;p++;break;
                case '+':flag|=1<<SF;p++;break;
                case ' ':flag|=1<<PF;p++;break;
                default: contiue_loop=0;break;
            }
        }// ############FLAG CHAR END########

        // ############WIDTH START##########
        contiue_loop=1;
        char width_str[20]={0};
        int i=0;
        while (*p&&contiue_loop) {
            if(isdigit(*p)){
                width_str[i++]=*p;
                p++;
            }else {
                contiue_loop=0;
            }
        }
        int width=atoi(width_str);
        // #############WIDTH END###########
        if (*p == 's') {
            const char *s = va_arg(ap, const char *);
            while (*s) {
                *str++ = *s++;
            }
            p++; // skip 's'
        } else if (*p == 'd' || *p == 'i') {
            long d = va_arg(ap, int);
            char num[20]; // assume the max length is 20
            int i = 0;
            if (d < 0) {
                *str++ = '-';
                d = -d;
            }
            do {
                num[i++] = d % 10 + '0';
                d /= 10;
            } while (d);
            while (i > 0) {
                *str++ = num[--i];
            }
            p++; // skip 'd'
        } else if (*p == 'x' || *p == 'X') {
            unsigned long d = (unsigned int)va_arg(ap, int);
            char num[20]; // assume the max length is 20
            int i = 0;
            do {
                unsigned long tmp=d % 16;
                num[i++] = tmp + '0' + ( (tmp>9) ? 7 : 0);
                d /= 16;
            } while (d);

            if (flag&(1<<AF)) {
                *str++ = '0';
                *str++ = *p;
                // TODO 更多格式化标志支持
            }
            if( (flag&(1<<LF)) == 0){
                if(i+1<=width){
                    int insert_char_num=width-i;
                    char insert_char= flag&(1<<ZF) ? '0' : ' ';

                    while (insert_char_num--) {
                        *str++ = insert_char;
                    }
                }
            }
            while (i > 0) {
                *str++ = num[--i]; // 复制数字
            }
            if( (flag&(1<<LF)) != 0){
                if(i+1<=width){
                    int insert_char_num=width-i;
                    char insert_char= flag&(1<<ZF) ? '0' : ' ';

                    while (insert_char_num--) {
                        *str++ = insert_char;
                    }
                }
            }
            p++; // skip 'd'
        } else if (*p=='c'){
            *str++=(char)va_arg(ap, int);
            p++;// skip 'c'
        } else if (*p!=0){
            // Unsupported format specifier, just copy as is
            *str++ = '%';
            *str++ = *p++;
        }
    }
    *str = '\0'; // null-terminate the string
    return str - out;
}

int sprintf(char *out, const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    int ret = vsprintf(out, fmt, args);
    va_end(args);
    return ret;
}

int vsnprintf_internal(char *out, size_t n, const char *fmt, va_list ap);

int snprintf(char *out, size_t n, const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    int ret = vsnprintf(out, n, fmt, args);
    va_end(args);
    return ret;
}

int vsnprintf(char *out, size_t n, const char *fmt, va_list ap) {
    int ret = vsnprintf_internal(out, n, fmt, ap);
    if (ret >= n) {
        out[n - 1] = '\0'; // Ensure the output string is null-terminated
        return ret;
    }
    return ret;
}

#endif
