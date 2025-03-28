#include <string>

#define CORE_MAJOR_VERSION 0
#define CORE_MINOR_VERSION 0
#define CORE_PATCH_VERSION 1

#define STR(s) #s

#define VERSION_CAT(a, b, c) STR(a) "." STR(b) "." STR(c)
#define CORE_VERSION VERSION_CAT(CORE_MAJOR_VERSION, CORE_MINOR_VERSION, CORE_PATCH_VERSION)

std::string lib_version = "core version: " CORE_VERSION "; build data: " __TIME__ ", " __DATE__;
const char* COREVERSION = CORE_VERSION;
const char* BUILDDATE = __TIME__ ", " __DATE__;
const char* COPYRIGHT = "All Rights Reserved.";
