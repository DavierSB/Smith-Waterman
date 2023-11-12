#include<bits/stdc++.h>
using namespace std;

string GREEN = "\033[32m";
string RESET = "\033[0m";

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
    int** H;
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
        int temp = H[i - 1][j - 1] + this->similarity[make_pair(s1[i - 1], s2[j - 1])];
        update_cell(temp, Diag, i, j);
        for (int k = 1; k <= i; k++)
        {
            temp = H[i - k][j] + this->gap_weight(k);
            update_cell(temp, Up, i, j);
        }
        for (int k = 1; k <= j; k++)
        {
            temp = H[i][j - k] + this->gap_weight(k);
            update_cell(temp, Left, i, j);    
        }
    }
    void update_cell(int new_value, direction new_direction, int i, int j)
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
    void traceback()
    {
        reverse(GREEN.begin(), GREEN.end());
        reverse(RESET.begin(), RESET.end());
        vector<pair<int, int>> maximums = find_maximums();
        for (auto par : maximums)
        {
            string segmento1 = "";
            string segmento2 = "";
            for (int i = n-1; i >= par.first; i--)segmento1 += s1[i];
            for (int i = m-1; i >= par.second; i--)segmento2 += s2[i];
            segmento1 += RESET;
            segmento2 += RESET;
            traceback(par.first, par.second, segmento1, segmento2);
        }
    }
    void traceback (int i, int j, string segmento1, string segmento2)
    {
        if(H[i][j])
        {
            if (D[i][j] & Up)traceback(i - 1, j, segmento1 + s1[i - 1], segmento2 + "-");
            if (D[i][j] & Diag)traceback(i - 1, j - 1, segmento1 + s1[i - 1], segmento2 + s2[j - 1]);
            if (D[i][j] & Left)traceback(i, j - 1, segmento1 + "-", segmento2 + s2[j - 1]);
        }
        else print(i, j, segmento1, segmento2);
    }
    void print(int i, int j, string segmento1, string segmento2)
    {
        segmento1 += GREEN;
        segmento2 += GREEN;
        for (int k = i - 1; k >= 0; k--)segmento1 += s1[k];
        for (int k = j - 1; k >= 0; k--)segmento2 += s2[k];
        reverse(segmento1.begin(), segmento1.end());
        reverse(segmento2.begin(), segmento2.end());
        for (int k = i; k < j; k++)segmento1 = " " + segmento1;
        for (int k = j; k < i; k++)segmento2 = " " + segmento2;
        cout<<segmento1<<"\n"<<segmento2<<"\n";
        cout<<"\n\n";
    }
    vector<pair<int, int>> find_maximums()
    {
        vector<pair<int, int>> answer;
        int partial = 0;
        for (int i = 1; i < n; i++)
            for (int j = 1; j < m; j++)
            {
                if (H[i][j] > partial)
                {
                    partial = H[i][j];
                    answer = vector{make_pair(i, j)};
                    continue;
                }
                if (abs(partial - H[i][j]) == 0)
                    answer.push_back(make_pair(i, j));
            }
        return answer;
    }
    public:
    SWCalculator(map<pair<char, char>, int> similarity, function<int(int)> gap_weight)
    {
        this->similarity = similarity;
        this->gap_weight = gap_weight;
    }
    map<pair<char, char>, int> similarity;
    function<int(int)> gap_weight;
    void Alinear(string s1, string s2)
    {
        this->n = s1.size() + 1;
        this->m = s2.size() + 1;
        this->s1 = s1;
        this->s2 = s2;
        this->H = new int*[n];
        this->D = new direction*[n];
        for (int i = 0; i < n; i++)
        {
            H[i] = new int[m];
            D[i] = new direction[m];
        }
        fill_matrix();
        Print_Matrix();
        traceback();
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
                cout<<D[i][j]<<";"<<H[i][j]<<"  ";
            cout<<"\n |\n";
        }
    }
};
void Test_Case();
int main()
{
    //Por ahora esta cableado el caso de prueba de Wikipedia, pero ponga el q usted quiera
    Test_Case();
}
//Ahora pegue aqui el caso de prueba que desea ejecutar, de los que se encuentran en Test_Case.txt
//o elabore su propio caso de prueba.
int gap_weight_lineal(int k)
{
    return -3;
}
void Test_Case()
{
    string s1 = "GGTTGACTA";
    string s2 = "TGTTACGG";
    string aux = "ACGT";
    map<pair<char, char>, int> dict;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            dict[make_pair(aux[i], aux[j])] = (i == j)?3:-3;
    SWCalculator MySWCalculator = SWCalculator(dict, gap_weight_lineal);
    MySWCalculator.Alinear(s1, s2);
}