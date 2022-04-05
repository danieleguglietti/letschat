#include "letschat/headers.h"
#include <gtest/gtest.h>
#include <string>

string_t raw = const_cast<string_t>("Content-Type:application/json;Connection:keep-alive;Content-Length:12;");
constexpr int max_length = (HEADER_FIELD_MAXLEN * 2 + 2) * HEADERS_MAXCOUNT;

TEST(Headers, Parser) {
    headers_t headers = headers_parse(raw);

    ASSERT_NE(headers, nullptr);
    EXPECT_STREQ(headers->get(headers, "Content-Type")->value, "application/json");
    EXPECT_EQ(headers->size, 3);
}

TEST(Headers, Serializer) {
    headers_t headers = headers_parse(raw);

    ASSERT_NE(headers, nullptr);
    std::string serialized = headers_serialize(headers);
    EXPECT_LE(serialized.size(), max_length);
    EXPECT_EQ(serialized.size(), strlen(raw));
    EXPECT_STREQ(serialized.c_str(), raw);
}
