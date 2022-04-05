#include "letschat/response.h"
#include <gtest/gtest.h>
#include <string>

string_t raw = const_cast<string_t>("202 [channel:general;author:danieleguglietti;] Hi everyone!");

constexpr int HEADER_STRING_LEN = (HEADER_FIELD_MAXLEN * 2 + 2) * HEADERS_MAXCOUNT;
constexpr int RESPONSE_STRING_MAXLEN =
    (CODE_MAXLEN + 1) +
    (HEADER_STRING_LEN + 2) +
    (MESSAGE_MAXLEN + 1);

TEST(Response, Parser) {
    response_t* res = response_parse(raw);

    ASSERT_NE(res, nullptr);
    EXPECT_STREQ(res->__raw, raw);
    EXPECT_STREQ(res->message, "Hi everyone!");
    EXPECT_EQ(res->code, FORWARDED);

    headers_t headers = res->headers;
    EXPECT_STREQ(headers->get(headers, "channel")->value, "general");
}

TEST(Response, Serializer) {
    response_t* res = response_parse(raw);

    ASSERT_NE(res, nullptr);

    string_t serialized = res->serialize(res);

    ASSERT_NE(serialized, nullptr);
    EXPECT_LE(strsize(serialized), RESPONSE_STRING_MAXLEN);
    EXPECT_EQ(strsize(serialized), strsize(raw));
    EXPECT_STREQ(serialized, raw);
}
