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

int main(int argc, char *argv[])
{
	QApplication app{argc, argv};
	PlotWindow win;
	win.show();

	OpenAlCapture cap{};
	thread t{&OpenAlCapture::start, &cap, [&win](int16_t* data, size_t sz) {
		win.add_data(data, sz);
	}};

	return app.exec();
}

