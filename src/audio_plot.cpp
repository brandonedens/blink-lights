/** @file
 * Implementation of audio_plot.
 *
 *==============================================================================
 * Copyright 2014 by Brandon Edens. All Rights Reserved
 *==============================================================================
 *
 * @author  Brandon Edens
 * @date    2014-11-22
 * @details
 *
 */

/*******************************************************************************
 * Include Files
 */
#include "audio_plot.hpp"

#include <QWidget>

/*******************************************************************************
 * Namespaces
 */
using namespace bl;

/*******************************************************************************
 * Static Initializers
 */

/*******************************************************************************
 * Constructors / Destructors
 */

PlotWindow::PlotWindow(QWidget *parent)
	: plot{new QCustomPlot(this)}
{
	plot->addGraph(); // blue line
	plot->graph(0)->setPen(QPen(Qt::blue));
	plot->graph(0)->setBrush(QBrush(QColor(240, 255, 200)));
	plot->graph(0)->setAntialiasedFill(false);

	auto *plot2 = new QCPAxisRect(plot.get(), true);
	plot->plotLayout()->addElement(1, 0, plot2);

	// Add the graph for the FFT.
	plot->addGraph(plot2->axis(QCPAxis::atBottom),
			plot2->axis(QCPAxis::atLeft));
	plot->graph(1)->setPen(QPen(Qt::red));
	plot->graph(1)->setBrush(QBrush(QColor(240, 255, 200)));
	plot->graph(1)->setAntialiasedFill(false);

	setWindowTitle("Audio");
	setCentralWidget(plot.get());
}

/*******************************************************************************
 * Public Methods
 */

constexpr int disp_samps = (22050 / 100) * 2;

void PlotWindow::add_data(int16_t* sample, size_t sz)
{
	static int ts = 0;
	plot->graph(0)->removeDataBefore(ts - disp_samps);
	for (auto i = 0; i < sz; i += 100) {
		plot->graph(0)->addData(++ts, sample[i]);
	}
	plot->graph(0)->rescaleKeyAxis();
	plot->graph(0)->rescaleValueAxis();
}

void PlotWindow::add_fft(std::vector<double>& data, size_t sz)
{
	static int i = 0;
	plot->graph(1)->clearData();
	for (auto i = 0; i < sz; i++) {
		plot->graph(1)->addData(i, data[i]);
	}
	plot->graph(1)->rescaleKeyAxis();
	if ((i % 10) == 0) {
		plot->graph(1)->rescaleValueAxis();
	} else {
		plot->graph(1)->rescaleValueAxis(true);
	}
	++i;
}

void PlotWindow::replot()
{
	plot->replot();
}

