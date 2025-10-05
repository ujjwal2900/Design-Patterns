#include <iostream>
#include <memory>
#include <string>

class Pizza
{
public:
    virtual std::string description() const = 0;
    virtual double price() const = 0;
    virtual ~Pizza() = default;
};

class MargheritaPizza : public Pizza
{
public:
    std::string description() const override
    {
        return "Margherita Pizza";
    }

    double price() const override
    {
        return 9.99;
    }

    virtual ~MargheritaPizza() = default;
};

class HawaaiianPizza : public Pizza
{
public:
    std::string description() const override
    {
        return "Hawaaiian Pizza";
    }

    double price() const override
    {
        return 11.0;
    }

    virtual ~HawaaiianPizza() = default;
};

class PepproroniPizza : public Pizza
{
public:
    std::string description() const override
    {
        return "Pepproroni Pizza";
    }

    double price() const override
    {
        return 12.0;
    }

    virtual ~PepproroniPizza() = default;
};

class ToppingDecorator : public Pizza
{
public:
    ToppingDecorator() = default;
    ToppingDecorator(Pizza *pizza) : m_pizza(pizza) {}

    std::string description() const override
    {
        return m_pizza->description();
    }

    double price() const override
    {
        return m_pizza->price();
    }

    virtual ~ToppingDecorator() = default;
private:
    const Pizza *m_pizza;
};

class MushroomDecorator : public ToppingDecorator
{
public:
    MushroomDecorator(ToppingDecorator pizza) : m_Pizza(pizza) {}

    std::string description()  const override
    {
        return m_Pizza.description() + " with Mushroom";
    }

    double price() const override
    {
        return m_Pizza.price() + 2.0;
    }

    ~MushroomDecorator() = default;

private:
    const ToppingDecorator m_Pizza;

};

class TomatoDecorator : public ToppingDecorator
{
public:
    TomatoDecorator(ToppingDecorator pizza) : m_Pizza(pizza) {}

    std::string description() const override
    {
        return m_Pizza.description() + " with Tomato";
    }

    double price() const override
    {
        return m_Pizza.price() + 3.0;
    }

    ~TomatoDecorator() = default;

private:
    const ToppingDecorator m_Pizza;

};

class ExtraCheeseDecorator : public ToppingDecorator
{
public:
    ExtraCheeseDecorator(ToppingDecorator pizza) : m_Pizza(pizza) {}

    std::string description()  const override
    {
        return m_Pizza.description() + " with ExtraCheese";
    }

    double price() const override
    {
        return m_Pizza.price() + 3.0;
    }

    ~ExtraCheeseDecorator() = default;
private:
    const ToppingDecorator m_Pizza;
};

int main()
{
    auto margheritaPizza = new MargheritaPizza();
    auto margheritaPizza_Mushrooms = new MushroomDecorator((margheritaPizza));
    auto margheritaPizza_Mushrooms_chesse = new ExtraCheeseDecorator((margheritaPizza_Mushrooms));
    auto margheritzPizza_Mushrooms_cheese_tomato = new TomatoDecorator(margheritaPizza_Mushrooms_chesse);

    std::cout << margheritaPizza_Mushrooms->description() << ", cost : " 
              << margheritaPizza_Mushrooms->price() << std::endl ;
    
    std::cout << margheritaPizza_Mushrooms_chesse->description() << ", cost : " 
              << margheritaPizza_Mushrooms_chesse->price() << std::endl ;
    
    std::cout << margheritzPizza_Mushrooms_cheese_tomato->description() << ", cost : " 
              << margheritzPizza_Mushrooms_cheese_tomato->price();

    
    return 0;
    
}
