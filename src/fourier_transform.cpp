/** @file
 * Implementation of software for performing fourier transform.
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
#include <cmath>

#include <iostream>

#include <fftw3.h>

#include "fourier_transform.hpp"

/*******************************************************************************
 * Namespaces
 */
using namespace std;
using namespace bl;

/*******************************************************************************
 * Constructors / Destructors
 */

FourierTransform::FourierTransform(const int samples_per_fft)
    : samples_max{samples_per_fft}, samples{}, results{} {}

/*******************************************************************************
 * Public Methods
 */

void FourierTransform::add(int16_t* data, size_t sz)
{
	// Erase samples from the beginning if we've exceeded our maximum
	// samples length allowed.
	const int new_len = samples.size() + sz;
	if (new_len > samples_max) {
		samples.erase(samples.begin(),
		              samples.begin() + (new_len - samples_max));
	}

	// Copy in the new samples.
	for (auto i = 0U; i < sz; i++) {
		samples.push_back(data[i]);
	}
}

void FourierTransform::process()
{
	const int nfft = samples.size();
	double* fft_in = (double*)fftw_malloc(sizeof(double) * nfft);
	for (auto i = 0; i < samples.size(); i++) {
		fft_in[i] = samples[i];
	}
	fftw_complex* fft_out =
	    (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * (nfft / 2 + 1));

	fftw_plan plan =
	    fftw_plan_dft_r2c_1d(nfft, fft_in, fft_out, FFTW_ESTIMATE);
	// TODO load fft_in
	fftw_execute(plan);

	results.clear();
	for (auto i = 0; i < (nfft / 2 + 1); i++) {
		auto re = fft_out[i][0];
		auto im = fft_out[i][1];
		auto mag = sqrt((re * re) + (im * im));

		results.push_back(mag);
	}

	fftw_destroy_plan(plan);
	fftw_free(fft_in);
	fftw_free(fft_out);
}

