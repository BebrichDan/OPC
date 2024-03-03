#include <memory.h>
#include <ctype.h>

size_t strlen_(const char *begin) {
    char *end = begin;
    while (*end != '\0')
        end++;
    return end - begin;
}
char* find(char *begin, char *end, int ch) {
    while (begin != end && *begin != ch)
        begin++;
    return begin;
}
char* findNonSpace(char *begin)
{
    while(isspace(*begin))
    {
        begin++;
        if(*begin == '\0')
            return begin;
    }
    return begin;
}
char* findSpace(char *begin)
{
    while(isspace(*begin)==0)
    {
        begin++;
        if(*begin == '\0')
            return begin;
    }
    return begin;
}
char* findNonSpaceReverse(char *rbegin, const char *rend)
{
    while(rbegin != rend && isspace(*rbegin))
        rbegin--;
    return rbegin;
}
char* findSpaceReverse(char *rbegin, const char *rend)
{
    while(rbegin != rend && isspace(*rbegin)==0)
        rbegin--;
    return rbegin;
}
int strcmp(const char *lhs, const char *rhs)
{
    while(*lhs != '\0')
    {
        if(*lhs != *rhs)
            return *lhs-*rhs;
    }
    return 0;
}
char* copy(const char *beginSource, const char *endSource,
             char *beginDestination)
{
    memcpy(beginDestination, beginSource, endSource-beginSource);
    return beginDestination+(endSource-beginSource);                         //нужно ли записывать ноль-символ?
}
char* copyIf(char *beginSource, const char *endSource,
             char *beginDestination, int (*f)(int))
{
    while(beginSource != endSource)
    {
        if(f(*beginSource))
        {
            *beginDestination = *beginSource;
            beginSource++;
            beginDestination++;
        }
    }
    return beginDestination;
}
char* copyIfReverse(char *rbeginSource, const char *rendSource,
                    char *beginDestination, int (*f)(int))
{
    while(rbeginSource != rendSource)
    {
        if(f(*rbeginSource))
        {
            *beginDestination = *rbeginSource;
            rbeginSource--;
            beginDestination++;
        }
    }
    return beginDestination;
}




















