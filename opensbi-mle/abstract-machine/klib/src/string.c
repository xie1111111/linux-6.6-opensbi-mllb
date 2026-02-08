#include <klib.h>
#include <klib-macros.h>
#include <stdint.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

size_t strlen(const char *s) {
    size_t len = 0;
    while (*s != '\0') {
        len++;
        s++;
    }
    return len;
}

char *strcpy(char *dst, const char *src) {
    char *ret = dst;
    while ((*dst++ = *src++) != '\0');
    return ret;
}

char *strncpy(char *dst, const char *src, size_t n) {
    size_t i;
    for (i = 0; i < n && src[i] != '\0'; i++) {
        dst[i] = src[i];
    }
    for (; i < n; i++) {
        dst[i] = '\0';
    }
    return dst;
}

char *strcat(char *dst, const char *src) {
    char *ret = dst;
    while (*dst != '\0') {
        dst++;
    }
    while ((*dst++ = *src++) != '\0');
    return ret;
}

int strcmp(const char *s1, const char *s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return *(unsigned char *)s1 - *(unsigned char *)s2;
}

int strncmp(const char *s1, const char *s2, size_t n) {
    while (n && *s1 && (*s1 == *s2)) {
        n--;
        s1++;
        s2++;
    }
    if (n == 0) {
        return 0;
    }
    return *(unsigned char *)s1 - *(unsigned char *)s2;
}

void *memset(void *s, int c, size_t n) {
    unsigned char *p = s;
    while (n--) {
        *p++ = (unsigned char)c;
    }
    return s;
}

void *memmove(void *dst, const void *src, size_t n) {
    char *d = dst;
    const char *s = src;
    if (d < s) {
        while (n--) {
            *d++ = *s++;
        }
    } else {
        d += n;
        s += n;
        while (n--) {
            *(--d) = *(--s);
        }
    }
    return dst;
}
#if 0
void *memcpy(void *out, const void *in, size_t n) {
    char *dest = out;
    const char *src = in;
    while (n--) {
        *dest++ = *src++;
    }
    return out;
}
#endif
void *memcpy(void *out, const void *in, size_t n) {
    char *dest = (char *)out;
    const char *src = (const char *)in;

    // 使用宽数据类型进行复制
    while (n >= sizeof(uint64_t)) {
        *(uint64_t *)dest = *(const uint64_t *)src;
        dest += sizeof(uint64_t);
        src += sizeof(uint64_t);
        n -= sizeof(uint64_t);
    }

    // 处理剩余的字节
    while (n >= sizeof(uint32_t)) {
        *(uint32_t *)dest = *(const uint32_t *)src;
        dest += sizeof(uint32_t);
        src += sizeof(uint32_t);
        n -= sizeof(uint32_t);
    }
    // 处理剩余的字节
    while (n >= sizeof(uint16_t)) {
        *(uint16_t *)dest = *(const uint16_t *)src;
        dest += sizeof(uint16_t);
        src += sizeof(uint16_t);
        n -= sizeof(uint16_t);
    }

    // 处理剩余的字节
    while (n > 0) {
        *dest++ = *src++;
        n--;
    }

    return out;
}
int memcmp(const void *s1, const void *s2, size_t n) {
    const unsigned char *p1 = s1, *p2 = s2;
    while (n-- > 0) {
        if (*p1 != *p2) {
            return *p1 - *p2;
        }
        p1++;
        p2++;
    }
    return 0;
}

#endif
