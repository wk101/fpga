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

```txt simulation

Total Position: 1000
Total PNL: -59.3603
-----------------------------
Updating Market Data - Second 31
Sell Order - Symbol ID: 2 | Quantity: 100 | Price: 99.8931
Sell Order - Symbol ID: 2 | Quantity: 100 | Price: 100.005
Updating Market Data - Second 32
Buy Order - Symbol ID: 1 | Quantity: 100 | Price: 99.9936
Sell Order - Symbol ID: 2 | Quantity: 100 | Price: 100.347
Updating Market Data - Second 33
Buy Order - Symbol ID: 1 | Quantity: 100 | Price: 100.38
Sell Order - Symbol ID: 2 | Quantity: 100 | Price: 100.094
Updating Market Data - Second 34
Buy Order - Symbol ID: 1 | Quantity: 100 | Price: 100.532
Sell Order - Symbol ID: 2 | Quantity: 100 | Price: 100.282
Updating Market Data - Second 35
Sell Order - Symbol ID: 2 | Quantity: 100 | Price: 100.209
Sell Order - Symbol ID: 2 | Quantity: 100 | Price: 100.125
Updating Market Data - Second 36
Buy Order - Symbol ID: 1 | Quantity: 100 | Price: 99.8654
Sell Order - Symbol ID: 2 | Quantity: 100 | Price: 99.9035
Updating Market Data - Second 37
Buy Order - Symbol ID: 1 | Quantity: 100 | Price: 99.5056
Sell Order - Symbol ID: 2 | Quantity: 100 | Price: 99.8922
Updating Market Data - Second 38
Buy Order - Symbol ID: 1 | Quantity: 100 | Price: 99.1851
Sell Order - Symbol ID: 2 | Quantity: 100 | Price: 100.289
Updating Market Data - Second 39
Buy Order - Symbol ID: 1 | Quantity: 100 | Price: 99.3326
Buy Order - Symbol ID: 1 | Quantity: 100 | Price: 100.734
Updating Market Data - Second 40
Sell Order - Symbol ID: 2 | Quantity: 100 | Price: 99.5697
Buy Order - Symbol ID: 1 | Quantity: 100 | Price: 100.683
Closing Positions - Second 40
Position Symbol ID: 1 | Quantity: 700 | PNL: -301.228
Position Symbol ID: 2 | Quantity: 200 | PNL: 136.543
Total Position: 900
Total PNL: -164.685
-----------------------------
Updating Market Data - Second 41
Sell Order - Symbol ID: 2 | Quantity: 100 | Price: 99.2643
Buy Order - Symbol ID: 1 | Quantity: 100 | Price: 101.158
Updating Market Data - Second 42
Buy Order - Symbol ID: 1 | Quantity: 100 | Price: 99.1739
Buy Order - Symbol ID: 1 | Quantity: 100 | Price: 101.302
Updating Market Data - Second 43
Buy Order - Symbol ID: 1 | Quantity: 100 | Price: 99.6386
Buy Order - Symbol ID: 1 | Quantity: 100 | Price: 101.411
Updating Market Data - Second 44
Sell Order - Symbol ID: 2 | Quantity: 100 | Price: 99.6951
Sell Order - Symbol ID: 2 | Quantity: 100 | Price: 101.638
Updating Market Data - Second 45
Buy Order - Symbol ID: 1 | Quantity: 100 | Price: 99.6544
Sell Order - Symbol ID: 2 | Quantity: 100 | Price: 101.704
Updating Market Data - Second 46
Buy Order - Symbol ID: 1 | Quantity: 100 | Price: 99.828
Buy Order - Symbol ID: 1 | Quantity: 100 | Price: 101.242
Updating Market Data - Second 47
Buy Order - Symbol ID: 1 | Quantity: 100 | Price: 99.3962
Buy Order - Symbol ID: 1 | Quantity: 100 | Price: 101.018
Updating Market Data - Second 48
Sell Order - Symbol ID: 2 | Quantity: 100 | Price: 99.6985
Buy Order - Symbol ID: 1 | Quantity: 100 | Price: 101.022
Updating Market Data - Second 49
Buy Order - Symbol ID: 1 | Quantity: 100 | Price: 99.2391
Buy Order - Symbol ID: 1 | Quantity: 100 | Price: 100.616
Updating Market Data - Second 50
Buy Order - Symbol ID: 1 | Quantity: 100 | Price: 99.6634
Sell Order - Symbol ID: 2 | Quantity: 100 | Price: 100.669
Closing Positions - Second 50
Position Symbol ID: 1 | Quantity: 700 | PNL: -235.586
Position Symbol ID: 2 | Quantity: 700 | PNL: 468.066
Total Position: 1400
Total PNL: 232.48
-----------------------------
Updating Market Data - Second 51
Sell Order - Symbol ID: 2 | Quantity: 100 | Price: 99.3947
Buy Order - Symbol ID: 1 | Quantity: 100 | Price: 100.369
Updating Market Data - Second 52
Buy Order - Symbol ID: 1 | Quantity: 100 | Price: 99.0645
Buy Order - Symbol ID: 1 | Quantity: 100 | Price: 100.175
Updating Market Data - Second 53
Sell Order - Symbol ID: 2 | Quantity: 100 | Price: 99.0678
Sell Order - Symbol ID: 2 | Quantity: 100 | Price: 99.7659
Updating Market Data - Second 54
Sell Order - Symbol ID: 2 | Quantity: 100 | Price: 99.3044
Buy Order - Symbol ID: 1 | Quantity: 100 | Price: 99.4095
Updating Market Data - Second 55
Sell Order - Symbol ID: 2 | Quantity: 100 | Price: 99.0243
Buy Order - Symbol ID: 1 | Quantity: 100 | Price: 99.5067
Updating Market Data - Second 56
Buy Order - Symbol ID: 1 | Quantity: 100 | Price: 99.3968
Buy Order - Symbol ID: 1 | Quantity: 100 | Price: 99.9877
Updating Market Data - Second 57
Sell Order - Symbol ID: 2 | Quantity: 100 | Price: 99.4
Buy Order - Symbol ID: 1 | Quantity: 100 | Price: 100.413
Updating Market Data - Second 58
Buy Order - Symbol ID: 1 | Quantity: 100 | Price: 99.6574
Sell Order - Symbol ID: 2 | Quantity: 100 | Price: 100.56
Updating Market Data - Second 59
Sell Order - Symbol ID: 2 | Quantity: 100 | Price: 99.5313
Sell Order - Symbol ID: 2 | Quantity: 100 | Price: 100.729
Updating Market Data - Second 60
Buy Order - Symbol ID: 1 | Quantity: 100 | Price: 99.6379
Sell Order - Symbol ID: 2 | Quantity: 100 | Price: 101.019
Closing Positions - Second 60
Position Symbol ID: 1 | Quantity: 400 | PNL: -144.859
Position Symbol ID: 2 | Quantity: 600 | PNL: 611.58
Total Position: 1000
Total PNL: 466.721
-----------------------------

```

## Conclusion

Using vector addition and FPGA acceleration, we have developed a solution to efficiently manage multiple market-making strategies in a portfolio. Market making is a sophisticated trading strategy, and our approach provides a holistic view of market dynamics while ensuring liquidity and profitability. As we continue to enhance our implementation with monitoring and risk management features, we aim to optimize the performance of the market-making portfolio further.

For any inquiries or further explanations, please feel free to reach out. We are excited about this project's potential and look forward to making it even better with each iteration.
