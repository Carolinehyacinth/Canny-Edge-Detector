SC_MODULE(BlurY)
{
	sc_fifo_in<FKERNAL> KernelIn;
	sc_fifo_in<int> CenterIn;
	sc_fifo_in<FIMAGE> TempimIn;
	sc_fifo_out<SIMAGE> SmoothedimOut;
	sc_event e,e0, e1, e2, e3, e4, e5, e6, e7;

	FKERNAL kernel;
	int center;
	FIMAGE tempim;
	SIMAGE smoothedim;

	void blur_y(int rows, int cols, int count)
	{
	   int r, c, rr;         /* Counter variables. */
	   float dot,            /* Dot product summing variable. */
	         sum;            /* Sum of the kernel weights variable. */

	   /****************************************************************************
	   * Blur in the y - direction.
	   ****************************************************************************/
	   if(VERBOSE) printf("   Bluring the image in the Y-direction.\n");
	   for(c=(cols/8)*count; c<(cols/8)*(count+1);c++){
	      for(r=0;r<rows;r++){
	         sum = 0.0;
	         dot = 0.0;
	         for(rr=(-center);rr<=center;rr++){
	            if(((r+rr) >= 0) && ((r+rr) < rows)){
	               dot += tempim[(r+rr)*cols+c] * kernel[center+rr];
	               sum += kernel[center+rr];
	            }
	         }
	         smoothedim[r*cols+c] = (short int)(dot*BOOSTBLURFACTOR/sum + 0.5);
	      }
	   }
	}
	void BlurY_Slice_X0()
	{
		while(1)
		{
			wait(e);
	     	blur_y(ROWS, COLS,0);
	     	e0.notify();
		}
	}

	void BlurY_Slice_X1()
	{
		while(1)
		{
			wait(e);
	     	blur_y(ROWS, COLS, 1);
	     	e1.notify();
		}
	}

	void BlurY_Slice_X2()
	{
		while(1)
		{
			wait(e);
	     	blur_y(ROWS, COLS, 2);
	     	e2.notify();
		}
	}

	void BlurY_Slice_X3()
	{
		while(1)
		{
			wait(e);
	     	blur_y(ROWS, COLS, 3);
	     	e3.notify();
		}
	}

	void BlurY_Slice_X4()
	{
		while(1)
		{
			wait(e);
	     	blur_y(ROWS, COLS, 4);
	     	e4.notify();
		}
	}

	void BlurY_Slice_X5()
	{
		while(1)
		{
			wait(e);
	     	blur_y(ROWS, COLS, 5);
	     	e5.notify();
		}
	}

	void BlurY_Slice_X6()
	{
		while(1)
		{
			wait(e);
	     	blur_y(ROWS, COLS, 6);
	     	e6.notify();
		}
	}

	void BlurY_Slice_X7()
	{
		while(1)
		{
			wait(e);
	     	blur_y(ROWS, COLS, 7);
	     	e7.notify();
		}
	}
	void main(void)
	{
	   while(1)
	   {
	   	  wait(235,SC_MS);
	      TempimIn.read(tempim);
	      KernelIn.read(kernel);
	      CenterIn.read(center);
	      e.notify(SC_ZERO_TIME);
	      wait(e0 & e1 & e2 & e3 & e4 & e5 & e6);
	      SmoothedimOut.write(smoothedim);
	   }
	}

	SC_CTOR(BlurY)
	{
	   SC_THREAD(BlurY_Slice_X0);
	   SC_THREAD(BlurY_Slice_X1);
	   SC_THREAD(BlurY_Slice_X2);
	   SC_THREAD(BlurY_Slice_X3);
	   SC_THREAD(BlurY_Slice_X4);
	   SC_THREAD(BlurY_Slice_X5);
	   SC_THREAD(BlurY_Slice_X6);
	   SC_THREAD(BlurY_Slice_X7);
	   SC_THREAD(main);
	   SET_STACK_SIZE
	}
};
