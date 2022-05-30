
#include "HealthPoints.h"


int main(int argc, char *argv[])
{
	HealthPoints a = HealthPoints(100);
    HealthPoints b;
    b = a + 100;
    b = a - 100;
    b = 100 + a;
    b = -100 + a;
}
