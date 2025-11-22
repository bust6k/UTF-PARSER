# Table of content
- [synopsis](#Synopsys)
- [features](#Features)
- [download](#Download)
- [project structure describe](#Project-structure-describing)
- [API of library](#API)
- [system versioning](#System-versioning)


# Synopsys

**UTF-PARSER** - is a library that provides encode/decode functions that implement some UTF formats (the current version can ensure only UTF-8). The library is written for educational purposes because I wanted to train a bitwise mind to write an operating system. But in the development process, I thought: if I write the parser, why I can't bind together educational and production purposes? From this idea, you are seeing the library that has the name **UTF-PARSER**. The current version of **UTF-PARSER** is *2.1.5.13.1* in dev option, or *2.1.5* in common option. Learn more about system versioning [here](#System-versioning).

# Features
 
- Cross platform code that works on any unix like system and on windows

- Library has own dumper for detailed meaning what happend while decode/ecnode symbol

- Library use colored and detailed output to determine error

- Library has simple and flexibility API

# Download

use the simple command below for cloning latest libary version on your project. have 2 variants how to download:

- via https

``` bash
git clone https://github.com/bust6k/UTF-PARSER.git
```

- via ssh

``` bash
git clone git@github.com:bust6k/UTF-PARSER.git
```


# Project structure describing

```bash
.
├── README.md # the file describes what the parser can do and some other descriptions (the current file)
├── utf_parser.c  # the implementation of encoder/decoder UTF formats
├── utf_parser.h # API for using

```
# API
**API** of **UTF-PARSER** library has simple,flexibility structure to comfortable dumping,and using. Here's 2 main **APU** functions:

- int32_t utf8_decode(signed char* bytes, int* out, bool dump)  - this function decodes bytes stream *bytes*,return its representation in Unicode form and writes in *out* its length. third parametr used for enable dump process.
 If you have hard problem you can enable dumper and see all stages where symbol decoding fails/pass. 
If *bytes* are incorrect, the function in *out* returns -1(INCORRECT_SYMBOL),and, if *bytes* null pointer,the function returns -2(UNKNOWN_THING).
If *bytes* are incorrect,or *bytes* is null,the function returns 1

- int32_t utf8_encode(uint8_t* c, int* out, bool dump) - this function encodes Unicode symbol *c*,return its representation in UTF-8 form and writes in *out* its length. third parametr does same as in utf8_decode function.
If *bytes* are incorrect, the function in *out* returns -1(INCORRECT_SYMBOL),and, if *bytes* null pointer,the function returns -2(UNKNOWN_THING).
If *bytes* are incorrect,or *bytes* is null,the function returns 1


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

