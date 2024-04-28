#include <memory.h>
#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>
#include "string_.h"

char _stringBuffer[MAX_STRING_SIZE + 1];
char _stringBuffer2[MAX_STRING_SIZE + 1];

BagOfWords _bag;
BagOfWords _bag2;

size_t strlen_(const char *begin)
{
    char *end = begin;
    while (*end != '\0')
        end++;
    return end - begin;
}

char *find(char *begin, char *end, int ch)
{
    while (begin != end && *begin != ch)
        begin++;
    return begin;
}

char *findNonSpace(char *begin)
{
    while (isspace(*begin))
    {
        begin++;
        if (*begin == '\0')
            return begin;
    }
    return begin;
}

char *findSpace(char *begin)
{
    while (isspace(*begin) == 0)
    {
        begin++;
        if (*begin == '\0')
            return begin;
    }
    return begin;
}

char *findNonSpaceReverse(char *rbegin, const char *rend)
{
    while (rbegin != rend && isspace(*rbegin))
        rbegin--;
    return rbegin;
}

char *findSpaceReverse(char *rbegin, const char *rend)
{
    while (rbegin != rend && isspace(*rbegin) == 0)
        rbegin--;
    return rbegin;
}

int strcmp(const char *lhs, const char *rhs)
{
    while (*lhs != '\0')
    {
        if (*lhs != *rhs)
            return *lhs - *rhs;
        lhs++;
        rhs++;
    }
    return 0;
}

char *copy(const char *beginSource, const char *endSource,
           char *beginDestination)
{
    memcpy(beginDestination, beginSource, endSource - beginSource);
    return beginDestination + (endSource - beginSource);                         //нужно ли записывать ноль-символ?
}

char *copyIf(char *beginSource, const char *endSource,
             char *beginDestination, int (*f)(int))
{
    while (beginSource != endSource)
    {
        if (f(*beginSource))
        {
            *beginDestination = *beginSource;
            beginSource++;
            beginDestination++;
        } else
            beginSource++;
    }
    return beginDestination;
}

char *copyIfReverse(char *rbeginSource, const char *rendSource,
                    char *beginDestination, int (*f)(int))
{
    while (rbeginSource != rendSource)
    {
        if (f(*rbeginSource))
        {
            *beginDestination = *rbeginSource;
            rbeginSource--;
            beginDestination++;
        } else
            rbeginSource--;
    }
    return beginDestination;
}


//18
char stringBuffer[50];
char stringBuffer1[MAX_STRING_SIZE + 1];

char *getEndOfString(char *s)
{
    return s + strlen_(s);
}

void removeNonLetters(char *s)
{
    char *endSource = getEndOfString(s);
    char *destination = copyIf(s, endSource, s, isgraph);
    *destination = '\0';
}

void assertString(const char *expected, char *got,
                  char const *fileName, char const *funcName,
                  int line)
{                                                            //какой смысл в том чтобы самому вывдить строку?
    if (strcmp(expected, got) != 0)
    {
        fprintf(stderr, "File %s\n", fileName);
        fprintf(stderr, "%s - failed on line %d\n", funcName, line);
        fprintf(stderr, "Expected: \"%s\"\n", expected);
        fprintf(stderr, "Got: \"%s\"\n\n", got);
    } else
        fprintf(stderr, "%s - OK\n", funcName);
}

void removeAdjacentEqualLetters(char *s)
{
    char *iRead = s + 1;
    char *iWrite = s + 1;
    while (*iRead != 0)
    {
        if (*iRead == *(iRead - 1))
            iRead++;
        else
        {
            *iWrite = *iRead;
            iWrite++;
            iRead++;
        }
    }
    *iWrite = '\0';
}

void removeExtraSpaces(char *s)
{
    char *iRead = s + 1;
    char *iWrite = s + 1;
    while (*iRead != 0)
    {
        if (*iRead == *(iRead - 1) && *iRead == ' ')
            iRead++;
        else
        {
            *iWrite = *iRead;
            iWrite++;
            iRead++;
        }
    }
    *iWrite = '\0';
}


