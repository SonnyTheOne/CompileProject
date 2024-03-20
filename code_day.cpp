#include <bits/stdc++.h>
#define pb push_back
#define ll int
#define psl pair<string, int>
using namespace std;
const int N = 1e6 + 10;

struct Triple
{
    string name, type, cat;
};
struct WordsAnalyse
{
    string P[17] = {"0", "-", "/", "(", ")", "==", "<=", "<", "++", "*", ">", "=", ",", ";", "+", "{", "}"};
    string K[16] = {"0", "int", "void", "break", "float", "char", "while", "do", "struct", "const", "case", "for", "return", "if", "default", "else"};
    vector<psl> Token;
    vector<string> I;
    vector<string> C1;
    vector<string> C2;
    vector<char> CT;
    vector<string> ST;
    vector<Triple> synbol;
    string s;
    ll c1num, c2num, inum, ctnum, stnum;
    bool isnum(char ch) { return (ch >= '0' && ch <= '9') ? 1 : 0; }
    ll solve(string str)
    {
        if (2 < str.size() && str[1] == 'x')
        {
            ll out = 0;
            for (ll j = 2; j < str.size(); j++)
            {
                ll plus = str[j] - '0';
                if (str[j] <= 'e' && str[j] >= 'a')
                    plus = str[j] - 'a' + 10;
                out = out * 16 + plus;
            }
            return out;
        }
        ll res = 0;
        for (ll i = 0; i < str.size(); i++)
        {
            res = res * 10 + str[i] - '0';
        }
        return res;
    }
    void work()
    {
        ifstream inFile2("E:\\test.txt", ios::in);
        if (!inFile2)
        {
            cout << "open fail!";
        }
        c1num = c2num = inum = ctnum = stnum = 0;
        s = "";
        Token.clear();
        I.clear();
        C1.clear();
        C2.clear();
        CT.clear();
        ST.clear();
        s.clear();
        string str;
        while (getline(inFile2, str))
        {
            s += str;
        }
        ll len = s.size();
        bool error = 0;
        for (ll i = 0; i < len; i++)
        {
            if (s[i] == ' ')
                continue;
            bool ok = 0;
            for (ll j = 1; j <= 16; j++)
            { //界符表
                if (i + P[j].size() - 1 >= s.size())
                    continue;
                if (P[j] == s.substr(i, P[j].size()))
                {
                    ll tt = j;
                    Token.push_back(make_pair("P", tt));
                    ok = 1;
                    i += (P[j].size() - 1);
                    break;
                }
            }
            if (!ok)
            { //关键字表
                for (ll j = 1; j <= 15; j++)
                {
                    if (i + K[j].size() - 1 >= s.size())
                        continue;
                    if (K[j] == s.substr(i, K[j].size()))
                    {
                        Token.push_back(make_pair("K", j));
                        ok = 1;
                        i += (K[j].size() - 1);
                        break;
                    }
                }
            }
            if (!ok)
            { //字符常量
                if (s[i] == '\'' && i + 2 < s.size() && s[i + 2] == '\'' && s[i + 1] != '\\')
                {
                    ok = 1;
                    ll tar = ctnum, found = -1;
                    for (ll k = 0; k < CT.size(); k++)
                    {
                        if (s[i + 1] == CT[k])
                        {
                            found = k + 1;
                            break;
                        }
                    }
                    if (found == -1)
                    {
                        ctnum++;
                        tar++;
                    }
                    else
                        tar = found;
                    Token.push_back(make_pair("CT", tar));
                    if (found == -1)
                        CT.push_back(s[i + 1]);
                    i += 2;
                }
                else if (s[i] == '\'')
                {
                    error = 1;
                    break;
                }
            }
            if (!ok)
            { //字符串常量,ST
                vector<ll> tr;
                tr.clear();
                if (s[i] == '\"')
                {
                    string str = "";
                    ll j = i + 1, get = -1;
                    while (j < s.size())
                    {
                        if (s[j] == '\\')
                            tr.push_back(j);
                        else if (s[j] == '\"')
                            break;
                        j++;
                    }
                    if (j == s.size())
                    {
                        error = 1;
                        break;
                    }
                    ll tt = i + 1;
                    for (ll k = 0; k < tr.size(); k++)
                    {
                        ll aa = tr[k];
                        str += s.substr(tt, aa - tt);
                        tt = aa + 1;
                    }
                    str += s.substr(tt, j - tt);
                    ok = 1;
                    ll tar = stnum, found = -1;
                    for (ll k = 0; k < ST.size(); k++)
                    {
                        if (str == ST[k])
                        {
                            found = k + 1;
                            break;
                        }
                    }
                    if (found == -1)
                    {
                        stnum++;
                        tar++;
                    }
                    else
                        tar = found;
                    Token.push_back(make_pair("ST", tar));
                    if (found == -1)
                        ST.push_back(str);
                    i = j;
                }
            }
            if (!ok)
            {
                if (isnum(s[i]))
                { //常数表
                    if (s[i] == '0' && i + 1 < s.size() && s[i + 1] == 'x')
                    {
                        ll j = i + 2;
                        while (j < s.size() && (isnum(s[j]) || s[j] == 'a' || s[j] == 'b' || s[j] == 'c' || s[j] == 'd' || s[j] == 'e'))
                            j++;
                        if (j == i + 2)
                        {
                            error = 1;
                            break;
                        }
                        ll delta = j - i, found = -1;
                        string str = s.substr(i, delta);
                        for (ll k = 0; k < C1.size(); k++)
                        {
                            ll aa = solve(str), bb = solve(C1[k]);
                            if (aa == bb)
                            {
                                found = k + 1;
                                break;
                            }
                        }
                        ll tar = c1num;
                        if (found == -1)
                        {
                            c1num++;
                            tar++;
                        }
                        else
                            tar = found;
                        Token.push_back(make_pair("C1", tar));
                        if (found == -1)
                            C1.push_back(str);
                        i = j - 1;
                    }
                    else
                    {
                        bool dot = 0, E = 0;
                        ll j = i;
                        while (j < s.size())
                        {
                            if (isnum(s[j]))
                                j++;
                            else if (s[j] == '.')
                            {
                                if (dot == 0 && j + 1 < s.size() && isnum(s[j + 1]))
                                    dot = 1;
                                else
                                {
                                    error = 1;
                                    break;
                                }
                                j++;
                            }
                            else if ((s[j] == 'e'))
                            {
                                if (E == 0 && ((j + 2 < s.size() && (s[j + 1] == '+' || s[j + 1] == '-') && isnum(s[j + 2])) || j + 1 < s.size() && isnum(s[j + 1])))
                                    E = 1;
                                else
                                {
                                    error = 1;
                                    break;
                                }
                                j += 2;
                            }
                            else
                                break;
                        }
                        if (error)
                            break;
                        ll two = (E || dot), delta = j - i, found = -1;
                        string str = s.substr(i, delta);
                        if (two)
                        {
                            for (ll k = 0; k < C2.size(); k++)
                            {
                                if (str == C2[k])
                                {
                                    found = k + 1;
                                    break;
                                }
                            }
                            ll tar = c2num;
                            if (found == -1)
                            {
                                c2num++;
                                tar++;
                            }
                            else
                                tar = found;
                            Token.push_back(make_pair("C2", tar));
                            if (found == -1)
                                C2.push_back(str);
                            i = j - 1;
                        }
                        else
                        {
                            for (ll k = 0; k < C1.size(); k++)
                            {
                                ll aa = solve(C1[k]), bb = solve(str);
                                if (aa == bb)
                                {
                                    found = k + 1;
                                    break;
                                }
                            }
                            ll tar = c1num;
                            if (found == -1)
                            {
                                c1num++;
                                tar++;
                            }
                            else
                                tar = found;
                            Token.push_back(make_pair("C1", tar));
                            if (found == -1)
                                C1.push_back(str);
                            i = j - 1;
                        }
                    }
                }
                else
                { //标识符表
                    ll j = i;
                    while (j < s.size() && isalnum(s[j]))
                        j++;
                    ll delta = j - i, found = -1;
                    string str = s.substr(i, delta);
                    for (ll k = 0; k < I.size(); k++)
                    {
                        if (str == I[k])
                        {
                            found = k + 1;
                            break;
                        }
                    }
                    ll tar = inum;
                    if (found == -1)
                        inum++, tar++;
                    else
                        tar = found;
                    Token.push_back(make_pair("I", tar));
                    if (found == -1)
                        I.push_back(str);
                    i = j - 1;
                }
            }
        }
        if (error)
        {
            puts("ERROR");
        }
        else
        {
            cout << "Token :";
            for (ll i = 0; i < Token.size(); i++)
                cout << '(' << Token[i].first << ' ' << Token[i].second << ')';
            cout << endl;
            cout << "I :";
            for (ll i = 0; i < I.size(); i++)
            {
                if (i > 0)
                    cout << ' ';
                cout << I[i];
            }
            cout << endl;
            cout << "C1 :";
            for (ll i = 0; i < C1.size(); i++)
            {
                if (i > 0)
                    cout << ' ';
                cout << solve(C1[i]);
            }
            cout << endl;
            cout << "C2 :";
            for (ll i = 0; i < C2.size(); i++)
            {
                if (i > 0)
                    cout << ' ';
                cout << C2[i];
            }
            cout << endl;
            cout << "CT :";
            for (ll i = 0; i < CT.size(); i++)
            {
                if (i > 0)
                    cout << ' ';
                cout << CT[i];
            }
            cout << endl;
            cout << "ST :";
            for (ll i = 0; i < ST.size(); i++)
            {
                if (i > 0)
                    cout << ' ';
                cout << ST[i];
            }
        }
        for (int i = 1; i < Token.size(); i++)
        {
            string a = Token[i - 1].first;
            int b = Token[i - 1].second;
            string res = "";
            if (a == "I")
                res = I[b - 1];
            else if (a == "C1")
                res = C1[b - 1];
            else if (a == "C2")
                res = C2[b - 1];
            else if (a == "ST")
                res = ST[b - 1];
            else if (a == "CT")
            {
                res = " ";
                res[0] = CT[b - 1];
            }
            else if (a == "P")
                res = P[b];
            else if (a == "K")
                res = K[b];

            string aa = Token[i].first;
            int bb = Token[i].second;
            string ress = "";
            if (aa == "I")
                ress = I[bb - 1];
            else if (aa == "C1")
                ress = C1[bb - 1];
            else if (aa == "C2")
                ress = C2[bb - 1];
            else if (aa == "ST")
                ress = ST[bb - 1];
            else if (aa == "CT")
            {
                ress = " ";
                ress[0] = CT[bb - 1];
            }
            else if (aa == "P")
                ress = P[bb];
            else if (aa == "K")
                ress = K[bb];
            if (res == "int")
            {
                synbol.push_back((Triple){ress, "int", "v"});
            }
            else if (res == "char")
            {
                synbol.push_back((Triple){ress, "char", "v"});
            }
            else if (res == "float")
            {
                synbol.push_back((Triple){ress, "float", "v"});
            }
            if (aa == "C2")
            {
                synbol.push_back((Triple){ress, "float", "c"});
            }
            if (aa == "C1")
            {
                synbol.push_back((Triple){ress, "int", "c"});
            }
        }
    }
} cq;

