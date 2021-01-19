#ifndef EX_1.H
#define EX_1.H

size_t StrLen(const char *s);

int StrCmp(const char *s1, const char *s2);

char *StrCpy(char *dest, const char *src);

char *StrNcpy(char *dest, const char *src, size_t n);

int StrCaseCmp(const char *s1, const char *s2);

char *StrChr(const char *s, int c);

char *StrDup(const char *s);

char *strncpy(char *dest, const char *src, size_t n);

char *StrCat(char *dest, const char *src);

char *StrNcat(char *dest, const char *src, size_t n);

char *StrStr(const char *haystack, const char *needle);

size_t strspn(const char *s1, const char *s2);

#endif /* ifdef GSTRING*/
