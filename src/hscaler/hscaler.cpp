#include "hscaler.h"

//output the scl_o_hsync according to the scl_i_hsync 

void hscaler::hscaler_o_vsync()
{
	if (!rst_n_scl.read())
	{
		itmp_vsync[0].write(1);
		itmp_vsync[1].write(1);
		scl_o_vsync.write(1);
	}
	else
	{
		itmp_vsync[0].write(scl_i_vsync.read());
		itmp_vsync[1].write(itmp_vsync[0].read());
		scl_o_vsync.write(itmp_vsync[1].read());
	}
}

void hscaler::hscaler_o_hsync()
{
	if (!rst_n_scl.read())
	{
		itmp_hsync[0].write(1);
		itmp_hsync[1].write(1);
		scl_o_hsync.write(1);
	}
	else
	{
		itmp_hsync[0].write(scl_i_hsync.read());
		itmp_hsync[1].write(itmp_hsync[0].read());
		scl_o_hsync.write(itmp_hsync[1].read());
	}
}


void hscaler::hscaler_main()
{
	//reset
	scl_o_data_en.write(0);
	scl_o_data_r.write(0);
	scl_o_data_g.write(0);
	scl_o_data_b.write(0);
	wait();

	//select the params of coef
	sc_int<11> coef[4] = { 0, 0, 0, 0 };
	switch (scl_cfg_flt.read())
	{
	case 0:
		coef[0] = -3;
		coef[1] = 498;
		coef[2] = 18;
		coef[3] = -1;
		break;
	case 1:
		coef[0] = -38;
		coef[1] = 376;
		coef[2] = 202;
		coef[3] = -28;
		break;
	case 2:
		coef[0] = -28;
		coef[1] = 202;
		coef[2] = 376;
		coef[3] = -38;
		break;
	case 3:
		coef[0] = -1;
		coef[1] = 18;
		coef[2] = 498;
		coef[3] = -3;
		break;
	default:
		coef[0] = 0;
		coef[1] = 512;
		coef[2] = 0;
		coef[3] = 0;
		break;
	}

	for (sc_uint<12> y = 0; y < height.read(); y++)
	{
		//during the 1st and 2nd periods hscaler only gets input datas 
		sc_uint<8> itmp_r[4] = { 0, 0, 0, 0 };
		sc_uint<8> itmp_g[4] = { 0, 0, 0, 0 };
		sc_uint<8> itmp_b[4] = { 0, 0, 0, 0 };
		for (sc_uint<12> x = 0; x < width.read() + 3; x++)
		{
			if (x == width.read() + 2)
			{
				scl_o_data_en.write(0);
				continue;
			}

			//3 Regs
			for (sc_uint<2> i = 0; i < 3; i++)
			{
				itmp_r[i] = itmp_r[i + 1];
				itmp_g[i] = itmp_g[i + 1];
				itmp_b[i] = itmp_b[i + 1];
			}

			while (!scl_i_data_en.read() && x < width.read())
			{
				wait();
			}

			if (x < width.read())
			{
				itmp_r[3] = scl_i_data_r.read();
				itmp_g[3] = scl_i_data_g.read();
				itmp_b[3] = scl_i_data_b.read();
			}

			//from the 3rd period hscaler starts processing the input datas
			if (1 < x && x < width.read() + 2)
			{
				sc_int<19> otmp_r = 0;
				sc_int<19> otmp_g = 0;
				sc_int<19> otmp_b = 0;

				sc_uint<8> out_r = 0;
				sc_uint<8> out_g = 0;
				sc_uint<8> out_b = 0;

				//three boundary points
				if (x == 2)
				{
					otmp_r = itmp_r[1] * coef[0] + itmp_r[1] * coef[1] + itmp_r[2] * coef[2] + itmp_r[3] * coef[3];
					otmp_g = itmp_g[1] * coef[0] + itmp_g[1] * coef[1] + itmp_g[2] * coef[2] + itmp_g[3] * coef[3];
					otmp_b = itmp_b[1] * coef[0] + itmp_b[1] * coef[1] + itmp_b[2] * coef[2] + itmp_b[3] * coef[3];
				}
				else if (x == width.read() )
				{
					otmp_r = itmp_r[0] * coef[0] + itmp_r[1] * coef[1] + itmp_r[2] * coef[2] + itmp_r[2] * coef[3];
					otmp_g = itmp_g[0] * coef[0] + itmp_g[1] * coef[1] + itmp_g[2] * coef[2] + itmp_g[2] * coef[3];
					otmp_b = itmp_b[0] * coef[0] + itmp_b[1] * coef[1] + itmp_b[2] * coef[2] + itmp_b[2] * coef[3];
				}
				else if (x == width.read() + 1)
				{
					otmp_r = itmp_r[0] * coef[0] + itmp_r[1] * coef[1] + itmp_r[1] * coef[2] + itmp_r[1] * coef[3];
					otmp_g = itmp_g[0] * coef[0] + itmp_g[1] * coef[1] + itmp_g[1] * coef[2] + itmp_g[1] * coef[3];
					otmp_b = itmp_b[0] * coef[0] + itmp_b[1] * coef[1] + itmp_b[1] * coef[2] + itmp_b[1] * coef[3];
				}
				else
				{
					for (int i = 0; i < 4; i++)
					{
						otmp_r += itmp_r[i] * coef[i];
						otmp_g += itmp_g[i] * coef[i];
						otmp_b += itmp_b[i] * coef[i];
					}
				}

				if (otmp_r < 0)
				{
					otmp_r = 0;
				}
				else if (otmp_r > 130560)
				{
					otmp_r = 130560;
				}

				if (otmp_g < 0)
				{
					otmp_g = 0;
				}
				else if (otmp_g > 130560)
				{
					otmp_g = 130560;
				}

				if (otmp_b < 0)
				{
					otmp_b = 0;
				}
				else if (otmp_b > 130560)
				{
					otmp_b = 130560;
				}

				otmp_r = (otmp_r >> 9);
				otmp_g = (otmp_g >> 9);
				otmp_b = (otmp_b >> 9);

				out_r = (sc_uint<8>)(otmp_r);
				out_g = (sc_uint<8>)(otmp_g);
				out_b = (sc_uint<8>)(otmp_b);

				//whether resize
				if (scl_cfg_mode.read())
				{
					switch (scl_cfg_rsz.read())
					{
					case 0:
						if (!x[0])
						{
							scl_o_data_r.write(out_r);
							scl_o_data_g.write(out_g);
							scl_o_data_b.write(out_b);

							scl_o_data_en.write(1);
						}
						else
						{
							scl_o_data_en.write(0);
						}
						break;
					case 1:
						if (x.range(1, 0) == 2)
						{
							scl_o_data_r.write(out_r);
							scl_o_data_g.write(out_g);
							scl_o_data_b.write(out_b);

							scl_o_data_en.write(1);
						}
						else
						{
							scl_o_data_en.write(0);
						}
						break;
					default:
						break;
					}
				}
				else
				{
					scl_o_data_r.write(itmp_r[1]);
					scl_o_data_g.write(itmp_g[1]);
					scl_o_data_b.write(itmp_b[1]);

					scl_o_data_en.write(1);
				}

			}

			wait();
		}

	}

}