int getWord(char *beginSearch, WordDescriptor *word)
{
    word->begin = findNonSpace(beginSearch);
    if (*word->begin == '\0')
        return 0;
    word->end = findSpace(word->begin);
    return 1;
}

bool getWordReverse(char *rbegin, char *rend, WordDescriptor *word)
{
    word->begin = findNonSpaceReverse(rbegin, rend);
    if (*word->end == '\0' || word->begin == rend)
        return 0;
    word->end = findSpaceReverse(word->begin, rend);
    return word->end != rend;
}

char *findComma(char *begin)
{
    char *ptr = begin;

    while (*ptr != '\0')
    {
        int res = 0;
        res = *ptr == ',';
        if (res)
        {
            return ptr;
        }

        ptr += sizeof(char);
    }
    return ptr;
}

char *findNonComma(char *begin)
{
    char *ptr = begin;

    while (*ptr != '\0')
    {
        int res = 0;
        res = *ptr == ',';
        if (!res)
        {
            return ptr;
        }

        ptr += sizeof(char);
    }
    return ptr;
}

int getWordByComma(char *beginSearch, WordDescriptor *word)
{
    word->begin = findNonComma(beginSearch);
    if (*word->begin == '\0')
        return 0;
    word->end = findComma(word->begin);
    return 1;
}

void digitToEnd(WordDescriptor word)
{
    char *endStringBuffer = copy(word.begin, word.end,
                                 stringBuffer);
    char *recPosition = copyIf(stringBuffer - 1,
                               endStringBuffer,
                               word.begin, isalpha);
    copyIf(stringBuffer, endStringBuffer, recPosition, isdigit);
}

void digitsToEnd(char *s)
{
    char *beginSearch = s;
    WordDescriptor word; // считываемое слово
    while (getWord(beginSearch, &word))
    {
        digitToEnd(word);
        beginSearch = word.end;
    }
}

void copyStringToBuffer(char *s)
{
    char *indicator = stringBuffer1;             //зачем доп указатель
    while (*s && indicator - stringBuffer1 < MAX_STRING_SIZE)
        *indicator++ = *s++;
    *indicator = '\0';
}

char *numberEqualToNumberSpaces(char *s)
{
    copyStringToBuffer(s);
    char *readPtr = stringBuffer1;

    char *result = (char *) malloc(MAX_STRING_SIZE * sizeof(char));
    char *writePtr = result;  // зачем указатель на начало результирующей строки

    while (*readPtr)
    {
        if (isdigit(*readPtr))
        {
            int digit = *readPtr - '0';
            for (int i = 0; i < digit; i++)
                *writePtr++ = ' ';

        } else
        {
            *writePtr++ = *readPtr;
        }
        readPtr++;
    }
    *writePtr = '\0';

    return result;
}

int strncmp_(const char *s1, const char *s2, size_t n)
{
    if (*(s1 - 1) == '\0' && *(s1 + n) == '\0')
    {
        while (n--)
        {
            if (*s1 != *s2)
            {
                return *s1 - *s2;
            }
            if (*s1 == '\0')
            {
                return 0;
            }
            s1++;
            s2++;
        }
    }
    return 0;
}

//функция копирования строки
void strcpy_(char *destination, const char *sourse)
{
    while (*sourse)
    {
        *destination = *sourse;
        destination++;
        sourse++;
    }
    *destination = '\0';
}

void replace(char *source, char *w1, char *w2)
{
    size_t w1Size = strlen_(w1);
    size_t w2Size = strlen_(w2);

    char *readPtr = source;
    char *recPtr = stringBuffer;

    while (*readPtr != '\0')
    {
        if (strncmp_(readPtr, w1, w1Size) == 0 &&
            (*(readPtr + w1Size) == ' ' || *(readPtr + w1Size) == '\0') && (readPtr == source || *(readPtr - 1) == ' '))
        {
            char *W2Ptr = w2;
            while (*W2Ptr != '\0')
            {
                *recPtr = *W2Ptr;
                recPtr++;
                W2Ptr++;
            }
            readPtr += w1Size;
        } else
        {
            *recPtr = *readPtr;
            readPtr++;
            recPtr++;
        }

    }
    *recPtr = '\0';

    strcpy_(source, stringBuffer);
}

