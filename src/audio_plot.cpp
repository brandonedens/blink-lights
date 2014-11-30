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

int PlotWindow::ts = 0;

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

	setWindowTitle("Audio");
	setCentralWidget(plot.get());
}

/*******************************************************************************
 * Public Methods
 */

constexpr int disp_samps = (22050 / 100) * 2;

void PlotWindow::add_data(int16_t* sample, size_t sz)
{
	plot->graph(0)->removeDataBefore(ts - disp_samps);
	for (auto i = 0; i < sz; i += 100) {
		plot->graph(0)->addData(++ts, sample[i]);
	}
	plot->graph(0)->rescaleKeyAxis();
	plot->graph(0)->rescaleValueAxis();
	plot->replot();
}

