#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;
typedef vector<ll> vll;
typedef long double ld;
typedef unsigned long long ull;
typedef string str;
#define forn(i, start, end) for (ll i = start; i < end; ++i)
#define revforn(i, start, end) for (ll i = start; i > end; --i)
#define trav(x, a) for (auto &x : a)
#define ZERO(box) memset(box, 0, sizeof(box))
#define ZERO_N(box, n) memset(box, 0, n * sizeof(*box))
#define SET_ARR(box, val) memset(box, val, sizeof(box))
#define iallvec(vec) copy(istream_iterator<ll>(cin), istream_iterator<ll>(), back_inserter(vec))
#define iarr(arr, size) copy_n(istream_iterator<ll>(cin), size, begin(arr))
#define icharr(arr, size) copy_n(istream_iterator<char>(cin), size, begin(arr))
#define ovec(vec, delimiter) copy(begin(vec), end(vec), ostream_iterator<ll>(cout, delimiter))
#define oarr(arr, size, delimiter) copy_n(begin(arr), size, ostream_iterator<ll>(cout, delimiter))
#define ocharr(arr, size, delimiter) copy_n(begin(arr), size, ostream_iterator<char>(cout, delimiter))
#define beginend(a) begin(a), end(a)

template <class T>
bool ckmin(T &a, const T &b)
{
    return b < a ? a = b, 1 : 0;
}
template <class T>
bool ckmax(T &a, const T &b) { return a < b ? a = b, 1 : 0; }

std::random_device dev;
std::mt19937 rng(dev());
ll get_rand(const ll &l, const ll &r)
{
    assert(r >= l);
    std::uniform_int_distribution<std::mt19937::result_type> dist(l, r);
    return dist(rng);
}

// https://codeforces.com/blog/entry/62393
struct custom_hash
{
    static uint64_t splitmix64(uint64_t x)
    {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const
    {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

const ll mod = 1e9 + 7;
const ld eps = 1e-10;
const ld pi = acosl(-1.0);
const ll N = 1e6 + 4;
const ll inf = 1e18;

void replace_all(str &s, const str &from, const str &to)
{
    size_t br_pos;
    while (((br_pos = s.find(from)) != string::npos))
    {
        s.replace(br_pos, from.length(), to);
    }
}

int main()
{
    ifstream cin("input.txt");
    ofstream cout("output.txt");
    ofstream tableout("table_output.txt");
    str s;
    {
        str tmp_s;
        while (getline(cin, tmp_s))
            s += tmp_s;
    }
    size_t question_pos;
    ull question_num = 0;
    auto get_question_pos = [&]() -> bool
    {
        return ((question_pos = s.find("<span class=\"M7eMe\">")) != string::npos);
    };
    while (get_question_pos())
    {
        ull in_pos = string("<span class=\"M7eMe\">").length();
        s = s.substr(question_pos + in_pos);
        cout << question_num << ". ";
        str question = "";
        while (s.substr(0, string("</span>").length()) != "</span>")
        {
            question += s[0];
            s = s.substr(1);
        }
        replace_all(question, "<br>", "");
        replace_all(question, "</div>", "");
        replace_all(question, "<b>", "");
        replace_all(question, "<u>", "");
        replace_all(question, "<i>", "");
        replace_all(question, "</b>", "");
        replace_all(question, "</u>", "");
        replace_all(question, "</i>", "");
        replace_all(question, "<div>", "\n" + string(to_string(question_num).length() + 2, ' '));
        cout << question << '\n';
        tableout << question << '\t';

        size_t answer_pos;
        auto get_answer_pos = [&]() -> bool
        {
            if (!get_question_pos())
            {
                return (((answer_pos = s.find("class=\"aDTYNe snByac OvPDhc OIC90c\">")) != string::npos) && (in_pos = string("class=\"aDTYNe snByac OvPDhc OIC90c\">").length())) || // one answer
                       (((answer_pos = s.find("class=\"aDTYNe snByac n5vBHf OIC90c\">")) != string::npos) && (in_pos = string("class=\"aDTYNe snByac n5vBHf OIC90c\">").length())) || // multiple answers
                       (((answer_pos = s.find("<span jsslot class=\"vRMGwf oJeWuf\">")) != string::npos) && (in_pos = string("<span jsslot class=\"vRMGwf oJeWuf\">").length()));     // one answer from list
            }
            return ((((answer_pos = s.find("class=\"aDTYNe snByac OvPDhc OIC90c\">")) != string::npos) && (in_pos = string("class=\"aDTYNe snByac OvPDhc OIC90c\">").length())) && (answer_pos < question_pos)) || // one answer
                   ((((answer_pos = s.find("class=\"aDTYNe snByac n5vBHf OIC90c\">")) != string::npos) && (in_pos = string("class=\"aDTYNe snByac n5vBHf OIC90c\">").length())) && (answer_pos < question_pos)) || // multiple answers
                   ((((answer_pos = s.find("<span jsslot class=\"vRMGwf oJeWuf\">")) != string::npos) && (in_pos = string("<span jsslot class=\"vRMGwf oJeWuf\">").length())) && (answer_pos < question_pos));     // one answer from list
        };
        ll ans_num = 1;
        bool was_skip = false;
        while (get_answer_pos())
        {
            s = s.substr(answer_pos + in_pos);
            str answer = "";
            while (s.substr(0, string("</span>").length()) != "</span>")
            {
                answer += s[0];
                s = s.substr(1);
            }
            if (answer == "Выбрать" && (ans_num == 1) && !was_skip)
                was_skip = true;
            else
            {
                cout << "\t" << ans_num++ << ") ";
                cout << answer << '\n';
                tableout << (ans_num - 1) << ") " << answer << ' ';
            }
        }
        if (ans_num == 1)
        {
            cout << "I CAN'T PARSE ANY ANSWERS!!!" << '\n';
            tableout << "I CAN'T PARSE ANY ANSWERS!!!";
        }

        ++question_num;
        cout << '\n';
        tableout << '\n';
    }
    return 0;
}