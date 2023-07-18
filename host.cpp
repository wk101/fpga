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
    std::vector<double> positionsTotal (1, 0.0); // Vector to keep track of all positions 
  
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
            // double totalPosition = positionsSymbol1[0] + positionsSymbol2[0];
            const size_t DATA_SIZE = 256;
            //std::vector<double> source_a(DATA_SIZE, 10.0);
            //std::vector<double> source_b(DATA_SIZE, 32.0);
            //std::vector<double> source_results(DATA_SIZE);

            performFPGAVectorAddition(positionsSymbol1, positionsSymbol2, positionsTotal, DATA_SIZE);
            double totalPosition = positionsTotal[0]
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

// Function to perform FPGA-based vector addition
void performFPGAVectorAddition(const std::vector<double>& a, const std::vector<double>& b, std::vector<double>& result, size_t buffer_size) {
    // The get_xil_devices will return vector of Xilinx Devices 
    std::vector<cl::Device> devices = xcl::get_xil_devices();
    cl::Device device = devices[0];

    // Creating Context and Command Queue for selected Device 
    cl::Context context(device);
    cl::CommandQueue q(context, device, CL_QUEUE_PROFILING_ENABLE);
    std::string device_name = device.getInfo<CL_DEVICE_NAME>(); 
    std::cout << "Found Device=" << device_name.c_str() << std::endl;

    // Import the OpenCL binary file
    std::string binaryFile = xcl::find_binary_file(device_name, "vector_addition");
    cl::Program::Binaries bins = xcl::import_binary_file(binaryFile);
    devices.resize(1);
    cl::Program program(context, devices, bins);

    // Compute the size of the array in bytes
    size_t size_in_bytes = buffer_size * sizeof(double);

    // Allocate memory on the FPGA
    cl::Buffer buffer_a(context, CL_MEM_USE_HOST_PTR | CL_MEM_READ_ONLY, size_in_bytes, const_cast<double*>(a.data()));
    cl::Buffer buffer_b(context, CL_MEM_USE_HOST_PTR | CL_MEM_READ_ONLY, size_in_bytes, const_cast<double*>(b.data()));
    cl::Buffer buffer_result(context, CL_MEM_USE_HOST_PTR | CL_MEM_WRITE_ONLY, size_in_bytes, result.data());

    // Separate Read/Write Buffer vector is needed to migrate data between host/device
    std::vector<cl::Memory> inBufVec, outBufVec;
    inBufVec.push_back(buffer_a);
    inBufVec.push_back(buffer_b);
    outBufVec.push_back(buffer_result);

    // Migrate data to FPGA
    q.enqueueMigrateMemObjects(inBufVec, 0 /* 0 means from host */);

    // Extract the kernel from the program
    cl::Kernel krnl_vector_add(program, "vector_add");

    // Set the kernel arguments
    int narg = 0;
    krnl_vector_add.setArg(narg++, buffer_result);
    krnl_vector_add.setArg(narg++, buffer_a);
    krnl_vector_add.setArg(narg++, buffer_b);
    krnl_vector_add.setArg(narg++, buffer_size);

    // Launch the Kernel
    q.enqueueTask(krnl_vector_add);

    // Retrieve the result from the FPGA
    q.enqueueMigrateMemObjects(outBufVec, CL_MIGRATE_MEM_OBJECT_HOST);
    q.finish();
}
