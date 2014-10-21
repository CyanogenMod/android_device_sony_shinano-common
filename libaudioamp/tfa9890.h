/*
 * Copyright (C) 2014, The CyanogenMod Project
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

/* From kernel */
#include <sound/tfa98xx.h>

#define TFA9890_DEVICE "/dev/tfa98xx"

/* All the files in /system/etc/tfa98xx */
#define PATCH_DSP_FILE "/system/etc/tfa98xx/TFA9890.patch"
#define PATCH_COLDBOOT_FILE "/system/etc/tfa98xx/coldboot.patch"

#define CONFIG_TOP "/system/etc/tfa98xx/TFA9890_top.config"
#define CONFIG_BOTTOM "/system/etc/tfa98xx/TFA9890_btm.config"
#define CONFIG_RECEIVER "/system/etc/tfa98xx/TFA9890_Receiver.config"

#define SPEAKER_TOP "/system/etc/tfa98xx/top.speaker"
#define SPEAKER_BOTTOM "/system/etc/tfa98xx/btm.speaker"

#define PRESET_HIFISPEAKER_TOP "/system/etc/tfa98xx/HiFiSpeaker_top.preset"
#define PRESET_HIFISPEAKER_BOTTOM "/system/etc/tfa98xx/HiFiSpeaker_btm.preset"
#define PRESET_HIFISPEAKER_RING_TOP "/system/etc/tfa98xx/HiFiSpeakerRing_top.preset"
#define PRESET_HIFISPEAKER_RING_BOTTOM "/system/etc/tfa98xx/HiFiSpeakerRing_btm.preset"
#define PRESET_HIFISPEAKER_SFORCE_TOP "/system/etc/tfa98xx/HiFiSpeakerSforce_top.preset"
#define PRESET_HIFISPEAKER_SFORCE_BOTTOM "/system/etc/tfa98xx/HiFiSpeakerSforce_btm.preset"
#define PRESET_VOICECALLSPEAKER_TOP "/system/etc/tfa98xx/VoiceCallSpeaker_top.preset"
#define PRESET_VOICECALLSPEAKER_BOTTOM "/system/etc/tfa98xx/VoiceCallSpeaker_btm.preset"
#define PRESET_FMSPEAKER_TOP "/system/etc/tfa98xx/FMSpeaker_top.preset"
#define PRESET_FMSPEAKER_BOTTOM "/system/etc/tfa98xx/FMSpeaker_btm.preset"
#define PRESET_VOICECALLEARPICE_TOP "/system/etc/tfa98xx/VoiceCallEarpice_top.preset"

#define EQ_HIFISPEAKER_TOP "/system/etc/tfa98xx/HiFiSpeaker_top.eq"
#define EQ_HIFISPEAKER_BOTTOM "/system/etc/tfa98xx/HiFiSpeaker_btm.eq"
#define EQ_HIFISPEAKER_RING_TOP "/system/etc/tfa98xx/HiFiSpeakerRing_top.eq"
#define EQ_HIFISPEAKER_RING_BOTTOM "/system/etc/tfa98xx/HiFiSpeakerRing_btm.eq"
#define EQ_HIFISPEAKER_SFORCE_TOP "/system/etc/tfa98xx/HiFiSpeakerSforce_top.eq"
#define EQ_HIFISPEAKER_SFORCE_BOTTOM "/system/etc/tfa98xx/HiFiSpeakerSforce_btm.eq"
#define EQ_VOICECALLSPEAKER_TOP "/system/etc/tfa98xx/VoiceCallSpeaker_top.eq"
#define EQ_VOICECALLSPEAKER_BOTTOM "/system/etc/tfa98xx/VoiceCallSpeaker_btm.eq"
#define EQ_FMSPEAKER_TOP "/system/etc/tfa98xx/FMSpeaker_top.eq"
#define EQ_FMSPEAKER_BOTTOM "/system/etc/tfa98xx/FMSpeaker_btm.eq"
#define EQ_VOICECALLEARPICE_TOP "/system/etc/tfa98xx/VoiceCallEarpice_top.eq"

/* Macros for ioctl with above files
 * This macro calls tfa9890_prepare_for_ioctl()
 * to setup the ioctl arg,
 * and then calls ioctl() */
