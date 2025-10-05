#include <iostream>
#include <memory>
#include <string>
using namespace std;

class IEngine
{
public:
    virtual void start() const = 0;
    virtual ~IEngine() = default;
};

class IVehicle
{
public:
        
    explicit IVehicle(const IEngine &engine) : m_engine(engine) {}
    void drive()
    {
        m_engine.start();
        driveVehicle();
    }

    virtual ~IVehicle() = default;

protected:
    virtual void driveVehicle() const = 0;

private:
    const IEngine &m_engine;
        
};

class GasEngine : public IEngine
{
public:
    void start() const override
    {
        std::cout << "Gas Engine : ";
    }
};

class ElectricEngine : public IEngine
{
public:
    void start() const override
    {
        std::cout << "Electric Engine : ";
    }
};

class HybridEngine : public IEngine
{
public:
    void start() const override
    {
        std::cout << "Hybrid Engine : ";
    }
};

/* Concrete implementation of Truck */
class Truck : public IVehicle
{
public:
    Truck(const IEngine &engine) : IVehicle(engine) {}

    void driveVehicle() const override
    {
        std::cout << "Truck ";
    }
};

/* Concrete implementation of Bike */
class Bike : public IVehicle
{
public:
    Bike(const IEngine &engine) : IVehicle(engine) {}

    void driveVehicle() const override
    {
        std::cout << "Bike ";
    }
};

/* Concrete implementation of Car */
class Car : public IVehicle
{
public:
    Car(const IEngine &engine) : IVehicle(engine) {}

    void driveVehicle() const override
    {
        std::cout << "Car ";
    }
};

int main()
{
    GasEngine gasEngine = GasEngine();
    ElectricEngine electricEngine = ElectricEngine();
    HybridEngine hybridEngine = HybridEngine();

    const std::unique_ptr<IVehicle> vehicles[] {
        make_unique<Car>(hybridEngine),
        make_unique<Truck>(gasEngine),
        make_unique<Bike>(electricEngine)
    };

    for(const auto &vehicle : vehicles)
    {
        vehicle->drive();
        std::cout << std::endl;
    }

    return 0;
}