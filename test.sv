logic [31:0] rol_result;
logic [31:0] rol_xor_result;
assign rol_result = (operator_i == ROL16XOR) ? {operand_a_i[15:0], 16'b0} | {16'b0, operand_a_i[31:16]}:
							  (operator_i == ROL13XOR) ? {operand_a_i[18:0], 13'b0} | {19'b0, operand_a_i[31:19]}:
							  	32'b0;
assign rol_xor_result = rol_result ^ $unsigned(operand_b_i);