int isOrdered(char *source)
{
    WordDescriptor wordRes;
    WordDescriptor prevWordRes;
    if (!getWord(source, &prevWordRes))
    {
        return 1;
    }
    source = prevWordRes.end;
    while (getWord(source, &wordRes))
    {
        unsigned long len1 = prevWordRes.end - prevWordRes.begin;
        unsigned long len2 = wordRes.end - wordRes.begin;
        unsigned long min_len = len1;
        if (min_len > len2)
        {
            min_len = len2;
        }
        int res = memcmp(prevWordRes.begin, wordRes.begin, min_len);
        if (res > 0)
        {
            return 0;
        }
        if ((res == 0) && (len1 > len2))
        {
            return 0;
        }
        prevWordRes = wordRes;
        source = wordRes.end;
    }
    return 1;
}

void getBagOfWords(BagOfWords *bag, char *s)
{
    WordDescriptor wordRes;
    int i = 0;
    while (getWord(s, &wordRes))
    {
        bag->words[i++] = wordRes;
        bag->size++;
        s = wordRes.end;
    }
}

void clearBagOfWords(BagOfWords *bag)
{
    bag->size = 0;
}

void printWord(const WordDescriptor *word)
{
    for (char *j = word->begin; j < word->end; j++)
    {
        printf("%c", *j);
    }
    printf("\n");
}

int isPalindrom(WordDescriptor *wordRes)
{
    int is_polyndrom = 1;
    unsigned long len = (*wordRes).end - (*wordRes).begin;
    (*wordRes).end -= sizeof(char);

    for (int i = 0; i < len / 2; i++)
    {
        if (*(*wordRes).begin != *(*wordRes).end)
        {
            is_polyndrom = 0;
            break;
        }
        (*wordRes).begin += sizeof(char);
        (*wordRes).end -= sizeof(char);
    }
    return is_polyndrom;
}

int countPalindroms(char *s)
{
    WordDescriptor wordRes;

    int counter = 0;

    while (getWordByComma(s, &wordRes))
    {
        s = wordRes.end;
        counter += isPalindrom(&wordRes);
    }
    return counter;
}

void getMixedString(char *res, char *s1, char *s2)
{
    WordDescriptor word1, word2;
    bool isW1Found, isW2Found;
    char *beginSearch1 = s1, *beginSearch2 = s2;
    while ((isW1Found = getWord(beginSearch1, &word1)),
            (isW2Found = getWord(beginSearch2, &word2)),
            isW1Found || isW2Found)
    {

        if (isW1Found)
        {
            if (*word1.end == '\0')
            {
                *word1.end = ' ';
            }
            copy(word1.begin, word1.end, res);
            res += word1.end - word1.begin + 1;
            beginSearch1 = word1.end;
        }
        if (isW2Found)
        {
            if (*word2.end == '\0')
            {
                *word2.end = ' ';
            }

            copy(word2.begin, word2.end, res);
            res += word2.end - word2.begin + 1;
            beginSearch2 = word2.end;
        }

    }
    res -= sizeof(char);
    *res = '\0';
}

void stringReverse(char *s)
{
    copy(s, getEndOfString(s), _stringBuffer);

    WordDescriptor wordRes;
    char *end = getEndOfString(_stringBuffer) + sizeof(char);

    while ((end >= _stringBuffer) && getWordReverse(end, _stringBuffer, &wordRes))
    {
        end = wordRes.begin - sizeof(char);

        copy(wordRes.begin, wordRes.end, s);
        s += wordRes.end - wordRes.begin;
        *s = ' ';
        s += sizeof(char);
    }
    s -= sizeof(char);
    *s = '\0';
}

int hasWordLetter(WordDescriptor *word, char letter)
{
    for (char *i = word->begin; i <= word->end; i += sizeof(char))
    {
        if (*i == letter)
        {
            return 1;
        }
    }
    return 0;
}

