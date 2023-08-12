#include <iostream>
#include <string>
using namespace std;


void winners(string customers[], int size, int N, int x)
{
    for(int i = 0; i < size; i++)
    {   
        if(N > (size - 1))
        {
            break;
        }
        cout << customers[N - 1] << endl;
        N = N + x;
    }
}
        
int main() {

    string customers[] = {"Alice", "Bob", "Rayan", "Emma", "Ann", "Bruce", "Synthia", "Daniel", "Richard", "Sam", "Nick", "Mary", "Paul"};

    int n;
    cin >> n;
    int x = n;
    winners(customers, 13, n, x);
    
    return 0;
}