#define TFA9890_IOCTL(ioctltype, filename, filetype) \
	ret = tfa9890_prepare_for_ioctl(filename, filetype); \
	if (ret > 0) { \
		ALOGV("ioctl %s", filename); \
		ret = ioctl(fd, ioctltype, &tfa9890_param_data); \
		if (ret == -1) { \
			ALOGE("ioctl failed for %s with %d", filename, errno); \
			goto error; \
		} \
	} else \
		goto error; \

/* Macro for only ".eq"/EQ_ files
 * Same as above but calls a different function
 * to setup the ioctl arg */
#define TFA9890_IOCTL_EQ(filename, filetype) \
	ret = tfa9890_prepare_for_ioctl_eq(filename, filetype); \
	if (!ret) { \
		ALOGV("ioctl %s", filename); \
		ret = ioctl(fd, TFA98XX_EQ_PARAM, &tfa9890_param_data); \
		if (ret == -1) { \
			ret = errno; \
			ALOGE("ioctl failed for %s with %d", filename, ret); \
			goto error; \
		} \
	} else \
		goto error; \

int tfa9890_init(void);

/* XXX: THis needs to go, or at least moved from here if it needs to stay.
 * EQ values for sirius
 * Dumped data the stock audio HAL sent to kernel via ioctl
 * TODO: Figure out the algorithm used to obtain this from the '.eq' files. */