struct Quaternion
{
    string a, b, c, d;
    int block;
    Quaternion(string aa, string bb, string cc, string dd, int idx)
    {
        a = aa;
        b = bb;
        c = cc;
        d = dd;
        block = idx;
    }
};

struct Grammar
{
    vector<string> names;
    set<int> Vt, Vn, Va;
    vector<pair<int, vector<int>>> Gram;
    vector<pair<int, vector<int>>> Gram1;
    set<int> Vnull;
    map<int, set<int>> First;
    map<int, set<int>> Follow;
    map<int, set<int>> Select;
    map<int, pair<int, set<int>>> L;
    stack<string> sem;
    stack<string> opr;
    vector<Quaternion> qt;
    int tcnt = 0;
    int bcnt = 0;
    int Id(string str);
    void Get_Set(set<int> &);
    void Get_Vn();
    void Get_Vt();
    void Get_Va();
    void Get_Gram();
    void Get_Vnull();
    bool Check_Vnull(vector<int> &);
    string num2str(int num);
    void Get_First();
    void Get_Follow();
    int find_Follow(vector<pair<bool, int>> k, int m, int n);
    void Calc_Select(int);
    void Get_Select();
    void Print_First();
    void Print_Follow();
    void Print_Select();
    void FFS_Out();
    void ll1();
    int Find_ll1(int x, int y);
    void PUSH(string str);
    int ll1_analysis();
};

ifstream inFile("E:\\gram_in.txt", ios::in);
ofstream outFile("E:\\gram_out.txt", ios::trunc);

void Grammar::Print_First()
{
    outFile << "First:" << endl;
    for (auto i : First)
    {
        outFile << names[i.first].c_str() << ':';
        for (auto j : i.second)
        {
            outFile << " " << names[j];
        }
        outFile << endl;
    }
    outFile << endl;
}

void Grammar::Print_Follow()
{
    outFile << "Follow:" << endl;
    for (auto i : Follow)
    {
        outFile << names[i.first].c_str() << ':';
        for (auto j : i.second)
        {
            outFile << " " << names[j];
        }
        outFile << endl;
    }
    outFile << endl;
}

void Grammar::Print_Select()
{
    outFile << "Select:" << endl;
    int num = 0;
    for (auto i : Select)
    {
        num++;
        outFile << num << ": ";
        pair<int, vector<int>> p = Gram[i.first];
        outFile << names[p.first].c_str() << ": ";
        for (auto x : p.second)
        {
            outFile << names[x].c_str() << ' ';
        }
        outFile << " [";
        for (auto j : i.second)
        {
            outFile << " " << names[j];
        }
        outFile << " ]" << endl;
    }
    outFile << endl;
}

int Grammar::Id(string str)
{
    for (int i = 0; i < names.size(); ++i)
    {
        if (names[i] == str)
        {
            return i;
        }
    }
    names.push_back(str);
    return names.size() - 1;
}

void Grammar::Get_Set(set<int> &Set)
{
    string str, line;
    getline(inFile, line, '\n');
    istringstream lin(line);
    while (getline(lin, str, ' '))
    {
        Set.insert(Id(str));
    }
}

void Grammar::Get_Vn()
{
    Get_Set(Vn);
}

void Grammar::Get_Vt()
{
    Get_Set(Vt);
}

void Grammar::Get_Va()
{
    Get_Set(Va);
}

void Grammar::Get_Gram()
{
    string line;
    while (getline(inFile, line, '\n'))
    {
        string str;
        int L;
        istringstream lin(line);
        getline(lin, str, '=');
        L = Id(str);
        vector<int> R, RR;
        while (getline(lin, str, ' '))
        {
            RR.push_back(Id(str));
            if (Va.count(Id(str)))
                continue;
            R.push_back(Id(str));
        }
        Gram.push_back({L, R});
        Gram1.push_back({L, RR});
    }
}

void Grammar::Get_Vnull()
{
    bool changing = true;
    while (changing)
    {
        changing = false;
        for (auto p : Gram)
        {
            vector<int> R = p.second;
            if (names[R[0]] == "~" && !Vnull.count(p.first))
            {
                Vnull.insert(p.first);
                changing = true;
            }
            else if (Check_Vnull(R) && !Vnull.count(p.first))
            {
                Vnull.insert(p.first);
                changing = true;
            }
        }
    }
}

