#include <string>
#include <map>

const std::map<std::string, char> HTML_ENTITIES = {
    {"&quot;", '"'},
    {"&apos;", '\''},
    {"&lt;", '<'},
    {"&gt;", '>'},
    {"&amp;", '&'}
};

bool TryDecodeEntity(const std::string& html, size_t pos, std::string& result, size_t& offset)
{
    for (const auto& entity : HTML_ENTITIES)
    {
        if (html.compare(pos, entity.first.length(), entity.first) == 0)
        {
            result += entity.second;
            offset = entity.first.length() - 1;
            return true;
        }
    }
    return false;
}

std::string HtmlDecode(std::string const& html)
{
    std::string result;
    result.reserve(html.length());
    
    for (size_t i = 0; i < html.length(); ++i)
    {
        if (html[i] == '&')
        {
            size_t offset = 0;
            if (!TryDecodeEntity(html, i, result, offset))
            {
                result += html[i];
            }
            else
            {
                i += offset;
            }
        }
        else
        {
            result += html[i];
        }
    }
    return result;
}