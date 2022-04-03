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
}

TEST(String, Append) {
    string_t src = const_cast<string_t>("Hello");
    string_t str = const_cast<string_t>("World");

    string_t res = strapp(&src, str);
    EXPECT_STREQ(res, "HelloWorld");
    EXPECT_STREQ(src, "HelloWorld");
}
