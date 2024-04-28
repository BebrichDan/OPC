#ifndef INC_STRING__H
#define INC_STRING__H

# include <stdint.h>

//возвращает полную длину строки
size_t strlen_(const char *s);

//возвращает указатель на первый элемент с кодом ch,
//расположенным на ленте памяти между адресами begin и end не включая end
char *find(char *begin, char *end, int ch);

//возвращает указатель на первый символ, отличный от пробельных
//расположенный на ленте памяти, начиная с begin и заканчивая ноль-символом,
//eсли символ не найден, возвращается адрес первого ноль-символа
char *findNonSpace(char *begin);

//возвращает указатель на первый пробельный символ, расположенный
//на ленте памяти начиная с адреса begin или на первый ноль-символ
char *findSpace(char *begin);

//возвращает указатель на первый справа символ, отличный от пробельных,
//расположенный на ленте памяти, начиная с rbegin (последний символ
//строки, за которым следует ноль-символ) и заканчивая rend (адрес символа перед началом строки),
//если символ не найден, возвращается адреc rend
char *findNonSpaceReverse(char *rbegin, const char *rend);

//возвращает указатель на первый пробельный символ справа, расположенный на
//ленте памяти, начиная с rbegin и заканчивая rend. Если символ не найден,
//возвращается адрес rend
char *findSpaceReverse(char *rbegin, const char *rend);

//функция возвращает отрицательное значение, если lhs располагается до rhs
//в лексикографическом порядке (как в словаре), значение 0, если
//lhs и rhs равны, иначе – положительное значение.
int strcmp(const char *lhs, const char *rhs);

//записывает по адресу beginDestination фрагмент памяти,
//начиная с адреса beginSource до endSource. возвращает
//указатель на следующий свободный фрагмент памяти в destination
char *copy(const char *beginSource, const char *endSource, char *beginDestination);

//записывает по адресу beginDestination элементы из фрагмента памяти
//начиная с beginSource заканчивая endSource, удовлетворяющие функции-предикату f.
//функция возвращает указатель на следующий свободный для записи фрагмент в памяти
char *copyIf(char *beginSource, const char *endSource, char *beginDestination, int (*f)(int));

//записывает по адресу beginDestination элементы из фрагмента памяти начиная
//с rbeginSource заканчивая rendSource, удовлетворяющие функции-предикату f.
//функция возвращает значение beginDestination по окончанию работы функции.
char *copyIfReverse(char *rbeginSource, const char *rendSource, char *beginDestination, int (*f)(int));

//------------------------------------------------------------------------------------------------------//
#define MAX_STRING_SIZE 200
#define MAX_N_WORDS_IN_STRING 200


typedef struct {
    char *begin; // позиция начала слова
    char *end; // позиция первого символа, после последнего символа слова
} WordDescriptor;

typedef struct BagOfWords {
    WordDescriptor words[MAX_N_WORDS_IN_STRING];
    size_t size;
} BagOfWords;

typedef enum WordBeforeFirstWordWithAReturnCode {
    FIRST_WORD_WITH_A,
    NOT_FOUND_A_WORD_WITH_A,
    WORD_FOUND,
    EMPTY_STRING
} WordBeforeFirstWordWithAReturnCode;

//удаляет из строки все пробельные символы,
void removeNonLetters(char *s);

//возвращает конец строки (указатель на ноль-символ)
char *getEndOfString(char *s);

//дает информацию о том, где именно произошла ошибка
void assertString(const char *expected, char *got, char const *fileName, char const *funcName, int line);

//преобразовывает строку, оставляя только один символ в каждой
//последовательности подряд идущих одинаковых символов
void removeAdjacentEqualLetters(char *s);

//сокращает количество пробелов между
// словами данного предложения до одного
void removeExtraSpaces(char *s);

//записывает в word начало и конец слова
int getWord(char *beginSearch, WordDescriptor *word);

//преобразовает строку таким образом, чтобы цифры
//каждого слова были перенесены в конец слова без
//изменения порядка следования их в слове, а буквы – в начало.
void digitsToEnd(char *s);

//функция для считывания слова с конца строки
bool getWordReverse(char *rbegin, char *rend, WordDescriptor *word);

//преобразовывает строку, заменяя каждую цифру соответствующим ей числом пробелов
char *numberEqualToNumberSpaces(char *s);

//функция для сравнения двух строк на указанное количество символов
int strncmp_(const char *s1, const char *s2, size_t n);

//функция копирования строки
void strcpy_(char *destination, const char *sourse);

//заменяет все вхождения слова w1 на слово w2
void replace(char *source, char *w1, char *w2);

int isOrdered(char *source);

void getBagOfWords(BagOfWords *bag, char *s);

void printBagOfWordsReverse(BagOfWords *bag);

void printWord(const WordDescriptor *word);

void clearBagOfWords(BagOfWords *bag);

int countPalindroms(char *s);

void getMixedString(char *res, char *s1, char *s2);

void stringReverse(char *s);

void printWordBeforeFirstWordWithA(char *s);

WordBeforeFirstWordWithAReturnCode getWordBeforeFirstWordWithA(char *source, WordDescriptor *w);

void assertString(const char *expected, char *got, char const *fileName, char const *funcName, int line);

void findLastWord(char *s1, char *s2);

int hasSameWords(char *s);

int hasWordsWithSameLetters(char *s);

void getStringWithoutEndWords(char *s);

int findWordBefore(char *s1, char *s2, char *res);

void deletePalindromes(char *s);

void appendMissingWords(char *s1, char *s2);

int isStringIncludeLetters(char *s, char *word);

#endif //INC_STRING__H
