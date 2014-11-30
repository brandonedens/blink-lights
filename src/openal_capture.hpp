/** @file
 * Interface to OpenAL microphone capture.
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
#ifndef OPENAL_CAPTURE_HPP_
#define OPENAL_CAPTURE_HPP_

/*******************************************************************************
 * Include Files
 */

#include <cstdint>

#include <functional>

#include <AL/al.h>
#include <AL/alc.h>

/*******************************************************************************
 * Namespaces
 */
namespace bl {

/*******************************************************************************
 * Classes
 */

class OpenAlCapture
{
public:
	~OpenAlCapture();
	OpenAlCapture();
	void start(const std::function<void (int16_t*, size_t)>& f);

private:
	ALCdevice* device;
	ALCcontext* context;
	ALCdevice* in_device;
	ALuint src;
};

}
#endif  // OPENAL_CAPTURE_HPP_
