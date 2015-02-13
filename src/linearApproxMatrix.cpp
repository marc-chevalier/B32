#include "../include/linearApproxMatrix.h"
#include<vector>
#include<cmath>
#include<bitset>
#include<iostream>

using namespace std;

linearApproxMatrix::linearApproxMatrix(vector<bitset<BLOC_LENGTH>>SBox) :
matrix(vector <vector <int> >())
{
    unsigned int a, b, x;
    for (a = 0; a < SBox.size(); ++a)
        for (b = 0; b < SBox.size(); ++b)
            for (x = 0; x < SBox.size(); ++x) {
                bitset<BLOC_LENGTH> bitset_a(a);
                bitset<BLOC_LENGTH> bitset_b(b);
                bitset<BLOC_LENGTH> bitset_x(x); // Init bitsets
                if (prod(bitset_a,bitset_x) == prod(bitset_b,SBox[x]))
                    (matrix[a])[b]++;
            }
}

void linearApproxMatrix::print(ostream& flux)
{
    vector< vector<int> >::iterator row;
    vector<int>::iterator col;
    for (row = matrix.begin(); row != matrix.end(); ++row) {
        for (col = row->begin(); col != row->end(); ++col) {
            flux << *col << " ";
        }
    }
}

bool prod(bitset<BLOC_LENGTH> a, bitset<BLOC_LENGTH> b)
{
    return ((a&b).count())%2;
}

ostream& operator<<(ostream& flux, linearApproxMatrix approx)
{
    approx.print(flux);
    return flux;
}
