//
//  SteepestDescent.cpp
//  SteepestDescent
//
//  Created by ladmin on 06.06.13.
//  Copyright (c) 2013 Philipp Gloor. All rights reserved.
//

class SteepestDescent {
public:
    static double step(double (*func)(double), double x, double h) {
        return x-h*(*func)(x);
    }
};