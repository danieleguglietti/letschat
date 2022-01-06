#include "letschat/request.h"
#include <gtest/gtest.h>
#include <string>

const char* raw = "SEND daniele@general [created_at:123123123;] Hi!";

TEST(Request, Parser) {
    request_t* req = request_parse(raw);

    ASSERT_NE(req, nullptr);
    EXPECT_STREQ(req->__raw, raw);
    EXPECT_STREQ(req->username, "daniele");
    EXPECT_STREQ(req->channel, "general");
    EXPECT_STREQ(req->message, "Hi!");

    headers_t headers = req->headers;
    EXPECT_STREQ(headers->get(headers, "created_at")->value, "123123123");
}
