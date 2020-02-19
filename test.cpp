#include <iostream>
#include <vector>
#include "array/fixed_vector.h"

int main()
{
    using namespace std;
    using namespace xstl;

    fixed_vector<int> v = {1,2,3,4, 5};
    cout<<v[1];

    return 0;
}