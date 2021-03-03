#ifndef TB_H
#define TB_H
#include<systemc.h>

#define B_porch 1

SC_MODULE(tb)
{
	sc_in<bool> clk_scl;
	sc_out<bool> rst_n_scl;

	sc_out<bool > scl_cfg_mode;
	sc_out<sc_uint<1> > scl_cfg_rsz;
	sc_out<sc_uint<2> > scl_cfg_flt;
	sc_out<sc_uint<12> > height, width;

	sc_out<bool> scl_i_vsync, scl_i_hsync;
	sc_out<bool> scl_i_data_en;
	sc_out<sc_uint<8> > scl_i_data_r, scl_i_data_g, scl_i_data_b;

	sc_in<bool> scl_o_vsync, scl_o_hsync;
	sc_in<bool> scl_o_data_en;
	sc_in<sc_uint<8> > scl_o_data_r, scl_o_data_g, scl_o_data_b;

	void source();
	void sink();

	SC_CTOR(tb)
	{
		SC_CTHREAD(source, clk_scl.pos() );
		SC_CTHREAD(sink, clk_scl.pos() );
	}

};

#endif // !TB_H
