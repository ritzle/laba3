#include <iostream>
#include <vector>
#include <tuple>
#include <cmath>
#include <random>
#include <limits>
#include <algorithm>

using namespace std;

vector<int> primes(int n);
pair<int, vector<int>> builder_test(vector<int> prime, int bit);
int test_poklin(int n, int t, vector<int> q);

int power_mod(int a, int b, int n);
int rn(int a, int b);

void print_results(const vector<int>& res, const vector<string>& res_ver_test, const vector<int>& otvegnutie);

int main() {
    int size_primes = 500;
    vector<int> prime = primes(size_primes);

    int bit = 0;
    cin >> bit;

    vector<int> q;
    int n;
    int k = 0;
    int probability;

    vector<int> res;
    vector<string> res_ver_test;
    vector<int> otvegnutie;



    while(res.size() != 10) {
        tie(n, q) = builder_test(prime, bit);
        probability = test_poklin(n, 10, q);

        if(probability == 1) {
            if (find(res.begin(), res.end(), n) == res.end()) {
                res.push_back(n);

                probability = test_poklin(n, 1, q);
                if(probability == 1) {
                    res_ver_test.push_back("+");
                }

                else{
                    res_ver_test.push_back("-");
                }

                otvegnutie.push_back(k);
                k = 0;
            }
        }

        else{
            k++;
        }
    }

    print_results(res, res_ver_test, otvegnutie);
}

vector<int> primes(int n) {
    vector<bool> is_prime(n + 1, true);
    vector<int> primes;

    for (int p = 2; p * p <= n; ++p) {
        if (is_prime[p]) {
            for (int i = p * p; i <= n; i += p)
                is_prime[i] = false;
        }
    }

    for (int p = 2; p <= n; ++p) {
        if (is_prime[p])
            primes.push_back(p);
    }

    return primes;
}

pair<int, vector<int>> builder_test(vector<int> prime, int bit) {
    int max_index = 0;
    int max_pow = 1;
// число ф должно содержать 6 бит
    for (; (prime[max_index] < pow(2, (bit / 2) + 1)) && (max_index < prime.size()); max_index++);
    for (; pow(2, max_pow) < pow(2, (bit / 2) + 1); max_pow++);
    
    int f = 1;
    vector<int> q;

    while(true){
        int num = rn(0, max_index);
        int power = rn(1, max_pow);
        
        if (pow(prime[num], power)) {
            if(f * pow(prime[num], power) < INT32_MAX) {
                f *= pow(prime[num], power);
                q.push_back(prime[num]);
            }
        }

        if(f > pow(2, (bit / 2))){

            if(f >= pow(2, (bit / 2) + 1)){
                f = 1;
                q.clear();
            }
            
            else{
                break;
            }
        }
    }

    int R;

    do
    {
        R = rn(pow(2, (bit / 2) - 1) + 1, pow(2, bit / 2));
    } while (R % 2 != 0);

    int n = R * f + 1;
    return make_pair(n, q);
}

int test_poklin(int n, int t, vector<int> q) {
    vector<int> a;
    int aj;

    while (a.size() != t) {
        aj = rn(2, n - 1);

        if (find(a.begin(), a.end(), aj) == a.end()) {
            a.push_back(aj);
        }
    }

    for (int aj : a) {
        if (power_mod(aj, n - 1, n) != 1) {
            return 0;
            break;
        }
    }

    bool flag = true;
    int i = 0;
    for (int aj : a) {
        if (q[i] != 0 && power_mod(aj, (n - 1) / q[i], n) == 1) {
            flag = false;

            return 0;
            break;
        }
    }

    if (flag) {
        return 1;
    }

    return 1;
}

int power_mod(int a, int b, int n) {
    long long result = 1;
    while (b > 0) {
        if (b % 2 == 1)
            result = (result * a) % n;
        a = (a * a) % n;
        b /= 2;
    }
    return result;
}

int rn(int a, int b) {
    mt19937 mt_rand(random_device{}());
    return uniform_int_distribution<int>(a, b)(mt_rand);
}

void print_results(const vector<int>& res, const vector<string>& res_ver_test, const vector<int>& otvegnutie) {
    cout << "Prime Numbers\tTest Results\tOccurrences" << endl;
    cout << "----------------------------------------------" << endl;

    for (size_t i = 0; i < res.size(); ++i) {
        cout << res[i] << "\t\t" << res_ver_test[i] << "\t\t" << otvegnutie[i] << endl;
    }
}
