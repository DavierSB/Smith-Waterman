#include<bits/stdc++.h>
using namespace std;

enum direction
{
    None = 0,
    Up = 1,
    Diag = 2,
    UpDiag = 3,
    Left = 4,
    UpLeft = 5,
    DiagLeft = 6,
    All = 7
};

direction operator|(direction left, direction right) {
    return static_cast<direction>(
        static_cast<std::underlying_type<direction>::type>(left) |
        static_cast<std::underlying_type<direction>::type>(right)
    );
}

class SWCalculator
{
    private:
    int n, m;
    string s1, s2;
    float** H;
    direction** D;
    void fill_matrix()
    {
        for (int i = 0; i < this->n; i++)
        {
            H[i][0] = 0;
            D[i][0] = None;
        }
        for (int i = 0; i < m; i++)
        {
            H[0][i] = 0;
            D[0][i] = None;
        }
        for (int i = 1; i < n; i++)
            for (int j = 1; j < m; j++)
                compute_cell(i, j);
    }
    void compute_cell(int i, int j)
    {
        H[i][j] = 0;
        D[i][j] = None;
        float temp = max(H[i - 1][j - 1] + this->similarity[make_pair(s1[i - 1], s2[j - 1])], H[i][j]);
        update_cell(temp, Diag, i, j);
        for (int k = 1; k <= i; k++)
        {
            temp = max(H[i - k][j] + this->gap_weight(k), H[i][j]);
            update_cell(temp, Up, i, j);
        }
        for (int k = 1; k <= j; k++)
        {
            temp = max(H[i][j - k] + this->gap_weight(k), H[i][j]);
            update_cell(temp, Left, i, j);    
        }
    }
    void update_cell(float new_value, direction new_direction, int i, int j)
    {
        if (new_value < H[i][j])return;
        if (new_value > H[i][j])
        {
            H[i][j] = new_value;
            D[i][j] = new_direction;
            return;
        }
        D[i][j] = D[i][j]|new_direction;
    }
    public:
    SWCalculator(map<pair<char, char>, float> similarity, function<float(int)> gap_weight)
    {
        this->similarity = similarity;
        this->gap_weight = gap_weight;
    }
    map<pair<char, char>, float> similarity;
    function<float(int)> gap_weight;
    void Alinear(string s1, string s2)
    {
        this->n = s1.size() + 1;
        this->m = s2.size() + 1;
        this->s1 = s1;
        this->s2 = s2;
        this->H = new float*[n];
        this->D = new direction*[n];
        for (int i = 0; i < n; i++)
        {
            H[i] = new float[m];
            D[i] = new direction[m];
        }
        fill_matrix();
        Print_Matrix();
    }
    void Print_Matrix()
    {
        cout<<"    ";
        for (int i = 0; i < m; i++)
            cout<<s2[i]<<"  ";
        cout<<"\n  __";
        for (int i = 0; i < m; i++)
            cout<<"__";
        cout<<"\n";
        for (int i = 1; i < n; i++)
        {
            cout<<s1[i - 1]<<"|  ";
            for (int j = 1; j < m; j++)
                cout<<H[i][j]<<"  ";
            cout<<"\n |\n";
        }
    }
};
int main()
{
    //Test_Case();
}
//Ahora pegue aqui el caso de prueba que desea ejecutar, de los que se encuentran en Test_Case.txt
//o elabore su propio caso de prueba.
