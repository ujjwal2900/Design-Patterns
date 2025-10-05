#include <iostream>
#include <vector>
#include <string>
#include <algorithm>


/* Abstract base class for concrete Shape classes */
class Shape
{
public:
    virtual void draw() const = 0;
    virtual ~Shape() = default;
};

//Concrete Shape classes
class Circle : public Shape
{
public:
    explicit Circle(double radius) : m_Radius(radius) {}

    void draw() const override
    {
        std::cout << "Drawing a circle with radius " << m_Radius << std::endl;
    }

private:
    double m_Radius;
};

class Rectangle : public Shape
{
public:
    Rectangle(double width, double height) : m_width(width), m_height(height) {}
    
    void draw() const override
    {
        std::cout << "Drawing a rectangle with width " << m_width << " and height " << m_height << std::endl;
    }

private:
    double m_width;
    double m_height;
};

class Triangle : public Shape
{
public:
    Triangle(double side1, double side2, double side3) : m_side1(side1), m_side2(side2), m_side3(side3) {}

    void draw() const override
    {
        std::cout << "Drawing a Triangle with sides " << m_side1 << "," << m_side2 << "," << m_side3 << std::endl;
    }

protected:
    double m_side1;
    double m_side2;
    double m_side3;
};

class CompositeShape : public Shape
{
public:
    
    void addShape(Shape &shape)
    {
        m_shapes.push_back(&shape);
    }

    void draw() const override
    {
        std::cout << "Drawing a composite shape " << std::endl;
        for(auto shapes : m_shapes)
        {
            shapes->draw();
        }
    }

    void removeShape(Shape &shape)
    {
        auto pos = std::remove(m_shapes.begin(), m_shapes.end(), &shape);
        m_shapes.erase(pos, m_shapes.end());
    }

    ~CompositeShape() = default;

private:
    std::vector<Shape*> m_shapes;
};


int main()
{
    Circle c(5);
    Rectangle r(10,20);
    Triangle t(3,4,5);

    CompositeShape cs;
    
    cs.addShape(c);
    cs.addShape(r);
    cs.addShape(t);

    cs.draw();

    cs.removeShape(r);
    std::cout << "\n\n";

    cs.draw();

    return 0;
}