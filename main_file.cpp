#include <iostream>
#include <cmath>
#include <vector>
#include <random>
#include <string>
#include <cstdint> // for specific size integers
#include <fstream> // for file handling

using namespace std;

//global declaration
random_device rd; // obtain a random number from hardware
mt19937 gen(rd()); // seed the generator
uniform_int_distribution<> distr(0, 360); // define the range
// use distr(gen)

struct pixel {
    int  r = 0;
    int  g = 0;
    int  b = 0;
};

struct BmpHeader {
    char bitmapSignatureBytes[2] = {'B', 'M'};
    uint32_t sizeOfBitmapFile = 54 + 786432;
    uint32_t reservedBytes = 0;
    uint32_t pixelDataOffset = 54;
} bmpHeader;

struct BmpInfoHeader {
    uint32_t sizeOfThisHeader = 40;
    int32_t width = 512; // in pixels
    int32_t height = 512; // in pixels
    uint16_t numberOfColorPlanes = 1; // must be 1
    uint16_t colorDepth = 24;
    uint32_t compressionMethod = 0;
    uint32_t rawBitmapDataSize = 0; // generally ignored
    int32_t horizontalResolution = 3780; // in pixel per meter
    int32_t verticalResolution = 3780; // in pixel per meter
    uint32_t colorTableEntries = 0;
    uint32_t importantColors = 0;
} bmpInfoHeader;

float fade(float t) {
	return ((6*t - 15)*t + 10)*t*t*t;
}

float lerp(float t, float a1, float a2) {
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
    float ret = (c/p)*(g-1); //Was causing the seg fault
    return ret;

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

int formatResult(float res){
    //shift and map range
    res = res + 1; // bring results from -1 to 1 to 0 to 2
    res = (res * 255) /2;
    int result = res;
    //clamping
    if (result > 255){
        result = 255;
    }
    else if (result < 0){
        result = 0;
    }
    return result;

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
    if(below_x == above_x){
        above_x++;
    }
    if (below_y == above_y){
        above_y++;
    }

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
    float xf = x_c - below_x;
    float yf = y_c - below_y;
    float u = fade(xf);
    float v = fade(yf);
    float result = lerp(u, lerp(v, dot_bl, dot_tl), lerp(v, dot_br, dot_tr));

    //Step 6 - Map value to correct range
    return formatResult(result);
}

void processPixels(vector<vector<pixel>> &pixel_grid, int pixel_dimension, vector<vector<vector<float>>> grid){
    for (int row = 0; row < pixel_dimension; row++){
        vector<pixel> new_row;
        pixel_grid.push_back(new_row);
        for (int col = 0; col < pixel_dimension; col++){
            pixel current;
            current.r = current.g = current.b = perlinNoise(row, col, grid, pixel_dimension);
            pixel_grid[row].push_back(current);
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

    string name = "";
    cout << "Enter a file name with no extension: ";
    cin >> name;
    name = name + ".bmp";

    ofstream fout(name, ios::binary);

    BmpHeader file_head;
    file_head.sizeOfBitmapFile = 54 + (3* pixel_dimension*pixel_dimension);
    BmpInfoHeader info_head;
    info_head.height = pixel_dimension;
    info_head.width = pixel_dimension;
    fout.write((char *) &file_head, 14);
    fout.write((char *) &info_head, 40);

    for (int x = 0; x < pixel_dimension; x++){
        vector<pixel> current_row = pixel_store[x];
        for (int y = 0; y < pixel_dimension; y++){
            pixel current_pixel = current_row[y];
            uint8_t blue = current_pixel.b;
            fout.write((char *) &blue, 1);
            uint8_t red = current_pixel.r;
            fout.write((char *) &red, 1);
            uint8_t green = current_pixel.g;
            fout.write((char *) &green, 1);
        }
    }

    fout.close();

    return 0;
}