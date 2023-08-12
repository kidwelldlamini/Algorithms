#include <iostream>
using namespace std;

class SparseMatrix
{
public:
    SparseMatrix(int r, int c, int v)
    {
        row = r;
        column = c;
        value = v;
    }
    SparseMatrix Transpose();
private:
    int row;
    int column;
    int value;
};
int main()
{
    return 0;
}