WordBeforeFirstWordWithAReturnCode getWordBeforeFirstWordWithA(char *source, WordDescriptor *w)
{
    WordDescriptor wordRes;
    WordDescriptor prevWordRes;


    if (!getWord(source, &prevWordRes))
    {
        return EMPTY_STRING;
    }

    if (hasWordLetter(&prevWordRes, 'a') || hasWordLetter(&prevWordRes, 'A'))
    {
        w->begin = prevWordRes.begin;
        w->end = prevWordRes.end;
        return FIRST_WORD_WITH_A;
    }

    source = prevWordRes.end;
    while (getWord(source, &wordRes))
    {

        if (hasWordLetter(&wordRes, 'a') || hasWordLetter(&wordRes, 'A'))
        {
            w->begin = prevWordRes.begin;
            w->end = prevWordRes.end;
            return WORD_FOUND;
        }

        prevWordRes = wordRes;
        source = wordRes.end;
    }
    return NOT_FOUND_A_WORD_WITH_A;
}

void printWordBeforeFirstWordWithA(char *s)
{
    WordDescriptor word;
    WordBeforeFirstWordWithAReturnCode res = getWordBeforeFirstWordWithA(s, &word);

    switch (res)
    {
        case EMPTY_STRING:
            printf("В строке нет слов");
            break;
        case FIRST_WORD_WITH_A:
            printf("Первое слово с ’a’ является первым в строке\n");
            printWord(&word);
            break;
        case WORD_FOUND:
            printf("Имеется слово перед словом с ’a’\n");
            printWord(&word);
        case NOT_FOUND_A_WORD_WITH_A:
            printf("В строке нет слов с ’a’");
            break;
    }
}


void findLastWord(char *s1, char *s2)
{
    clearBagOfWords(&_bag);
    clearBagOfWords(&_bag2);
    getBagOfWords(&_bag, s1);
    getBagOfWords(&_bag2, s2);

    size_t len1 = 0;
    size_t len2 = 0;

    for (int i = _bag.size - 1; i >= 0; i--)
    {
        for (int j = _bag2.size - 1; j >= 0; j--)
        {
            len1 = &_bag.words[i].end - &_bag.words[i].begin;
            len2 = &_bag2.words[j].end - &_bag2.words[j].begin;

            if (len1 != len2)
            {
                continue;
            }

            int res = memcmp(_bag.words[i].begin, _bag2.words[j].begin, len1);

            if (res == 0)
            {
                printWord(&_bag.words[i]);
            }
        }
    }
}

int compareWordDescriptors(const void *wordPtr1, const void *wordPtr2)
{
    WordDescriptor *word1 = (WordDescriptor *) wordPtr1;
    WordDescriptor *word2 = (WordDescriptor *) wordPtr2;

    unsigned long len1 = word1->end - word1->begin;
    unsigned long len2 = word2->end - word2->begin;
    unsigned long min_len = len1;
    if (min_len > len2)
    {
        min_len = len2;
    }

    int res = memcmp(word1->begin, word2->begin, min_len);

    if (res == 0)
    {
        if (len1 != len2)
        {
            res = len1 > len2 ? 1 : -1;
        }
    }
    return res;
}


int hasSameWords(char *s)
{
    clearBagOfWords(&_bag);
    getBagOfWords(&_bag, s);
    qsort(_bag.words, _bag.size, sizeof(WordDescriptor), compareWordDescriptors);

    for (int i = 1; i <= _bag.size; i++)
    {
        int res = compareWordDescriptors(&_bag.words[i - 1], &_bag.words[i]);

        if (res == 0)
        {
            return 1;
        }
    }
    return 0;
}

int compareLetters(const void *charPtr1, const void *charPtr2)
{
    const char *char1 = (const char *) charPtr1;
    const char *char2 = (const char *) charPtr2;

    return *char1 - *char2;
}

int hasWordsWithSameLetters(char *s)
{
    copy(s, getEndOfString(s), _stringBuffer);
    clearBagOfWords(&_bag);
    getBagOfWords(&_bag, _stringBuffer);

    for (int i = 0; i <= _bag.size; i++)
    {
        qsort(_bag.words[i].begin, _bag.words[i].end - _bag.words[i].begin, sizeof(char), compareLetters);
    }

    qsort(_bag.words, _bag.size, sizeof(WordDescriptor), compareWordDescriptors);

    for (int i = 1; i <= _bag.size; i++)
    {
        int res = compareWordDescriptors(&_bag.words[i - 1], &_bag.words[i]);

        if (res == 0)
        {
            return 1;
        }
    }
    return 0;
}

