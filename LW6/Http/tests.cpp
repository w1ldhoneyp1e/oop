#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include "HttpUrl.h"
#include "UrlParsingError.h"

TEST_CASE("url constructor valid cases") 
{
    SECTION("full url") 
    {
        HttpUrl url("http://example.com:8080/index.html");
        REQUIRE(url.GetProtocol() == Protocol::HTTP);
        REQUIRE(url.GetDomain() == "example.com");
        REQUIRE(url.GetPort() == 8080);
        REQUIRE(url.GetDocument() == "/index.html");
        REQUIRE(url.GetURL() == "http://example.com:8080/index.html");
    }

    SECTION("without port") 
    {
        HttpUrl url("https://example.com/path");
        REQUIRE(url.GetProtocol() == Protocol::HTTPS);
        REQUIRE(url.GetDomain() == "example.com");
        REQUIRE(url.GetPort() == 443);
        REQUIRE(url.GetDocument() == "/path");
        REQUIRE(url.GetURL() == "https://example.com/path");
    }

    SECTION("without document") 
    {
        HttpUrl url("http://example.com");
        REQUIRE(url.GetProtocol() == Protocol::HTTP);
        REQUIRE(url.GetDomain() == "example.com");
        REQUIRE(url.GetPort() == 80);
        REQUIRE(url.GetDocument() == "/");
        REQUIRE(url.GetURL() == "http://example.com/");
    }

    SECTION("default port HTTP") 
    {
        HttpUrl url("example.com", "page", Protocol::HTTP);
        REQUIRE(url.GetProtocol() == Protocol::HTTP);
        REQUIRE(url.GetDomain() == "example.com");
        REQUIRE(url.GetPort() == 80);
        REQUIRE(url.GetDocument() == "/page");
        REQUIRE(url.GetURL() == "http://example.com/page");
    }

    SECTION("default port HTTPS") 
    {
        HttpUrl url("secure.com", "secure", Protocol::HTTPS);
        REQUIRE(url.GetProtocol() == Protocol::HTTPS);
        REQUIRE(url.GetDomain() == "secure.com");
        REQUIRE(url.GetPort() == 443);
        REQUIRE(url.GetDocument() == "/secure");
        REQUIRE(url.GetURL() == "https://secure.com/secure");
    }

    SECTION("custom port") 
    {
        HttpUrl url("example.com", "folder/file.txt", Protocol::HTTPS, 444);
        REQUIRE(url.GetProtocol() == Protocol::HTTPS);
        REQUIRE(url.GetDomain() == "example.com");
        REQUIRE(url.GetPort() == 444);
        REQUIRE(url.GetDocument() == "/folder/file.txt");
        REQUIRE(url.GetURL() == "https://example.com:444/folder/file.txt");
    }
}

TEST_CASE("url constructor invalid cases") 
{
    SECTION("invalid protocol") 
    {
        REQUIRE_THROWS_AS(HttpUrl("ftp://example.com/"), UrlParsingError);
    }

    SECTION("invalid port") 
    {
        REQUIRE_THROWS_AS(HttpUrl("http://example.com:0/"), UrlParsingError);
        REQUIRE_THROWS_AS(HttpUrl("http://example.com:70000/"), UrlParsingError);
    }

    SECTION("empty domain") 
    {
        REQUIRE_THROWS_AS(HttpUrl("http:///"), UrlParsingError);
    }

    SECTION("throws on empty domain") 
    {
        REQUIRE_THROWS_AS(HttpUrl("", "doc", Protocol::HTTP, 80), UrlParsingError);
    }

    SECTION("throws on invalid port") 
    {
        REQUIRE_THROWS_AS(HttpUrl("example.com", "doc", Protocol::HTTP, 0), UrlParsingError);
        REQUIRE_THROWS_AS(HttpUrl("example.com", "doc", Protocol::HTTP, 70000), UrlParsingError);
    }
}

