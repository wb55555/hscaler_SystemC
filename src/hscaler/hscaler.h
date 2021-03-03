#ifndef HSCALER_H
#define HSCALER_H
#include<systemc.h>

SC_MODULE(hscaler)
{
	sc_in<bool> rst_n_scl, clk_scl;

	sc_in<bool > scl_cfg_mode;
	sc_in<sc_uint<1> > scl_cfg_rsz;
	sc_in<sc_uint<2> > scl_cfg_flt;
	sc_in<sc_uint<12> > height, width;

	sc_in<bool> scl_i_vsync, scl_i_hsync;
	sc_in<bool> scl_i_data_en;
	sc_in<sc_uint<8> > scl_i_data_r, scl_i_data_g, scl_i_data_b;

	sc_out<bool> scl_o_vsync, scl_o_hsync;
	sc_out<bool> scl_o_data_en;
	sc_out<sc_uint<8> > scl_o_data_r, scl_o_data_g, scl_o_data_b;

	sc_signal<bool> itmp_vsync[2];
	sc_signal<bool> itmp_hsync[2];

	void hscaler_o_vsync();
	void hscaler_o_hsync();
	void hscaler_main();

	SC_CTOR(hscaler)
	{

		SC_METHOD(hscaler_o_vsync);
		sensitive << clk_scl.pos() << rst_n_scl.neg();

		SC_METHOD(hscaler_o_hsync);
		dont_initialize();
		sensitive << clk_scl.pos() << rst_n_scl.neg();

		SC_CTHREAD(hscaler_main, clk_scl.pos() );
		reset_signal_is(rst_n_scl, false);
	}

};

#endif // !HSCALER_H
