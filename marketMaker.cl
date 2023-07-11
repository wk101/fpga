__kernel void marketMaker(__global const float* bidPrices,
                          __global const float* askPrices,
                          __global float* tradingDecisions,
                          const int numPrices,
                          const float spreadThreshold) {
    int globalId = get_global_id(0);

    // Check if the globalId is within the valid range
    if (globalId < numPrices) {
        float bidPrice = bidPrices[globalId];
        float askPrice = askPrices[globalId];

        // Perform market-making calculations
        float spread = askPrice - bidPrice;
        float midPrice = (askPrice + bidPrice) * 0.5f;

        // Adjust trading decisions based on spread threshold
        tradingDecisions[globalId] = (spread >= spreadThreshold && bidPrice > 0.0f && askPrice > 0.0f) ? midPrice : 0.0f;
    }
}