TEST_CASE("constructor (domain, document, protocol) valid cases")
{
    SECTION("http, document with slash")
    {
        HttpUrl url("example.com", "/page", Protocol::HTTP);
        REQUIRE(url.GetProtocol() == Protocol::HTTP);
        REQUIRE(url.GetDomain() == "example.com");
        REQUIRE(url.GetPort() == 80);
        REQUIRE(url.GetDocument() == "/page");
        REQUIRE(url.GetURL() == "http://example.com/page");
    }

    SECTION("http, document without slash")
    {
        HttpUrl url("example.com", "page", Protocol::HTTP);
        REQUIRE(url.GetProtocol() == Protocol::HTTP);
        REQUIRE(url.GetDomain() == "example.com");
        REQUIRE(url.GetPort() == 80);
        REQUIRE(url.GetDocument() == "/page");
        REQUIRE(url.GetURL() == "http://example.com/page");
    }

    SECTION("https, document with slash")
    {
        HttpUrl url("secure.com", "/secure", Protocol::HTTPS);
        REQUIRE(url.GetProtocol() == Protocol::HTTPS);
        REQUIRE(url.GetDomain() == "secure.com");
        REQUIRE(url.GetPort() == 443);
        REQUIRE(url.GetDocument() == "/secure");
        REQUIRE(url.GetURL() == "https://secure.com/secure");
    }

    SECTION("https, document without slash")
    {
        HttpUrl url("secure.com", "secure", Protocol::HTTPS);
        REQUIRE(url.GetProtocol() == Protocol::HTTPS);
        REQUIRE(url.GetDomain() == "secure.com");
        REQUIRE(url.GetPort() == 443);
        REQUIRE(url.GetDocument() == "/secure");
        REQUIRE(url.GetURL() == "https://secure.com/secure");
    }

    SECTION("empty document")
    {
        HttpUrl url("example.com", "", Protocol::HTTP);
        REQUIRE(url.GetDocument() == "/");
        REQUIRE(url.GetURL() == "http://example.com/");
    }
}

TEST_CASE("constructor (domain, document, protocol) invalid cases")
{
    SECTION("empty domain")
    {
        REQUIRE_THROWS_AS(HttpUrl("", "doc", Protocol::HTTP), UrlParsingError);
    }
}

TEST_CASE("constructor (domain, document, protocol, port) valid cases")
{
    SECTION("http, custom port, document with slash")
    {
        HttpUrl url("example.com", "/file", Protocol::HTTP, 8080);
        REQUIRE(url.GetProtocol() == Protocol::HTTP);
        REQUIRE(url.GetDomain() == "example.com");
        REQUIRE(url.GetPort() == 8080);
        REQUIRE(url.GetDocument() == "/file");
        REQUIRE(url.GetURL() == "http://example.com:8080/file");
    }

    SECTION("http, custom port, document without slash")
    {
        HttpUrl url("example.com", "file", Protocol::HTTP, 8080);
        REQUIRE(url.GetProtocol() == Protocol::HTTP);
        REQUIRE(url.GetDomain() == "example.com");
        REQUIRE(url.GetPort() == 8080);
        REQUIRE(url.GetDocument() == "/file");
        REQUIRE(url.GetURL() == "http://example.com:8080/file");
    }

    SECTION("https, custom port, empty document")
    {
        HttpUrl url("secure.com", "", Protocol::HTTPS, 1234);
        REQUIRE(url.GetProtocol() == Protocol::HTTPS);
        REQUIRE(url.GetDomain() == "secure.com");
        REQUIRE(url.GetPort() == 1234);
        REQUIRE(url.GetDocument() == "/");
        REQUIRE(url.GetURL() == "https://secure.com:1234/");
    }
}

TEST_CASE("constructor (domain, document, protocol, port) invalid cases")
{
    SECTION("empty domain")
    {
        REQUIRE_THROWS_AS(HttpUrl("", "doc", Protocol::HTTP, 8080), UrlParsingError);
    }

    SECTION("invalid port (0)")
    {
        REQUIRE_THROWS_AS(HttpUrl("example.com", "doc", Protocol::HTTP, 0), UrlParsingError);
    }

    SECTION("invalid port (too large)")
    {
        REQUIRE_THROWS_AS(HttpUrl("example.com", "doc", Protocol::HTTP, 70000), UrlParsingError);
    }
}
