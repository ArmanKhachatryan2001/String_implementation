#include <iostream>

class string {
public:
    string();
    string(const string&);
    string(string&&);
    string(const char*);
    ~string();
public:
    string& operator=(string&& str);
    char operator[](int size) const;
    string operator+(const string& str);
    string& operator=(const string& str);
    string& operator+=(const string& str);
    friend bool operator<(const string& str, const string& str1);
    friend bool operator>(const string& str, const string& str1);
    friend bool operator==(const string& str, const string& str1);
    friend bool operator!=(const string& str, const string& str1);
    friend bool operator>=(const string& str, const string& str1);
    friend bool operator<=(const string& str, const string& str1);
    friend std::ostream& operator<<(std::ostream& cout, string& str)
    {
        for (int i = 0; i < str.m_size; ++i) {
            cout << str.ptr[i];
        }
        return cout;
    }
    friend std::istream& operator>>(std::istream& in, string& str) {
        std::string tmp;
        in >> tmp;
        str.m_size = tmp.size()+1;
        str.copy(tmp.c_str(), tmp.size());
        return in;
    }

public:
    bool empty();
    void clear();
    char& back();
    char& front();
    size_t size();
    size_t length();
    void pop_back();
    char& at(int index);
    void swap(string& str);
    void push_back(char val);
    string& erase(int index);
    const char* c_str() const;
    string& append(const string& str);
    string& append(int count, char val);
    void merge_copy(char* arr, int size);
    string& insert(int index,const char* val);

private:
    void add_copy(char*, int, int, bool);
    void copy(const char*, int);
    char* ptr;
    int m_size;
};

int main()
{
    //const char* cst = "hello";
    //string s;
    //s.append(3, '*');
    //s.append(cst);
    string str1;
    std::cin >> str1;
    std::cout << str1;
    //str1 = "BB";
    //const char* ptr = str1.c_str();
    //char& f = str1.front();
    //f = 'p';
    //char& t = str1.back();
    //t = 'T';
    //str1.at(1) = 'p';
    string str("BBB");
    std::cout << str << str.size();
    //str.swap(str1);
    //str += str1;
    //string str2 = str + str1;
    //str2.insert(8, "A");
    //str2.erase(8);
    //str2.push_back('a');
    //str2.pop_back();
    //std::cout << str2 << " " << str2.size() <<  " " << str2.length();
}
bool operator<=(const string& str, const string& str1)
{
    if (str.m_size <= str1.m_size) {
        return true;
    }
    return false;
}

bool operator>=(const string& str, const string& str1)
{
    if (str.m_size >= str1.m_size) {
        return true;
    }
    return false;
}

bool operator>(const string& str, const string& str1)
{
    if (str.m_size > str1.m_size) {
        return true;
    }
    return false;
}

bool operator<(const string& str, const string& str1)
{
    if (str.m_size < str1.m_size) {
        return true;
    }
    return false;
}

bool operator!=(const string& str, const string& str1)
{
    return !(str == str1);
}

bool operator==(const string& str, const string& str1)
{
    if (str.m_size != str1.m_size) {
        return false;
    }
    for (int i = 0; i < str.m_size; ++i) {
        if (str.ptr[i] != str1.ptr[i]) {
            return false;
        }
    }
    return true;
}

const char* string::c_str() const
{
    return ptr;
}

char& string::front()
{
    return ptr[0];
}

char& string::back()
{
    return ptr[m_size - 2];
}

char& string::at(int index)
{
    char* pt;
    for (int i = 0; i < m_size; ++i) {
        if (index == i) {
            pt = &ptr[i];
        }
    }
    return *pt;
}

bool string::empty()
{
    if (m_size == 1) {
        return true;
    }
    return false;
}

void string::swap(string& str)
{
    string tmp;
    tmp.m_size = m_size;
    tmp.ptr = new char[m_size];
    for (int i = 0; i < m_size; ++i) {
        tmp.ptr[i] = ptr[i];
    }
    delete[] ptr;
    m_size = str.m_size;
    ptr = new char[m_size];
    for (int i = 0; i < m_size; ++i) {
        ptr[i] = str.ptr[i];
    }
    delete[] str.ptr;
    str.m_size = tmp.m_size;
    str.ptr = new char[str.m_size];
    for (int i = 0; i < str.m_size; ++i) {
        str.ptr[i] = tmp.ptr[i];
    }
}

string& string::append(const string& str)
{
    merge_copy(str.ptr, (m_size + str.m_size)-1);
    return *this;
}

