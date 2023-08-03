#pragma once
#include "util.h"
#include <cstdint>

struct StringTableEntry {
    char* value;
    int hash;
};

struct StringTable {
    char* name;
    int columnCount;
    int rowCount;
    StringTableEntry* values;
};

namespace String {

IW4_FUNCTION(Format, char*, (const char* format, ...), 0x5C1EE0);

IW4_FUNCTION(GetString, uint32_t, (const char* str, unsigned int user), 0x57A360);

IW4_FUNCTION(Parse, void, (const char** p, char* out, int len), 0x5A22F0);

IW4_FUNCTION(CleanString, char *, (char *string), 0x5C1E50);

IW4_FUNCTION(ConvertToString, const char *, (unsigned int stringValue), 0x5799B0);

IW4_FUNCTION(LocalizedStringIndex, int, (const char *string), 0x54D4D0);

IW4_FUNCTION(FindConfigstringIndex, int, (const char *name, int start, int max, int create, const char *errormsg), 0x54D400);

IW4_FUNCTION(FindString, unsigned int, (const char *string), 0x579DB0);

IW4_FUNCTION(Sprintf, int, (char *dest, int size, const char *fmt, ...), 0x5C1EB0);

IW4_FUNCTION(RemoveRefToString, void, (unsigned int stringValue), 0x57A890);

int CustomLocalizedStringIndex(const char *string);

}
