#include "HttpUrl.h"
#include <regex>
#include <algorithm>
#include <cctype>
#include <sstream>

namespace
{
    const unsigned short HTTP_DEFAULT_PORT = 80;
    const unsigned short HTTPS_DEFAULT_PORT = 443;
    const unsigned short MIN_PORT = 1;
    const unsigned short MAX_PORT = 65535;

    unsigned short GetDefaultPort(Protocol protocol)
    {
        return protocol == Protocol::HTTP 
            ? HTTP_DEFAULT_PORT 
            : HTTPS_DEFAULT_PORT;
    }
}

std::string HttpUrl::ToLower(const std::string& str)
{
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(),
        [](unsigned char c) { 
            return std::tolower(c); 
        });
    return result;
}

Protocol HttpUrl::ParseProtocol(const std::string& str)
{
    std::string proto = ToLower(str);
    if (proto == "http")
    {
        return Protocol::HTTP;
    }
    if (proto == "https")
    {
        return Protocol::HTTPS;
    }
    throw UrlParsingError("Invalid protocol: " + str);
}

HttpUrl::HttpUrl(std::string const& url)
{
    std::regex urlRegex(R"(^([a-zA-Z]+)://([^/:]+)(?::(\d+))?(/.*)?$)");
    std::smatch match;
    if (!std::regex_match(url, match, urlRegex))
    {
        throw UrlParsingError("Invalid URL format");
    }

    m_protocol = ParseProtocol(match[1].str());
    m_domain = match[2].str();

    if (match[3].matched)
    {
        int port = std::stoi(match[3].str());
        if (port < MIN_PORT || port > MAX_PORT)
            throw UrlParsingError("Port out of range");
        m_port = static_cast<unsigned short>(port);
    }
    else
    {
        m_port = GetDefaultPort(m_protocol);
    }

    m_document = match[4].matched ? match[4].str() : "/";
    if (m_document.empty() || m_document[0] != '/')
        m_document = "/" + m_document;
}

HttpUrl::HttpUrl(std::string const& domain, std::string const& document, Protocol protocol)
    : HttpUrl(domain, document, protocol, GetDefaultPort(protocol))
{
}

HttpUrl::HttpUrl(std::string const& domain, std::string const& document, Protocol protocol, unsigned short port)
    : m_domain(domain)
    , m_protocol(protocol)
    , m_port(port)
{
    if (domain.empty())
    {
        throw std::invalid_argument("Domain cannot be empty");
    }
    if (port < MIN_PORT || port > MAX_PORT)
    {
        throw std::invalid_argument("Port out of range");
    }
    m_document = document.empty() ? "/" : document;
    if (m_document[0] != '/')
    {
        m_document = "/" + m_document;
    }
}

std::string HttpUrl::GetURL() const
{
    std::ostringstream oss;
    oss << (m_protocol == Protocol::HTTP ? "http" : "https")
        << "://" << m_domain;
    if (m_port != GetDefaultPort(m_protocol))
    {
        oss << ":" << m_port;
    }
    oss << m_document;
    return oss.str();
}

std::string HttpUrl::GetDomain() const
{
    return m_domain;
}

std::string HttpUrl::GetDocument() const
{
    return m_document;
}

Protocol HttpUrl::GetProtocol() const
{
    return m_protocol;
}

unsigned short HttpUrl::GetPort() const
{
    return m_port;
}