void string::merge_copy(char* arr, int size)
{
    string tmp;
    if (ptr != nullptr) {
    tmp.m_size = m_size - 1;
    for (int i = 0; i < m_size - 1; ++i) {
        tmp.ptr[i] = ptr[i];
    }
    delete[] ptr;
    }
    m_size = size;
    ptr = new char[m_size];
    for (int i = 0; i <= tmp.m_size; ++i) {
        ptr[i] = tmp.ptr[i];
    }
    int j = 0;
    for (int i = tmp.m_size; i < size; ++i) {
        ptr[i] = arr[j];
        ++j;
    }
}

size_t string::size()
{
    return --m_size;
}

size_t string::length()
{
    return m_size;
}

string& string::append(int count, char val)
{
    if (count == 0) {
        return *this;
    }
    m_size = count + 1;
    ptr = new char[m_size];
    for (int i = 0; i < count; ++i) {
        ptr[i] = val;
    }
    ptr[count] = '\0';
    return *this;
}

void string::push_back(char val)
{
    string tmp;
    for (int i = 0; i < m_size - 1; ++i) {
        tmp.ptr[i] = ptr[i];
    }
    tmp.ptr[m_size - 1] = val;
    ++m_size;
    tmp.ptr[m_size] = '\0';
    delete[] ptr;
    copy(tmp.ptr, m_size);
}

void string::pop_back()
{
    if (m_size == 1) {
        return;
    }
    string tmp;
    for (int i = 0; i < m_size - 2; ++i) {
        tmp.ptr[i] = ptr[i];
    }
    --m_size;
    delete[] ptr;
    copy(tmp.ptr, m_size);
}

string& string::erase(int index)
{
    if (index > m_size - 1) {
        return *this;
    }
    string tmp;
    int j = 0;
    for (int i = 0; i < m_size - 1; ++i) {
        if (index == i) {
            continue;
        }
        tmp.ptr[j] = ptr[i];
        ++j;
    }
    delete[] ptr;
    copy(tmp.ptr, m_size - 1);
    return *this;
}

string& string::insert(int index, const char* val)
{
    if (m_size < index) {
        return *this;
    }
    string tmp;
    tmp.m_size = m_size;
    int j = 0;
    for (int i = 0; i < m_size; ++i) {
        if (index == j) {
            tmp.ptr[j] = *val;
            ++j;
        }
        tmp.ptr[j] = ptr[i];
        ++j;
    }
    delete[] ptr;
    copy(tmp.ptr, m_size+1);

    delete[] tmp.ptr;
    tmp.ptr = nullptr;
    return *this;
}

void string::clear()
{
    delete[] ptr;
    ptr = nullptr;
    m_size = 0;
}

char string::operator[](int size) const
{
    if (size > this->m_size) {
        exit(0);
    }
    return ptr[size];
}

string& string::operator=(string&& str)
{
    copy(str.ptr, str.m_size);
    return *this;
}

string& string::operator=(const string& str)
{
    copy(str.ptr, str.m_size);
    return *this;
}

string::string()
{
    this->m_size = 1;
    ptr = new char[m_size];
    ptr[m_size - 1] = '\0';
}

string::string(const string& str)
{
    if (str.m_size != 0) {
        copy(str.ptr, str.m_size);
    }
}

string::string(string&& str)
{
    copy(str.ptr, str.m_size);
}

string::~string()
{
    if (ptr != nullptr) {
    delete[] ptr;
    ptr = nullptr;
    m_size = 0;
    }
}

void string::copy(const char* str, int size)
{
    this->m_size = size;
    this->ptr =  new char[this->m_size];
    for (int i = 0; i < m_size; ++i) {
        ptr[i] = str[i];
    }
}

void string::add_copy(char* str, int size, int size1, bool flag)
{
    if (flag == 0) {
        this->m_size = size;
        this->ptr = new char[this->m_size];
        for (int i = 0; i < size1; ++i) {
            ptr[i] = str[i];
        }
    }
    if (flag == 1) {
        int j = 0;
        for (int i = size-1; i < size1 - 1; ++i) {
            ptr[i] = str[j];
            ++j;
        }
        ptr[size1] = '\0';
    }
}

string::string(const char* str)
{
    int i = 0;
    while (str[i] != '\0') {
        ++i;
    }
    m_size = i + 1;
    ptr = new char[m_size];
    for (int j = 0; j < i; ++j) {
        ptr[j] = str[j];
    }
    ptr[m_size] = '\0';
}

string string::operator+(const string& str)
{
    string tmp;
    tmp.add_copy(ptr, ((m_size + str.m_size) - 1), m_size - 1, 0);
    tmp.add_copy(str.ptr, m_size, ((m_size + str.m_size) - 1), 1);
    return tmp;
}

string& string::operator+=(const string& str)
{
    merge_copy(str.ptr, (m_size + str.m_size)-1);
    return *this;

}
