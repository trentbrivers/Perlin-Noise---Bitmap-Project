#include <iostream>
#include <cmath>
#include <vector>
#include <random>

using namespace std;

//global declaration
random_device rd; // obtain a random number from hardware
mt19937 gen(rd()); // seed the generator
uniform_int_distribution<> distr(0, 360); // define the range
// use distr(gen)

double lerp(double t, double a, double b) {
    //linear interpolation function
    return a + t * (b - a); 
}

float degreeToRadian(int degree){
    return degree * (M_PI / 180);
}

vector<float> makeUnitVector(){
    vector<float> ret = {0.0, 0.0};
    int degree = distr(gen);
    ret[0] = 1* cos(degreeToRadian(degree));
    ret[1] = 1* sin(degreeToRadian(degree));

    return ret;
}

void populateGrid(vector<vector<vector<float>>> &grid, int dimension){
    for (int row = 0; row < dimension; row++){
        vector<vector<float>> new_row;
        grid.push_back(new_row);
        for (int col = 0; col < dimension; col++){
            vector<float> current = makeUnitVector();
            grid[row].push_back(current);
        }
    }
}

int main(){

    int dimension = 0;
    while(dimension < 3 || dimension > 10){
        cout << "Define grid width and height with an integer between 3 and 10: "; 
        cin >> dimension;
    }
    vector<vector<vector<float>>> grid; // grid[row][column] populated with 2D unit vectors
    populateGrid(grid, dimension);

    cout << "testing pi: " << M_PI << endl;
    cout <<"This is a test. Project work to follow. dim: " << dimension << endl;
    return 0;
}