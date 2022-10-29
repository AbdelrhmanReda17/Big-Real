#include "BigReal.cpp"

using namespace std;

int main(){
    BigReal x;
    cin >> x;
    BigReal y("-111.3");
    BigReal z = x - y ;
    cout << z;

    return 0;
}
