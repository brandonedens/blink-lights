/** @file
 * Implementation of software for capturing audio from OpenAL microphone
 * interface.
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

#include "openal_capture.hpp"

#include <array>
#include <chrono>
#include <iostream>
#include <thread>

/*******************************************************************************
 * Namespaces
 */

using namespace std;
using namespace bl;

/*******************************************************************************
 * Constants
 */

// Sample rate
constexpr auto freq = 22050;

// How much to capture at a time (affects latency)
constexpr auto cap_size = 2048;

/*******************************************************************************
 * Constructors / Destructors
 */

OpenAlCapture::OpenAlCapture()
{
	// Grab the default audio device.
	device = alcOpenDevice(nullptr); // Request default audio device
	if (alcGetError(device)) {
		throw runtime_error("Failure to get default audio device.");
	}

	// Create the audio context
	context = alcCreateContext(device, nullptr);
	alcMakeContextCurrent(context);
	if (alcGetError(device)) {
		throw runtime_error("Failure to get audio context.");
	}

	// Request the default capture device with a half-second buffer
	in_device = alcCaptureOpenDevice(nullptr, freq, AL_FORMAT_MONO16, freq / 2);
	if (alcGetError(device)) {
		throw runtime_error("Failure to open capture device.");
	}

	alcCaptureStart(in_device); // Begin capturing
	if (alcGetError(device)) {
		throw runtime_error("Failure to start audio capture.");
	}

	alGenSources(1, &src); // Create a sound source
	if (alGetError()) {
		throw runtime_error("Failure to create sound source.");
	}
}

OpenAlCapture::~OpenAlCapture()
{
	// Stop capture
	alcCaptureStop(in_device);
	alcCaptureCloseDevice(in_device);

	// Stop the sources
	alSourceStopv(1, &src);
	alSourcei(src, AL_BUFFER, 0);

	// Clean-up
	alDeleteSources(1, &src);
	if (alGetError()) {
		throw runtime_error("Failure to delete snd bufs.");
	}

	alcMakeContextCurrent(nullptr);
	if (alGetError()) {
		throw runtime_error("Failure to make context current.");
	}

	alcDestroyContext(context);
	alcCloseDevice(device);
}

/*******************************************************************************
 * Public Methods
 */

void OpenAlCapture::start(const function<void (int16_t*, size_t)>& f)
{
	cout << "exec start()" << endl;
	array<short, freq * 2> buffer;
	ALCint num_samples = 0;   // How many samples are captured

	while (true) {
		// Poll for captured audio
		alcGetIntegerv(in_device, ALC_CAPTURE_SAMPLES, 1, &num_samples);
		if (num_samples > cap_size) {
			// Grab the sound
			alcCaptureSamples(in_device, buffer.data(), cap_size);
			f(buffer.data(), cap_size);
		} else {
			// Sleep for a moment then continue.
			this_thread::sleep_for(chrono::milliseconds(10));
		}
	}
}

