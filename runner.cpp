#include "runner.h"

#include <iostream>
#include <thread>
#include <chrono>

#include "data2fields.h"
#include "commands.h"

static void worker_thread(Data2Fields &data, const std::vector<Command> &cmds) {
    for (const auto &c : cmds) {
        switch (c.op) {
            case OpType::Read:
                (void)data.get(c.field);
                break;
            case OpType::Write:
                data.set(c.field, c.value);
                break;
            case OpType::ToString:
                (void)std::string(data);
                break;
        }
    }
}

double run_scenario(
    const std::string &scenario_name,
    int num_threads,
    const std::vector<std::string> &files,
    int repeats
) {
    std::cout << "Сценарій: " << scenario_name
              << ", потоків: " << num_threads << std::endl;

    if ((int)files.size() != num_threads) {
        std::cerr << "run_scenario: files.size() != num_threads\n";
        return -1.0;
    }

    std::vector<std::vector<Command>> all_cmds;
    all_cmds.reserve(files.size());
    for (const auto &f : files) {
        all_cmds.push_back(load_commands(f));
    }

    double sum_ms = 0.0;

    for (int rep = 0; rep < repeats; ++rep) {
        Data2Fields data;

        auto start = std::chrono::steady_clock::now();

        std::vector<std::thread> threads;
        threads.reserve(num_threads);

        for (int i = 0; i < num_threads; ++i) {
            threads.emplace_back(worker_thread,
                                 std::ref(data),
                                 std::cref(all_cmds[i]));
        }

        for (auto &t : threads) {
            t.join();
        }

        auto end = std::chrono::steady_clock::now();
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        sum_ms += static_cast<double>(ms);
    }

    double avg_ms = sum_ms / repeats;
    std::cout << "Середній час: " << avg_ms << " ms\n\n";
    return avg_ms;
}

