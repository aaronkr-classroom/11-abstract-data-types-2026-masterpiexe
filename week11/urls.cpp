// urls.cpp

#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>

#include "Vec.h"

using namespace std;

typedef string::const_iterator iter;
typedef Vec<string>::const_iterator v_iter;

// URL 문자가 아닌지 검사
bool not_url_char(char c)
{
    static const string url_ch = "~;/?:@=&$-_.+!*'(),";

    return !(isalnum(static_cast<unsigned char>(c)) ||
        find(url_ch.begin(), url_ch.end(), c) != url_ch.end());
}

// URL 끝 찾기
iter url_end(iter b, iter e)
{
    return find_if(b, e, not_url_char);
}

// URL 시작 찾기
iter url_beg(iter b, iter e)
{
    static const string sep = "://";

    iter i = b;

    while ((i = search(i, e, sep.begin(), sep.end())) != e)
    {
        if (i != b && i + sep.size() != e)
        {
            iter beg = i;

            while (beg != b &&
                isalpha(static_cast<unsigned char>(beg[-1])))
            {
                --beg;
            }

            if (beg != i &&
                !not_url_char(i[sep.size()]))
            {
                return beg;
            }
        }

        i += sep.size();
    }

    return e;
}

// URL 추출
Vec<string> find_urls(const string& s)
{
    Vec<string> urls;

    iter b = s.begin();
    iter e = s.end();

    while (b != e)
    {
        b = url_beg(b, e);

        if (b != e)
        {
            iter after = url_end(b, e);

            urls.push_back(string(b, after));

            b = after;
        }
    }

    return urls;
}

int main()
{
    string s;

    while (getline(cin, s))
    {
        Vec<string> v = find_urls(s);

        for (v_iter i = v.begin(); i != v.end(); ++i)
        {
            cout << "Found: " << *i << endl;
        }
    }

    return 0;
}
