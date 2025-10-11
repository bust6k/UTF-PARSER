#include "../include/utf_parser.h"
#include <stdio.h>
#include <string.h>
#include<stdlib.h>
#include<unistd.h>

#define TEST_CASE_SIZE 4


// it's functions that i've tried write,but logic is very harder,  and i resolve stay the functions in the current condition while i don't publish the UTF_PARSER on the github

/*
int test_common_case()
 {
    int8_t* v1 = "\x57";
    int8_t* v2 = "\xCE\x92";
    int8_t* v3 = "\xEC\x9C\x84";
    int8_t* v4 = "\xF0\x90\x8D\x85";

    int8_t* expected_values[] = {v1, v2, v3, v4}
    ;\
    int32_t test_codepoints[] = {0x57, 0x392, 0xC704, 0x10345};
    int expected_lengths[] = {1, 2, 3, 4};

    for(int i = 0; i < TEST_CASE_SIZE; i++) {
        int out_len = 0;
        int32_t res = utf8_encode(test_codepoints[i], &out_len);
        
        if(res != expected_values[i]) 
        {
            printf("[UTF-8-ENCODE-UNIT-TESTER-TEST-#1]: expected: 0x%X but got: 0x%X \n \n", 
                   expected_codepoints[i], res);
            return 0;
        }
        
        if(out_len != expected_lengths[i]) 
        {
            printf("[UTF8-ENCODE-UNIT-TESTER-TEST-#1]: expected length: %d but got: %d \n \n",
                   expected_lengths[i], out_len);
            return 0;
        }
        
    }
return 1;
}

int test_edge_cases() 
{
int8_t* v1 = "\x7F";          
int8_t* v2 = "\xC2\x80";      
int8_t* v3 = "\xDF\xBF";      
int8_t* v4 = "\xE0\xA0\x80";  

    int8_t* expected_values[] = {v1, v2, v3, v4};
    int32_t test_codepoints[] = {0x7F, 0x80, 0x7FF, 0x800};
    int expected_lens[] = {1, 2, 2, 3};
    
    for(int i = 0; i < TEST_CASE_SIZE; i++) {
        int len = 0;
        int32_t res = utf8_encode(test_values[i], &len);
        
        if(res != expected_values[i]) 
        {
            printf("[UTF-8-ENCODE-UNIT-TESTER-TEST-#2]: exepted: 0x%X but got: 0x%X \n \n", expected[i],res);
            return 0;
        }
    
          if(len != expected_lens[i])
        {
            printf("[UTF8-ENCODE-UNIT-TESTER-TEST-#1]: expected length: %d but got: %d \n \n",
                   expected_lengths[i], out_len);
            return 0;
        }
    }
return 1;
}
*/

int main() {
    printf("Running UTF-8 encoder tests...\n \n");



    // the very simple unit tests. i promise, in the future you see backend-like style testing:) just, for now write tests with harder logic,harder than encoder is fool

    char* t_v1 = "W";
    char* t_v2 = "Β";
    char* t_v3 = "위";
    char*t_v4 =  "𐍅";

    int32_t e_v1 = 0x57;
    int32_t e_v2 = 0xCE92;
    int32_t e_v3 = 0xEC9C84;
    int32_t e_v4 = 0xF0908D85;

    fflush(stdout);
    int out_1 = 0; 
    int32_t r_v1 = utf8_encode(t_v1,&out_1);

        
    if(r_v1 != e_v1)
    {
        printf("[UTF8-ENCODE-UNIT-TESTER:TEST-#1]: expected: 0x%X but gotten: 0x%X \n",e_v1,r_v1);
        return 1;
    }

    if(out_1 != 1)
    {
        printf("[UTF8-ENCODE-UNIT-TESTER:TEST-#1]: expected: len 1  but gotten: %d \n",out_1);
        return 1;
    }
int out_2 = 0; 
    int32_t r_v2 = utf8_encode(t_v2,&out_2);

    if(r_v2 != e_v2)
    {
        printf("[UTF8-ENCODE-UNIT-TESTER:TEST-#2]: expected: %d but gotten: %d \n",e_v2,r_v2);
        return 1;
    }


    if(out_2 != 2)
    {
        printf("[UTF8-ENCODE-UNIT-TESTER:TEST-#1]: expected: len 2  but gotten: %d \n",out_2);
        return 1;
    }

    int out_3 = 0; 
    int32_t r_v3 = utf8_encode(t_v3,&out_3);

    if(r_v3 != e_v3)
    {
        printf("[UTF8-ENCODE-UNIT-TESTER:TEST-#3]: expected: %d but gotten: %d \n",e_v3,r_v3);
        return 1;
    }


    if(out_3 != 3)
    {
        printf("[UTF8-ENCODE-UNIT-TESTER:TEST-#1]: expected: len 3  but gotten: %d \n",out_3);
        return 1;
    }

    int out_4 = 0; 
    int32_t r_v4 = utf8_encode(t_v4,&out_4);

    if(r_v4 != e_v4)
    {
        printf("[UTF8-ENCODE-UNIT-TESTER:TEST-#4]: expected: %d but gotten: %d \n",e_v4,r_v4);
        return 1;
    }


    if(out_4 != 4)
    {
        printf("[UTF8-ENCODE-UNIT-TESTER:TEST-#1]: expected: len 1  but gotten: %d \n",out_4);
        return 1;
    }


    printf("[UTF8-ENCODE-UNIT-TESTER]: all tests has been passed");
}
