#include "bitmap.h"
namespace bitmap
{
	void drawbmp(const pixelvector & data, const char * filename, const uint_fast64_t & width, const uint_fast64_t & height)
	{
		unsigned int headers[13];
		FILE *outfile = nullptr;

		int extrabytes = 4 - ((width * 3) % 4);		//Padding

		if (extrabytes == 4)
			extrabytes = 0;

		int paddedsize = ((width * 3) + extrabytes) * height;

		headers[0] = paddedsize + 54;      // bfSize (whole file size)
		headers[1] = 0;                    // bfReserved (both)
		headers[2] = 54;                   // bfOffbits
		headers[3] = 40;                   // biSize
		headers[4] = width;  // biwidth
		headers[5] = height; // biheight

							 // Would have biPlanes and biBitCount in position 6, but they're shorts.
							 // It's easier to write them out separately (see below) than pretend
							 // they're a single int, especially with endian issues...

		headers[7] = 0;                    // biCompression
		headers[8] = paddedsize;           // biSizeImage
		headers[9] = 0;                    // biXPelsPerMeter
		headers[10] = 0;                    // biYPelsPerMeter
		headers[11] = 0;                    // biClrUsed
		headers[12] = 0;                    // biClrImportant

		outfile = fopen(filename, "wb");

		fprintf(outfile, "BM");

		for (int n = 0; n != 6; ++n)
		{
			fprintf(outfile, "%c", headers[n] & 0x000000FF);
			fprintf(outfile, "%c", (headers[n] & 0x0000FF00) >> 8);
			fprintf(outfile, "%c", (headers[n] & 0x00FF0000) >> 16);
			fprintf(outfile, "%c", (headers[n] & (unsigned int)0xFF000000) >> 24);
		}

		// These next 4 characters are for the biPlanes and biBitCount fields.

		fprintf(outfile, "%c", 1);
		fprintf(outfile, "%c", 0);
		fprintf(outfile, "%c", 24);
		fprintf(outfile, "%c", 0);

		for (int n = 7; n <= 12; n++)
		{
			fprintf(outfile, "%c", headers[n] & 0x000000FF);
			fprintf(outfile, "%c", (headers[n] & 0x0000FF00) >> 8);
			fprintf(outfile, "%c", (headers[n] & 0x00FF0000) >> 16);
			fprintf(outfile, "%c", (headers[n] & (unsigned int)0xFF000000) >> 24);
		}

		for (int y = height - 1; y >= 0; y--)     // BMP image format is written from bottom to top...
		{
			for (int x = 0; x <= width - 1; x++)
			{
				fprintf(outfile, "%c", data[y][x].getBlueByte());
				fprintf(outfile, "%c", data[y][x].getGreenByte());
				fprintf(outfile, "%c", data[y][x].getRedByte());
			}
			if (extrabytes)      // See above - BMP lines must be of lengths divisible by 4.
			{
				for (int n = 1; n <= extrabytes; n++)
				{
					fprintf(outfile, "%c", 0);
				}
			}
		}

		fclose(outfile);
		return;
	}

	void drawbmp(const bitvector8 & data, const char * filename, const uint_fast64_t & width, const uint_fast64_t & height)
	{
		unsigned int headers[13];
		FILE *outfile = nullptr;

		int extrabytes = 4 - ((width * 3) % 4);

		if (extrabytes == 4)
			extrabytes = 0;

		int paddedsize = ((width * 3) + extrabytes) * height;

		headers[0] = paddedsize + 54;
		headers[1] = 0;
		headers[2] = 54;
		headers[3] = 40;
		headers[4] = width;
		headers[5] = height;

		headers[7] = 0;
		headers[8] = paddedsize;
		headers[9] = 0;
		headers[10] = 0;
		headers[11] = 0;
		headers[12] = 0;

		outfile = fopen(filename, "wb");

		fprintf(outfile, "BM");

		for (int n = 0; n != 6; ++n)
		{
			fprintf(outfile, "%c", headers[n] & 0x000000FF);
			fprintf(outfile, "%c", (headers[n] & 0x0000FF00) >> 8);
			fprintf(outfile, "%c", (headers[n] & 0x00FF0000) >> 16);
			fprintf(outfile, "%c", (headers[n] & (unsigned int)0xFF000000) >> 24);
		}

		fprintf(outfile, "%c", 1);
		fprintf(outfile, "%c", 0);
		fprintf(outfile, "%c", 24);
		fprintf(outfile, "%c", 0);

		for (int n = 7; n <= 12; n++)
		{
			fprintf(outfile, "%c", headers[n] & 0x000000FF);
			fprintf(outfile, "%c", (headers[n] & 0x0000FF00) >> 8);
			fprintf(outfile, "%c", (headers[n] & 0x00FF0000) >> 16);
			fprintf(outfile, "%c", (headers[n] & (unsigned int)0xFF000000) >> 24);
		}

		for (int y = height - 1; y >= 0; y--)     // BMP image format is written from bottom to top...
		{
			for (int x = 0; x <= width - 1; x++)
			{
				fprintf(outfile, "%c", data[y][x]);
				fprintf(outfile, "%c", data[y][x]);
				fprintf(outfile, "%c", data[y][x]);
			}
			if (extrabytes)
			{
				for (int n = 1; n <= extrabytes; n++)
				{
					fprintf(outfile, "%c", 0);
				}
			}
		}

		fclose(outfile);
		return;
	}
}