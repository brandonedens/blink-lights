/** @file
 * Interface of audio_plot
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
#ifndef AUDIO_PLOT_HPP_
#define AUDIO_PLOT_HPP_

/*******************************************************************************
 * Include Files
 */
#include <memory>
#include <vector>

#include <QMainWindow>
#include <QWidget>

#include "qcustomplot.h"

/*******************************************************************************
 * Namespaces
 */
namespace bl
{

/*******************************************************************************
 * Classes
 */

class PlotWindow : public QMainWindow
{
	Q_OBJECT
public:
	explicit PlotWindow(QWidget *parent = 0);
	void add_data(int16_t* sample, size_t sz);
	void add_fft(std::vector<double>& data, size_t sz);
	void replot();

private:
	std::shared_ptr<QCustomPlot> plot;
};

}
#endif  // AUDIO_PLOT_HPP_
