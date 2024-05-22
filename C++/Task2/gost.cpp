#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <algorithm>

using namespace std;
// решето эратосфена
vector<int> primes(int n);
int build_new_from_old(vector<int> prime, int bit);
int power_mod(int a, int b, int n);

int rn_int(int a, int b);
double rn_double(int a, int b);

void print_res(vector<int> res);

int main() {
    vector<int> prime = primes(500);

    int bit;
    cin >> bit;

    vector<int> res;
    while (res.size() != 10) {
        int p = build_new_from_old(prime, bit);

        if (find(res.begin(), res.end(), p) == res.end()) {
            res.push_back(p);
        }
    }

    print_res(res);
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
//Алгоритм перехода от меньшего простого числа к большему
int build_new_from_old(vector<int> prime, int bit) {
    int q;
    int max_index = 0;
    int p;

    for (; prime[max_index] < pow(2, bit / 2); max_index++);

    while (true) {
        q = prime[rn_int(0, max_index)];
        if (q > pow(2, (bit / 2) - 1) && q <= pow(2, bit / 2) - 1) break;
    }

    while (true) {
        double zakaruchka = rn_double(0, 1);
        double n = (pow(2, bit - 1) / q) + (pow(2, bit - 1) * zakaruchka / q);

        if ((int)n % 2 == 1) n++;

        for (int u = 0; true; u += 2) {
            p = (n + u) * q + 1;
            if (p > pow(2, bit)) break;

            if (power_mod(2, p - 1, p) == 1 && power_mod(2, n + u, p) != 1) return p;
        }
    }
}

int power_mod(int a, int b, int n) {
    int result = 1;
    while (b > 0) {
        if (b % 2 == 1)
            result = (result * a) % n;
        a = (a * a) % n;
        b /= 2;
    }
    return result;
}

int rn_int(int a, int b) {
    static mt19937 mt_rand(random_device{}());
    return uniform_int_distribution<int>(a, b)(mt_rand);
}

double rn_double(int a, int b) {
    static mt19937 mt_rand(random_device{}());
    return uniform_real_distribution<double>(a, b)(mt_rand);
}

void print_res(vector<int> res) {
    for (int i = 0; i < res.size(); i++) {
        cout << i + 1 << "\t\t" << "|" << "\t\t" << res[i] << endl;
    }
}
