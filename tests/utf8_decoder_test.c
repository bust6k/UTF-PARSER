#include "../include/utf_parser.h"
#include <stdio.h>
#include <string.h>
#include<stdlib.h>

#define TEST_CASE_SIZE 4

// don't amazing why the decoder test is normal but in parralel the encoder test looks like  poop. Just, the decoder have simpler logic for testing therefore decoder tests is normal

int test_common_case() {
    uint8_t test1[] = {0x57};
    uint8_t test2[] = {0xCE, 0x92};
    uint8_t test3[] = {0xEC, 0x9C, 0x84};
    uint8_t test4[] = {0xF0, 0x90, 0x8D, 0x85};
    
    uint8_t* test_values[] = {test1, test2, test3, test4};
    uint32_t expected_codepoints[] = {0x57, 0x392, 0xC704, 0x10345};
    int expected_lengths[] = {1, 2, 3, 4};

    for(int i = 0; i < TEST_CASE_SIZE; i++) {
        int out_len = 0;
        uint32_t res = utf8_decode(test_values[i], &out_len);
        
        if(res != expected_codepoints[i]) 
        {
            printf("[UTF-8-DECODE-UNIT-TESTER-TEST-#1]: expected: 0x%X but got: 0x%X \n \n", 
                   expected_codepoints[i], res);
            return 0;
        }
        
        if(out_len != expected_lengths[i]) 
        {
            printf("[UTF8-DECODE-UNIT-TESTER-TEST-#1]: expected length: %d but got: %d \n \n",
                   expected_lengths[i], out_len);
            return 0;
        }
        
    }
return 1;
}

int test_edge_cases() {
    uint8_t max_1byte[] = {0x7F};
    uint8_t first_2byte[] = {0xC2, 0x80};
    uint8_t last_2byte[] = {0xDF, 0xBF};
    uint8_t first_3byte[] = {0xE0, 0xA0, 0x80};
    
    uint8_t* edge_tests[] = {max_1byte, first_2byte, last_2byte, first_3byte};
    uint32_t expected[] = {0x7F, 0x80, 0x7FF, 0x800};
    int expected_lens[] = {1, 2, 2, 3};
    
    for(int i = 0; i < TEST_CASE_SIZE; i++) {
        int len = 0;
        uint32_t res = utf8_decode(edge_tests[i], &len);
        
        if(res != expected[i]) 
        {
            printf("[UTF-8-DECODE-UNIT-TESTER-TEST-#2]: exepted: 0x%X but got: 0x%X \n \n", expected[i],res);
            return 0;
        }
  
    }
return 1;
}

int main() {
    printf("Running UTF-8 decoder tests...\n \n");

   

 int t1 =  test_common_case();
 int t2 = test_edge_cases();

     if(t1 + t2 == 2)
     {    
printf("All tests has been passed\n");
     } 
   return 0;
}
