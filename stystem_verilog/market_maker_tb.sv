module MarketMakerModule_TB;
  logic clk;
  logic reset;
  logic [7:0] websocket_data;
  logic [7:0] s;
  logic [7:0] q;
  logic [7:0] t;
  logic [7:0] delta_a;
  logic [7:0] delta_b;
  logic buy_order;
  logic sell_order;

  MarketMakerModule dut (
    .clk(clk),
    .reset(reset),
    .websocket_data(websocket_data),
    .s(s),
    .q(q),
    .t(t),
    .delta_a(delta_a),
    .delta_b(delta_b),
    .buy_order(buy_order),
    .sell_order(sell_order)
  );

  // Clock generation
  always #5 clk = ~clk;

  initial begin
    // Initialize inputs
    clk = 0;
    reset = 1;
    websocket_data = 8'h00;
    s = 8'h00;
    q = 8'h00;
    t = 8'h00;
    delta_a = 8'h00;
    delta_b = 8'h00;

    // Reset
    #10 reset = 0;

    // Test scenario 1
    #20 websocket_data = 8'hA5;
    #20 s = 8'hC0;
    #20 q = 8'h10;
    #20 t = 8'h05;
    #20 delta_a = 8'h08;
    #20 delta_b = 8'h08;

    // Test scenario 2
    #20 websocket_data = 8'hB2;
    #20 s = 8'h80;
    #20 q = 8'h05;
    #20 t = 8'h0A;
    #20 delta_a = 8'h04;
    #20 delta_b = 8'h04;

    // Add more test scenarios here...

    #100 $finish;
  end
endmodule
