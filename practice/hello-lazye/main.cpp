#include <lazye/math.h>
#include <lazye/logger.h>

#include <iostream>

using namespace lazye;
using namespace std;

int main()
{
    Vector3f vector(1.f, 2.f, 3.f);
    cout << GetLength(vector) << endl;
	Log(LogLevel::Info, "Hello log!");
    return 0;
}