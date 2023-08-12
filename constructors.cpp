#include <iostream>
#include <string>
using namespace std;

class Painting {
    private:
        string name;
    public:
        // Painting(string s)
        // {
        //     setName(s);
        //     cout << getName() << endl;
        // } 
        void setName(string x)
        {
            name = x;
        } 
        string getName()
        {
            return name;
        }
        
};
int main() {
    string name;
    cin >> name;

    Painting painting;
    painting.setName(name);
    cout << painting.getName() << endl;

    return 0;
}