bool Grammar::Check_Vnull(vector<int> &R)
{
    for (auto i : R)
    {
        if (!Vnull.count(i))
            return false;
    }
    return true;
}

void Grammar::Get_First()
{
    bool changing = true;
    while (changing)
    {
        changing = false;
        for (auto p : Gram)
        {
            vector<int> R = p.second;
            for (auto i : R)
            {
                if (Vt.count(i) || names[R[0]] == "~")
                {
                    if (!First[p.first].count(i))
                    {
                        First[p.first].insert(i);
                        changing = true;
                    }
                    break;
                }
                else if (Vn.count(i))
                {
                    for (auto vt : First[i])
                    {
                        if (!First[p.first].count(vt) && vt != (names.size() - 1))
                        {
                            changing = true;
                            First[p.first].insert(vt);
                        }
                    }
                    if (!Vnull.count(i))
                        break;
                }
            }
        }
    }
}

void Grammar::Get_Follow()
{
    vector<vector<int>> K;
    vector<int> temp;
    for (int i = 0; i < Vn.size(); i++)
        K.push_back(temp);
    Follow[0].insert(names.size() - 1);
    for (auto p : Gram)
    {
        vector<pair<bool, int>> k;
        vector<int> R = p.second;
        for (auto i : R)
        {
            if (Vn.count(i))
            {
                k.push_back({1, i});
            }
            else
            {
                k.push_back({0, i});
            }
        }
        for (int j = k.size() - 1; j >= 0; j--)
        {
            if (k[j].first)
            {
                int flag;
                flag = find_Follow(k, j, j);
                if (flag == 0 && k[j].second != p.first)
                {
                    K[k[j].second].push_back(p.first);
                }
            }
        }
    }
    int i = 2;
    while (i > 0)
    {
        for (int j = 0; j <= K.size() - 1; j++)
        {
            if (K[j].size() == 0)
                continue;
            for (auto p : Follow[K[j][0]])
            {
                if (!Follow[j].count(p))
                    Follow[j].insert(p);
                p++;
            }
        }
        i--;
    }
    for (i = 0; i < Vn.size(); i++)
    {
        if (Vnull.count(i))
            Follow[i].insert(names.size() - 1);
    }
}

int Grammar::find_Follow(vector<pair<bool, int>> k, int m, int n)
{
    if ((m + 1) == k.size())
    {
        return 0;
    }
    else if (k[m + 1].first)
    {
        for (auto p : First[k[m + 1].second])
        {
            if (!Follow[k[n].second].count(p) && p != (names.size() - 1))
            {
                Follow[k[n].second].insert(p);
            }
            else if (p == (names.size() - 1))
            {
                return find_Follow(k, m + 1, n);
            }
        }
        return 1;
    }
    else if (!k[m + 1].first)
    {
        if (!Follow[k[n].second].count(k[m + 1].second))
        {
            Follow[k[n].second].insert(k[m + 1].second);
        }
        return 1;
    }
}

void Grammar::Calc_Select(int i)
{
    pair<int, vector<int>> p = Gram[i];
    vector<int> R = p.second;
    for (auto j : R)
    {
        if (Vt.count(j))
        {
            Select[i].insert(j);
            return;
        }
        else if (Vn.count(j))
        {
            for (auto f : First[j])
            {
                if (f != names.size() - 1)
                    Select[i].insert(f);
            }
            if (!Vnull.count(j))
                return;
        }
    }
    for (auto f : Follow[p.first])
    {
        Select[i].insert(f);
    }
}

void Grammar::Get_Select()
{
    for (int i = 0; i < Gram.size(); ++i)
    {
        Calc_Select(i);
    }
}

void Grammar::FFS_Out()
{
    if (!inFile)
    {
        cout << "open fail!" << endl;
        exit(1);
    }
    Get_Vn();   //从文件录入非终止符集
    Get_Vt();   //从文件录入终止符集
    Get_Va();   //从文件录入语义动作集
    Get_Gram(); //从文件录入文法，储存进gram数组
    Get_Vnull();
    Get_First();    //计算First集
    Get_Follow();   //计算Follow集
    Get_Select();   //计算Select集
    Print_First();  //输出
    Print_Follow(); //输出
    Print_Select(); //输出
}
string Grammar::num2str(int num)
{
    stringstream ss;
    string ans_s;
    ss << num;
    ss >> ans_s;
    ans_s = ss.str();
    return ans_s;
}
void Grammar::ll1()
{
    outFile << "LL(1):" << endl;
    pair<int, set<int>> l;
    for (auto i : Select)
    {
        l.first = Gram[i.first].first;
        l.second = i.second;
        L.insert({i.first, l});
        for (auto p : L[i.first].second)
            outFile << "L(" << L[i.first].first << ',' << p << ")=" << i.first << endl;
    }
}
int Grammar::Find_ll1(int x, int y)
{
    int m = 0, flag = 0;
    while (!flag)
    {
        for (; L[m].first != x; m++)
        {
            if (m == L.size() - 1)
                return -1;
        }
        for (auto p : L[m].second)
        {
            if (p == y)
            {
                flag = 1;
                return m;
            }
        }
        m++;
    }
}
void push(int k[], int &top, int x)
{
    k[top + 1] = x;
    top++;
}
void Grammar::PUSH(string str) { sem.push(str); }
bool checkNum(string str)
{
    for (int i = 0; i < str.size(); i++)
    {
        if (str[i] < '0' || str[i] > '9')
            return 0;
    }
    return 1;
}
int now = -1;
string NextWord()
{
    ++now;

    psl tt = cq.Token[now];
    string a = tt.first;
    int b = tt.second;
    string res;
    if (a == "I")
        res = cq.I[b - 1];
    else if (a == "C1")
        res = cq.C1[b - 1];
    else if (a == "C2")
        res = cq.C2[b - 1];
    else if (a == "ST")
        res = cq.ST[b - 1];
    else if (a == "CT")
    {
        res = " ";
        res[0] = cq.CT[b - 1];
    }
    else if (a == "P")
        res = cq.P[b];
    else if (a == "K")
        res = cq.K[b];

    return res;
}
int Grammar::ll1_analysis()
{

    tcnt = 0;
    bcnt = 1;
    int x[200], top = -1, y, i, flag = 0, linenum = 0;
    push(x, top, 0);
    while (1)
    {
        if (now >= (int)cq.Token.size() - 1)
            break;
        string str = NextWord();
        if (!Vt.count(Id(str)) && str[0] > '9')
        {
            y = Id("i");
            names.erase(names.end());
        }
        else
        {
            y = Id(str);
        }
        flag = 0;
        while (!flag)
        {
            if (x[top] == y)
            {
                if ((y == Id("i") && str != "main") || checkNum(str))
                    PUSH(str);
                string sss = names[x[top]];
                if (sss == "+" || sss == "-" || sss == "*" || sss == "/" || sss == "=")
                    opr.push(sss);
                flag = 1;
                top--;
                break;
            }
            i = Find_ll1(x[top], y);
            if (i == -1)
            {
                if (Va.count(x[top]))
                { // cout << "ok" << endl;
                    //语义动作
                    string ss = names[x[top]];
                    if ((ss.size() >= 3 && ss.substr(0, 3) == "GEQ") || (ss.size() >= 4 && ss.substr(1, 3) == "GEQ"))
                    {
                        tcnt++;
                        string a1 = opr.top();
                        opr.pop();
                        string a3 = sem.top();
                        sem.pop();
                        string a2 = sem.top();
                        sem.pop();
                        string a4 = "t";
                        a4 += num2str(tcnt);
                        qt.push_back((Quaternion){a1, a2, a3, a4, bcnt});
                        PUSH(a4);
                    }
                    else if ((ss.size() >= 4 && ss.substr(0, 4) == "ASSI") || (ss.size() >= 5 && ss.substr(1, 4) == "ASSI"))
                    {
                        string a1 = opr.top();
                        opr.pop();
                        string a2 = sem.top();
                        sem.pop();
                        string a4 = sem.top();
                        sem.pop();
                        string a3 = "_";
                        qt.push_back((Quaternion){a1, a2, a3, a4, bcnt});
                    }
                    else if ((ss.size() >= 2 && ss.substr(0, 2) == "IF") || (ss.size() >= 2 && ss.substr(1, 2) == "IF"))
                    {
                        string a1 = "if";
                        string a2 = sem.top();
                        sem.pop();
                        string a3 = "_";
                        string a4 = "_";
                        qt.push_back((Quaternion){a1, a2, a3, a4, bcnt++});
                    }
                    else if ((ss.size() >= 2 && ss.substr(0, 2) == "EL") || (ss.size() >= 2 && ss.substr(1, 2) == "EL"))
                    {
                        string a1 = "el";
                        string a2 = "_";
                        string a3 = "_";
                        string a4 = "_";
                        qt.push_back((Quaternion){a1, a2, a3, a4, bcnt++});
                    }
                    else if ((ss.size() >= 2 && ss.substr(0, 2) == "IE") || (ss.size() >= 2 && ss.substr(1, 2) == "IE"))
                    {
                        string a1 = "ie";
                        string a2 = "_";
                        string a3 = "_";
                        string a4 = "_";
                        qt.push_back((Quaternion){a1, a2, a3, a4, bcnt++});
                    }
                    else if ((ss.size() >= 2 && ss.substr(0, 2) == "WH") || (ss.size() >= 2 && ss.substr(1, 2) == "WH"))
                    {
                        string a1 = "wh";
                        string a2 = "_";
                        string a3 = "_";
                        string a4 = "_";
                        qt.push_back((Quaternion){a1, a2, a3, a4, bcnt});
                    }
                    else if ((ss.size() >= 2 && ss.substr(0, 2) == "DO") || (ss.size() >= 2 && ss.substr(1, 2) == "DO"))
                    {
                        string a1 = "do";
                        string a2 = sem.top(); sem.pop();
                        string a3 = "_";
                        string a4 = "_";
                        qt.push_back((Quaternion){a1, a2, a3, a4, ++bcnt});
                    }
                    else if ((ss.size() >= 2 && ss.substr(0, 2) == "WE") || (ss.size() >= 2 && ss.substr(1, 2) == "WE"))
                    {
                        string a1 = "we";
                        string a2 = "_";
                        string a3 = "_";
                        string a4 = "_";
                        qt.push_back((Quaternion){a1, a2, a3, a4, bcnt++});
                    }
                    top--;
                    continue;
                }
                i = Find_ll1(x[top], names.size() - 1);
                if (i == -1)
                {
                    cout << "error!" << endl;
                    cout << "Expected " << names[x[top]] << endl;
                    cout << names[y];
                    exit(1);
                }
                else
                {
                    top--;
                    continue;
                }
            }
            top--;
            for (int j = Gram1[i].second.size() - 1; j >= 0; j--)
            {
                push(x, top, Gram1[i].second[j]);
            }
            if (x[top] == y)
            {
                if ((y == Id("i") && str != "main") || checkNum(str))
                    PUSH(str);
                string sss = names[x[top]];
                if (sss == "+" || sss == "-" || sss == "*" || sss == "/" || sss == "=")
                    opr.push(sss);
                if (sss == ">=" || sss == "==" || sss == "!=" || sss == "<=" || sss == ">" || sss == "<")
                    opr.push(sss);
                flag = 1;
                top--;
            }
            else if (x[top] == names.size() - 1)
            {
                top--;
            }
        }
    }
    cout << "分析成功，未发现错误!" << endl;
}

