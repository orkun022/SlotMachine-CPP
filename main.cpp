// Virtual-credit terminal game. No money, accounts, or external services.
#include <array>
#include <charconv>
#include <cstdint>
#include <iostream>
#include <random>
#include <string>
#include <string_view>

bool parseUnsigned(std::string_view text, unsigned& value) {
    const auto result = std::from_chars(text.data(), text.data() + text.size(), value);
    return !text.empty() && result.ec == std::errc{} && result.ptr == text.data() + text.size();
}

int multiplier(const std::array<int, 3>& reels) {
    if (reels[0] == reels[1] && reels[1] == reels[2]) return 5;
    if (reels[0] == reels[1] || reels[1] == reels[2] || reels[0] == reels[2]) return 2;
    return 0;
}

int main(int argc, char* argv[]) {
    unsigned seed = std::random_device{}();
    if (argc == 2 && std::string_view(argv[1]) == "--help") {
        std::cout << "Usage: slot-machine [--seed unsigned-integer]\n"
                     "Start with 100 virtual credits. Bet 1-10 credits per spin.\n"
                     "Three matches return 5x the bet; two matches return 2x.\n"
                     "Returns include the stake. Enter q or EOF to quit.\n";
        return 0;
    }
    if (argc != 1 && (argc != 3 || std::string_view(argv[1]) != "--seed" || !parseUnsigned(argv[2], seed))) {
        std::cerr << "Invalid arguments. Use --help for usage.\n";
        return 2;
    }
    std::mt19937 engine(seed);
    std::uniform_int_distribution<int> symbol(0, 3);
    std::int64_t credits = 100;
    unsigned spins = 0;
    constexpr std::array<char, 4> symbols{'A', 'B', 'C', 'D'};
    std::cout << "\nSLOT MACHINE / C++17\n"
                 "100 virtual credits. No real money. Type q to quit.\n"
                 "Payouts (stake included): 3 matches = 5x, 2 matches = 2x.\n";
    std::string input;
    while (credits > 0 && spins < 10000) {
        std::cout << "\nBalance: " << credits << " | Bet 1-10 or q: " << std::flush;
        if (!std::getline(std::cin, input) || input == "q" || input == "Q") break;
        unsigned bet = 0;
        if (!parseUnsigned(input, bet) || bet < 1 || bet > 10 || bet > credits) {
            std::cout << "Enter a whole-number bet from 1 to 10 within your balance.\n";
            continue;
        }
        const std::array<int, 3> reels{symbol(engine), symbol(engine), symbol(engine)};
        const int factor = multiplier(reels);
        credits += static_cast<std::int64_t>(bet) * (factor - 1);
        ++spins;
        std::cout << "[ " << symbols[reels[0]] << " | " << symbols[reels[1]] << " | " << symbols[reels[2]] << " ]\n";
        if (factor > 0) std::cout << "Return: " << bet * factor << " credits\n";
        else std::cout << "No match this spin.\n";
    }
    std::cout << "\nSession complete. Spins: " << spins << " | Balance: " << credits << "\n";
}
