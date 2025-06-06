#pragma once
#include <string>
#include "UrlParsingError.h"

enum class Protocol
{
    HTTP,
    HTTPS
};

class HttpUrl
{
public:
    HttpUrl(std::string const& url);
    HttpUrl(
        std::string const& domain,
        std::string const& document,
        Protocol protocol = Protocol::HTTP
    );
    HttpUrl(
        std::string const& domain,
        std::string const& document,
        Protocol protocol,
        unsigned port
    );

    std::string GetURL() const;
    std::string GetDomain() const;
    std::string GetDocument() const;
    Protocol GetProtocol() const;
    unsigned GetPort() const;

private:
    std::string m_domain;
    std::string m_document;
    Protocol m_protocol;
    unsigned m_port;
};