struct Node
{
    int id;
    int lson, rson;
    string opt;
    string val;
    list<string> same;
    Node()
    {
        same.clear();
        id = 0;
        lson = 0;
        rson = 0;
        val = "";
        opt = "";
    }
    Node(int idd, int lsonn, int rsonn, string vall, string op)
    {
        same.clear();
        
        id = idd;
        lson = lsonn;
        rson = rsonn;
        val = vall;
        opt = op;
    }
} node[N];
struct GetBetter
{
    int tot = 0;
    int bbcnt = 0;
    string num2str(int num)
    {
        stringstream ss;
        string ans_s;
        ss << num;
        ss >> ans_s;
        ans_s = ss.str();
        return ans_s;
    }
    bool isTwo(string op)
    {
        string tmp[10] = {"+", "-", "*", "/", "==", ">=", ">", "<", "<=", "!="};
        for (int i = 0; i < 10; i++)
        {
            if (op == tmp[i])
                return 1;
        }
        return 0;
    }
    map<string, vector<int>> showup; //在哪些编号的结点里出现了
    vector<Quaternion> QT;
    void PostOrder(int idx)
    {
        if (idx == 0)
            return;
        PostOrder(node[idx].lson);
        PostOrder(node[idx].rson);
        if (node[idx].opt == "")
        {
            node[idx].opt = "=";

            for (list<string>::iterator it = node[idx].same.begin(); it != node[idx].same.end(); it++)
            {
                string stt = *it;
                if (stt.size() < 1 || (!(stt[0] == 't' && stt[1] >= '0' && stt[1] <= '9')))
                    QT.push_back((Quaternion){node[idx].opt, node[idx].val, "_", stt, bbcnt});
            }
        }
        if (node[idx].opt != "=")
            QT.push_back((Quaternion){node[idx].opt, node[node[idx].lson].val, node[node[idx].rson].val, node[idx].val, bbcnt});
    }

