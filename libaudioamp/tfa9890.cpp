/*
 * Copyright (C) 2013-2014, The CyanogenMod Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#define LOG_NDEBUG 0
#define LOG_TAG "tfa9890"

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <cutils/log.h>
#include <cutils/misc.h>
#include <sys/ioctl.h>
#include <system/audio.h>

#include "tfa9890.h"

struct tfa98xx_param_data tfa9890_param_data = {
	.size = 0,
	.type = 0,
	.data = NULL
};

/* Helper functions */

static int read_file(const char *file_name, unsigned char *buf, int sz) {
	int ret;
	int fd;

	fd = open(file_name, O_RDONLY);
	if (fd < 0) {
		ret = errno;
		ALOGE("%s: unable to open file %s: %d", __func__, file_name, ret);
		return ret;
	}

	ret = read(fd, buf, sz);
	if (ret < 0) {
		ret = errno;
		ALOGE("%s: error reading from file %s: %d", __func__, file_name, ret);
	}

	close(fd);
	return ret;
}

/* Module functions */

int tfa9890_prepare_for_ioctl(const char *file_name, unsigned int type) {
	int ret;
	unsigned int size;
	unsigned char buf[PARAM_SIZE_MAX];

	ALOGV("Preparing %s", file_name);

	/* Reset values */
	tfa9890_param_data.size = 0;
	tfa9890_param_data.type = 0;
	tfa9890_param_data.data = NULL;


	ret = read_file(file_name, buf, PARAM_SIZE_MAX);
	size = (ret > 0) ? ret : 0;

	/* Set the data for the ioctl arg */
	if (size)
		tfa9890_param_data.size = size;
	if (type)
		tfa9890_param_data.type = type;
	if (buf != NULL)
		tfa9890_param_data.data = buf;

	if (ret < 0)
		ALOGE("error in preparing %s: %d", file_name, ret);

	return ret;
}

int tfa9890_prepare_for_ioctl_eq(const char *file_name, unsigned int type) {
	ALOGV("Stub: (not actually) Preparing %s", file_name);

	/* Reset values */
	tfa9890_param_data.size = 0;
	tfa9890_param_data.type = 0;
	tfa9890_param_data.data = NULL;

	return 0;
}

/* Public functions */

int tfa9890_init(void) {
	int fd;
	int ret = 0;

	ALOGV("enter %s", __func__);

	/* Open the amplifier device */
	if ((fd = open(TFA9890_DEVICE, O_RDWR)) < 0) {
		ALOGE("error opening amplifier device %s", TFA9890_DEVICE);
		return -1;
	}

	/* The ".patch" files */
	TFA9890_IOCTL(TFA98XX_PATCH_PARAM, PATCH_DSP_FILE, PATCH_DSP)
	TFA9890_IOCTL(TFA98XX_PATCH_PARAM, PATCH_COLDBOOT_FILE, PATCH_COLDBOOT)

	/* The ".config" files */
	TFA9890_IOCTL(TFA98XX_CONFIG_PARAM, CONFIG_TOP, AMP_TOP)
	TFA9890_IOCTL(TFA98XX_CONFIG_PARAM, CONFIG_BOTTOM, AMP_BOTTOM)
	TFA9890_IOCTL(TFA98XX_CONFIG_PARAM, CONFIG_RECEIVER, AMP_RECEIVER)

	/* The ".speaker" files */
	TFA9890_IOCTL(TFA98XX_SPEAKER_PARAM, SPEAKER_TOP, AMP_TOP)
	TFA9890_IOCTL(TFA98XX_SPEAKER_PARAM, SPEAKER_BOTTOM, AMP_BOTTOM)

	/* The ".preset" files */
	TFA9890_IOCTL(TFA98XX_PRESET_PARAM, PRESET_HIFISPEAKER_TOP, TYPE_HIFISPEAKER_TOP)
	TFA9890_IOCTL(TFA98XX_PRESET_PARAM, PRESET_HIFISPEAKER_BOTTOM, TYPE_HIFISPEAKER_BOTTOM)
	TFA9890_IOCTL(TFA98XX_PRESET_PARAM, PRESET_HIFISPEAKER_RING_TOP, TYPE_HIFISPEAKER_RING_TOP)
	TFA9890_IOCTL(TFA98XX_PRESET_PARAM, PRESET_HIFISPEAKER_RING_BOTTOM, TYPE_HIFISPEAKER_RING_BOTTOM)
	TFA9890_IOCTL(TFA98XX_PRESET_PARAM, PRESET_HIFISPEAKER_SFORCE_TOP, TYPE_HIFISPEAKER_SFORCE_TOP)
	TFA9890_IOCTL(TFA98XX_PRESET_PARAM, PRESET_HIFISPEAKER_SFORCE_BOTTOM, TYPE_HIFISPEAKER_SFORCE_BOTTOM)
	TFA9890_IOCTL(TFA98XX_PRESET_PARAM, PRESET_VOICECALLSPEAKER_TOP, TYPE_VOICECALLSPEAKER_TOP)
	TFA9890_IOCTL(TFA98XX_PRESET_PARAM, PRESET_VOICECALLSPEAKER_BOTTOM, TYPE_VOICECALLSPEAKER_BOTTOM)
	TFA9890_IOCTL(TFA98XX_PRESET_PARAM, PRESET_FMSPEAKER_TOP, TYPE_FMSPEAKER_TOP)
	TFA9890_IOCTL(TFA98XX_PRESET_PARAM, PRESET_FMSPEAKER_BOTTOM, TYPE_FMSPEAKER_BOTTOM)
	TFA9890_IOCTL(TFA98XX_PRESET_PARAM, PRESET_VOICECALLEARPICE_TOP, TYPE_VOICECALLEARPICE_TOP)

	/* The ".eq" files */
	TFA9890_IOCTL_EQ(EQ_HIFISPEAKER_TOP, TYPE_HIFISPEAKER_TOP)
	TFA9890_IOCTL_EQ(EQ_HIFISPEAKER_BOTTOM, TYPE_HIFISPEAKER_BOTTOM)
	TFA9890_IOCTL_EQ(EQ_HIFISPEAKER_RING_TOP, TYPE_HIFISPEAKER_RING_TOP)
	TFA9890_IOCTL_EQ(EQ_HIFISPEAKER_RING_BOTTOM, TYPE_HIFISPEAKER_RING_BOTTOM)
	TFA9890_IOCTL_EQ(EQ_HIFISPEAKER_SFORCE_TOP, TYPE_HIFISPEAKER_SFORCE_TOP)
	TFA9890_IOCTL_EQ(EQ_HIFISPEAKER_SFORCE_BOTTOM, TYPE_HIFISPEAKER_SFORCE_BOTTOM)
	TFA9890_IOCTL_EQ(EQ_VOICECALLSPEAKER_TOP, TYPE_VOICECALLSPEAKER_TOP)
	TFA9890_IOCTL_EQ(EQ_VOICECALLSPEAKER_BOTTOM, TYPE_VOICECALLSPEAKER_BOTTOM)
	TFA9890_IOCTL_EQ(EQ_FMSPEAKER_TOP, TYPE_FMSPEAKER_TOP)
	TFA9890_IOCTL_EQ(EQ_FMSPEAKER_BOTTOM, TYPE_FMSPEAKER_BOTTOM)
	TFA9890_IOCTL_EQ(EQ_VOICECALLEARPICE_TOP, TYPE_VOICECALLEARPICE_TOP)

error:
	ALOGV("exit %s with %d", __func__, ret);
	close(fd);
	return ret;
}
