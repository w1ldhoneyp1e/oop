#include <string>
#include <map>

const std::map<std::string, char> HTML_ENTITIES = {
    {"&quot;", '"'},
    {"&apos;", '\''},
    {"&lt;", '<'},
    {"&gt;", '>'},
    {"&amp;", '&'}
};

std::string GetDecodeEntity(std::string const& html, size_t pos)
{
    for (const auto& entity : HTML_ENTITIES)
    {
        if (html.compare(pos, entity.first.length(), entity.first) == 0)
        {
            return entity.first;
        }
    }
    return "";
}

std::string HtmlDecode(std::string const& html)
{
    std::string result;
    result.reserve(html.length());
    
    for (size_t i = 0; i < html.length(); ++i)
    {
        if (html[i] == '&')
        {
            std::string entity = GetDecodeEntity(html, i);
            if (!entity.empty())
            {
                result += HTML_ENTITIES.at(entity);
                i += entity.length() - 1;
                continue;
            }
        }
        result += html[i];
    }
    return result;
}