    vector<Quaternion> solve(vector<Quaternion> qt)
    {
        vector<Quaternion> res; bbcnt = 1;
        for (int i = 0; i < qt.size(); i++)
        {//cout << "i is" << i << endl;
            if (qt[i].a == "if" || qt[i].a == "el" || qt[i].a == "ie" || qt[i].a == "wh" || qt[i].a == "do" || qt[i].a == "we")
            {
                for (int j = 1; j <= tot; j++)
                {
                    string u = node[j].val;
                    string tttt = "";
                    bool found = 0;
                    if (u.size() > 1 && u[0] == 't' && (u[1] >= '0' && u[1] <= '9'))
                    {
                        list<string>::iterator it;
                        for (it = node[j].same.begin(); it != node[j].same.end(); it++)
                        {
                            string v = *it;
                            if (v.size() < 1 || (!(v[0] == 't' && (v[1] >= '0' && v[1] <= '9'))))
                            {
                                found = 1;
                                tttt = *it;
                                break;
                            }
                        }
                        if (found)
                        {
                            node[j].same.remove(tttt);
                            node[j].val = tttt;
                            node[j].same.push_back(u);
                        }
                    }
                    found = 0;
                    u = node[j].val;
                    list<string>::iterator it;
                    for (it = node[j].same.begin(); it != node[j].same.end(); it++)
                    {
                        string v = *it;
                        if (checkNum(v))
                        {
                            found = 1;
                            tttt = *it;
                            break;
                        }
                    }
                    if (found)
                    {
                        node[j].same.remove(tttt);
                        node[j].val = tttt;
                        node[j].same.push_back(u);
                    }
                }
                PostOrder(tot);
                QT.push_back((Quaternion)qt[i]);
                bbcnt++;
                for(int j = 1; j <= tot; j++){
                    node[j] = {0, 0, 0, "", ""};
                    node[j].same.clear();
                }
                tot = 0;
                showup.clear();
                continue;
            }
            if (qt[i].a == "=")
            {
                if (showup[qt[i].b].size() == 0)
                {
                    ++tot;
                    node[tot] = {tot, 0, 0, qt[i].b, ""};
                    showup[qt[i].b].push_back(tot);
                }
                vector<int> ttt;
                ttt.clear();
                for (int i = 0; i < showup[qt[i].d].size(); i++)
                {
                    int idx = showup[qt[i].d][i];
                    if (qt[i].d != node[idx].val)
                    {
                        node[idx].same.remove(qt[i].d);
                    }
                    else
                        ttt.push_back(idx);
                }
                showup[qt[i].d] = ttt;
                showup[qt[i].d].push_back(showup[qt[i].b][showup[qt[i].b].size() - 1]);
                node[showup[qt[i].b][showup[qt[i].b].size() - 1]].same.push_back(qt[i].d);
            }
            else if (isTwo(qt[i].a))
            {
                if (showup[qt[i].b].size() == 0)
                {//cout << "check1" << endl;
                    ++tot;
                    //cout << tot << endl;
                    node[tot] = {tot, 0, 0, qt[i].b, ""};
                    //cout << "check3" << endl;
                    showup[qt[i].b].push_back(tot);
                }
                if (checkNum(qt[i].c) && checkNum(qt[i].b))
                {
                    int oo;
                    string opp = qt[i].a;
                    if (opp == "+")
                        oo = stoi(qt[i].c) + stoi(qt[i].b);
                    if (opp == "-")
                        oo = stoi(qt[i].c) - stoi(qt[i].b);
                    if (opp == "*")
                        oo = stoi(qt[i].c) * stoi(qt[i].b);
                    if (opp == "/")
                        oo = stoi(qt[i].c) / stoi(qt[i].b);
                    if (opp == "%")
                        oo = stoi(qt[i].c) % stoi(qt[i].b);
                    if (opp == ">")
                        oo = (stoi(qt[i].c) > stoi(qt[i].b));
                    if (opp == ">=")
                        oo = (stoi(qt[i].c) >= stoi(qt[i].b));
                    if (opp == "<")
                        oo = (stoi(qt[i].c) < stoi(qt[i].b));
                    if (opp == "<=")
                        oo = (stoi(qt[i].c) <= stoi(qt[i].b));
                    if (opp == "==")
                        oo = (stoi(qt[i].c) == stoi(qt[i].b));
                    if (opp == "!=")
                        oo = (stoi(qt[i].c) != stoi(qt[i].b));
                    string st = num2str(oo);
                    bool fff = 0;
                    for (int j = 1; j <= tot; j++)
                    {
                        if (node[j].val == st)
                        {
                            node[j].same.push_back(qt[i].d);
                            showup[qt[i].d].push_back(j);
                            fff = 1;
                        }
                    }
                    if (fff = 0)
                    {
                        ++tot;
                        node[tot] = {tot, 0, 0, st, ""};
                        showup[st].push_back(tot);
                        node[tot].same.push_back(qt[i].d);
                        showup[qt[i].d].push_back(tot);
                    }
                    for (int j = 1; j < tot; j++)
                    {
                        bool fff = 0;
                        list<string>::iterator it;
                        for (it = node[j].same.begin(); it != node[j].same.end(); it++)
                        {
                            if (*it == qt[i].d)
                            {
                                fff = 1;
                                break;
                            }
                        }
                        if (fff)
                            node[j].same.remove(qt[i].d);
                    }
                }
                else
                {//cout << "check2" << endl;
                    if (showup[qt[i].c].size() == 0)
                    {
                        ++tot;
                        node[tot] = {tot, 0, 0, qt[i].c, ""};
                        showup[qt[i].c].push_back(tot);
                    }
                    bool suc = 0;
                    for (int j = 1; j <= tot; j++)
                    {
                        if (node[j].opt == qt[i].a && node[node[j].lson].val == qt[i].b && node[node[j].rson].val == qt[i].c)
                        {
                            node[j].same.push_back(qt[i].d);
                            showup[qt[i].d].push_back(j);
                            suc = 1;
                            break;
                        }
                    }
                    if (suc == 0)
                    {
                        ++tot;
                        node[tot] = {tot, showup[qt[i].b][showup[qt[i].b].size() - 1], showup[qt[i].c][showup[qt[i].c].size() - 1], qt[i].d, qt[i].a};
                        showup[qt[i].d].push_back(tot);
                    }
                    for (int j = 0; j < showup[qt[i].d].size() - 1; j++)
                    {
                        int idx = showup[qt[i].d][j];
                        if (node[idx].val != qt[i].d)
                            node[idx].same.remove(qt[i].d);
                    }
                }
            }
        }
        for (int i = 1; i <= tot; i++)
        {
            string u = node[i].val;
            string tttt = "";
            bool found = 0;
            if (u.size() > 1 && u[0] == 't' && (u[1] >= '0' && u[1] <= '9'))
            {
                list<string>::iterator it;
                for (it = node[i].same.begin(); it != node[i].same.end(); it++)
                {
                    string v = *it;
                    if (v.size() < 1 || (!(v[0] == 't' && (v[1] >= '0' && v[1] <= '9'))))
                    {
                        found = 1;
                        tttt = *it;
                        break;
                    }
                }
                if (found)
                {
                    node[i].same.remove(tttt);
                    node[i].val = tttt;
                    node[i].same.push_back(u);
                }
            }
            found = 0;
            u = node[i].val;
            list<string>::iterator it;
            for (it = node[i].same.begin(); it != node[i].same.end(); it++)
            {
                string v = *it;
                if (checkNum(v))
                {
                    found = 1;
                    tttt = *it;
                    break;
                }
            }
            if (found)
            {
                node[i].same.remove(tttt);
                node[i].val = tttt;
                node[i].same.push_back(u);
            }
        }
        PostOrder(tot);
        res = QT;
        return res;
    }
};

struct QUA_active_information //四元式的活跃信息
{
    string data1;
    string data2;
    string ans;
    QUA_active_information(string a = "", string b = "", string c = "")
    {
        data1 = a;
        data2 = b;
        ans = c;
    }
};

struct R_active_information //寄存器活跃信息
{
    string name;
    string qua_act;
    R_active_information(string a = "", string b = "")
    {
        name = a;
        qua_act = b;
    }
};

struct Quaternion_evo //新四元式
{
    int block; //模块
    string op; //操作
    pair<string, int> data1;
    pair<string, int> data2;
    pair<string, int> ans;
    Quaternion_evo(int bl, string oopp, pair<string, int> a, pair<string, int> b, pair<string, int> c)
    {
        block = bl;
        op = oopp;
        data1 = a;
        data2 = b;
        ans = c;
    }
    Quaternion_evo() {}
};

int to_int(string s)
{
    int result = 0;
    int n = s.size();
    for (int i = 0; i < n; i++)
    {
        result = result * 10 + (s[i] - 48);
    }
    return result;
}

vector<vector<QUA_active_information>> Qua_act;
vector<vector<Quaternion>> Q;       //四元式
vector<vector<Quaternion_evo>> Qua; //新四元式
vector<vector<R_active_information>> R_act;
vector<string> targetcode;
stack<string> SEM; //保存地址

int IS_NORMAL(string pp)
{
    stringstream sin(pp);
    int t;
    if (!(sin >> t))
        return 0;
    return 1;
}

int IS_LIN(string pp)
{
    if (pp[0] == 't')
        return 1;
    return 0;
}

void Change_QUA()
{
    for (int i = 0; i < Q.size(); i++)
    {
        vector<Quaternion_evo> QEV;
        for (int j = 0; j < Q[i].size(); j++)
        {
            Quaternion_evo qq;
            qq.block = Q[i][j].block;
            string op = Q[i][j].a;
            string data1 = Q[i][j].b;
            string data2 = Q[i][j].c;
            string ans = Q[i][j].d;
            qq.op = op;
            qq.data1.first = data1;
            qq.data2.first = data2;
            qq.ans.first = ans;
            if (IS_NORMAL(data1))
                qq.data1.second = 2;
            else if (IS_LIN(data1))
                qq.data1.second = 1;
            else
                qq.data1.second = 0;
            if (IS_NORMAL(data2))
                qq.data2.second = 2;
            else if (IS_LIN(data2))
                qq.data2.second = 1;
            else
                qq.data2.second = 0;
            if (IS_NORMAL(ans))
                qq.ans.second = 2;
            else if (IS_LIN(ans))
                qq.ans.second = 1;
            else
                qq.ans.second = 0;
            QEV.push_back(qq);
        }
        Qua.push_back(QEV);
    }
}

