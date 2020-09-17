class Rectangle: public Shape {
public: 
    Rectangle(double length, double width) {
        // If the rectangle can't be successfully created,
        // handle the exception by throwing string "This is not a rectangle!"
    }
    
    double area() const {
        // return the area of the Rectangle.
    }
    
    double perimeter() const {
        // return the perimeter of the Rectangle.
    }
    
    std::string info() const {
        // return the info of the Rectangle.
        // ex. Rectangle (3.712, 4.000)
    }
};
