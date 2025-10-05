#include <iostream>
#include <string>
#include <memory>
#include <random>

int randomValue(int from, int to) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(from, to);
    return dist(gen);
}

class CloudStorage
{
public:
    virtual bool uploadContents(const std::string& content) = 0;
    virtual int getFreeSpace() = 0;
    virtual ~CloudStorage() = default;
};

class CloudDrive : public CloudStorage
{
public:
    bool uploadContents(const std::string& content) override
    {
        std::cout << "Uploading " << content.length() << " bytes to CloudDrive: " << std::endl;
        return true;
    }

    int getFreeSpace() override
    {
        // Implement the logic for getting the free space on CloudDrive here
        const int size = randomValue(0, 20);
        std::cout << "Available CloudDrive storage: " << size << "GB" << std::endl;
        return size;
    }
};

class FastShare : public CloudStorage
{
public:
    bool uploadContents(const std::string& content) override
    {
        std::cout << "Uploading " << content.length() << " bytes to FastShare: " << std::endl;
        return true;
    }
    int getFreeSpace() override
    {
        // Implement the logic for getting the free space on CloudDrive here
        const int size = randomValue(0, 10);
        std::cout << "Available FastShare storage: " << size << "GB" << std::endl;
        return size;
    }
};

// 3rd party service
class VirtualDrive
{
public:
    bool uploadData(const std::string& data, const int uniqueID)
    {
        std::cout << "Uploading to VirtualDrive: \"" << data << "\" ID: " << uniqueID << std::endl;
        std::cout << "Uploading " << data.length() << " bytes to VirtualDrive: " << std::endl;
        return true;
    }
    int usedSpace()
    {
        const int size = randomValue(0, 10);
        std::cout << "Available VirtualDrive storage: " << size << "GB" << std::endl;
        return size;
    }
    const int totalSpace = 15;
};

class LegacyAdapter : public CloudStorage
{
private:
    std::unique_ptr<VirtualDrive> m_adaptee;
public:
    LegacyAdapter() : m_adaptee(std::make_unique<VirtualDrive>()) {};

    bool uploadContents(const std::string& content) override
    {
        int uniqueID = randomValue(0, 10);
        std::cout << "LeagceAdapter::uploadContents() -> Calling VirtualDrive::uploadData() " << std::endl;
        return m_adaptee->uploadData(content, uniqueID);
    }

    int getFreeSpace() override
    {
        std::cout << "LeagceAdapter::getFreeSpace() -> Calling VirtualDrive::usedSpace() " << std::endl;
        return m_adaptee->usedSpace();
    }
};

int main()
{
    // Create an array of pointers to CloudStorage objects
    const std::unique_ptr<CloudStorage> cloudServices[]
    {
        std::make_unique<CloudDrive>(),
        std::make_unique<FastShare>(),
        std::make_unique<LegacyAdapter>()
    };

    // Iterate through the array and invoke the uploadContents and getFreeSpace
    // methods on each object
    const std::string content = "Beam me up, scooty";
    for(const auto &service: cloudServices)
    {
        service->uploadContents(content);
        service->getFreeSpace();
        std::cout << std::endl;
    }

    return 0;
}