bool IN_S_act(pair<string, int> data, vector<R_active_information> s_act)
{
    bool pp = 0;
    for (int i = 0; i < s_act.size(); i++)
    {
        if (data.first == s_act[i].name)
        {
            pp = 1;
            break;
        }
    }
    //	cout << pp;
    return pp;
}

void SET_QUA_ACT(vector<vector<Quaternion_evo>> qua)
{
    for (int i = 0; i < qua.size(); i++) //先建表，临时变量设X，非临时变量设y
    {
        vector<R_active_information> s_act;
        for (int j = 0; j < qua[i].size(); j++)
        {
            if (qua[i][j].data1.first != "_" && qua[i][j].data1.second != 2) // data1是变量
            {
                if (!IN_S_act(qua[i][j].data1, s_act)) //表中没有data1则新增一项
                {
                    //				    cout << qua[i][j].data1.first+" ";
                    if (qua[i][j].data1.second == 0) //非临时变量，设为y
                    {
                        R_active_information stri(qua[i][j].data1.first, "y");
                        s_act.push_back(stri);
                    }
                    else if (qua[i][j].data1.second == 1) //临时变量，则设n
                    {
                        R_active_information stri(qua[i][j].data1.first, "n");
                        s_act.push_back(stri);
                    }
                }
            }
            if (qua[i][j].data2.first != "_" && qua[i][j].data2.second != 2) //与data1相同的操作
            {
                //			    cout << qua[i][j].data2.first+" ";
                if (!IN_S_act(qua[i][j].data2, s_act))
                {
                    if (qua[i][j].data2.second == 0)
                    {
                        R_active_information stri(qua[i][j].data2.first, "y");
                        s_act.push_back(stri);
                    }
                    else if (qua[i][j].data2.second == 1)
                    {
                        R_active_information stri(qua[i][j].data2.first, "n");
                        s_act.push_back(stri);
                    }
                }
            }
            if (qua[i][j].ans.first != "_" && qua[i][j].ans.second != 2)
            {
                if (!IN_S_act(qua[i][j].ans, s_act))
                {
                    if (qua[i][j].ans.second == 0)
                    {
                        R_active_information stri(qua[i][j].ans.first, "y");
                        s_act.push_back(stri);
                    }
                    else if (qua[i][j].ans.second == 1)
                    {
                        R_active_information stri(qua[i][j].ans.first, "n");
                        s_act.push_back(stri);
                    }
                }
            }
        }
        R_act.push_back(s_act); //添加第i个模块的活跃信息表
    }

    for (int i = 0; i < Qua.size(); i++)
    {
        cout << "第" << i << "个基本块的活跃信息为：" << endl;
        for (int k = 0; k < R_act[i].size(); k++)
        {
            cout << "(" + R_act[i][k].name + "," + R_act[i][k].qua_act << ")" << endl;
        }
    }
    Qua_act.resize(Qua.size());
    for (int i = 0; i < Qua.size(); i++) //在四元式中添加活跃信息
    {
        Qua_act[i].resize(Qua[i].size());
        vector<QUA_active_information> qua_act;
        for (int j = Qua[i].size() - 1; j >= 0; j--) //从后往前
        {
            for (int k = 0; k < R_act[i].size(); k++)
            {
                if (qua[i][j].data1.first == R_act[i][k].name)
                {
                    Qua_act[i][j].data1 = R_act[i][k].qua_act;
                    R_act[i][k].qua_act = "y";
                }

                if (qua[i][j].data2.first == R_act[i][k].name)
                {
                    Qua_act[i][j].data2 = R_act[i][k].qua_act;
                    R_act[i][k].qua_act = "y";
                }

                if (qua[i][j].ans.first == R_act[i][k].name)
                {
                    Qua_act[i][j].ans = R_act[i][k].qua_act;
                    R_act[i][k].qua_act = "n";
                }
            }
        }
    }
    cout << "添加了活跃信息后的四元式：" << endl;
    for (int i = 0; i < (int)Qua.size(); i++)
    {
        cout << "第" << i << "个基本块：" << endl;
        for (int j = 0; j < (int)Qua_act[i].size(); j++)
        {
            cout << "(" + Qua[i][j].op + "," + Qua[i][j].data1.first;
            if (Qua[i][j].data1.first != "_" && Qua[i][j].data1.second != 2)
                cout << "(" + Qua_act[i][j].data1 + ")";
            cout << "," + Qua[i][j].data2.first;
            if (Qua[i][j].data2.first != "_" && Qua[i][j].data2.second != 2)
                cout << "(" + Qua_act[i][j].data2 + ")";
            cout << "," + Qua[i][j].ans.first;
            if (Qua[i][j].ans.first != "_" && Qua[i][j].ans.second != 2)
                cout << "(" + Qua_act[i][j].ans + ")";
            cout << ")" << endl;
        }
    }
}

