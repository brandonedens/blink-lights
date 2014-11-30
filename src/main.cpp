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
#include "openal_capture.hpp"

/*******************************************************************************
 * Namespaces
 */
using namespace std;
using namespace bl;

/******************************************************************************/

/** Print sample data. */
static void print_samples(int16_t* data, size_t sz)
{
	for (auto i = 0U; i < sz; i += 5) {
		for (auto j = 0; j < data[i]; j += 30) {
			cout << "*";
		}
		cout << endl;
	}
}

int main(int argc, char *argv[])
{
	QApplication app{argc, argv};
	PlotWindow win;
	win.show();

	OpenAlCapture cap{};
	thread t{&OpenAlCapture::start, &cap, [&win](int16_t* data, size_t sz) {
#if 1
		win.add_data(data, sz);
#else
		print_samples(data, sz);
#endif
	}};

	return app.exec();
}

