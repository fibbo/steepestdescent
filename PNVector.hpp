//
//  
//  RK4_project
//
//  
//  
//
//  Created by Philipp Gloor on 01.05.11.
//  Copyright 2011 UZH. All rights reserved.
//


#ifndef RK4_project_PNVector_hpp
#define RK4_project_PNVector_hpp
#include <vector>
#include <iostream>

class PNVector {
public:
    PNVector(int N){
        m_vector.resize(N);
    }
    
    ~PNVector(){}
    
    PNVector(const PNVector &vSource)
    {
        m_vector = vSource.m_vector;
    }

    PNVector operator+(const PNVector &rhs);
    PNVector operator+(const double h);
    PNVector operator*(const PNVector &rhs);
    PNVector operator*(const double h);
    PNVector operator/(const double h);    
    PNVector& operator=(const PNVector &other);
    double &operator[](unsigned int index);

    void Print();
    unsigned long getSize() const;
    


private:
        std::vector<double> m_vector;
protected:
};


#endif
