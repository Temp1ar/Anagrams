#include <iostream>
#include <string>
#include <cassert>

template <char first, char last>
class CharMap 
{
public:
    CharMap() 
    {
        std::fill(data_, data_+letters_, 0);
    }

    CharMap(const std::string& s) 
    {
        std::fill(data_, data_+letters_, 0);
        for (size_t i = 0; i < s.length(); ++i) {
            assert(s[i] >= first && s[i] <= last);
            data_[s[i] - first]++;
        }
    }

    int& operator[](char c)
    {
        assert(c >= first && c <= last);
        return data_[c - first];
    }

    int operator[](char c) const
    {
        assert(c >= first && c <= last);
        return data_[c - first];
    }

    int deficit() const
    {
        int deficit = 0;
        for (int i = 0; i < letters_; ++i) {
            if(data_[i] < 0) {
                deficit += data_[i];
            }
        }

        return -deficit;
    }

private:
    const static int letters_ = last - first + 1;
    int data_[letters_];
};

template<char first, char last>
CharMap<first, last> operator-(const CharMap<first, last>& left, 
                               const CharMap<first, last>& right) {
    CharMap<first, last> difference;
    for (char i = first; i < last + 1; ++i) {
        difference[i] = left[i] - right[i];
    }

    return difference;
}

int main() 
{     
    std::string s;
    std::getline(std::cin, s);

    std::string p;
    std::getline(std::cin, p);

    if (p.length() > s.length()) {
        std::cout << "0";
        return 0;
    }

    CharMap<'?', 'z'> pattern(p);

    size_t answer = 0;
    CharMap<'?', 'z'> input;
    for (size_t i = 0; i < s.length(); ++i) {
        input[s[i]]++;

        if(i >= p.length()) {
            input[s[i - p.length()]]--;
        }

        if ((input - pattern).deficit() <= input['?']) {
            answer++;
        }
    }

    std::cout << answer << std::endl;

    return 0;
}