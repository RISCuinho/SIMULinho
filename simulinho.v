`timescale 10s/1s

module SIMULinho;

reg clk = 1'b0;

initial
    begin
    forever
    #2 clk = !clk;
end

initial begin
#2 $simulinho;

$simulinho_clock(clk);

#2000 $simulinho_finish;
end

endmodule
