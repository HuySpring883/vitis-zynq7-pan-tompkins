/******************************************************************************
* Copyright (C) 2023 Advanced Micro Devices, Inc. All Rights Reserved.
* SPDX-License-Identifier: MIT
******************************************************************************/
/*
 * helloworld.c: simple test application
 *
 * This application configures UART 16550 to baud rate 9600.
 * PS7 UART (Zynq) is not initialized by this application, since
 * bootrom/bsp configures it to baud rate 115200
 *
 * ------------------------------------------------
 * | UART TYPE   BAUD RATE                        |
 * ------------------------------------------------
 *   uartns550   9600
 *   uartlite    Configurable only in HW design
 *   ps7_uart    115200 (configured by bootrom/bsp)
 */

#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include <stdlib.h> // For exit() function
#include "PanTompkins.h"


int main(int argc, char* argv[])
{
    init_platform();

    // --------------Input Arguments ------------------ //
	if (argc == 1 || argc > 3)
	{
		printf("\nProvide an input ecg filename!\n");
		printf("=================================\n");
		printf("Usage: PanTompkinsCMD FILENAME VERBOSITY\n\n");
		printf("Example: PanTompkinsCMD ecg.txt 1\n");
		printf("Reads ecg.txt and prints the results to both console and output file.\n\n");
		printf("Example: PanTompkinsCMD ecg.txt \n");
		printf("Reads ecg.txt but does not print to console and only prints to the file.\n");
		printf("Program prints the results in output.csv\n");
		exit(1);
	}

    int16_t delay, Rcount,s1, s2, s3, s4, s5, ThF1;
	uint16_t ThI1, SPKI, NPKI;
	int32_t RLoc, c, SampleCount;
	SampleCount = 0;

	Rcount = 0;
	int err, err1;


	// -------------- Reading Input File ------------------ //
	FILE *fptr, *fptr_out;
	err  = fopen_s(&fptr, argv[1], "r");
	err1  = fopen_s(&fptr_out, "output.csv", "w");
	if( err == 0 || err1 == 0)
	{
      printf( "The file %s was opened\n", argv[1]);

	  // -------header --------//
	  fprintf_s(fptr_out, "Input,LPFilter,HPFilter,DerivativeF,SQRFilter,MVAFilter,RBeat,RunningThI1,SignalLevel,NoiseLevel,RunningThF\n");
	}
	else
	{
      printf( "The file %s was not opened\n", argv[1]);
	  exit(1);
	}



	int verbosity = atoi(argv[2]);

	
	PT_init();															// Always Initialize the Algorithm before use ---> This prepares all filters and parameters

	// ------ Pass the signal sample by sample mimicing a real-time scenario ----------- //
	while (fscanf_s(fptr, "%ld", &c) != EOF) {
		++SampleCount;
		
		delay = PT_StateMachine((int16_t) c);							// This is the main function of the algorithm

		// ------- A positive delay to current sample is returned in case of beat detection ----------- //
		if (delay != 0)
		{
			RLoc = SampleCount - (int32_t) delay;
			++Rcount;
		}
		else
		{
			RLoc = 0;
		}

		// -------- Toolbox comes with many helper functions for debugging, see PanTompkins.c for more details ---------- //
		s1 = PT_get_LPFilter_output();
		s2 = PT_get_HPFilter_output();
		s3 = PT_get_DRFilter_output();
		s4 = PT_get_SQRFilter_output();
		s5 = PT_get_MVFilter_output();

		ThI1 = PT_get_ThI1_output();
		SPKI = PT_get_SKPI_output();
		NPKI = PT_get_NPKI_output();
		ThF1 = PT_get_ThF1_output();
		
		if (verbosity)
			printf("%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n", c, s1, s2, s3, s4, s5, RLoc, ThI1, SPKI, NPKI, ThF1);

		fprintf_s(fptr_out, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n", c, s1, s2, s3, s4, s5, RLoc, ThI1, SPKI, NPKI, ThF1);
		
	}
    printf("%d beats detected\n", Rcount);
	fclose(fptr);
	fclose(fptr_out);

    printf("Successfully ran ECG application");
    cleanup_platform();
    return 0;
}
