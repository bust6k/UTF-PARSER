/*
Copyright 2025 bust6k

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#include "utf_parser.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#define INCORRECT_SYMBOL -1
#define UNKNOWN_THING -2

// КРОССПЛАТФОРМЕННЫЕ ЦВЕТА
#ifdef _WIN32
#include <windows.h>

void set_console_color(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

#define RED_COLOR set_console_color(FOREGROUND_RED | FOREGROUND_INTENSITY)
#define RESET_COLOR set_console_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE)
#define GREEN_COLOR set_console_color(FOREGROUND_GREEN | FOREGROUND_INTENSITY)
#define CYAN_COLOR set_console_color(FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY)

#else
// Unix/Linux/MacOS
#define RED_COLOR "\e[31m"
#define RESET_COLOR "\e[0m"
#define GREEN_COLOR "\e[32m"
#define CYAN_COLOR "\e[36m"
#define STDOUT 1
#endif

#define DUMP_STAGE(num, desc, bytes, len) \
    if(dump) { \
        printf(CYAN_COLOR "[UTF-8 DECODER-DUMPER]:\e[0m stage " #num ": " desc " "); \
        for(int i = 0; i < len; i++) printf("%02X ", (unsigned char)bytes[i]); \
        printf(GREEN_COLOR "PASS\e[0m\n"); \
        fflush(stdout); \
    }

#define DUMP_FAIL(num, desc, bytes, len) \
    if(dump) { \
        printf(CYAN_COLOR "[UTF-8 DECODER-DUMPER]:\e[0m stage " #num ": " desc " "); \
        for(int i = 0; i < len; i++) printf("%02X ", (unsigned char)bytes[i]); \
        printf(RED_COLOR "FAIL\e[0m\n"); \
        fflush(stdout); \
    }

int8_t utf8_decode_len(int8_t b)
{
    if(b == 0)
    { 
        return UNKNOWN_THING;
    }
    if ((b & 0x80) == 0x00)
    {
        return 1;
    }
    if ((b & 0xE0) == 0xC0)
    {
        return 2;
    }
    if ((b & 0xF0) == 0xE0)
    {
        return 3;
    }
    if ((b & 0xF8) == 0xF0)
    {
        return 4;
    }
    return INCORRECT_SYMBOL;
}

int32_t utf8_decode(signed char* bytes, int* out, bool dump)
{
        if (bytes == NULL)
    {
        if(dump)
        {
            DUMP_FAIL(0, "check character on null sequences: NULL pointer", bytes, 0)
        }
        else
        {
            printf(RED_COLOR"[UTF-8 DECODER-ERROR]:\e[0m given character has null\n");
        }
        return 0;
    }
    
    if (*bytes == 0x00)
    {
        if(dump)
        {
            DUMP_FAIL(0, "check character on null sequences:", bytes, 4)
        }
        else
        {
            printf(RED_COLOR"[UTF-8 DECODER-ERROR]:\e[0m given character has null\n");
        }
        return 0;
    }
    
    if (*(bytes + 1) == 0x00)
    {
        if(dump)
        {
            DUMP_FAIL(0, "check character on null sequences:", bytes, 4)
        }
        else
        {
            printf(RED_COLOR"[UTF-8 DECODER-ERROR]:\e[0m given character has null\n");
        }
        return 0;
    }
    
    if (*(bytes + 2) == 0x00)
    {
        if(dump)
        {
            DUMP_FAIL(0, "check character on null sequences:", bytes, 4)
        }
        else
        {
            printf(RED_COLOR"[UTF-8 DECODER-ERROR]:\e[0m given character has null\n");
        }
        return 0;
    }
    
    if (*(bytes + 3) == 0x00)
    {
        if(dump)
        {
            DUMP_FAIL(0, "check character on null sequences:", bytes, 4)
        }
        else
        {
            printf(RED_COLOR"[UTF-8 DECODER-ERROR]:\e[0m given character has null\n");
        }
        return 0;
    }
    
    DUMP_STAGE(0, "check character on null sequences:", bytes, 4)

    int8_t l = utf8_decode_len(*bytes);
   
    DUMP_STAGE(1, "determine length of", bytes, 4)
    switch (l)
    {
        case INCORRECT_SYMBOL:
        {
            if(!dump)
            {
                *out = INCORRECT_SYMBOL;
                printf(RED_COLOR"[UTF-8 DECODER-ERROR]:\e[0m bytes ");
                for(int i = 0; i < 4; i++)
                { 
                    if(bytes[i] != 0xFF)
                    { 
                        printf("%02X ", (unsigned char)bytes[i]);
                    }
                }
                printf("are incorrect\n"); 
            }
            else
            {
                DUMP_FAIL(2, "check if determined length of", bytes, 4)
            }
            return 1;
        }

        case 1:
        {
            *out = 1;
            goto decode_final_stage;
        }
        case 2:
        {
            if ((*(bytes + 1) & 0xC0) != 0x80 || (*bytes & 0xE0) != 0xC0) 
            {
                DUMP_FAIL(3, "check if character", bytes, 2)
                
                *out = INCORRECT_SYMBOL;
                if(!dump)
                {
                    printf(RED_COLOR"[UTF-8 DECODER-ERROR]:\e[0m bytes ");
                    for(int i = 0; i < 2; i++)
                    {
                        printf("%02X ", (unsigned char)bytes[i]);
                    }
                    printf("are incorrect\n");
                }
                return 1;
            }

            DUMP_STAGE(3, "check if character", bytes, 2)
            
            *out = 2;
            goto decode_final_stage;
        }
        case 3:
        {
            if ((*(bytes + 1) & 0xC0) != 0x80 || (*(bytes + 2) & 0xC0) != 0x80 || (*bytes) & 0xF0 != 0xE0) 
            {
                DUMP_FAIL(3, "check if character", bytes, 3)
                
                *out = INCORRECT_SYMBOL;
                if(!dump)
                {
                    printf(RED_COLOR"[UTF-8 DECODER-ERROR]:\e[0m bytes ");
                    for(int i = 0; i < 3; i++)
                    {
                        printf("%02X ", (unsigned char)bytes[i]);
                    }
                    printf("are incorrect\n");
                }
                return 1;
            }

            DUMP_STAGE(3, "check if character", bytes, 3)
            
            *out = 3;
            goto decode_final_stage;
        }
        case 4:
        {
            if ((*(bytes + 1) & 0xC0) != 0x80 || (*(bytes + 2) & 0xC0) != 0x80 || (*(bytes + 3) & 0xC0) != 0x80 || (*bytes) & 0xF8 != 0xF0) 
            {
                DUMP_FAIL(3, "check if character", bytes, 4)
                
                *out = INCORRECT_SYMBOL;
                if(!dump)
                {
                    printf(RED_COLOR"[UTF-8 DECODER-ERROR]:\e[0m bytes ");
                    for(int i = 0; i < 4; i++)
                    {
                        printf("%02X ", (unsigned char)bytes[i]);
                    }
                    printf("are incorrect\n");
                }
                return 1;
            }

            DUMP_STAGE(3, "check if character", bytes, 4)
            
            *out = 4;
            goto decode_final_stage;
        }
        default:
        {
            *out = UNKNOWN_THING;
            printf(RED_COLOR"[UTF-8 DECODER-ERROR]:\e[0m given character has null\n");
            return 0;
        }
    }

decode_final_stage:
    DUMP_STAGE(4, "decode character", bytes, *out)
    
  
    switch(l)
    {
        case 1:
            return *bytes;
        case 2:
            return ((*bytes & 0x1F) << 6) | (*(bytes + 1) & 0x3F);
        case 3:
            return ((*bytes & 0x0F) << 12) | ((*(bytes + 1) & 0x3F) << 6) | (*(bytes + 2) & 0x3F);
        case 4:
            return ((*bytes & 0x07) << 18) | ((*(bytes + 1) & 0x3F) << 12) | ((*(bytes + 2) & 0x3F) << 6) | *(bytes + 3) & 0x3F;
    }

decoding_null_ptr_err:
  if(dump)
  {     
DUMP_STAGE(0, "check character on null sequences:", bytes, 4)
 }
else
{
    printf(RED_COLOR"[UTF-8 DECODER-ERROR]:\e[0m given character has null\n");
    return 0;
}
}

int8_t utf8_encode_len(uint32_t cp)
{
    if(cp == NULL)
    {
        return UNKNOWN_THING;
    }
    if (cp <= 0x7F)
    {
        return 1;
    }
    if (cp <= 0x7FF)
    {
        return 2;
    }
    if (cp <= 0xFFFF)
    {
        return 3;
    }
    if (cp <= 0x10FFFF)
    {
        return 4;
    }
    return INCORRECT_SYMBOL;
}

int32_t utf8_encode(uint8_t* c, int* out, bool dump)
{
    if (c == NULL) 
    {
        goto encoding_null_ptr_err;
    }

    if (*c == 0x00)
    {
        goto encoding_null_ptr_err;
    }

    if (*(c + 1) == 0x00)
    {
        goto encoding_null_ptr_err;
    }

    if (*(c + 2) == 0x00)
    {
        goto encoding_null_ptr_err;
    }

    if (*(c + 3) == 0x00)
    {
        goto encoding_null_ptr_err;
    }

    DUMP_STAGE(0, "check character on null sequences:", c, 4)

    int32_t char_true = (*c << 24) | (*(c + 1) << 16) | (*(c + 2) << 8) | (*(c + 3));

    DUMP_STAGE(1, "create 32-bit code point from bytes:", c, 4)

    int8_t l = utf8_encode_len(char_true);
    
    DUMP_STAGE(2, "determine encoding length for code point:", c, 4)
    
    switch(l)
    {
        case INCORRECT_SYMBOL:
        {
            if(!dump)
            {
                *out = INCORRECT_SYMBOL;
                printf(RED_COLOR"[UTF-8 ENCODER-ERROR]:\e[0m bytes ");
                for(int i = 0; i < 4; i++) 
                { 
                    printf("%02X ", (unsigned char)c[i]);
                }
                printf("are incorrect\n");
            }
            else
            {
                DUMP_FAIL(3, "check if code point is valid:", c, 4)
            }
            return 1;
        }
        case 1:
        {
            DUMP_STAGE(3, "encode as 1-byte UTF-8 sequence:", c, 1)
            *out = 1;
            return char_true & 0x7F;
        }
        case 2:
        {
            DUMP_STAGE(3, "encode as 2-byte UTF-8 sequence:", c, 2)
            int32_t data1 = *c | 0xC0;
            int32_t data2 = *(c + 1) | 0x80;
            *out = 2;
            return (data1 << 8) | data2;
        }
        case 3:
        {
            DUMP_STAGE(3, "encode as 3-byte UTF-8 sequence:", c, 3)
            int32_t data1 = *c | 0xE0;
            int32_t data2 = *(c + 1) | 0x80;
            int32_t data3 = *(c + 2) | 0x80;
            *out = 3;
            return (data1 << 16) | (data2 << 8) | data3;
        }
        case 4:
        {
            DUMP_STAGE(3, "encode as 4-byte UTF-8 sequence:", c, 4)
            int32_t data1 = *c | 0xF0;
            int32_t data2 = *(c + 1) | 0x80;
            int32_t data3 = *(c + 2) | 0x80;
            int32_t data4 = *(c + 3) | 0x80;
            *out = 4;
            return (data1 << 24) | (data2 << 16) | (data3 << 8) | data4;
        }
        default:
        {
            *out = UNKNOWN_THING;
            printf(RED_COLOR"[UTF-8 ENCODER-ERROR]:\e[0m given character has null\n");
            return 1;
        }
    }

encoding_null_ptr_err:
    printf(RED_COLOR"[UTF-8 ENCODER-ERROR]:\e[0m given character has null\n");
    return 1;
}

