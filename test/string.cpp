#include "letschat/utils/string.h"
#include <string.h>
#include <gtest/gtest.h>

string_t str = "Hello World!";

TEST(String, Size) {
    uint64_t size = strsize(str);
    EXPECT_EQ(size, 12);
}

TEST(String, AppendChar) {
    string_t str2 = strdup(str);

    strapp(str2, '?');
    EXPECT_STREQ(str2, "Hello World!?");
} 

TEST(String, Join) {
    string_t str1 = "Hello ";
    string_t str2 = "World!";

    string_t str3 = strjoin(str1, str2);
    EXPECT_STREQ(str3, "Hello World!");
}
