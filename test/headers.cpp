#include "letschat/headers.h"
#include <gtest/gtest.h>
#include <string>

const char* raw = "Content-Type: application/json;Content-Length: 12;Connection: keep-alive;";

TEST(Headers, Parser) {
    headers_t headers = headers_parse(raw);

    ASSERT_NE(headers, nullptr);
    EXPECT_STREQ(headers->get(headers, "Content-Type")->value, "application/json");
    EXPECT_EQ(headers->size, 3);
}
