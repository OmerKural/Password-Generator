#include <iostream>
#include <string>
#include <sstream>
#include <random>
#include <iterator>
#include <algorithm>
using namespace std;

vector<int> UI ()
{
    vector<int> selection;
    string in;

    // UI
    cout << "\nPlease select below packs and enter your selection. (Ex. 1 / 1 3)" << endl;
    cout << " | 1 - SYMBOLS ( ! ? * + ... )\n | 2 - DIGITS ( 1 2 3 4 ... )\n | 3 - CHARACTERS ( A B C a b c ... )" << endl;
    cout << "\nSelection -> ";
    getline(cin, in);

    for (int i = 0; i < in.size(); i++)
    {
        if (in[i] != ' ')
        {
            stringstream s;
            s << in[i];
            int n;
            s >> n;
            selection.push_back(n);
        }
    }
    return selection;
}

string generate_password(vector<int> selection)
{
    // ASCII Letters Dictionary
    pair<int, int> SYMBOLS1 = {33, 47};
    pair<int, int> SYMBOLS2 = {58, 64};
    pair<int, int> SYMBOLS3 = {91, 96};
    pair<int, int> SYMBOLS4 = {123, 126};
    pair<int, int> DIGITS = {48, 57};
    pair<int, int> ALPHA1 = {65, 90};
    pair<int, int> ALPHA2 = {97, 122};
    vector<pair<int, int>> selections;
    if (count(selection.begin(), selection.end(), 1))
    {
        selections.insert(selections.end(), {SYMBOLS1, SYMBOLS2, SYMBOLS3, SYMBOLS4});
    }
    if (count(selection.begin(), selection.end(), 2))
    {
        selections.insert(selections.end(), {DIGITS});
    }
    if (count(selection.begin(), selection.end(), 3))
    {
        selections.insert(selections.end(), {ALPHA1, ALPHA2});
    }

    // Defiing output string
    string password = "";
    
    // random integer generator start
    random_device rd;
    mt19937 gen(rd());


    // Adding random numbers to template XXXX-XXXX-XXXX-XXXX
    for (int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            int rand_num = rand() % selections.size();
            uniform_int_distribution<> distr(selections[rand_num].first, selections[rand_num].second);
            char c = distr(gen);
            while (c == '-')
            {
                rand_num = rand() % selections.size();
                uniform_int_distribution<> distr(selections[rand_num].first, selections[rand_num].second);
                c = distr(gen);
            }
            password += c;
        }
        password += '-';
    } password.pop_back();

    return password;
}

int main()
{
    string password = generate_password(UI());
    cout << "Generated Password -> " << password;
}