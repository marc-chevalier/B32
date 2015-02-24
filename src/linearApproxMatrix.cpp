#include "../include/linearApproxMatrix.h"
#include<vector>
#include<cmath>
#include<bitset>
#include<iostream>

using namespace std;

linearApproxMatrix::linearApproxMatrix(vector<bitset<BLOC_LENGTH>>SBox) :
matrix(vector<vector<int>>()), minima(vector<unsigned int>()), maxima(vector<unsigned int>())
{
    // Build the matrix
    matrix.resize(SBox.size());
    for (unsigned int x = 0; x< SBox.size(); ++x)
        matrix[x].resize(SBox.size(),0);

    for (unsigned int a = 0; a < SBox.size(); ++a)
        for (unsigned int b = 0; b < SBox.size(); ++b)
            for (unsigned int x = 0; x < SBox.size(); ++x)
            {
                bitset<BLOC_LENGTH> bitset_a(a);
                bitset<BLOC_LENGTH> bitset_b(b);
                bitset<BLOC_LENGTH> bitset_x(x); // Init bitsets
                if (prod(bitset_a,bitset_x) == prod(bitset_b,SBox[x]))
                    matrix[a][b]++;
            }
    // Build the max/min
    this->build_farthest_couples();
}

void linearApproxMatrix::print(ostream& flux)
{
    for(vector<int> row : matrix)
    {
        for(int col : row)
        {
            if(col<10)
                flux << ' ';
            flux << col << " ";
        }
        flux << endl;
    }
}

void linearApproxMatrix::build_farthest_couples()
{
    int min = static_cast<int>(matrix.size());
	int max = 0;
	for(vector<int> row : matrix)
	{
		for(int col : row)
		{
			if(col > max && col != static_cast<int>(matrix.size()))
				max = col;
			if(col < min)
				min = col;
		}
	}
	for(unsigned int a = 0; a < matrix.size(); ++a)
		for(unsigned int b = 0; b < matrix[0].size(); ++b)
		{
			if(matrix[a][b] == min)
            {
				minima.push_back(a);
				minima.push_back(b);
            }
            else if(matrix[a][b] == max)
            {
				maxima.push_back(a);
                maxima.push_back(b);
            }
        }
}

void linearApproxMatrix::print_farthest_couples()
{
	int min = matrix[minima[0]][minima[1]];
	int max = matrix[maxima[0]][maxima[1]];
	cout << "Smaller probability : " << (static_cast<double>(min))/(static_cast<double>(matrix.size()));
	cout << " for the couples :" << endl;
	for(unsigned int i = 0; i < minima.size()/2; ++i)
				cout << "(" << minima[2*i]<< "," << minima[2*i+1] << ") ";
	cout << "\nBigger probability (none 1): " << (static_cast<double>(max))/(static_cast<double>(matrix.size()));
	cout <<" for the couples :" << endl;
	for(unsigned int i = 0; i < maxima.size()/2; ++i)
				cout << "(" << maxima[2*i]<< "," << maxima[2*i+1] << ") ";
	cout << endl;
}

unsigned int linearApproxMatrix::get_min(unsigned int index)
{
    return minima[index];
}

unsigned int linearApproxMatrix::get_max(unsigned int index)
{
    return maxima[index];
}

bool prod(bitset<BLOC_LENGTH> a, bitset<BLOC_LENGTH> b)
{
    return (a&b).count()%2;
}

ostream& operator<<(ostream& flux, linearApproxMatrix approx)
{
    approx.print(flux);
    return flux;
}