void to_targetcode(vector<vector<Quaternion_evo>> qua, vector<vector<QUA_active_information>> qua_act) //目标代码生成
{
    int dizhi = 0; //地址
    for (int i = 0; i < qua.size(); i++)
    {

        R_active_information R("", ""); //新建寄存器描述表
        for (int j = 0; j < qua[i].size(); j++)
        {
            if (qua[i][j].op == "-" || qua[i][j].op == "/" || qua[i][j].op == ">" || qua[i][j].op == "<" || qua[i][j].op == ">=" || qua[i][j].op == "<=" || qua[i][j].op == "!=") //不可交换的双操作数
            {
                if (R.name == "") //寄存器空闲
                {
                    string stri1 = "\tMOV AL," + qua[i][j].data1.first;
                    R.name = qua[i][j].data1.first;
                    targetcode.push_back(stri1); //添加目标代码
                }
                else
                {
                    if (R.name != qua[i][j].data1.first) // data1不在寄存器中
                    {
                        string stri1, stri2;
                        if (R.qua_act == "y") //如果活跃则将其移出
                        {
                            stri1 = "\tMOV " + R.name + ",AL"; //先移出
                            targetcode.push_back(stri1);
                            stri2 = "\tMOV AL," + qua[i][j].data1.first;
                            targetcode.push_back(stri2);
                        }
                        else //如果不活跃则直接覆盖
                        {
                            string stri1 = "\tMOV AL," + qua[i][j].data1.first;
                            targetcode.push_back(stri1);
                        }
                    }
                }
                string stri2;
                R.qua_act = Qua_act[i][j].data1;
                if (qua[i][j].op == "-")
                {
                    stri2 = "\tSUB AL," + qua[i][j].data2.first;
                    targetcode.push_back(stri2);
                }
                else if (qua[i][j].op == "/")
                {
                    stri2 = "\tDIV " + qua[i][j].data2.first;
                    targetcode.push_back(stri2);
                    stri2 = "\tXOR AH,AH";
                    targetcode.push_back(stri2);
                }
                else if (qua[i][j].op == ">")
                {
                    stri2 = "\tSUB AL," + qua[i][j].data2.first;
                    targetcode.push_back(stri2);
                }
                else if (qua[i][j].op == "<")
                {
                    stri2 = "\tMOV " + R.name + ",AX"; //先移出
                    targetcode.push_back(stri2);
                    stri2 = "\tMOV AL," + qua[i][j].data2.first;
                    targetcode.push_back(stri2);
                    stri2 = "\tSUB AL," + qua[i][j].data1.first;
                    targetcode.push_back(stri2);
                }
                else if (qua[i][j].op == ">=")
                {
                    stri2 = "\tADD AL,1";
                    targetcode.push_back(stri2);
                    stri2 = "\tSUB AL," + qua[i][j].data2.first;
                    targetcode.push_back(stri2);
                }
                else if (qua[i][j].op == "<=")
                {
                    stri2 = "\tMOV " + R.name + ",AL"; //先移出
                    targetcode.push_back(stri2);
                    stri2 = "\tMOV AL," + qua[i][j].data2.first;
                    targetcode.push_back(stri2);
                    stri2 = "\tADD AL,1";
                    targetcode.push_back(stri2);
                    stri2 = "\tSUB AL," + qua[i][j].data1.first;
                    targetcode.push_back(stri2);
                }
                else if (qua[i][j].op == "!=")
                {
                    stri2 = "\tSUB AL," + qua[i][j].data2.first;
                    targetcode.push_back(stri2);
                    stri2 = "\tCMP AL,0";
                    targetcode.push_back(stri2);
                    stri2 = "\tJAE PARA"; //跳转
                    string res;           // int转string
                    stringstream ss;
                    ss << i;
                    ss >> res;
                    string stri_ad = "PARA" + res + "_";
                    stri2 = stri2 + res + "_";
                    ss << j;
                    ss >> res;
                    stri2 = stri2 + res;
                    stri_ad = stri_ad + res;
                    targetcode.push_back(stri2);
                    stri2 = "\tNOT AL";
                    targetcode.push_back(stri2);
                    stri2 = stri_ad + ":";
                    targetcode.push_back(stri2);
                }
                R.name = qua[i][j].ans.first;
                R.qua_act = Qua_act[i][j].ans; //修改寄存器描述表
            }
            else if (qua[i][j].op == "+" || qua[i][j].op == "*") //可交换操作
            {

                if (R.name != "" && R.name != qua[i][j].data1.first && R.name != qua[i][j].data2.first) //寄存器中没有操作数1和2
                {
                    if (R.qua_act == "y")
                    {
                        string stri1 = "\tMOV " + R.name + ",AL";
                        targetcode.push_back(stri1);
                    }
                }
                else
                {
                    string stri1, stri2;
                    if (R.name == qua[i][j].data1.first) //寄存器中是操作数1
                    {
                        R.qua_act = qua_act[i][j].data1;
                        if (R.qua_act == "y")
                        { //若data1活跃
                            stri1 = "\tMOV " + R.name + ",AL";
                            targetcode.push_back(stri1);
                            //                            targetcode.push_back(stri1+qua[i][j].data1.first);
                        }
                        if (qua[i][j].op == "*")
                            stri1 = "\tMUL ";
                        else if (qua[i][j].op == "+")
                            stri1 = "\tADD AL,";
                        targetcode.push_back(stri1 + qua[i][j].data2.first);
                    }
                    else if (R.name == qua[i][j].data2.first) //寄存器中是操作数2
                    {
                        R.qua_act = qua_act[i][j].data2;
                        if (R.qua_act == "y")
                        {
                            stri1 = "\tMOV " + R.name + ",AL";
                            targetcode.push_back(stri1);
                        }
                        if (qua[i][j].op == "*")
                            stri1 = "\tMUL ";
                        else if (qua[i][j].op == "+")
                            stri1 = "\tADD AL,";
                        targetcode.push_back(stri1 + qua[i][j].data1.first);
                    }
                    else //寄存器为空
                    {
                        stri1 = "\tMOV AL," + qua[i][j].data1.first;
                        targetcode.push_back(stri1);
                        if (qua[i][j].op == "*")
                            stri2 = "\tMUL ";
                        else if (qua[i][j].op == "+")
                            stri2 = "\tADD AL,";
                        targetcode.push_back(stri2 + qua[i][j].data2.first);
                    }
                }
                R.name = qua[i][j].ans.first;
                R.qua_act = qua_act[i][j].ans; //寄存器中保存运算结果
            }
            else if (qua[i][j].op == "=")
            {
                string stri1, stri2;
                if (R.name != qua[i][j].data1.first) //寄存器中不是当前操作数
                {
                    if (R.qua_act == "y")
                    {
                        stri1 = "\tMOV " + R.name + ",AL";
                        targetcode.push_back(stri1);
                    }
                    stri2 = "\tMOV AL," + qua[i][j].data1.first;
                    targetcode.push_back(stri2);
                }
                R.name = qua[i][j].ans.first; //寄存器信息更新为结果
                R.qua_act = qua_act[i][j].ans;
            }
            else if (qua[i][j].op == "if" || qua[i][j].op == "el" || qua[i][j].op == "ie")
            {
                if (qua[i][j].op == "if")
                    R.qua_act = qua_act[i][j].data1; //如果是if，直接将条件保存进寄存器
                if (R.qua_act == "y")
                {
                    targetcode.push_back("\tMOV " + R.name + ",AL");
                    R.qua_act = "n";
                } //如果活跃到下一模块就不活跃了
                string stri;
                if (qua[i][j].op == "if")
                {
                    stri = "\tCMP AL,0";
                    targetcode.push_back(stri);
                    stri = "\tJBE ";
                    string res; // int转string
                    stringstream ss;
                    ss << targetcode.size();
                    ss >> res;
                    stri = stri + "ELSE_" + res;
                    targetcode.push_back(stri);
                }
                else if (qua[i][j].op == "el")
                {
                    stri = "\tJMP ";
                    string res; // int转string
                    stringstream ss;
                    ss << targetcode.size() + 1;
                    ss >> res;
                    stri = stri + "OUT_" + res;
                    targetcode.push_back(stri);
                    stri = "ELSE_" + SEM.top() + ":";
                    targetcode.push_back(stri);
                }
                if (qua[i][j].op == "ie")
                {
                    stri = "OUT_" + SEM.top() + ":";
                    targetcode.push_back(stri);
                }
                else
                {
                    string res;
                    stringstream ss;
                    ss << targetcode.size() - 1;
                    ss >> res;
                    SEM.push(res);
                }
            }
            else if (qua[i][j].op == "wh" || qua[i][j].op == "do" || qua[i][j].op == "we")
            {
                if (qua[i][j].op == "do")
                    R.qua_act = qua_act[i][j].data1; //如果是do，直接将条件保存进寄存器
                if (R.qua_act == "y")
                {
                    targetcode.push_back("\tMOV " + R.name + ",AL");
                    R.qua_act = "n";
                }
                string stri;
                if (qua[i][j].op == "wh")
                {
                    dizhi = targetcode.size();
                    string res; // int转string
                    stringstream ss;
                    ss << dizhi;
                    ss >> res;
                    stri = "WHILE_" + res + ":";
                    targetcode.push_back(stri);
                }
                else if (qua[i][j].op == "do")
                {
                    stri = "\tCMP AL,0";
                    targetcode.push_back(stri);
                    stri = "\tJBE ";
                    string res; // int转string
                    stringstream ss;
                    ss << targetcode.size();
                    ss >> res;
                    SEM.push(res);
                    stri = stri + "OUT_" + res;
                    targetcode.push_back(stri);
                }
                else if (qua[i][j].op == "we")
                {
                    string res;
                    stringstream ss;
                    ss << dizhi;
                    ss >> res;
                    stri = "\tJMP WHILE_" + res;
                    targetcode.push_back(stri);
                    stri = "OUT_" + SEM.top() + ":";
                    targetcode.push_back(stri);
                }
            }
        }
        if (R.qua_act == "y")
        {
            targetcode.push_back("\tMOV " + R.name + ",AL");
        }
    }
    vector<string> vari;
    for (int i = 0; i < qua.size(); i++)
    {
        for (int j = 0; j < qua[i].size(); j++)
        {
            int n = vari.size();
            int have1 = 0, have2 = 0, have3 = 0;
            for (int p = 0; p < n; p++)
            {
                if (have1 && have2 && have3)
                    break;
                if (qua[i][j].data1.first == vari[p])
                {
                    have1 = 1;
                }
                if (qua[i][j].data2.first == vari[p])
                {
                    have2 = 1;
                }
                if (qua[i][j].ans.first == vari[p])
                {
                    have3 = 1;
                }
            }
            if (!have1 && qua[i][j].data1.second != 2 && qua[i][j].data1.first != "_")
            {
                vari.push_back(qua[i][j].data1.first);
                n++;
            }
            if (!have2 && qua[i][j].data2.second != 2 && qua[i][j].data2.first != "_")
            {
                vari.push_back(qua[i][j].data2.first);
                n++;
            }
            if (!have3 && qua[i][j].ans.second != 2 && qua[i][j].ans.first != "_")
            {
                vari.push_back(qua[i][j].ans.first);
                n++;
            }
        }
    }
    ofstream out("D:\\Desktop\\target_huibian\\tar.asm");
    cout << "目标代码为" << endl;
    cout << "DSEG SEGMENT" << endl;
    out << "DSEG SEGMENT" << endl;
    for (int i = 0; i < vari.size(); i++)
    {
        cout << "\t" << vari[i] << " DB 4 DUP(0)" << endl;
        out << "\t" << vari[i] << " DB 4 DUP(0)" << endl;
    }
    cout << "DSEG ENDS" << endl;
    cout << "CSEG SEGMENT" << endl;
    cout << "\t"
         << "ASSUME CS:CSEG,DS:DSEG" << endl;
    cout << "START:" << endl;
    out << "DSEG ENDS" << endl;
    out << "CSEG SEGMENT" << endl;
    out << "\t"
        << "ASSUME CS:CSEG,DS:DSEG" << endl;
    out << "START:" << endl;
    for (int i = 0; i < targetcode.size(); i++)
    {
        cout << targetcode[i] << endl;
        out << targetcode[i] << endl;
    }
    cout << "\tINT 21H" << endl
         << "\tRET" << endl;
    cout << "CSEG ENDS" << endl;
    cout << "\t"
         << "END START" << endl;
    out << "\tINT 21H" << endl
        << "\tRET" << endl;
    out << "CSEG ENDS" << endl;
    out << "\t"
        << "END START" << endl;
}
void TAR_run() //用来被主函数调用的函数
{
    Change_QUA();
    SET_QUA_ACT(Qua);
    to_targetcode(Qua, Qua_act);
}
void Add_qua()
{
    vector<Quaternion> QQ0, QQ1, QQ2, QQ3, QQ4, QQ5;
    string data_a = "a";
    string data_b = "b";
    string data_c = "c";
    string data_d = "d";
    string data_t1 = "t1";
    string data_t2 = "t2";
    string data_t3 = "t3";
    string data_t4 = "t4";
    string data_t5 = "t5";
    string data_2 = "2";
    string data_7 = "7";
    string data_5 = "5";
    string data_x = "x";
    string data_void = "_";
    Quaternion quaternion1("=", data_7, data_void, data_c, 0);         //(=,7,,c)
    Quaternion quaternion2("=", data_2, data_void, data_a, 0);         //(=,2,,a)
    Quaternion quaternion3("=", data_5, data_void, data_b, 0);         //(=,5,,b)
    Quaternion quaternion4("!=", data_a, data_b, data_t1, 0);          //(!=,a,b,t1)
    Quaternion quaternion5("if", data_t1, data_void, data_void, 0);    //(if,t1,,)
    Quaternion quaternion6("+", data_a, data_b, data_t2, 1);           //(+,a,b,t2)
    Quaternion quaternion7("*", data_t2, data_c, data_x, 1);           //(*,t2,c,x)
    Quaternion quaternion8("el", data_void, data_void, data_void, 1);  //(el,,,)
    Quaternion quaternion9("*", data_a, data_b, data_t3, 2);           //(*,a,b,t3)
    Quaternion quaternion10("-", data_5, data_t3, data_x, 2);          //(-,5,t3,x)
    Quaternion quaternion11("ie", data_void, data_void, data_void, 2); //(ie,,,)
    Quaternion quaternion12("wh", data_void, data_void, data_void, 3); //(wh,,,)
    Quaternion quaternion13(">", data_a, data_b, data_t1, 3);          //(>,a,b,t1)
    Quaternion quaternion14("do", data_t1, data_void, data_void, 3);   //(do,t1,,)
    Quaternion quaternion15("+", data_a, data_b, data_t2, 4);          //(*,a,b,t2)
    Quaternion quaternion16("*", data_t2, data_c, data_x, 4);          //(*,t2,c,x)
    Quaternion quaternion17("we", data_void, data_void, data_void, 5); //(we,,,)
    /*
    int a=2;
    int b=5;
    if(a!=b){
        x=(a+b)*c;
    }
    else{
        x=a*b-5;
    }
    int c=7;
    while(a>b){
        x=(a+b)*c;
    }
    */
    QQ0.push_back(quaternion2);
    QQ0.push_back(quaternion3);
    QQ0.push_back(quaternion4);
    QQ0.push_back(quaternion5);
    QQ1.push_back(quaternion6);
    QQ1.push_back(quaternion7);
    QQ1.push_back(quaternion8);
    QQ2.push_back(quaternion9);
    QQ2.push_back(quaternion10);
    QQ2.push_back(quaternion11);
    QQ2.push_back(quaternion1);
    QQ3.push_back(quaternion12);
    QQ3.push_back(quaternion13);
    QQ3.push_back(quaternion14);
    QQ4.push_back(quaternion15);
    QQ4.push_back(quaternion16);
    QQ5.push_back(quaternion17);
    Q.push_back(QQ0);
    Q.push_back(QQ1);
    Q.push_back(QQ2);
    Q.push_back(QQ3);
    Q.push_back(QQ4);
    Q.push_back(QQ5);
    cout << "四元式为：" << endl;
    for (int i = 0; i < Q.size(); i++)
    {
        cout << "第" << i << "个基本块：" << endl;
        for (int j = 0; j < Q[i].size(); j++)
        {
            cout << "(" + Q[i][j].a + "," + Q[i][j].b + "," + Q[i][j].c + "," + Q[i][j].d + ")" << endl;
        }
    }
}

