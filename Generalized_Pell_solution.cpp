#include <iostream>
#include <cmath>
#include <cstdint>
#include <vector>
#include <set>
#include <utility>
#include <string>

using i128 = __int128_t;

// Pretty print for __int128
void print_i128(i128 num) {
    if (num == 0) { std::cout << "0"; return; }
    if (num < 0) { std::cout << "-"; num = -num; }
    std::string digits;
    while (num > 0) {
        digits += '0' + num % 10;
        num /= 10;
    }
    for (auto it = digits.rbegin(); it != digits.rend(); ++it)
        std::cout << *it;
}

// Check if perfect square
bool isPerfectSquare(i128 val, int64_t& root_out) {
    if (val < 0) return false;
    int64_t root = int64_t(std::sqrt((double)val));
    if ((i128)root * root == val) {
        root_out = root;
        return true;
    }
    return false;
}

// Solve x^2 - n y^2 = 1
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

// Generate a family of solutions from an initial solution
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

int main() {
    int64_t n, N, y_bound, num_terms, max_families;
    std::cout << "Enter non-square positive integer n: ";
    std::cin >> n;
    if (n <= 0 || std::floor(std::sqrt(n)) * std::floor(std::sqrt(n)) == n) {
        std::cerr << "n must be >0 and not a perfect square\n";
        return 1;
    }

    std::cout << "Enter integer N (for equation x^2 - n y^2 = N): ";
    std::cin >> N;
    std::cout << "Enter max y-bound to search for initial solutions: ";
    std::cin >> y_bound;
    std::cout << "Enter number of solutions to generate per family: ";
    std::cin >> num_terms;
    std::cout << "Enter number of distinct families you want: ";
    std::cin >> max_families;

    int64_t alpha, beta;
    solve_pell(n, alpha, beta);
    std::cout << "\nFundamental solution to x^2 - " << n << " y^2 = 1:\n";
    std::cout << "alpha = " << alpha << ", beta = " << beta << "\n";

    std::set<std::pair<i128, i128>> all_seen;
    int64_t tables = 0;

    for (int64_t y = 0; y <= y_bound; ++y) {
        i128 candidate = (i128)n * y * y + N;
        int64_t x_candidate;
        if (isPerfectSquare(candidate, x_candidate)) {
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
                std::cout << "\n========== TABLE " << tables << " (Initial guess: x=";
                print_i128(x_candidate);
                std::cout << ", y=" << y << ") ==========\n";

                for (size_t k = 0; k < family.size(); ++k) {
                    std::cout << "k=" << k << ": x = ";
                    print_i128(family[k].first);
                    std::cout << ", y = ";
                    print_i128(family[k].second);
                    std::cout << "\n";

                    all_seen.insert(family[k]);
                }
            }

            if (tables >= max_families) break;
        }
    }

    if (tables == 0) {
        std::cout << "No initial solutions found within the given y-bound.\n";
    } else {
        std::cout << "\nGenerated " << tables << " distinct families of solutions.\n";
    }

    return 0;
}
