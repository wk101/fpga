# FPGA Acceleration for Multiple Market Makers

## Introduction

Market making is a common trading strategy in financial markets, where a trader provides liquidity by simultaneously placing buy and sell orders for a particular asset with the goal of profiting from the bid-ask spread. To efficiently manage multiple market-making strategies in a portfolio, we can use FPGA acceleration with vector addition.

## The Concept

The basic idea of using vector addition in this context is to treat each market maker as a separate strategy. We create position vectors for each strategy, representing the current holdings or positions. The FPGA kernel is then employed to combine the position vectors of all market makers, providing an overall view of the market-making portfolio.

## Approach

1. **Define Strategies:** Each market maker represents a different strategy. For example, we can have separate strategies for providing liquidity for different stocks, each with its own parameters like pricing rules and position limits.

2. **Create Position Vectors:** For each strategy, we create a position vector that holds information about the quantities of assets held, whether they are long or short positions, and any other relevant data.

3. **Combine Positions with FPGA Kernel:** We use the FPGA kernel to efficiently combine the position vectors of all market makers. This combined position vector gives us a comprehensive picture of our market-making portfolio.

## Status and Future Enhancements

As of now, we have successfully implemented the vector addition using the FPGA kernel to manage the market-making portfolio efficiently. However, we plan to implement further enhancements to our strategy:

**TODO later Adjust Pricing and Orders:** Based on the combined position vector, each market maker can adjust its pricing and orders. For instance, if there is an overall excess of buyers, a market maker may adjust its sell prices to attract more sellers and vice versa.

**Todo later Monitor and Rebalance:** Continuously monitor the market and the performance of each market maker. If required, we will rebalance the positions of individual market makers to ensure they stay within their predefined risk limits.

**Todo later Risk Management:** Implement risk management techniques to control the exposure and potential losses of the overall market-making portfolio. This will include setting stop-loss limits, position sizing, and diversification among different assets and strategies.

## Code Overview

```cpp
// ... Code for generating market data and defining market makers ...

#include "xcl2.hpp"
#include <vector>

// ... Existing code ...

int main() {
    // ... Existing code ...

    // Initialize OpenCL
    std::vector<cl::Device> devices = xcl::get_xil_devices();
    cl::Device device = devices[0];
    cl::Context context(device);
    cl::CommandQueue q(context, device, CL_QUEUE_PROFILING_ENABLE);

    // Compute the size of arrays in bytes
    size_t size_in_bytes = marketData.size() * sizeof(int);

    // Create OpenCL buffers for position vectors
    cl::Buffer buffer_position_a(context, CL_MEM_USE_HOST_PTR | CL_MEM_READ_ONLY,
                                 size_in_bytes, marketData.data());
    cl::Buffer buffer_position_b(context, CL_MEM_USE_HOST_PTR | CL_MEM_READ_ONLY,
                                 size_in_bytes, marketData.data());
    cl::Buffer buffer_result(context, CL_MEM_USE_HOST_PTR | CL_MEM_WRITE_ONLY,
                             size_in_bytes, marketData.data());

    // Separate Read/write Buffer vector is needed to migrate data between host/device
    std::vector<cl::Memory> inBufVec, outBufVec;
    inBufVec.push_back(buffer_position_a);
    inBufVec.push_back(buffer_position_b);
    outBufVec.push_back(buffer_result);

    // Execute the vector addition kernel
    cl::Kernel krnl_vector_add(program, "vector_add");
    int narg = 0;
    krnl_vector_add.setArg(narg++, buffer_result);
    krnl_vector_add.setArg(narg++, buffer_position_a);
    krnl_vector_add.setArg(narg++, buffer_position_b);
    krnl_vector_add.setArg(narg++, marketData.size());

    q.enqueueMigrateMemObjects(inBufVec, 0 /* 0 means from host */);
    q.enqueueTask(krnl_vector_add);
    q.enqueueMigrateMemObjects(outBufVec, CL_MIGRATE_MEM_OBJECT_HOST);
    q.finish();

    // Print the combined position vector (result)
    std::vector<MarketData> combinedPositions(marketData.size());
    std::memcpy(combinedPositions.data(), marketData.data(), size_in_bytes);
    for (const auto& data : combinedPositions) {
        constantSpreadMarketMaker(data);
    }

    return 0;
}


```

## Conclusion

Using vector addition and FPGA acceleration, we have developed a solution to efficiently manage multiple market-making strategies in a portfolio. Market making is a sophisticated trading strategy, and our approach provides a holistic view of market dynamics while ensuring liquidity and profitability. As we continue to enhance our implementation with monitoring and risk management features, we aim to optimize the performance of the market-making portfolio further.

For any inquiries or further explanations, please feel free to reach out. We are excited about this project's potential and look forward to making it even better with each iteration.
