#include <iostream>
#include "tree/splay_tree.h"

int main()
{
    using namespace std;
    using namespace xstl;

    splay_tree<int> t;

    t.insert(1);
    t.insert(2);
    t.insert(3);

    cout << t.contains(3);

    return 0;
}