#include "HealthPoints.h"
#include <iostream>
using std::cout;
using std::endl;

int main(){
    try{
        HealthPoints hp = HealthPoints(0);
    }
    catch (HealthPoints::InvalidArguments& e){
        cout << "gay";
    }
}