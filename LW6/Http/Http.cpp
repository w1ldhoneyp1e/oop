#include <iostream>
#include <string>
#include "HttpUrl.h"

int main()
{
    std::string line;
    while (std::getline(std::cin, line))
    {
        try
        {
            HttpUrl url(line);
            std::cout << "URL: " << url.GetURL() << std::endl;
            std::cout << "  Protocol: " << (url.GetProtocol() == Protocol::HTTP ? "HTTP" : "HTTPS") << std::endl;
            std::cout << "  Domain:   " << url.GetDomain() << std::endl;
            std::cout << "  Port:     " << url.GetPort() << std::endl;
            std::cout << "  Document: " << url.GetDocument() << std::endl;
        }
        catch (const UrlParsingError& e)
        {
            std::cout << "Error: " << e.what() << std::endl;
        }
    }
    return 0;
}

