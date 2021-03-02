#include "tb.h"
#include "bmp.h"
#include<ostream>

using namespace std;

void tb::source()
{
	//read param.txt
	char param_file[256] = "param.txt";
	FILE* fp0 = fopen(param_file, "r");

	if (fp0 == NULL) {
		cout << "Input File open Error! : param.txt" << endl;
		exit(1);
	}


	char buf[256] = { 0 };
	char imgin_file[256] = { 0 };
	char imgout_file[256] = { 0 };
	int  i = 0;
	int mode = 0;
	int rsz = 0;
	int flt = 0;

	//get params
	while (fgets(buf, 256, fp0) )
	{
		if (buf[0] == '#')
		{
			continue;
		}

		switch (i)
		{
		case 0:  sscanf(buf, "%d", &mode);
			break;
		case 1:  sscanf(buf, "%d", &rsz);
			break;
		case 2:  sscanf(buf, "%d", &flt);
			break;
		case 3:  sscanf(buf, "%s", &imgin_file, 20);
			break;
		case 4:  sscanf(buf, "%s", &imgout_file, 20);
			break;
		default:
			break;
		}

		i++;
	}

	scl_cfg_mode.write(mode);
	scl_cfg_rsz.write(rsz);
	scl_cfg_flt.write(flt);

	//read input.bmp
	bmp* rbmp = new bmp(imgin_file, "READ");
	BMP_Header_Data rheader;
	rheader = rbmp->ReadHeader();

	height.write(rheader.Ysize);
	width.write(rheader.Xsize);

	int** imgin_buf_R = new int* [rheader.Ysize];
	int** imgin_buf_G = new int* [rheader.Ysize];
	int** imgin_buf_B = new int* [rheader.Ysize];
	for (unsigned int i = 0; i < rheader.Ysize; i++)
	{
		imgin_buf_R[i] = new int[rheader.Xsize];
		imgin_buf_G[i] = new int[rheader.Xsize];
		imgin_buf_B[i] = new int[rheader.Xsize];
	}

	for (unsigned int y = 0; y < rheader.Ysize; y++) 
	{
		for (unsigned int x = 0; x < rheader.Xsize; x++) 
		{
			BMP_Pixel_Data  iPD = rbmp->ReadPixel();
			imgin_buf_R[y][x] = (int)(iPD.R);
			imgin_buf_G[y][x] = (int)(iPD.G);
			imgin_buf_B[y][x] = (int)(iPD.B);
		}
	}

	//sent pixel data
	rst_n_scl.write(0);
	scl_i_vsync.write(1);
	scl_i_hsync.write(1);
	scl_i_data_en.write(0);
	wait();
	rst_n_scl.write(1);
	wait();
	scl_i_vsync.write(0);
	scl_i_hsync.write(0);
	wait();
	scl_i_vsync.write(1);
	scl_i_hsync.write(1);

	for (unsigned int y = 0; y < rheader.Ysize; y++)
	{
		scl_i_data_en.write(1);
		for (unsigned int x = 0; x < rheader.Xsize; x++)
		{
			scl_i_data_r.write(imgin_buf_R[y][x]);
			scl_i_data_g.write(imgin_buf_G[y][x]);
			scl_i_data_b.write(imgin_buf_B[y][x]);
			wait();
		}

		scl_i_data_en.write(0);
		wait(B_porch);
		scl_i_hsync.write(0);
		wait();
		scl_i_hsync.write(1);

	}

	wait(5);

	delete rbmp;
	delete[]imgin_buf_R;
	delete[]imgin_buf_G;
	delete[]imgin_buf_B;
}

void tb::sink()
{
	//read param.txt
	char param_file[256] = "param.txt";
	FILE* fp1 = fopen(param_file, "r");

	if (fp1 == NULL) {
		cout << "Input File open Error! : param.txt" << endl;
		exit(1);
	}


	char buf[256] = { 0 };
	char imgin_file[256] = { 0 };
	char imgout_file[256] = { 0 };
	int  i = 0;
	int mode = 0;
	int rsz = 0;
	int flt = 0;

	while (fgets(buf, 256, fp1))
	{
		if (buf[0] == '#')
		{
			continue;
		}

		switch (i)
		{
		case 0:  sscanf(buf, "%d", &mode);
			break;
		case 1:  sscanf(buf, "%d", &rsz);
			break;
		case 2:  sscanf(buf, "%d", &flt);
			break;
		case 3:  sscanf(buf, "%s", &imgin_file, 20);
			break;
		case 4:  sscanf(buf, "%s", &imgout_file, 20);
			break;
		default:
			break;
		}

		i++;
	}

	//create output.bmp and read exp.bmp
	bmp* rbmp;
	bmp* wbmp;
	bmp* ebmp;

	BMP_Header_Data rheader, wheader, eheader;;

	rbmp = new bmp(imgin_file, "READ");
	wbmp = new bmp(imgout_file, "WRITE");
	ebmp = new bmp("exp.bmp", "READ");

	rheader = rbmp->ReadHeader();
	eheader = ebmp->ReadHeader();

	wheader = rheader;


	int resize = 1;
	if (mode == 1)
	{
		if (rsz == 0)
		{
			resize = 2;
		}
		else if (rsz == 1)
		{
			resize = 4;
		}
	}

	wheader.ImageBodySize /= resize;
	wheader.FileSize = wheader.ImageBodySize + 54;
	wheader.Xsize /= resize;

	wbmp->WriteHeader(wheader);

	//receive pixel data
	while (scl_o_vsync.read() )
	{
		wait();
	}

	for (unsigned int y = 0; y < wheader.Ysize; y++)
	{
		for (unsigned int x = 0; x < wheader.Xsize; x++)
		{
			while (!scl_o_data_en.read() )
			{
				wait();
			}

			BMP_Pixel_Data oPD;
			sc_uint<8> out[3] = { 0, 0, 0 };
			out[0] = scl_o_data_r.read();
			out[1] = scl_o_data_g.read();
			out[2] = scl_o_data_b.read();
			oPD.R = (unsigned char)(out[0]);
			oPD.G = (unsigned char)(out[1]);
			oPD.B = (unsigned char)(out[2]);

			//compare the out data and exp data
			BMP_Pixel_Data ePD = ebmp->ReadPixel();
			if (oPD.R != ePD.R)
			{
				fprintf(stderr, "R error(%d, %d) exp: %d out: %d\n", y + 1, x + 1, int(ePD.R), int(out[0]));
			}

			if (oPD.G != ePD.G)
			{
				fprintf(stderr, "G error(%d, %d) exp: %d out: %d\n", y + 1, x + 1, int(ePD.G), int(out[1]));
			}

			if (oPD.B != ePD.B)
			{
				fprintf(stderr, "B error(%d, %d) exp: %d out: %d\n", y + 1, x + 1, int(ePD.B), int(out[2]));
			}
			
			wbmp->WritePixel(oPD);

			wait();
		}

	}

	delete rbmp;
	delete wbmp;

	sc_stop();
}