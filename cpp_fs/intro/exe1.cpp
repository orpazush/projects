/* c++ intro 7. */
#include <malloc.h>
#include <iostream>
using namespace std;

int main()
{
    float *f = new float(12.6);


    delete f;
    f =  NULL;
    int i = 4;

    std::cout << "ldkfkclkkmd" << i << std :: endl;
    std::cin >> i;
    std::cerr << "ldkfkclkkmd\n" << i << endl;

    // f = new float[15];
    // f[3] = 8.88;
    // // f[1] = 3.333;
    // // cout << f[3] << endl;
    // // delete[] f;
    // //
    // // f = new float[0];
    // //
    // // delete[] f;
    // //
    // int *ptr = (int *)malloc(1000 * sizeof(int));
    // delete ptr;
    //
    // int *ptr2 = new int[50];
    // free(ptr2);

    return (0);
}
