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


#include "../include/utf_parser.h"
#include<unistd.h>
#include <stdint.h>
#include<stdio.h>


#define UNCORRECT_SYMBOL -1
#define UNKNOWN_THING -2
#define STDOUT 1

int len(const char* s)
{
int l = 0;

while(*s != '\0')
{
++l;
*s++;
}

int l_cp = l;

return l;
}


int8_t utf8_decode_len(int8_t b)
{
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
    return UNCORRECT_SYMBOL;
}


int32_t utf8_decode(int8_t* bytes, int* out)
{
    int8_t l = utf8_decode_len(*bytes);
    
    switch (l)
    {
        case UNCORRECT_SYMBOL:
        {

        *out = UNCORRECT_SYMBOL;
        
        const char* msg = "[UTF-8 DECODER]: do you sure the symbol is correct? \n";
        
        write(STDOUT, msg, len(msg));
        
        return 0;
        }

        case 1:
        {
            *out = 1;
        
            return *bytes;
        }
        case 2:
        {

            if ((*(bytes + 1) & 0xC0) != 0x80 || (*bytes & 0xE0) != 0xC0) 
            {
             *out = UNCORRECT_SYMBOL;
            const char* msg = "[UTF-8 DECODER]: do you sure the symbol is correct? \n";
            write(STDOUT, msg, len(msg));
            return 0;
            }

            *out = 2;

            return ((*bytes & 0x1F) << 6) | (*(bytes + 1) & 0x3F);
        }
        case 3:
        {
            if ((*(bytes + 1) & 0xC0) != 0x80 || (*(bytes + 2) & 0xC0) != 0x80 || ((*bytes) & 0xF0) != 0xE0) 
            {

            *out = UNCORRECT_SYMBOL;

            const char* msg = "[UTF-8 DECODER]: do you sure the symbol is correct? \n";

            write(STDOUT, msg, len(msg));

            return 0;
            }
            *out = 3;

            return ((*bytes & 0x0F) << 12) | ((*(bytes + 1) & 0x3F) << 6) | (*(bytes + 2) & 0x3F);
        }
    

        case 4:
        {
            if ((*(bytes + 1) & 0xC0) != 0x80 || (*(bytes + 2) & 0xC0) != 0x80 || (*(bytes + 3) & 0xC0) != 0x80 || ((*bytes) & 0xF8) != 0xF0) 
            {
            *out = UNCORRECT_SYMBOL;

            const char* msg = "[UTF-8 DECODER]: do you sure the symbol is correct? \n";

            write(STDOUT, msg, len(msg));

            return 0;

            }

            *out = 4;

            return ((*bytes & 0x07) << 18) | ((*(bytes + 1) & 0x3F )<< 12) | ((*(bytes + 2) & 0x3F) << 6) | *(bytes + 3) & 0x3F;
        }
        default:
        {
            *out = UNKNOWN_THING;

            const char* msg = "[UTF-8 DECODER]: do you sure the symbol is symbol? \n";

            write(STDOUT, msg, len(msg));

            return 0;
        }
    }
}



int8_t utf8_encode_len(uint32_t cp)
{
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
    return UNCORRECT_SYMBOL;
}





int32_t utf8_encode(uint8_t* c,int* out)
{
    //if your terminal automiacly encode a symbols,but you want testing the encode function,then  uncomment the lines(exclude current line) and put on first parametr of utf8_encode_len fl(manual for users:))
    /*
    int f =0;
    int *o = &f;

    int32_t fl = utf8_decode(c,o);
    
*/
    int32_t char_true = (*c << 24) | (*(c + 1 ) << 16) | (*(c + 2 ) << 8) | (*(c + 3 ));

    int8_t l = utf8_encode_len(char_true);
  
    switch(l)
    {
        case UNCORRECT_SYMBOL:
        {
        *out = UNCORRECT_SYMBOL;

         const char* msg = "[UTF-8 ECNODER]: do you sure the symbol is correct? \n";

        write(STDOUT, msg, len(msg));

        return 0;
        }
        case 1:
        {

            *out = 1;

            return char_true &  0x7F;
        }
        case 2:
        {
        int32_t data1 = *c | 0xC0;

        int32_t data2 = *(c + 1) | 0x80;

        *out = 2;

      return  (data1 << 8) | data2;
        }

        case 3:
        {
        int32_t data1 = *c | 0xE0;

        int32_t data2 = *(c + 1) | 0x80;

        int32_t data3 = *(c + 2) | 0x80;

        *out = 3;

      return  (data1 << 16) | (data2 << 8) | data3;
        }
        case 4:
        {
        int32_t data1 = *c | 0xF0;

        int32_t data2 = *(c + 1) | 0x80;

        int32_t data3 = *(c + 2) | 0x80;

        int32_t data4 = *(c + 3) | 0x80;

        *out = 4;

      return  (data1 << 24) | (data2 << 16) | (data3 << 8) | data4;
        }
            
        default:
        {
         *out = UNKNOWN_THING;

         const char* msg = "[UTF-8 ECNODER]: do you sure the symbol is symbol \n?";

        write(STDOUT, msg, len(msg));

        return 0;
        }
            
    }
}



int main()
{
printf("enter Unicode point \n");
unsigned char buf[10];

int r = read(0,buf,10);

buf[r] = '\0';
printf(buf);
int out = 0;
uintutf8_encode(buf,&out);
printf("the UTF-8 symbol:%s,  him len: %d \n",buf,out);


printf("enter UTF-8  symbol  \n");
signed char buf1[20];

int r1 = read(0,buf,20);

buf1[r1] = '\0';

int out1 = 0;
utf8_decode(buf1,&out);
printf("the Unicode point:%s, t him len: %d \n",buf1,out1);
}
