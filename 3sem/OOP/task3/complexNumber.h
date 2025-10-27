bool equal(double a, double b);

class complexNumber {
    public:
        complexNumber(double r, double phi);
        complexNumber();

        double radius();
        double angle();
        double getRe();
        double getIm();
        bool getIsExtended();

        void setRadius(double r);
        void setAngle(double phi);

        void print();

        ~complexNumber();

        bool operator==(complexNumber &num);
        bool operator!=(complexNumber &num);
        complexNumber operator+(complexNumber &num);
        complexNumber operator-();
        complexNumber operator-(complexNumber &num);
        complexNumber operator*(complexNumber &num);
        complexNumber operator/(complexNumber &num);

    private:
        void setRe();
        void setIm();
        void setIsExtended();
        bool isExtended;
        double re;
        double im;
        double r;
        double phi;
};
