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

struct pixel {
    int r = 0;
    int g = 0;
    int b = 0;
};

float fade(float coord) {
	return ((6*coord - 15)*coord + 10)*coord*coord*coord;
}
float lerp(float t,float  a1, float a2) {
	return a1 + t*(a2-a1);
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

float pointConvert(int coordinate, int pixel_dimension, int grid_dimension){
    float c = float(coordinate);
    float p = float(pixel_dimension);
    float g = float(grid_dimension);
    float ret = (c/p)*g;
    return ret + 0.0000000000001;

}

vector<float> calcDistance(float point_x, float point_y, int corner_x, int corner_y){
    vector<float> ret = {0.0, 0.0};
    ret[0] = point_x - corner_x;
    ret[1] = point_y - corner_y;

    return ret;
}

float dotProduct (vector<float> random_vector, vector<float> distance_vector){
    return (random_vector[0]*distance_vector[0]) + (random_vector[1]*distance_vector[1]);
}

int perlinNoise(int x, int y, vector<vector<vector<float>>> grid, int pixel_dimension){
    //Input is x, y coordinate pair, Output is an integer from 0 to 255
    //Step 1 - coordinates to grid points
    float x_c = pointConvert(x, pixel_dimension, grid.size());
    float y_c = pointConvert(y, pixel_dimension, grid.size());

    //Step 2 - find nearest points
    int below_x = floor(x_c);
    int above_x = ceil(x_c);
    int below_y = floor(y_c);
    int above_y = ceil(y_c);

    //Step 3 - Calculate distance vectors from point
    vector<float> bottom_l_dist = calcDistance(x_c, y_c, below_x, below_y);
    vector<float> bottom_r_dist = calcDistance(x_c, y_c, above_x, below_y);
    vector<float> top_l_dist = calcDistance(x_c, y_c, below_x, above_y);
    vector<float> top_r_dist = calcDistance(x_c, y_c, above_x, above_y);

    //Retrieving pseudo-random point vectors
    vector<float> bottom_left = grid[below_x][below_y];
    vector<float> bottom_right = grid[above_x][below_y];
    vector<float> top_left = grid[below_x][above_y];
    vector<float> top_right = grid[above_x][above_y];

    //Step 4 - Calculating the dot product
    float dot_bl = dotProduct(bottom_left, bottom_l_dist);
    float dot_br = dotProduct(bottom_right, bottom_r_dist);
    float dot_tl = dotProduct(top_left, top_r_dist);
    float dot_tr = dotProduct(top_right, top_r_dist);

    //Step 5 - Interpolate dot products
    float faded_x = fade(x_c);
    float faded_y = fade(y_c);
    float result = lerp(faded_x, lerp(faded_y, dot_bl, dot_tl), lerp(faded_y,dot_br, dot_tr));

    //Step 6 - Map value to correct range
    return 0;
}

void processPixels(vector<vector<pixel>> &pixel_grid, int pixel_dimension, vector<vector<vector<float>>> grid){
    for (int row = 0; row < pixel_dimension; row++){
        for (int col = 0; col < pixel_dimension; col++){
            pixel current;
            current.r = current.g = current.b = perlinNoise(row, col, grid, pixel_dimension);
        }
    }
}

int main(){

    int dimension = 0;
    while(dimension < 3 || dimension > 10){
        cout << "Define grid width and height with an integer between 3 and 10: "; 
        cin >> dimension;
    }
    int pixel_dimension = 0;
    while (pixel_dimension < 50 || pixel_dimension > 1500){
        cout <<"This program will create a square bitmap image. Please enter a pixel dimension (an integer): ";
        cin >> pixel_dimension;
    }
    
    // Step 1 - Create the grid and populate it with pseudorandom unit vectors
    vector<vector<vector<float>>> grid; // grid[row][column] populated with 2D unit vectors
    populateGrid(grid, dimension);

    //Step 2 - Conduct Project Work
    vector<vector<pixel>> pixel_store;
    processPixels(pixel_store,pixel_dimension, grid);

    //float testo = pointConvert(123, pixel_dimension, dimension);
    //cout << "point conversion: " << testo << endl;

    return 0;
}