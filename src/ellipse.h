class Ellipse: public Shape{
public: 
    Ellipse(double semiMajorAxes, double semiMinorAxes) {
        // If the ellipse can't be successfully created,
        // handle the exception by throwing string "This is not a ellipse!"
    }
    
    double area() const {
        // return the area of the Ellipse.
    }
    
    double perimeter() const {
        // return the perimeter of the Ellipse.
    }
    
    std::string info() const {
        // return the info of the Ellipse.
        // ex. Ellipse (3.712, 4.000)
    }
}
