module ejemplo (
    input logic a,
    input logic b,
    output logic y
);
    and_gate u_and(
        .a(a),
        .b(b),
        .y(y)
    );

endmodule

/*
*    Se vería algo asi:
*    a (input) - - - - - -            
*                         | U AND | - - - - - - - y (output)
*    b (input) - - - - - -
*/