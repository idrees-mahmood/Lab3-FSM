module lfsr # (
    parameter DATA_WIDTH = 4
)(
    input logic rst,
    input logic en,
    input logic clk,
    output logic [DATA_WIDTH-1:0] data_out
);

    logic[4:1] sreg;

always_ff @ (posedge clk, posedge rst) 
    if (rst) 
        sreg <= 4'b1;
    else if (en) begin
        sreg <= {sreg[3:1], sreg[4] ^ sreg[3]};
    end
assign data_out = sreg;
endmodule
