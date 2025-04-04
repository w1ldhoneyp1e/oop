#include <catch2/catch_test_macros.hpp>
#include "HtmlDecode_functions.h"

TEST_CASE("HtmlDecode handles empty string", "[HtmlDecode]")
{
    REQUIRE(HtmlDecode("") == "");
}

TEST_CASE("HtmlDecode handles string without entities", "[HtmlDecode]")
{
    REQUIRE(HtmlDecode("Hello, World!") == "Hello, World!");
}

TEST_CASE("HtmlDecode handles all HTML entities", "[HtmlDecode]")
{
    REQUIRE(HtmlDecode("&quot;") == "\"");
    REQUIRE(HtmlDecode("&apos;") == "'");
    REQUIRE(HtmlDecode("&lt;") == "<");
    REQUIRE(HtmlDecode("&gt;") == ">");
    REQUIRE(HtmlDecode("&amp;") == "&");
}

TEST_CASE("HtmlDecode handles multiple entities in string", "[HtmlDecode]")
{
    REQUIRE(HtmlDecode("Cat &lt;says&gt; &quot;Meow&quot;. M&amp;M&apos;s")
        == "Cat <says> \"Meow\". M&M's");
}

TEST_CASE("HtmlDecode handles partial or invalid entities", "[HtmlDecode]")
{
    REQUIRE(HtmlDecode("&quot") == "&quot");
    REQUIRE(HtmlDecode("quot;") == "quot;");
    REQUIRE(HtmlDecode("&quo") == "&quo");
}

TEST_CASE("HtmlDecode handles multiple consecutive entities", "[HtmlDecode]")
{
    REQUIRE(HtmlDecode("&lt;&gt;&quot;&apos;&amp;") == "<>\"'&");
}

TEST_CASE("HtmlDecode handles entities at start and end", "[HtmlDecode]")
{
    REQUIRE(HtmlDecode("&quot;Hello&quot;") == "\"Hello\"");
}

TEST_CASE("HtmlDecode handles ampersand edge cases", "[HtmlDecode]")
{
    REQUIRE(HtmlDecode("&amp;quot;") == "&quot;");
    REQUIRE(HtmlDecode("&&amp;&&") == "&&&&");
}

TEST_CASE("HtmlDecode handles partial entity matches", "[HtmlDecode]")
{
    REQUIRE(HtmlDecode("&l&lt;t;") == "&l<t;");
}