int main()
{
    cout << endl; cout << endl; cout << endl;
    cout << "-------词法分析处理结果-------" << endl;
    cq.work();
    cout << endl;
    struct Grammar gram;
    cout << endl;
    cout << "-------语法分析处理结果-------" << endl;
    gram.FFS_Out();
    gram.ll1();
    gram.ll1_analysis();
    cout << endl;
    cout << "-------语义分析处理结果-------" << endl;
    for (int i = 0; i < gram.qt.size(); i++)
    {
        cout << gram.qt[i].a << ' ' << gram.qt[i].b << ' ' << gram.qt[i].c << ' ' << gram.qt[i].d << endl;
    }
    int q = 1;
    vector<Quaternion> pp;
    for (int i = 0; i < gram.qt.size(); i++)
    {
        if (gram.qt[i].block > q)
        {
            q++;
            Q.push_back(pp);
            pp.clear();
        }
        pp.push_back(gram.qt[i]);
    }
    Q.push_back(pp);
    cout << endl;
    cout << "-------优化处理结果-------" << endl;
    GetBetter gb;
    vector<Quaternion> t = gb.solve(gram.qt);
    for (int i = 0; i < t.size(); i++)
    {
        cout << t[i].a << ' ' << t[i].b << ' ' << t[i].c << ' ' << t[i].d << endl;
    }
    cout << endl;
    cout << "-------目标代码生成结果-------" << endl;
    TAR_run();
   
}
