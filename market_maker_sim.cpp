#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <thread>

struct MarketData {
    int symbolId; // Use integer IDs to identify symbols
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
void buy(std::vector<double>& positions, int symbolId, double price, int quantity) {
    positions[symbolId - 1] += quantity;
    std::cout << "Buy Order - Symbol ID: " << symbolId << " | Quantity: " << quantity << " | Price: " << price << "\n";
}

// Function to sell a quantity of a symbol
void sell(std::vector<double>& positions, int symbolId, double price, int quantity) {
    positions[symbolId - 1] -= quantity;
    std::cout << "Sell Order - Symbol ID: " << symbolId << " | Quantity: " << quantity << " | Price: " << price << "\n";
}

// Function to calculate PNL for a position based on the current mid price
double calculatePNL(double positionQuantity, double midPrice) {
    return positionQuantity * (midPrice - 100.0); // Assume initial price was 100.0 for simplicity
}

int main() {
    const std::vector<int> cryptoSymbolIds = {1, 2}; // Use integer IDs to identify symbols (1 and 2)
    const double initialPrice = 100.0;

    std::vector<MarketData> marketData; // Data for multiple crypto symbols

    // Initialize market data for each crypto symbol
    for (int i = 0; i < cryptoSymbolIds.size(); ++i) {
        MarketData data;
        data.symbolId = cryptoSymbolIds[i];
        data.midPrice = initialPrice;
        marketData.push_back(data);
    }

    std::vector<double> positions(cryptoSymbolIds.size(), 0); // Vector to keep track of positions

    // Generate fake market data every half second for 30 seconds (reduce for faster testing)
    for (int i = 0; i < 60; ++i) {
        std::cout << "Updating Market Data - Second " << (i + 1) << "\n";
        for (int j = 0; j < marketData.size(); ++j) {
            MarketData& data = marketData[j];
            data.midPrice = generatePrice(data.midPrice);

            // Buy and sell randomly
            int symbolId = data.symbolId;
            double price = data.midPrice;
            int quantity = 100; // For simplicity, assume fixed quantity

            // Randomly decide to buy or sell
            if (std::rand() % 2 == 0) {
                buy(positions, symbolId, price, quantity);
            } else {
                sell(positions, symbolId, price, quantity);
            }
        }

        if ((i + 1) % 10 == 0) {
            // Close positions and calculate PNL every 5 seconds
            std::cout << "Closing Positions - Second " << (i + 1) << "\n";
            double totalPNL = 0.0;
            for (int j = 0; j < positions.size(); ++j) {
                double pnl = calculatePNL(positions[j], marketData[j].midPrice);
                totalPNL += pnl;
                std::cout << "Position Symbol ID: " << (j + 1) << " | Quantity: " << positions[j] << " | PNL: " << pnl << "\n";
            }
            std::cout << "Total PNL: " << totalPNL << "\n";
            std::cout << "-----------------------------\n";
            positions.assign(cryptoSymbolIds.size(), 0); // Close all positions
        }

        // Simulate half-second interval
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    return 0;
}
