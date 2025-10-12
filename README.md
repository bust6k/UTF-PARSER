# Table of content


- [synopsis](#Synopsys)
- [features](#Features)
- [project structure describe](#Project-structure-describing)
- [engineering approach](#Approach-on-project)
- [system versioning](#System-versioning)
- [plans on a future](#Future-of-the-project)

# Synopsys

**UTF-PARSER** - is a library that provides encode/decode functions that implement some UTF formats (the current version can ensure only UTF-8). The library is written for educational purposes because I wanted to train a bitwise mind to write an operating system. But in the development process, I thought: if I write the parser, why I can't bind together educational and production purposes? From this idea, you are seeing the library that has the name **UTF-PARSER**. The current version of **UTF-PARSER** is *1.0.1.F.1* in dev option, or *1.0.1* in common option. Learn more about system versioning [here](#System-versioning). The current version of the parser can't have unit tests because writing them on decode/encode signatures is very uncomfortable. I've decided to write unit tests at some other time.

# Features
 
- Custom len function to determine a string length

- The decoder and encoder functions have simple structs; the source code of the parser can be read in less than 1 day

- The decoder function defends against invalid UTF-8 bytes; in fault cases, the function writes an error message on stdout and returns

- The encoder functions defend against invalid codepoints; in fault cases, they write an error message on stdout and return, similar to the decoder

-  The parser has minimal dependencies. Once the parser involves unistd and stdint, making **UTF-PARSER** a flexible library.

# Project structure describing

```bash
.
├── include
│   ├── utf_parser.h # API for using
├── README.md # the file describes what the parser can do and some other descriptions (the current file)
├── src
│   ├── utf_parser.c # the implementation of encoder/decoder UTF formats
└── tests
├── utf8_decoder_test.c # currently, tests are not ready for work, but soon I'll link them with an object file, and tests will work
└── utf8_encoder_test.c
```


# Approach on project

- Comfortable API first: Firstly, I tried to make the API comfortable for use. Instead of int, I chose char* because nobody works directly with raw endpoints; all work with byte streams. Our pointer is easier for debugging sessions because you mustn't check big-endian bits. The library provides a comfortable interface for knowing the length of an encoded/decoded symbol.


- Security: the parser checks any byte on invalid sequence;the parser process any edge case she can process;the parser checks the symbol is entry on correct symbol ranges.


- Independence: The library has minimal dependencies; therefore, the parser can be used on any UNIX-like system (and on Windows). The parser only depends on system calls.

# System versioning

The parser has two versioning systems: one necessary to see the development process, middle versions, critical bugs, and more; the other is for learning only the production version of the parser. The second system uses only decimal numbering. Here's a description of both versioning systems:

- The dev versioning system has 5 states that describe something:

1. The major (1st state) version displays how many times a big update has been released that can change root logic. Example: adding multi-threading, cache, and lock-free features in utf8_encode and utf8_decode. The 1st state uses an octal number system.

2. The minor (2nd state) version shows how many medium updates have been released, such as adding new functions, redefining old API, or fixing big bugs. Example: adding multi-threading to the len() function. The 2nd state uses a decimal number system.

3. The patch (3rd state) version indicates how many small updates have been released, like fixing small bugs or adding small helper functions. Example: fixing an error in a unit test. The 3rd state uses a decimal number system.

4. The middle (4th state) versions show the number of middle development versions that may be unstable. Example: a middle version before the last stable release. The 4th state uses a hexadecimal number system. After each major version, the state resets.

5. The critical bugs (5th state) versions show how many times critical bugs have slowed development or caused major issues. Example: deleting all source code without recovery options. The 5th state uses an octal number system. After each major version, the state resets.

- The common versioning system has 3 states:

1. The major (1st state) version shows how many big updates that can change core logic have been released.

2. The minor (2nd state) version indicates medium updates, such as adding new functions or fixing big bugs.

3. The patch (3rd state) version reflects small updates, bug fixes, or small helper functions.

# Future of the project

- Revise tests to a work condition

- Add multi-threading with lock-free algorithms

- Add cache

- Add JIT compilation
