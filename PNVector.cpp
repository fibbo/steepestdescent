//
//  PNVector.cpp
//  RK4_project
//
//  Created by Philipp Gloor on 26.08.11.
//  Copyright 2011 UZH. All rights reserved.
//
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

#include "PNVector.hpp"

PNVector PNVector::operator+(const PNVector &rhs) {
    PNVector vector(*this);
    for (unsigned int i = 0; i < this->m_vector.size(); ++i) {
        vector.m_vector.at(i) += rhs.m_vector.at(i);
    }
    return vector;
}

PNVector PNVector::operator+(const double h) {
    PNVector vector(*this);
    for (unsigned int i = 0; i < this->m_vector.size(); ++i) {
        vector.m_vector.at(i) += h;
    }
    return vector;
}

double& PNVector::operator[](unsigned int index) {
    return (*this).m_vector.at(index);
}

PNVector PNVector::operator*(const double h) {
    PNVector vector(*this);
    for (unsigned int i = 0; i < this->m_vector.size(); ++i) {
        vector.m_vector.at(i) *= h;
    }
    return vector; 
}
// Inner product
PNVector PNVector::operator*(const PNVector &rhs) {
    PNVector vector(*this);
    for (unsigned int i = 0; i<this->m_vector.size(); ++i) {
        vector.m_vector.at(i) *= rhs.m_vector.at(i);
    }
    return vector; 
}

PNVector PNVector::operator/(const double h) {
    PNVector vector(*this);
    for (unsigned int i = 0; i<this->m_vector.size(); ++i) {
        vector.m_vector.at(i) /= h;
    }
    return vector; 
}

PNVector& PNVector::operator=(const PNVector &other) {
    if (this!= &other)
        this->m_vector = other.m_vector;
    return *this;
}

void PNVector::Print() {
    for (unsigned int i = 0; i<this->m_vector.size(); ++i) {
        std::cout << m_vector.at(i) << std::endl;
    }
}

unsigned long PNVector::getSize() const{
    return this->m_vector.size();
}

inline PNVector operator/(const PNVector &lhs, const double rhs) {
    PNVector vector(lhs);
    for (unsigned int i =0; i<lhs.getSize(); ++i) {
        vector[i] /= rhs;
    }
    return lhs;
}

