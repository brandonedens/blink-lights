/** @file
 * Main entry point into the software.
 *
 *==============================================================================
 * Copyright 2014 by Brandon Edens. All Rights Reserved
 *==============================================================================
 *
 * @author  Brandon Edens
 * @date    2014-11-30
 * @details
 *
 */

/*******************************************************************************
 * Include Files
 */

#include <iostream>
#include <thread>

#include <QApplication>

#include "audio_plot.hpp"
#include "fourier_transform.hpp"
#include "openal_capture.hpp"

/*******************************************************************************
 * Namespaces
 */
using namespace std;
using namespace bl;

/*******************************************************************************
 * Constants
 */

constexpr auto freq = 22050;

/******************************************************************************/

int main(int argc, char *argv[])
{
	QApplication app{argc, argv};
	PlotWindow win;
	win.show();

	OpenAlCapture cap{};
	FourierTransform fft{freq / 8};

	thread t{&OpenAlCapture::start, &cap,
	         [&fft, &win](int16_t* data, size_t sz) {
		win.add_data(data, sz);
		fft.add(data, sz);
		fft.process();
		auto fft_out = fft.fft();
		win.add_fft(fft_out, fft_out.size());
		win.replot();
	}};

	return app.exec();
}

