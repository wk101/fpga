class MarketMaker;
  logic [7:0] reservation_price;
  logic [7:0] bid_price;
  logic [7:0] ask_price;
  logic [7:0] current_price;
  logic is_trending_up;
  logic is_trending_down;
  logic risk_threshold_crossed;

  function automatic [7:0] calculate_optimal_spread;
    input logic [7:0] sigma;
    input logic [7:0] gamma;
    input logic [7:0] delta_a;
    input logic [7:0] delta_b;
    begin
      calculate_optimal_spread = sigma * $sqrt(gamma * (delta_a + delta_b));
    end
  endfunction

  function automatic [7:0] calculate_reservation_price;
    input logic [7:0] s;
    input logic [7:0] q;
    input logic [7:0] t;
    input logic [7:0] delta;
    begin
      logic [7:0] sqrt_term;
      sqrt_term = $sqrt(t);
      calculate_reservation_price = s - (q * sqrt_term) - calculate_optimal_spread();
    end
  endfunction

  function automatic void generate_order;
    input logic [7:0] reservation_price;
    input logic [7:0] bid_price;
    input logic [7:0] ask_price;
    input logic [7:0] current_price;
    input logic is_trending_up;
    input logic is_trending_down;
    input logic risk_threshold_crossed;
    begin
      buy_order = 0;
      sell_order = 0;

      if (current_price < bid_price && is_trending_up && !risk_threshold_crossed)
        buy_order = 1;

      if (current_price > ask_price && is_trending_down && !risk_threshold_crossed)
        sell_order = 1;
    end
  endfunction

  // Inputs
  input logic clk;
  input logic reset;
  input logic [7:0] websocket_data;
  input logic [7:0] s;
  input logic [7:0] q;
  input logic [7:0] t;
  input logic [7:0] delta_a;
  input logic [7:0] delta_b;

  // Outputs
  output logic buy_order;
  output logic sell_order;

  // Clock and reset logic
  always_ff @(posedge clk or posedge reset) begin
    if (reset) begin
      reservation_price <= 8'h0;
      bid_price <= 8'h0;
      ask_price <= 8'h0;
      current_price <= 8'h0;
      is_trending_up <= 1'b0;
      is_trending_down <= 1'b0;
      risk_threshold_crossed <= 1'b0;
      buy_order <= 1'b0;
      sell_order <= 1'b0;
    end else begin
      reservation_price <= calculate_reservation_price(s, q, t, delta_a);
      bid_price <= reservation_price - calculate_optimal_spread();
      ask_price <= reservation_price + calculate_optimal_spread();
      current_price <= websocket_data;
      is_trending_up <= (current_price > s + t);
      is_trending_down <= (current_price < s - t);
      risk_threshold_crossed <= (current_price < reservation_price - delta_a) || (current_price > reservation_price + delta_b);
      generate_order(reservation_price, bid_price, ask_price, current_price, is_trending_up, is_trending_down, risk_threshold_crossed);
    end
  end
endclass

module MarketMakerModule(
  input logic clk,
  input logic reset,
  input logic [7:0] websocket_data,
  input logic [7:0] s,
  input logic [7:0] q,
  input logic [7:0] t,
  input logic [7:0] delta_a,
  input logic [7:0] delta_b,
  output logic buy_order,
  output logic sell_order
);
  MarketMaker market_maker;

  // Connect inputs and outputs to the market_maker instance
  assign market_maker.clk = clk;
  assign market_maker.reset = reset;
  assign market_maker.websocket_data = websocket_data;
  assign market_maker.s = s;
  assign market_maker.q = q;
  assign market_maker.t = t;
  assign market_maker.delta_a = delta_a;
  assign market_maker.delta_b = delta_b;
  assign buy_order = market_maker.buy_order;
  assign sell_order = market_maker.sell_order;
endmodule

