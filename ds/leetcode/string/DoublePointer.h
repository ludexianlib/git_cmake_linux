#pragma once
#include <string>

namespace str
{
    /*
     *brief  \双指针
     *param  \
     */
    class DoublePointer
    {
    public:
        /*
         *brief  \反转字符串
         *param  \
         */
        void reverse(std::string& str)
        {
            int hSize = str.size() / 2;
            int i = 0, j = str.size() - 1;
            while (i < hSize)
            {
                auto c = str[i];
                str[i] = str[j];
                str[j] = c;
                i++;
                j--;
            }
        }
    };
    
}
