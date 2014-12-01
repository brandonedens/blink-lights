/** @file
 * Interface to software for performing fourier transform.
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
#ifndef FOURIER_TRANSFORM_HPP_
#define FOURIER_TRANSFORM_HPP_

/*******************************************************************************
 * Include Files
 */

#include <cstdint>
#include <vector>

/*******************************************************************************
 * Namespaces
 */
namespace bl {

/*******************************************************************************
 * Classes
 */

class FourierTransform
{
public:
	FourierTransform(const int samples_per_fft);
	/** Add data to the FFT transform. */
	void add(int16_t *data, size_t sz);
	/** Process the available data. */
	void process();
	std::vector<double>& fft() { return results; }

private:
	const int samples_max;
	std::vector<double> samples;
	std::vector<double> results;
};


}
#endif  // FOURIER_TRANSFORM_HPP_
