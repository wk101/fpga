#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <thread>

struct MarketData {
    double midPrice; // Use mid price for trading
};

// Function to generate random price movement
double generatePrice(double previousPrice) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-0.5, 0.5); // Price change range (-0.5 to +0.5)
    return previousPrice + dis(gen);
}

// Function to buy a quantity of a symbol
void buy(std::vector<double>& positions, double price, int quantity) {
    positions[0] += quantity; // Symbol ID 1 corresponds to index 0
    std::cout << "Buy Order - Symbol ID: 1 | Quantity: " << quantity << " | Price: " << price << "\n";
}

// Function to sell a quantity of a symbol
void sell(std::vector<double>& positions, double price, int quantity) {
    positions[1] -= quantity; // Symbol ID 2 corresponds to index 1
    std::cout << "Sell Order - Symbol ID: 2 | Quantity: " << quantity << " | Price: " << price << "\n";
}

// Function to calculate PNL for a position based on the current mid price
double calculatePNL(double positionQuantity, double midPrice) {
    return positionQuantity * (midPrice - 100.0); // Assume initial price was 100.0 for simplicity
}

int main() {
    const double initialPrice = 100.0;

    std::vector<MarketData> marketData(2); // Data for 2 crypto symbols

    // Initialize market data for each crypto symbol
    marketData[0].midPrice = initialPrice; // Symbol ID 1 corresponds to index 0
    marketData[1].midPrice = initialPrice; // Symbol ID 2 corresponds to index 1

    std::vector<double> positionsSymbol1(1, 0.0); // Vector to keep track of positions for symbol 1
    std::vector<double> positionsSymbol2(1, 0.0); // Vector to keep track of positions for symbol 2

    // Generate fake market data every half second for 30 seconds (reduce for faster testing)
    for (int i = 0; i < 60; ++i) {
        std::cout << "Updating Market Data - Second " << (i + 1) << "\n";
        for (int symbolId = 1; symbolId <= 2; ++symbolId) {
            MarketData& data = marketData[symbolId - 1]; // Adjust the index to access the correct symbol's data
            data.midPrice = generatePrice(data.midPrice);

            // Buy and sell randomly
            double price = data.midPrice;
            int quantity = 100; // For simplicity, assume fixed quantity

            // Randomly decide to buy or sell
            if (std::rand() % 2 == 0) {
                if (symbolId == 1) {
                    buy(positionsSymbol1, price, quantity);
                } else if (symbolId == 2) {
                    buy(positionsSymbol2, price, quantity);
                }
            } else {
                if (symbolId == 1) {
                    sell(positionsSymbol1, price, quantity);
                } else if (symbolId == 2) {
                    sell(positionsSymbol2, price, quantity);
                }
            }
        }

        if ((i + 1) % 10 == 0) {
            // Close positions and calculate PNL every 10 seconds
            std::cout << "Closing Positions - Second " << (i + 1) << "\n";
            double totalPNL = 0.0;

            // Calculate PNL for each symbol and reset positions
            double pnlSymbol1 = calculatePNL(positionsSymbol1[0], marketData[0].midPrice);
            double pnlSymbol2 = calculatePNL(positionsSymbol2[0], marketData[1].midPrice);

            // Add the positions for both symbols together to get the overall position
            double totalPosition = positionsSymbol1[0] + positionsSymbol2[0];

            totalPNL = pnlSymbol1 + pnlSymbol2;
            std::cout << "Position Symbol ID: 1 | Quantity: " << positionsSymbol1[0] << " | PNL: " << pnlSymbol1 << "\n";
            std::cout << "Position Symbol ID: 2 | Quantity: " << positionsSymbol2[0] << " | PNL: " << pnlSymbol2 << "\n";
            std::cout << "Total Position: " << totalPosition << "\n";
            std::cout << "Total PNL: " << totalPNL << "\n";
            std::cout << "-----------------------------\n";

            // Reset positions for both symbols
            positionsSymbol1[0] = 0.0;
            positionsSymbol2[0] = 0.0;
        }

        // Simulate half-second interval
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    return 0;
}
