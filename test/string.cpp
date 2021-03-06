#include "letschat/utils/string.h"
#include <string>
#include <stdlib.h>
#include <string.h>
#include <gtest/gtest.h>

TEST(String, Size) {
    const string_t str = const_cast<string_t>("Hello World!");
    uint64_t size = strsize(str);

    EXPECT_EQ(size, 12);
}

TEST(String, Find) {
    string_t src = const_cast<string_t>("Hello");
    size_t pos = strfind(src, 'o');

    EXPECT_NE(pos, -1);
    EXPECT_EQ(pos, 4);

    pos = strfind(src, 'a');
    EXPECT_EQ(pos, -1);
} 

TEST(String, Copy) {
    string_t src = const_cast<string_t>("Hello");
    string_t dest = (string_t) malloc(strsize(src) + 1);

    strcopy(src, dest);
    EXPECT_STREQ(src, dest);

    free(dest);
}

TEST(String, NCopy) {
    string_t src = const_cast<string_t>("Hello");
    string_t dest = strinit(5, 'a');

    strncopy(src, dest, 4);
    EXPECT_STREQ(dest, "Hell");

    free(dest);
}

TEST(String, Append) {
    string_t src = dupstr(const_cast<string_t>("Hello"));
    string_t str = const_cast<string_t>("World");

    string_t res = strapp(&src, str);
    EXPECT_STREQ(res, "HelloWorld");
    EXPECT_STREQ(src, "HelloWorld");

    free(res);
}

TEST(String, Substring) {
    string_t src = const_cast<string_t>("Hello World!");
    string_t str = substr(src, 6);

    EXPECT_STREQ(str, "World!");

    free(str);
}

TEST(String, SubNString) {
    string_t src = const_cast<string_t>("Hello World!");
    string_t str = subnstr(src, 6, 5);

    EXPECT_STREQ(str, "World");

    free(str);
}

TEST(String, Duplicate) {
    string_t src = const_cast<string_t>("Hello World!");
    string_t dup = dupstr(src);

    EXPECT_NE(src, dup);
    EXPECT_STREQ(src, dup);

    free(dup);
}

TEST(String, Split) {
    string_t src = dupstr(const_cast<string_t>("Hello World!"));
    string_t tok = strsplit(&src, ' ');

    EXPECT_STREQ(tok, "Hello");
    EXPECT_STREQ(src, "World!");

    free(tok);
}

TEST(String, Equals) {
    EXPECT_TRUE(
        streq(const_cast<string_t>("Hello"), const_cast<string_t>("Hello"))
    );
    
    EXPECT_FALSE(
        streq(const_cast<string_t>("Hello"), const_cast<string_t>("HeLlo"))
    );
}

TEST(String, EqualsNoCase) {
    EXPECT_TRUE(
        streq_nocase(const_cast<string_t>("Hello"), const_cast<string_t>("Hello"))
    );
    
    EXPECT_TRUE(
        streq_nocase(const_cast<string_t>("Hello"), const_cast<string_t>("HeLlo"))
    );
}

TEST(String, Fill) {
    string_t str = static_cast<string_t>(malloc(5));
    strfill(str, '*', 5);

    str[4] = '\0';

    EXPECT_STREQ(str, "****");

    free(str);
}

TEST(String, Init) {
    string_t str = strinit(5, '*');
    EXPECT_STREQ(str, "*****");

    free(str);
}

TEST(String, Trim) {
    string_t trm = strtrim(const_cast<string_t>("  Hello World!  "));
    EXPECT_STREQ(trm, "Hello World!");
}
