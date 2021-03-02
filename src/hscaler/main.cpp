#include <systemc.h>
#include "hscaler.h"
#include "tb.h"

int sc_main(int argc, char* argv[])
{
	//signal
	sc_clock clk_scl_sig;
	sc_signal<bool> rst_n_scl_sig;

	sc_signal<bool > scl_cfg_mode_sig;
	sc_signal<sc_uint<1> > scl_cfg_rsz_sig;
	sc_signal<sc_uint<2> > scl_cfg_flt_sig;
	sc_signal<sc_uint<12> > height_sig, width_sig;

	sc_signal<bool> scl_i_vsync_sig, scl_i_hsync_sig;
	sc_signal<bool> scl_i_data_en_sig;
	sc_signal<sc_uint<8> > scl_i_data_r_sig, scl_i_data_g_sig, scl_i_data_b_sig;

	sc_signal<bool> scl_o_vsync_sig, scl_o_hsync_sig;
	sc_signal<bool> scl_o_data_en_sig;
	sc_signal<sc_uint<8> > scl_o_data_r_sig, scl_o_data_g_sig, scl_o_data_b_sig;

	//module
	hscaler hscaler0("hscaler");
	tb tb0("tb");

	//port
	tb0.clk_scl(clk_scl_sig);
	tb0.rst_n_scl(rst_n_scl_sig);

	tb0.scl_cfg_mode(scl_cfg_mode_sig);
	tb0.scl_cfg_rsz(scl_cfg_rsz_sig);
	tb0.scl_cfg_flt(scl_cfg_flt_sig);
	tb0.height(height_sig);
	tb0.width(width_sig);

	tb0.scl_i_vsync(scl_i_vsync_sig);
	tb0.scl_i_hsync(scl_i_hsync_sig);
	tb0.scl_i_data_en(scl_i_data_en_sig);
	tb0.scl_i_data_r(scl_i_data_r_sig);
	tb0.scl_i_data_g(scl_i_data_g_sig);
	tb0.scl_i_data_b(scl_i_data_b_sig);

	tb0.scl_o_vsync(scl_o_vsync_sig);
	tb0.scl_o_hsync(scl_o_hsync_sig);
	tb0.scl_o_data_en(scl_o_data_en_sig);
	tb0.scl_o_data_r(scl_o_data_r_sig);
	tb0.scl_o_data_g(scl_o_data_g_sig);
	tb0.scl_o_data_b(scl_o_data_b_sig);

	hscaler0.clk_scl(clk_scl_sig);
	hscaler0.rst_n_scl(rst_n_scl_sig);

	hscaler0.scl_cfg_mode(scl_cfg_mode_sig);
	hscaler0.scl_cfg_rsz(scl_cfg_rsz_sig);
	hscaler0.scl_cfg_flt(scl_cfg_flt_sig);
	hscaler0.height(height_sig);
	hscaler0.width(width_sig);

	hscaler0.scl_i_vsync(scl_i_vsync_sig);
	hscaler0.scl_i_hsync(scl_i_hsync_sig);
	hscaler0.scl_i_data_en(scl_i_data_en_sig);
	hscaler0.scl_i_data_r(scl_i_data_r_sig);
	hscaler0.scl_i_data_g(scl_i_data_g_sig);
	hscaler0.scl_i_data_b(scl_i_data_b_sig);

	hscaler0.scl_o_vsync(scl_o_vsync_sig);
	hscaler0.scl_o_hsync(scl_o_hsync_sig);
	hscaler0.scl_o_data_en(scl_o_data_en_sig);
	hscaler0.scl_o_data_r(scl_o_data_r_sig);
	hscaler0.scl_o_data_g(scl_o_data_g_sig);
	hscaler0.scl_o_data_b(scl_o_data_b_sig);

	//wave
	/*
	sc_trace_file* trace_file = sc_create_vcd_trace_file("h");
	sc_trace(trace_file, clk_scl_sig, "clk_scl");
	sc_trace(trace_file, rst_n_scl_sig, "rst_n_scl");

	sc_trace(trace_file, scl_cfg_mode_sig, "scl_cfg_mode");
	sc_trace(trace_file, scl_cfg_rsz_sig, "scl_cfg_rsz");
	sc_trace(trace_file, scl_cfg_flt_sig, "scl_cfg_flt");
	sc_trace(trace_file, height_sig, "height");
	sc_trace(trace_file, width_sig, " width");

	sc_trace(trace_file, scl_i_vsync_sig, "scl_i_vsync");
	sc_trace(trace_file, scl_i_hsync_sig, " scl_i_hsync");
	sc_trace(trace_file, scl_i_data_en_sig, "scl_i_data_en");
	sc_trace(trace_file, scl_i_data_r_sig, "scl_i_data_r");
	sc_trace(trace_file, scl_i_data_g_sig, "scl_i_data_g");
	sc_trace(trace_file, scl_i_data_b_sig, "scl_i_data_b");

	sc_trace(trace_file, scl_o_vsync_sig, "scl_o_vsync");
	sc_trace(trace_file, scl_o_hsync_sig, " scl_o_hsync");
	sc_trace(trace_file, scl_o_data_en_sig, "scl_o_data_en");
	sc_trace(trace_file, scl_o_data_r_sig, "scl_o_data_r");
	sc_trace(trace_file, scl_o_data_g_sig, "scl_o_data_g");
	sc_trace(trace_file, scl_o_data_b_sig, "scl_o_data_b");
	*/
	sc_start();
	return 0;

}