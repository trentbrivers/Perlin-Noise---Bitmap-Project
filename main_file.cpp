#include <iostream>
#include <cmath>

using namespace std;

double lerp(double t, double a, double b) {
    //linear interpolation function
    return a + t * (b - a); 
}

int main(){
    cout <<"This is a test. Project work to follow." << endl;
    return 0;
}