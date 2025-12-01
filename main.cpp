#include <iostream>
#include <iomanip>
#include <random>
#include <sstream>
#include <vector>
#include <cstddef>
#include <filesystem>

#include "generator.h"
#include "runner.h"

int main() {
    const std::size_t OPS_PER_FILE = 300000;
    const int REPEATS = 5;

    std::random_device rd;
    std::mt19937 gen(rd());

    // A – розподіл за варіантом
    Distribution dist_a{
        0.05, // write0
        0.05, // write1
        0.40, // read0
        0.05, // read1
        0.45  // string
    };

    // B – рівномірний
    Distribution dist_b{
        0.20,
        0.20,
        0.20,
        0.20,
        0.20
    };

    // C – сильно невідповідний 
    Distribution dist_c{
        0.40,
        0.20,
        0.10,
        0.10,
        0.20
    };


	std::filesystem::path outDir = "res";
	// Створити папку, якщо її нема
	if (!std::filesystem::exists(outDir)) {
		std::filesystem::create_directory(outDir);
	}

	
    auto gen_for_case = [&](char id, const Distribution &dist) {
        for (int threads = 1; threads <= 3; ++threads) {
            for (int ti = 0; ti < threads; ++ti) {
                std::ostringstream oss;
                oss << outDir.string() << "/case_" << id
                    << "_thr" << threads
                    << "_t" << ti << ".txt";
                generate_file(oss.str(), OPS_PER_FILE, dist, gen);
            }
        }
    };	


    gen_for_case('A', dist_a);
    gen_for_case('B', dist_b);
    gen_for_case('C', dist_c);

    double results[3][3]{};

    // A
    {
        std::vector<std::string> f1 = { "res/case_A_thr1_t0.txt" };
        std::vector<std::string> f2 = { "res/case_A_thr2_t0.txt", "res/case_A_thr2_t1.txt" };
        std::vector<std::string> f3 = { "res/case_A_thr3_t0.txt", "res/case_A_thr3_t1.txt", "res/case_A_thr3_t2.txt" };

        results[0][0] = run_scenario("A", 1, f1, REPEATS);
        results[0][1] = run_scenario("A", 2, f2, REPEATS);
        results[0][2] = run_scenario("A", 3, f3, REPEATS);
    }

    // B
    {
        std::vector<std::string> f1 = { "res/case_B_thr1_t0.txt" };
        std::vector<std::string> f2 = { "res/case_B_thr2_t0.txt", "res/case_B_thr2_t1.txt" };
        std::vector<std::string> f3 = { "res/case_B_thr3_t0.txt", "res/case_B_thr3_t1.txt", "res/case_B_thr3_t2.txt" };

        results[1][0] = run_scenario("B", 1, f1, REPEATS);
        results[1][1] = run_scenario("B", 2, f2, REPEATS);
        results[1][2] = run_scenario("B", 3, f3, REPEATS);
    }

    // C
    {
        std::vector<std::string> f1 = { "res/case_C_thr1_t0.txt" };
        std::vector<std::string> f2 = { "res/case_C_thr2_t0.txt", "res/case_C_thr2_t1.txt" };
        std::vector<std::string> f3 = { "res/case_C_thr3_t0.txt", "res/case_C_thr3_t1.txt", "res/case_C_thr3_t2.txt" };

        results[2][0] = run_scenario("C", 1, f1, REPEATS);
        results[2][1] = run_scenario("C", 2, f2, REPEATS);
        results[2][2] = run_scenario("C", 3, f3, REPEATS);
    }

    std::cout << "Підсумкова таблиця (усереднений час, мс):\n\n";
    std::cout << "\t\t1 потік\t\t2 потоки\t3 потоки\n";

    const char* rowNames[3] = { "Сценарій A", "Сценарій B", "Сценарій C" };

    for (int i = 0; i < 3; ++i) {
        std::cout << std::setw(12) << rowNames[i];
        for (int j = 0; j < 3; ++j) {
            std::cout << "\t" << std::fixed << std::setprecision(1) << results[i][j] << "\t";
        }
        std::cout << "\n";
    }

    return 0;
}

