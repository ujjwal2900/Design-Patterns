#include <iostream>
#include <string>

class Storage
{
public:
    virtual const std::string getContents() = 0;
    virtual ~Storage() = default;
};

class SecureStorage : public Storage
{
public:
    explicit SecureStorage(const std::string &data) : m_Contents(data) {}

    const std::string getContents()
    {
        return m_Contents;
    }

private:
    const std::string m_Contents;
};


class Proxy 
{
public:
    explicit Proxy(const std::string msg, const std::string code) : m_secureStorage(new SecureStorage(msg)), m_code(code) {}

    const std::string getContents()
    {
        if(authorized())
            return m_secureStorage->getContents();
        else{
            std::cout << "Incorrect code" << std::endl;
        }
    }

    ~Proxy() = default;

private:

    bool authorized()
    {
        return m_code == "hello";
    }
    SecureStorage *m_secureStorage;
    const std::string m_code;
};

int main()
{
    //SecureStorage secureStorage("Toppp Seecreet INfo");
    Proxy secureStorage("Topp Secret info", "hello");

    std::cout << "Sensitive Data: " << secureStorage.getContents() << std::endl;

    return 0;
}