static unsigned char eq_data[TYPE_MAX][190] = {
{ 1, 0, 0, 1, 195, 207, 36, 124, 24, 88, 19, 160, 244, 216, 190, 24, 19, 160, 244, 2, 0, 0, 1, 195, 104, 116, 124, 93, 192, 60, 98, 84, 131, 162, 64, 64, 53, 60, 3, 0, 0, 1, 198, 154, 48, 120, 91, 240, 56, 254, 176, 135, 164, 16, 64, 103, 32, 4, 0, 0, 2, 227, 93, 48, 60, 114, 246, 32, 58, 224, 188, 41, 228, 35, 203, 22, 5, 0, 0, 1, 200, 34, 84, 115, 93, 148, 54, 130, 108, 140, 162, 108, 65, 91, 64, 6, 0, 0, 1, 219, 166, 224, 79, 156, 140, 46, 11, 232, 176, 99, 116, 54, 77, 56, 7, 0, 0, 1, 232, 179, 128, 65, 162, 128, 26, 194, 24, 181, 8, 240, 69, 222, 252, 8, 0, 0, 1, 228, 54, 228, 29, 128, 232, 20, 80, 208, 226, 127, 24, 71, 120, 76, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 0, 0, 1, 237, 166, 188, 250, 157, 56, 34, 195, 48, 69, 134, 100, 34, 195, 48 },
{ 1, 0, 0, 1, 194, 5, 164, 125, 231, 176, 12, 144, 120, 230, 223, 16, 12, 144, 120, 2, 0, 0, 1, 195, 67, 136, 124, 135, 132, 60, 55, 132, 131, 120, 124, 64, 132, 244, 3, 0, 0, 1, 197, 179, 128, 121, 64, 168, 56, 20, 144, 134, 191, 88, 66, 55, 244, 4, 0, 0, 1, 214, 7, 48, 58, 223, 244, 28, 84, 28, 197, 32, 12, 77, 164, 176, 5, 0, 0, 1, 208, 72, 68, 99, 138, 140, 50, 24, 104, 156, 117, 116, 61, 159, 80, 6, 0, 0, 1, 219, 210, 28, 73, 144, 92, 44, 108, 60, 182, 111, 164, 55, 193, 164, 7, 0, 0, 1, 236, 194, 24, 54, 15, 176, 33, 134, 52, 161, 200, 240, 89, 223, 20, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 0, 0, 1, 196, 186, 100, 122, 87, 4, 58, 168, 232, 133, 168, 252, 64, 156, 180, 10, 0, 0, 0, 217, 102, 176, 43, 30, 112, 48, 236, 248, 97, 217, 232, 48, 236, 248 },
{ 1, 0, 0, 1, 194, 95, 244, 125, 141, 108, 17, 178, 168, 220, 154, 176, 17, 178, 168, 2, 0, 0, 1, 195, 104, 116, 124, 93, 192, 59, 227, 152, 131, 162, 64, 64, 179, 244, 3, 0, 0, 1, 198, 154, 48, 120, 91, 240, 56, 254, 176, 135, 164, 16, 64, 103, 32, 4, 0, 0, 1, 204, 92, 16, 103, 9, 76, 53, 113, 252, 152, 246, 180, 62, 49, 248, 5, 0, 0, 1, 200, 34, 84, 115, 93, 148, 54, 130, 108, 140, 162, 108, 65, 91, 64, 6, 0, 0, 1, 211, 232, 68, 85, 193, 120, 49, 153, 168, 170, 62, 136, 58, 126, 20, 7, 0, 0, 1, 232, 179, 128, 65, 162, 128, 26, 194, 24, 181, 8, 240, 69, 222, 252, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 80, 146, 60, 10, 0, 0, 1, 237, 166, 188, 250, 157, 56, 34, 195, 48, 69, 134, 100, 34, 195, 48 },
{ 1, 0, 0, 1, 196, 145, 112, 123, 13, 40, 12, 75, 132, 231, 104, 248, 12, 75, 132, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 1, 197, 179, 128, 121, 64, 168, 56, 20, 144, 134, 191, 88, 66, 55, 244, 4, 0, 0, 1, 214, 7, 48, 58, 223, 244, 28, 84, 28, 197, 32, 12, 77, 164, 176, 5, 0, 0, 1, 208, 72, 68, 99, 138, 140, 50, 24, 104, 156, 117, 116, 61, 159, 80, 6, 0, 0, 1, 219, 210, 28, 73, 144, 92, 44, 108, 60, 182, 111, 164, 55, 193, 164, 7, 0, 0, 1, 236, 194, 24, 54, 15, 176, 33, 134, 52, 161, 200, 240, 89, 223, 20, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 0, 0, 1, 196, 186, 100, 122, 87, 4, 58, 168, 232, 133, 168, 252, 64, 156, 180, 10, 0, 0, 0, 217, 102, 176, 43, 30, 112, 48, 236, 248, 97, 217, 232, 48, 236, 248 },
{ 1, 0, 0, 1, 195, 207, 36, 124, 24, 88, 19, 160, 244, 216, 190, 24, 19, 160, 244, 2, 0, 0, 1, 195, 104, 116, 124, 93, 192, 60, 98, 84, 131, 162, 64, 64, 53, 60, 3, 0, 0, 1, 198, 154, 48, 120, 91, 240, 56, 254, 176, 135, 164, 16, 64, 103, 32, 4, 0, 0, 2, 227, 93, 48, 60, 114, 246, 32, 58, 224, 188, 41, 228, 35, 203, 22, 5, 0, 0, 1, 200, 34, 84, 115, 93, 148, 54, 130, 108, 140, 162, 108, 65, 91, 64, 6, 0, 0, 1, 219, 166, 224, 79, 156, 140, 46, 11, 232, 176, 99, 116, 54, 77, 56, 7, 0, 0, 1, 232, 179, 128, 65, 162, 128, 26, 194, 24, 181, 8, 240, 69, 222, 252, 8, 0, 0, 1, 228, 54, 228, 29, 128, 232, 20, 80, 208, 226, 127, 24, 71, 120, 76, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 0, 0, 1, 237, 166, 188, 250, 157, 56, 34, 195, 48, 69, 134, 100, 34, 195, 48 },
{ 1, 0, 0, 1, 194, 5, 164, 125, 231, 176, 12, 144, 120, 230, 223, 16, 12, 144, 120, 2, 0, 0, 1, 195, 67, 136, 124, 135, 132, 60, 55, 132, 131, 120, 124, 64, 132, 244, 3, 0, 0, 1, 197, 179, 128, 121, 64, 168, 56, 20, 144, 134, 191, 88, 66, 55, 244, 4, 0, 0, 1, 214, 7, 48, 58, 223, 244, 28, 84, 28, 197, 32, 12, 77, 164, 176, 5, 0, 0, 1, 208, 72, 68, 99, 138, 140, 50, 24, 104, 156, 117, 116, 61, 159, 80, 6, 0, 0, 1, 219, 210, 28, 73, 144, 92, 44, 108, 60, 182, 111, 164, 55, 193, 164, 7, 0, 0, 1, 236, 194, 24, 54, 15, 176, 33, 134, 52, 161, 200, 240, 89, 223, 20, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 0, 0, 1, 196, 186, 100, 122, 87, 4, 58, 168, 232, 133, 168, 252, 64, 156, 180, 10, 0, 0, 0, 217, 102, 176, 43, 30, 112, 48, 236, 248, 97, 217, 232, 48, 236, 248 },
{ 1, 0, 0, 1, 196, 124, 228, 123, 63, 108, 51, 231, 216, 152, 48, 80, 51, 231, 216, 2, 0, 0, 1, 219, 122, 52, 92, 222, 236, 1, 233, 184, 3, 211, 112, 1, 233, 184, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 1, 0, 0, 1, 196, 124, 228, 123, 63, 108, 51, 231, 216, 152, 48, 80, 51, 231, 216, 2, 0, 0, 1, 219, 122, 52, 92, 222, 236, 1, 233, 184, 3, 211, 112, 1, 233, 184, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 1, 0, 0, 1, 195, 207, 36, 124, 24, 88, 19, 160, 244, 216, 190, 24, 19, 160, 244, 2, 0, 0, 1, 195, 104, 116, 124, 93, 192, 60, 98, 84, 131, 162, 64, 64, 53, 60, 3, 0, 0, 1, 198, 154, 48, 120, 91, 240, 56, 254, 176, 135, 164, 16, 64, 103, 32, 4, 0, 0, 2, 227, 93, 48, 60, 114, 246, 32, 58, 224, 188, 41, 228, 35, 203, 22, 5, 0, 0, 1, 200, 34, 84, 115, 93, 148, 54, 130, 108, 140, 162, 108, 65, 91, 64, 6, 0, 0, 1, 219, 166, 224, 79, 156, 140, 46, 11, 232, 176, 99, 116, 54, 77, 56, 7, 0, 0, 1, 232, 179, 128, 65, 162, 128, 26, 194, 24, 181, 8, 240, 69, 222, 252, 8, 0, 0, 1, 228, 54, 228, 29, 128, 232, 20, 80, 208, 226, 127, 24, 71, 120, 76, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 0, 0, 1, 237, 166, 188, 250, 157, 56, 34, 195, 48, 69, 134, 100, 34, 195, 48 },
{ 1, 0, 0, 1, 194, 5, 164, 125, 231, 176, 12, 144, 120, 230, 223, 16, 12, 144, 120, 2, 0, 0, 1, 195, 67, 136, 124, 135, 132, 60, 55, 132, 131, 120, 124, 64, 132, 244, 3, 0, 0, 1, 197, 179, 128, 121, 64, 168, 56, 20, 144, 134, 191, 88, 66, 55, 244, 4, 0, 0, 1, 214, 7, 48, 58, 223, 244, 28, 84, 28, 197, 32, 12, 77, 164, 176, 5, 0, 0, 1, 208, 72, 68, 99, 138, 140, 50, 24, 104, 156, 117, 116, 61, 159, 80, 6, 0, 0, 1, 219, 210, 28, 73, 144, 92, 44, 108, 60, 182, 111, 164, 55, 193, 164, 7, 0, 0, 1, 236, 194, 24, 54, 15, 176, 33, 134, 52, 161, 200, 240, 89, 223, 20, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 0, 0, 1, 196, 186, 100, 122, 87, 4, 58, 168, 232, 133, 168, 252, 64, 156, 180, 10, 0, 0, 0, 217, 102, 176, 43, 30, 112, 48, 236, 248, 97, 217, 232, 48, 236, 248 },
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 225, 214, 112, 79, 20, 200, 19, 197, 48, 39, 138, 104, 19, 197, 48, 9, 0, 0, 0, 234, 90, 0, 198, 187, 104, 51, 186, 168, 103, 117, 72, 51, 186, 168, 10, 0, 0, 0, 230, 68, 176, 10, 13, 248, 35, 235, 88, 71, 214, 176, 35, 235, 88 }
};
