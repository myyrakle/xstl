#include <iostream>
#include <vector>
#include "heap/heap.h"

int main()
{
    using namespace std;
    using namespace xstl;

    heap<int> h{1,4,3,2,5,0};

    cout<<h.front();

    return 0;
}