void getStringWithoutEndWords(char *s)
{
    copy(s, getEndOfString(s), _stringBuffer);
    clearBagOfWords(&_bag);
    getBagOfWords(&_bag, _stringBuffer);
    WordDescriptor lastWord = _bag.words[_bag.size - 1];

    for (int i = 0; i < _bag.size - 1; i++)
    {
        WordDescriptor currWord = _bag.words[i];
        int res = compareWordDescriptors(&currWord, &lastWord);

        if (res != 0)
        {
            copy(currWord.begin, currWord.end, s);
            s += currWord.end - currWord.begin;
            *s = ' ';
            s += sizeof(char);
        }
    }
    s -= sizeof(char);
    *s = '\0';
}

int findWordBefore(char *s1, char *s2, char *res)
{
    clearBagOfWords(&_bag);
    clearBagOfWords(&_bag2);
    getBagOfWords(&_bag, s1);
    getBagOfWords(&_bag2, s2);

    int get;
    for (int i = 1; i < _bag.size - 1; i++)
    {
        WordDescriptor lineOneWord = _bag.words[i];
        for (int j = 0; j < _bag2.size - 1; j++)
        {
            WordDescriptor lineTwoWord = _bag2.words[j];
            get = compareWordDescriptors(&lineOneWord, &lineTwoWord);

            if (get == 0)
            {
                WordDescriptor resWord = _bag.words[i - 1];
                copy(resWord.begin, resWord.end, res);
                res += resWord.end - resWord.begin;
                *res = '\0';
                return 1;
            }
        }
    }
    return 0;
}

void deletePalindromes(char *s)
{
    copy(s, getEndOfString(s) + sizeof(char), _stringBuffer);
    clearBagOfWords(&_bag);
    getBagOfWords(&_bag, _stringBuffer);

    for (int i = 0; i < _bag.size; i++)
    {
        WordDescriptor lineOneWord = _bag.words[i];

        int isPal = isPalindrom(&lineOneWord);

        if (!isPal)
        {
            copy(lineOneWord.begin, lineOneWord.end, s);
            s += lineOneWord.end - lineOneWord.begin + 1;
            *s = ' ';
            s += sizeof(char);
        }
    }
    s -= sizeof(char);
    *s = '\0';
}

void appendMissingWords(char *s1, char *s2)
{
    clearBagOfWords(&_bag);
    clearBagOfWords(&_bag2);
    getBagOfWords(&_bag, s1);
    getBagOfWords(&_bag2, s2);

    size_t min_len = 0;
    BagOfWords *maxPtr;
    char *resStr;

    if (_bag.size < _bag2.size)
    {
        min_len = _bag.size;
        maxPtr = &_bag2;
        resStr = s1;
    } else
    {
        min_len = _bag2.size;
        maxPtr = &_bag;
        resStr = s2;
    }

    resStr += strlen_(resStr);
    *resStr = ' ';
    resStr += sizeof(char);

    WordDescriptor word;
    for (int i = min_len; i < maxPtr->size; i++)
    {
        word = maxPtr->words[i];
        copy(word.begin, word.end, resStr);
        resStr += word.end - word.begin + 1;
    }
}

int isStringIncludeLetters(char *s, char *word)
{
    copy(s, getEndOfString(s), _stringBuffer);
    copy(word, getEndOfString(word), _stringBuffer2);

    size_t lenStr = strlen_(_stringBuffer);
    qsort(_stringBuffer, lenStr, sizeof(char), compareLetters);
    size_t lenStr1 = strlen_(_stringBuffer2);
    qsort(_stringBuffer2, lenStr1, sizeof(char), compareLetters);

    int counter = 0;
    char *endStrPtr = _stringBuffer + lenStr;
    char *currChar = _stringBuffer2;
    for (char *i = _stringBuffer; i <= endStrPtr; i += sizeof(char))
    {
        if (*i == *currChar)
        {
            counter++;

            if (counter == lenStr1)
            {
                return 1;
            }
            currChar += sizeof(char);
        }

    }
    return 0;
}






