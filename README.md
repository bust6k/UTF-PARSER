
# Table of content

- [synopsis](#Synopsys)
- [features](#Features)
- [examples decoding/encoding](#Examples)
- [project structure describe](#Project structure describing)
- [engeenering approach](#Approach on project)
- [system versioning](#Sytem versioning)
- [plans on a future](#Furture of the project)


# Synopsys

**UTF-PARSER** - is a libary that provides encode/decode functions that implements some UTF formats(the current version can ensure only UTF-8). the libary was wrote in educaion purpose,because i've wanted   training a bitwise mind  to write an operating system. But in the development process i've thought: if  i'll write the parser binds together educaional and production puproses?  from the idea, you are seeing the libary that have name **UTF-PARSER**.  Current version of **UTF-PARSER** is *1.0.0.F.1* in dev option, or *1.0.0* on common option. learn more about system versioning you can on [system versioning](#Sytem versioning). current version of the parser can't have unit tests because write they on decode/encode signature it's very uncomfortable. i've decided write an unit tests in some other time.

# Features

- custom len function to determine a string len

- the decoder and encoder  functions have simple struct, the src code of the parser can be read lesser than 1 day 

- the decoder function have defend from an invalid UTF-8 bytes, in fault case,the function writes on stdout error message and returns.

- the encoder functions have defend from an invalid codepoint. in fault case,the function writes on stdout error message and returns,like as decoder

- the parser have minimal addictions. Once, the parser involve in the src code is unistd and stdint. Therefore, **UTF-PARSER** is flexbility libary.

# Project structure describing

```bash
.
├── include
│   ├── utf_parser.h # API for using
│   └── utf_parser.o
├── README.md # the file describes what the parser can and some other descriptions(the current file)
├── src
│   ├── utf_parser.c # the implentation of encoder/decoder UTF formats
│   └── utf_parser.o
└── tests
    ├── utf8_decoder_test.c # now tests don't ready for work, but soon i'll link them with an object file and tests will work
    └── utf8_encoder_test.c

```


# Approach on project
 - comfortable API first: firstly, i've tried make the API comfortable for using. instead int i've choosen char* because nobody works with raw endpoint,all works with byte stream. Out pointer easyer debuging sessions,because you mustn't check big endian bits, the libary give comfortable interfave for knowing len of encode/decode symbol

 - indepence:  the libary have minimal addictions, therefore the parser can use on any UNIX-like system(and on windows). the parser addicts only system calls

 # Sytem versioning

 the parser have two versioning systems: first nesscary when you want see development process, middle versions,critical bugs and some more fisrt versioning system have some number systems. second system versioning nesscary when you want learn only production version of parser. the second system have only decimal number system this is describe of both versioning systems:

 - dev versioning system have 5 states that describes something.

1. the major(1 state) version displays  what quantity times relised big update that can edit root logic. example: add multi thread,cache and lock free on utf8_encode and utf8_decode functions. the 1 state have octemal number system
2. the minor(2 state) version displays what quantity times relised  medium updates that can add new functions, redefine old API,or fix big bugs. example: add multi thread on len() function. the 2 state have decimal number system
3. the patch(3 state) version  displays what quantity times relised  small  updates that can edit small bugs,or add small helper functions.. example: fix error on an unit test. the 3 state have decimal number system
4. the middle(4 state) versions displays what quantity times in development process been middle versions of the proggram,that can be unstable. example:  been A middle versions before publish last stable version. the 4 state have hexadecimal  number system. after each major version the state reseting
5. the critical bugs(5 state) versions displays what quantity times in development process been  critical bugs that slower development process on many time,or just big miss.example: delete all source code without recovery opportunity.the 5 state have octemal system versioning. after each major version the state reseting

 - common versioning system have 3 states that describes something. 

 1. the major(1 state) version displays  what quantity times relised big update that can edit root logic. example: add multi thread,cache and lock free on utf8_encode and utf8_decode functions. 
 2. the minor(2 state) version displays what quantity times relised  medium updates that can add new functions, redefine old API,or fix big bugs. example: add multi thread on len() function.
 3. the patch(3 state) version  displays what quantity times relised  small  updates that can edit small bugs,or add small helper functions.. example: fix error on an unit test.



# Furture of the project

- revise tests to work condition

- add multi threading with lock free algoritms

- add cache

- add jit compilation