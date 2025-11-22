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


#ifndef UTF_PARSER_H
#define UTF_PARSER_H

#include <stdint.h>
#include<stdbool.h>

#define INCORRECT_SYMBOL -1
#define UNKNOWN_THING -2
// the len functions are helper and for internally use, but if you want you can use their for your purposes

int len(const char* s);
int8_t utf8_decode_len(int8_t b);
int8_t utf8_encode_len(uint32_t cp);

// it's main API.

int32_t utf8_decode(int8_t* bytes, int* out,bool dump);
int32_t utf8_encode(uint8_t* c, int* out,bool dump);

#endif // UTF_PARSER_H
