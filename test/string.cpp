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
    string_t dest = (string_t) malloc(strsize(src) - 1);

    strncopy(src, dest, 4);
    EXPECT_STREQ(dest, "Hell");

    free(dest);
}

TEST(String, Append) {
    string_t src = const_cast<string_t>("Hello");
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
}

TEST(String, Split) {
    string_t src = dupstr(const_cast<string_t>("Hello World!"));
    string_t tok = strsplit(src, ' ');

    EXPECT_STREQ(src, "Hello");
    EXPECT_STREQ(tok, "World!");
}
