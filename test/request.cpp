#include "letschat/request.h"
#include <gtest/gtest.h>
#include <string>

const char* raw = "SEND daniele@general [created_at:123123123;] Hi!";

constexpr int HEADER_STRING_LEN = (HEADER_FIELD_MAXLEN * 2 + 2) * HEADERS_MAXCOUNT;
constexpr int REQUEST_STRING_MAXLEN =
    (COMMAND_MAXLEN + 1) +
    (USERNAME_MAXLEN + 1) +
    (CHANNEL_MAXLEN + 1) +
    (HEADER_STRING_LEN + 2) +
    (MESSAGE_MAXLEN + 1);

TEST(Request, Parser) {
    request_t* req = request_parse(raw);

    ASSERT_NE(req, nullptr);
    EXPECT_STREQ(req->__raw, raw);
    EXPECT_STREQ(req->username, "daniele");
    EXPECT_STREQ(req->channel, "general");
    EXPECT_STREQ(req->message, "Hi!");
    EXPECT_EQ(req->command, SEND);

    headers_t headers = req->headers;
    EXPECT_STREQ(headers->get(headers, "created_at")->value, "123123123");
}

TEST(Request, Serializer) {
    request_t* req = request_parse(raw);

    ASSERT_NE(req, nullptr);

    const char* serialized = req->serialize(req);

    ASSERT_NE(serialized, nullptr);
    EXPECT_LE(strlen(serialized), REQUEST_STRING_MAXLEN);
    EXPECT_EQ(strlen(serialized), strlen(raw));
    EXPECT_STREQ(serialized, raw);
}
