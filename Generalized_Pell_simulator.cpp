#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdint>
#include <vector>
#include <set>
#include <utility>
#include <string>
#include <random>
#include <algorithm>

using i128 = __int128_t;

// CSV-friendly i128 to string
std::string i128_to_string(i128 num) {
    if (num == 0) return "0";
    std::string digits;
    bool neg = false;
    if (num < 0) {
        neg = true;
        num = -num;
    }
    while (num > 0) {
        digits += '0' + num % 10;
        num /= 10;
    }
    if (neg) digits += '-';
    std::reverse(digits.begin(), digits.end());
    return digits;
}

bool isPerfectSquare(i128 val, int64_t& root_out) {
    if (val < 0) return false;
    int64_t root = int64_t(std::sqrt((double)val));
    if ((i128)root * root == val) {
        root_out = root;
        return true;
    }
    return false;
}

void solve_pell(int64_t n, int64_t& alpha, int64_t& beta) {
    int64_t A = 0, B = 1;
    double root = std::sqrt((double)n);
    int64_t a = int64_t(root);

    int64_t p_prev2 = 1, p_prev1 = a;
    int64_t q_prev2 = 0, q_prev1 = 1;

    if ((i128)p_prev1*p_prev1 - (i128)n*q_prev1*q_prev1 == 1) {
        alpha = p_prev1; beta = q_prev1; return;
    }

    while (true) {
        int64_t Anext = a * B - A;
        int64_t Bnext = (n - Anext * Anext) / B;
        double xnext = (root + Anext) / Bnext;
        int64_t anext = int64_t(std::floor(xnext));

        A = Anext; B = Bnext; a = anext;

        int64_t p_k = a * p_prev1 + p_prev2;
        int64_t q_k = a * q_prev1 + q_prev2;

        if ((i128)p_k*p_k - (i128)n*q_k*q_k == 1) {
            alpha = p_k; beta = q_k; return;
        }

        p_prev2 = p_prev1; p_prev1 = p_k;
        q_prev2 = q_prev1; q_prev1 = q_k;
    }
}

std::vector<std::pair<i128, i128>> generate_family(int64_t n, int64_t alpha, int64_t beta, i128 x0, i128 y0, int num_terms) {
    std::vector<std::pair<i128, i128>> family;
    i128 xk = x0, yk = y0;
    for (int k = 0; k < num_terms; ++k) {
        family.emplace_back(xk, yk);
        i128 next_x = alpha * xk + n * beta * yk;
        i128 next_y = beta * xk + alpha * yk;
        xk = next_x; yk = next_y;
    }
    return family;
}

std::random_device rd;
std::mt19937_64 gen(rd());

int64_t random_non_square(int64_t min, int64_t max) {
    std::uniform_int_distribution<int64_t> dist(min, max);
    while (true) {
        int64_t candidate = dist(gen);
        int64_t root = int64_t(std::sqrt(candidate));
        if (root * root != candidate) return candidate;
    }
}

int64_t random_integer(int64_t min, int64_t max) {
    std::uniform_int_distribution<int64_t> dist(min, max);
    return dist(gen);
}

int main() {
    const int trials = 500;
    const int64_t y_bound = 500;
    const int num_terms = 20;
    const int max_families = 15;

    std::ofstream csv("pell_data.csv");
    csv << "trial,n,N,alpha,beta,family,k,x,y\n";

    for (int trial = 1; trial <= trials; ++trial) {
        int64_t n = random_non_square(2, 100);
        int64_t N = random_integer(-100, 100);

        int64_t alpha, beta;
        solve_pell(n, alpha, beta);

        std::set<std::pair<i128, i128>> all_seen;
        int64_t tables = 0;
        bool found_any = false;

        for (int64_t y = 0; y <= y_bound; ++y) {
            i128 candidate = (i128)n * y * y + N;
            int64_t x_candidate;
            if (isPerfectSquare(candidate, x_candidate)) {
                if (x_candidate == 0 && y == 0) continue; // skip (0,0)

                auto family = generate_family(n, alpha, beta, x_candidate, y, num_terms);

                bool conflict = false;
                for (const auto& sol : family) {
                    if (all_seen.count(sol)) {
                        conflict = true;
                        break;
                    }
                }

                if (!conflict) {
                    ++tables;
                    found_any = true;
                    for (size_t k = 0; k < family.size(); ++k) {
                        csv << trial << "," << n << "," << N << ","
                            << alpha << "," << beta << ","
                            << tables << "," << k << ","
                            << i128_to_string(family[k].first) << ","
                            << i128_to_string(family[k].second) << "\n";

                        all_seen.insert(family[k]);
                    }
                }
                if (tables >= max_families) break;
            }
        }

        if (!found_any) {
            // Write the zero fallback row
            csv << trial << "," << n << "," << N << ","
                << alpha << "," << beta << ","
                << 0 << "," << 0 << ",0,0\n";
        }
    }

    csv.close();
    std::cout << "Dataset generation complete. Output written to pell_data.csv\n";

    return 0;
}
