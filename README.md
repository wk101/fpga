
# Market-Making Algorithm with FPGA Acceleration

This project demonstrates a market-making algorithm using FPGA acceleration on AWS F1 instances. The algorithm incorporates real-time data from the BitMEX WebSocket API and utilizes an OpenCL kernel to perform high-performance computation on the FPGA.

## Overview

The market-making algorithm aims to generate trading decisions based on bid and ask prices received from the BitMEX WebSocket API. The FPGA acceleration provided by AWS F1 instances allows for the efficient processing of large datasets and enables real-time decision-making.

The FPGA acceleration is achieved through the use of Xilinx UltraScale+ FPGAs available on AWS F1 instances. The FPGA design is developed using the Xilinx Vivado Design Suite and programmed onto the F1 instance using an Amazon FPGA Image (AFI).

The algorithm leverages the OpenCL programming framework to write a parallelized OpenCL kernel that performs the market-making calculations on the FPGA. The OpenCL kernel is executed on the FPGA device, enabling significant acceleration compared to traditional CPU-based processing.

## Approach

The following approach is followed to implement the market-making algorithm with FPGA acceleration:

1. **F1 Instance**: An F1 instance is provisioned on AWS, which combines CPUs with Xilinx UltraScale+ FPGAs. F1 instances offer a high-performance computing environment suitable for FPGA acceleration.

2. **AFI Creation**: Using the Xilinx Vivado Design Suite, an Amazon FPGA Image (AFI) is generated. The AFI encapsulates the FPGA configuration specific to the targeted F1 instance. It contains the bitstream that configures the FPGA for the market-making algorithm.

3. **WebSocket Connection**: The project establishes a WebSocket connection with the BitMEX WebSocket API to receive real-time bids and ask prices. This connection is handled using a WebSocket library, such as WebSocket++.

4. **Data Parsing**: The received WebSocket messages are parsed to extract bid and ask prices. The parsing logic should be customized to match the specific BitMEX WebSocket message format.

5. **OpenCL Kernel**: An OpenCL kernel, named "market maker", is developed to perform the market-making calculations on the FPGA. The kernel takes bid prices, ask prices, and other parameters as inputs and produces trading decisions as outputs.

6. **OpenCL Integration**: The project uses the Xilinx Vivado Design Suite to compile the OpenCL kernel into a hardware bitstream that is loaded onto the FPGA. The OpenCL code is integrated into the main application, which manages the execution of the kernel on the FPGA.

7. **Data Transfer**: The bid and ask prices obtained from the WebSocket connection are transferred from the host application to the FPGA device memory using OpenCL memory objects. The market-making algorithm is then executed on the FPGA using the OpenCL kernel.

8. **Result Retrieval**: Once the OpenCL kernel execution is complete, the resulting trading decisions are transferred back from the FPGA device memory to the host application using OpenCL memory transfer functions.

9. **Trading Decision Processing**: The trading decisions obtained from the FPGA are further processed or analyzed as needed. This can involve sending orders, updating trading strategies, or performing risk management.

## Getting Started

To replicate and test the market-making algorithm with FPGA acceleration, follow these steps:

1. Provision an F1 instance on AWS in your desired region.

2. Generate an Amazon FPGA Image (AFI) using the Xilinx Vivado Design Suite. Configure the AFI to match the FPGA resources on the F1 instance.

3. Establish a WebSocket connection with the BitMEX WebSocket API to receive bid and ask prices. Use a WebSocket library compatible with your chosen programming language, such as WebSocket++.

4. Parse the WebSocket messages to extract the bid and ask prices. Customize the parsing logic to match the BitMEX WebSocket message format.

5. Develop the OpenCL kernel, "market maker", to implement the market-making algorithm. Compile the kernel using the Xilinx Vivado Design Suite to generate the FPGA bitstream.

6. Integrate the OpenCL code into your host application. Use the Xilinx Vivado Design Suite and the AWS FPGA Developer AMI to manage the FPGA deployment and execution.

7. Transfer the bid and ask prices from the host application to the FPGA device memory using OpenCL memory objects.

8. Execute the market-making algorithm on the FPGA by enqueuing the OpenCL kernel for execution.

9. Retrieve the trading decisions from the FPGA device memory back to the host application using OpenCL memory transfer functions.

10. Process the trading decisions as required, such as sending orders or performing further analysis.

## Dependencies

- Xilinx Vivado Design Suite
- AWS F1 Instance
- WebSocket library (e.g., WebSocket++)

Please refer to the documentation and resources provided by Xilinx, AWS, and the WebSocket library of your choice for detailed instructions on setting up the development environment and incorporating FPGA acceleration into your market-making algorithm.

## Disclaimer

This project serves as a demonstration and starting point for implementing a market-making algorithm with FPGA acceleration. It is important to thoroughly test and validate the algorithm before deploying it in a production environment. The code provided should be customized and expanded to meet specific requirements and compliance standards.

## References

- [AWS F1 Instances](https://aws.amazon.com/ec2/instance-types/f1/)
- [Xilinx Vivado Design Suite](https://www.xilinx.com/products/design-tools/vivado.html)
- [WebSocket++](https://github.com/zaphoyd/websocketpp)

Please consult the official documentation and resources of the respective tools and frameworks for detailed information and updates.

