#ifndef _TRSRE_H_
#define _TRSRE_H_

#include <stdbool.h>
#include <stddef.h>

/*
 * enum trsre_TokenType
 * @description An enum of token types.
 */
typedef enum {
    TRSRE_TOKEN_TYPE_EMPTY = 0,
    TRSRE_TOKEN_TYPE_LITERAL,
    TRSRE_TOKEN_TYPE_ANY,
    TRSRE_TOKEN_TYPE_EOE, // End Of Expression
    TRSRE_TOKEN_TYPE_RANGE,
    TRSRE_TOKEN_TYPE_CHOOSE,
    TRSRE_TOKEN_TYPE_GROUP
} trsre_TokenType;

/*
 * enum trsre_TokenMod
 * @description An enum of token modifiers (expansion modes).
 */
typedef enum {
    TRSRE_TOKEN_MODE_SINGLE       = 0,
    TRSRE_TOKEN_MODE_NOT          = 0x01, // 0b00000001,
    TRSRE_TOKEN_MODE_PLUS         = 0x02, // 0b00000010,
    TRSRE_TOKEN_MODE_STAR         = 0x04, // 0b00000100,
    TRSRE_TOKEN_MODE_QUESTION     = 0x08, // 0b00001000,
    TRSRE_TOKEN_MODE_NOT_PLUS     = 0x03, // 0b00000011,
    TRSRE_TOKEN_MODE_NOT_STAR     = 0x05, // 0b00000101,
    TRSRE_TOKEN_MODE_NOT_QUESTION = 0x09, // 0b00001001 
} trsre_TokenMode;

/*
 * struct trsre_Token
 * @description A string view of token with given type.
 */
typedef struct {
    const char* m_Value;
    size_t m_Length;
    trsre_TokenType m_Type;
    trsre_TokenMode m_Mode;
} trsre_Token;

/*
 * trsre_match_char
 * @param rule - cstr with regex 
 * @param c - char to match 
 * @return length of rule that matches c, negative if c does'n match, 0 if rule or c equals 0
 */
long trsre_match_char(const char* rule, char c);

/*
 * trsre_match_group
 * @param rule - cstr with regex 
 * @param text - cstr with text to match 
 * @param ti - optional ptr to size_t where length of text that matches should be saved
 * @return length of characters of 1st group in rule, negative if text does'n match entire group
 */
long trsre_match_group_ext(const char* rule, const char* text, size_t* ti, bool neg);
long trsre_match_group(const char* rule, const char* text, size_t* ti);

/*
 * trsre_match
 * @param rule - cstr with regex 
 * @param text - cstr with text to match 
 * @return length of text that matches rule 
 */
size_t trsre_match(const char* rule, const char* text);

/*
 * trsre_fing
 * @param rule - cstr with regex 
 * @param text - cstr with text
 * @param len - a pointer where the length of found match should be pasted
 * @return ptr to the first char of found match, or ptr to \0 in text if not found
 */
const char* trsre_find(const char* rule, const char* text, size_t* len);

/*
 * trsre_get_token
 * @param rule - cstr with regex 
 * @return the very first token in rule
 */
trsre_Token trsre_get_token(const char* rule);

#ifdef TRSRE_EXT

/*
 * trsre_token_to_string_ext
 * @param token - a token
 * @param buffer - a char* buffer where result will be saved
 * @param size - max size of buffer
 * @return length of saved string or predicted length of needed buffer if buffer == 0
 */
size_t trsre_token_to_string_ext(trsre_Token token, char* buffer, size_t size);

/*
 * trsre_token_type_to_string_ext
 * @param type - a token type
 * @return a name of type in cstr
 */
const char* trsre_token_type_to_string_ext(trsre_TokenType type);

/*
 * trsre_token_mode_to_string_ext
 * @param type - a token type
 * @return a name of mode in cstr
 */
const char* trsre_token_mode_to_string_ext(trsre_TokenMode mode);

/*
 * trsre_token_type_to_string3_ext
 * @param type - a token type
 * @return a cstr of 4 chars, where 3 are type's name and last one i s always 0 
 */
const char* trsre_token_type_to_string3_ext(trsre_TokenType type);

/*
 * trsre_token_mode_to_string3_ext
 * @param mode - a token mode
 * @return a cstr of 4 chars, where 3 are mode's name and last one i s always 0 
 */
const char* trsre_token_mode_to_string3_ext(trsre_TokenMode mode);

#endif // TRSRE_EXT 

#endif // _TRSRE_H_
