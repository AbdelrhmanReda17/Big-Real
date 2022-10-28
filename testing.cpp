#include "BigReal.cpp"

using namespace std;

int main(){
    BigReal x(3.0123);
    BigReal y("55.592713");
    BigReal z(55);
    x=y=z;
    return 0;
}