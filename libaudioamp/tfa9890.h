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

/* From kernel */
#include <sound/tfa98xx.h>

#define TFA9890_DEVICE "/dev/tfa98xx"

#define PATCH_DSP_FILE "/system/etc/tfa98xx/TFA9890.patch"
#define PATCH_COLDBOOT_FILE "/system/etc/tfa98xx/coldboot.patch"

#define CONFIG_TOP "/system/etc/tfa98xx/TFA9890_top.config"
#define CONFIG_BTM "/system/etc/tfa98xx/TFA9890_btm.config"

#define SPEAKER_TOP "/system/etc/tfa98xx/top.speaker"
#define SPEAKER_BTM "/system/etc/tfa98xx/btm.speaker"

//TODO: Rearrange, Top then Bottom, and according to the enum in sound/tfa98xx.h
#define PRESET_FM_SPEAKER_BTM "/system/etc/tfa98xx/FMSpeaker_btm.preset"
#define PRESET_FM_SPEAKER_TOP "/system/etc/tfa98xx/FMSpeaker_top.preset"
#define PRESET_SPEAKER_RING_BTM "/system/etc/tfa98xx/HiFiSpeakerRing_btm.preset"
#define PRESET_SPEAKER_RING_TOP "/system/etc/tfa98xx/HiFiSpeakerRing_top.preset"
#define PRESET_SPEAKER_SFORCE_BTM "/system/etc/tfa98xx/HiFiSpeakerSforce_btm.preset"
#define PRESET_SPEAKER_SFORCE_TOP "/system/etc/tfa98xx/HiFiSpeakerSforce_top.preset"
#define PRESET_SPEAKER_BTM "/system/etc/tfa98xx/HiFiSpeaker_btm.preset"
#define PRESET_SPEAKER_TOP "/system/etc/tfa98xx/HiFiSpeaker_top.preset"
#define PRESET_VOICE_EARPIECE_TOP "/system/etc/tfa98xx/VoiceCallEarpice_top.preset" // unused
#define PRESET_VOICE_SPEAKER_BTM "/system/etc/tfa98xx/VoiceCallSpeaker_btm.preset"
#define PRESET_VOICE_SPEAKER_TOP "/system/etc/tfa98xx/VoiceCallSpeaker_top.preset"

#define EQ_FM_SPEAKER_BTM "/system/etc/tfa98xx/FMSpeaker_btm.eq"
#define EQ_FM_SPEAKER_TOP "/system/etc/tfa98xx/FMSpeaker_top.eq"
#define EQ_SPEAKER_RING_BTM "/system/etc/tfa98xx/HiFiSpeakerRing_btm.eq"
#define EQ_SPEAKER_RING_TOP "/system/etc/tfa98xx/HiFiSpeakerRing_top.eq"
#define EQ_SPEAKER_SFORCE_BTM "/system/etc/tfa98xx/HiFiSpeakerSforce_btm.eq"
#define EQ_SPEAKER_SFORCE_TOP "/system/etc/tfa98xx/HiFiSpeakerSforce_top.eq"
#define EQ_SPEAKER_BTM "/system/etc/tfa98xx/HiFiSpeaker_btm.eq"
#define EQ_SPEAKER_TOP "/system/etc/tfa98xx/HiFiSpeaker_top.eq"
#define EQ_VOICE_EARPIECE_TOP "/system/etc/tfa98xx/VoiceCallEarpice_top.eq" // unused
#define EQ_VOICE_SPEAKER_BTM "/system/etc/tfa98xx/VoiceCallSpeaker_btm.eq"
#define EQ_VOICE_SPEAKER_TOP "/system/etc/tfa98xx/VoiceCallSpeaker_top.eq"

int tfa9890_init(void);
