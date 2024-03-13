#include <stdio.h>
#include <stdint.h>
#include <io.h>
#include <stdarg.h>
#include <mbctype.h>
#include <locale.h>
#include <lychy.h>

#pragma region Wave Formats
/* WAVE form wFormatTag IDs */
#define  WAVE_FORMAT_UNKNOWN                    0x0000 /* Microsoft Corporation */
#define WAVE_FORMAT_PCM         1
#define  WAVE_FORMAT_ADPCM                      0x0002 /* Microsoft Corporation */
#define  WAVE_FORMAT_IEEE_FLOAT                 0x0003 /* Microsoft Corporation */
#define  WAVE_FORMAT_VSELP                      0x0004 /* Compaq Computer Corp. */
#define  WAVE_FORMAT_IBM_CVSD                   0x0005 /* IBM Corporation */
#define  WAVE_FORMAT_ALAW                       0x0006 /* Microsoft Corporation */
#define  WAVE_FORMAT_MULAW                      0x0007 /* Microsoft Corporation */
#define  WAVE_FORMAT_DTS                        0x0008 /* Microsoft Corporation */
#define  WAVE_FORMAT_DRM                        0x0009 /* Microsoft Corporation */
#define  WAVE_FORMAT_WMAVOICE9                  0x000A /* Microsoft Corporation */
#define  WAVE_FORMAT_WMAVOICE10                 0x000B /* Microsoft Corporation */
#define  WAVE_FORMAT_OKI_ADPCM                  0x0010 /* OKI */
#define  WAVE_FORMAT_DVI_ADPCM                  0x0011 /* Intel Corporation */
#define  WAVE_FORMAT_IMA_ADPCM                  (WAVE_FORMAT_DVI_ADPCM) /*  Intel Corporation */
#define  WAVE_FORMAT_MEDIASPACE_ADPCM           0x0012 /* Videologic */
#define  WAVE_FORMAT_SIERRA_ADPCM               0x0013 /* Sierra Semiconductor Corp */
#define  WAVE_FORMAT_G723_ADPCM                 0x0014 /* Antex Electronics Corporation */
#define  WAVE_FORMAT_DIGISTD                    0x0015 /* DSP Solutions, Inc. */
#define  WAVE_FORMAT_DIGIFIX                    0x0016 /* DSP Solutions, Inc. */
#define  WAVE_FORMAT_DIALOGIC_OKI_ADPCM         0x0017 /* Dialogic Corporation */
#define  WAVE_FORMAT_MEDIAVISION_ADPCM          0x0018 /* Media Vision, Inc. */
#define  WAVE_FORMAT_CU_CODEC                   0x0019 /* Hewlett-Packard Company */
#define  WAVE_FORMAT_HP_DYN_VOICE               0x001A /* Hewlett-Packard Company */
#define  WAVE_FORMAT_YAMAHA_ADPCM               0x0020 /* Yamaha Corporation of America */
#define  WAVE_FORMAT_SONARC                     0x0021 /* Speech Compression */
#define  WAVE_FORMAT_DSPGROUP_TRUESPEECH        0x0022 /* DSP Group, Inc */
#define  WAVE_FORMAT_ECHOSC1                    0x0023 /* Echo Speech Corporation */
#define  WAVE_FORMAT_AUDIOFILE_AF36             0x0024 /* Virtual Music, Inc. */
#define  WAVE_FORMAT_APTX                       0x0025 /* Audio Processing Technology */
#define  WAVE_FORMAT_AUDIOFILE_AF10             0x0026 /* Virtual Music, Inc. */
#define  WAVE_FORMAT_PROSODY_1612               0x0027 /* Aculab plc */
#define  WAVE_FORMAT_LRC                        0x0028 /* Merging Technologies S.A. */
#define  WAVE_FORMAT_DOLBY_AC2                  0x0030 /* Dolby Laboratories */
#define  WAVE_FORMAT_GSM610                     0x0031 /* Microsoft Corporation */
#define  WAVE_FORMAT_MSNAUDIO                   0x0032 /* Microsoft Corporation */
#define  WAVE_FORMAT_ANTEX_ADPCME               0x0033 /* Antex Electronics Corporation */
#define  WAVE_FORMAT_CONTROL_RES_VQLPC          0x0034 /* Control Resources Limited */
#define  WAVE_FORMAT_DIGIREAL                   0x0035 /* DSP Solutions, Inc. */
#define  WAVE_FORMAT_DIGIADPCM                  0x0036 /* DSP Solutions, Inc. */
#define  WAVE_FORMAT_CONTROL_RES_CR10           0x0037 /* Control Resources Limited */
#define  WAVE_FORMAT_NMS_VBXADPCM               0x0038 /* Natural MicroSystems */
#define  WAVE_FORMAT_CS_IMAADPCM                0x0039 /* Crystal Semiconductor IMA ADPCM */
#define  WAVE_FORMAT_ECHOSC3                    0x003A /* Echo Speech Corporation */
#define  WAVE_FORMAT_ROCKWELL_ADPCM             0x003B /* Rockwell International */
#define  WAVE_FORMAT_ROCKWELL_DIGITALK          0x003C /* Rockwell International */
#define  WAVE_FORMAT_XEBEC                      0x003D /* Xebec Multimedia Solutions Limited */
#define  WAVE_FORMAT_G721_ADPCM                 0x0040 /* Antex Electronics Corporation */
#define  WAVE_FORMAT_G728_CELP                  0x0041 /* Antex Electronics Corporation */
#define  WAVE_FORMAT_MSG723                     0x0042 /* Microsoft Corporation */
#define  WAVE_FORMAT_INTEL_G723_1               0x0043 /* Intel Corp. */
#define  WAVE_FORMAT_INTEL_G729                 0x0044 /* Intel Corp. */
#define  WAVE_FORMAT_SHARP_G726                 0x0045 /* Sharp */
#define  WAVE_FORMAT_MPEG                       0x0050 /* Microsoft Corporation */
#define  WAVE_FORMAT_RT24                       0x0052 /* InSoft, Inc. */
#define  WAVE_FORMAT_PAC                        0x0053 /* InSoft, Inc. */
#define  WAVE_FORMAT_MPEGLAYER3                 0x0055 /* ISO/MPEG Layer3 Format Tag */
#define  WAVE_FORMAT_LUCENT_G723                0x0059 /* Lucent Technologies */
#define  WAVE_FORMAT_CIRRUS                     0x0060 /* Cirrus Logic */
#define  WAVE_FORMAT_ESPCM                      0x0061 /* ESS Technology */
#define  WAVE_FORMAT_VOXWARE                    0x0062 /* Voxware Inc */
#define  WAVE_FORMAT_CANOPUS_ATRAC              0x0063 /* Canopus, co., Ltd. */
#define  WAVE_FORMAT_G726_ADPCM                 0x0064 /* APICOM */
#define  WAVE_FORMAT_G722_ADPCM                 0x0065 /* APICOM */
#define  WAVE_FORMAT_DSAT                       0x0066 /* Microsoft Corporation */
#define  WAVE_FORMAT_DSAT_DISPLAY               0x0067 /* Microsoft Corporation */
#define  WAVE_FORMAT_VOXWARE_BYTE_ALIGNED       0x0069 /* Voxware Inc */
#define  WAVE_FORMAT_VOXWARE_AC8                0x0070 /* Voxware Inc */
#define  WAVE_FORMAT_VOXWARE_AC10               0x0071 /* Voxware Inc */
#define  WAVE_FORMAT_VOXWARE_AC16               0x0072 /* Voxware Inc */
#define  WAVE_FORMAT_VOXWARE_AC20               0x0073 /* Voxware Inc */
#define  WAVE_FORMAT_VOXWARE_RT24               0x0074 /* Voxware Inc */
#define  WAVE_FORMAT_VOXWARE_RT29               0x0075 /* Voxware Inc */
#define  WAVE_FORMAT_VOXWARE_RT29HW             0x0076 /* Voxware Inc */
#define  WAVE_FORMAT_VOXWARE_VR12               0x0077 /* Voxware Inc */
#define  WAVE_FORMAT_VOXWARE_VR18               0x0078 /* Voxware Inc */
#define  WAVE_FORMAT_VOXWARE_TQ40               0x0079 /* Voxware Inc */
#define  WAVE_FORMAT_VOXWARE_SC3                0x007A /* Voxware Inc */
#define  WAVE_FORMAT_VOXWARE_SC3_1              0x007B /* Voxware Inc */
#define  WAVE_FORMAT_SOFTSOUND                  0x0080 /* Softsound, Ltd. */
#define  WAVE_FORMAT_VOXWARE_TQ60               0x0081 /* Voxware Inc */
#define  WAVE_FORMAT_MSRT24                     0x0082 /* Microsoft Corporation */
#define  WAVE_FORMAT_G729A                      0x0083 /* AT&T Labs, Inc. */
#define  WAVE_FORMAT_MVI_MVI2                   0x0084 /* Motion Pixels */
#define  WAVE_FORMAT_DF_G726                    0x0085 /* DataFusion Systems (Pty) (Ltd) */
#define  WAVE_FORMAT_DF_GSM610                  0x0086 /* DataFusion Systems (Pty) (Ltd) */
#define  WAVE_FORMAT_ISIAUDIO                   0x0088 /* Iterated Systems, Inc. */
#define  WAVE_FORMAT_ONLIVE                     0x0089 /* OnLive! Technologies, Inc. */
#define  WAVE_FORMAT_MULTITUDE_FT_SX20          0x008A /* Multitude Inc. */
#define  WAVE_FORMAT_INFOCOM_ITS_G721_ADPCM     0x008B /* Infocom */
#define  WAVE_FORMAT_CONVEDIA_G729              0x008C /* Convedia Corp. */
#define  WAVE_FORMAT_CONGRUENCY                 0x008D /* Congruency Inc. */
#define  WAVE_FORMAT_SBC24                      0x0091 /* Siemens Business Communications Sys */
#define  WAVE_FORMAT_DOLBY_AC3_SPDIF            0x0092 /* Sonic Foundry */
#define  WAVE_FORMAT_MEDIASONIC_G723            0x0093 /* MediaSonic */
#define  WAVE_FORMAT_PROSODY_8KBPS              0x0094 /* Aculab plc */
#define  WAVE_FORMAT_ZYXEL_ADPCM                0x0097 /* ZyXEL Communications, Inc. */
#define  WAVE_FORMAT_PHILIPS_LPCBB              0x0098 /* Philips Speech Processing */
#define  WAVE_FORMAT_PACKED                     0x0099 /* Studer Professional Audio AG */
#define  WAVE_FORMAT_MALDEN_PHONYTALK           0x00A0 /* Malden Electronics Ltd. */
#define  WAVE_FORMAT_RACAL_RECORDER_GSM         0x00A1 /* Racal recorders */
#define  WAVE_FORMAT_RACAL_RECORDER_G720_A      0x00A2 /* Racal recorders */
#define  WAVE_FORMAT_RACAL_RECORDER_G723_1      0x00A3 /* Racal recorders */
#define  WAVE_FORMAT_RACAL_RECORDER_TETRA_ACELP 0x00A4 /* Racal recorders */
#define  WAVE_FORMAT_NEC_AAC                    0x00B0 /* NEC Corp. */
#define  WAVE_FORMAT_RAW_AAC1                   0x00FF /* For Raw AAC, with format block AudioSpecificConfig() (as defined by MPEG-4), that follows WAVEFORMATEX */
#define  WAVE_FORMAT_RHETOREX_ADPCM             0x0100 /* Rhetorex Inc. */
#define  WAVE_FORMAT_IRAT                       0x0101 /* BeCubed Software Inc. */
#define  WAVE_FORMAT_VIVO_G723                  0x0111 /* Vivo Software */
#define  WAVE_FORMAT_VIVO_SIREN                 0x0112 /* Vivo Software */
#define  WAVE_FORMAT_PHILIPS_CELP               0x0120 /* Philips Speech Processing */
#define  WAVE_FORMAT_PHILIPS_GRUNDIG            0x0121 /* Philips Speech Processing */
#define  WAVE_FORMAT_DIGITAL_G723               0x0123 /* Digital Equipment Corporation */
#define  WAVE_FORMAT_SANYO_LD_ADPCM             0x0125 /* Sanyo Electric Co., Ltd. */
#define  WAVE_FORMAT_SIPROLAB_ACEPLNET          0x0130 /* Sipro Lab Telecom Inc. */
#define  WAVE_FORMAT_SIPROLAB_ACELP4800         0x0131 /* Sipro Lab Telecom Inc. */
#define  WAVE_FORMAT_SIPROLAB_ACELP8V3          0x0132 /* Sipro Lab Telecom Inc. */
#define  WAVE_FORMAT_SIPROLAB_G729              0x0133 /* Sipro Lab Telecom Inc. */
#define  WAVE_FORMAT_SIPROLAB_G729A             0x0134 /* Sipro Lab Telecom Inc. */
#define  WAVE_FORMAT_SIPROLAB_KELVIN            0x0135 /* Sipro Lab Telecom Inc. */
#define  WAVE_FORMAT_VOICEAGE_AMR               0x0136 /* VoiceAge Corp. */
#define  WAVE_FORMAT_G726ADPCM                  0x0140 /* Dictaphone Corporation */
#define  WAVE_FORMAT_DICTAPHONE_CELP68          0x0141 /* Dictaphone Corporation */
#define  WAVE_FORMAT_DICTAPHONE_CELP54          0x0142 /* Dictaphone Corporation */
#define  WAVE_FORMAT_QUALCOMM_PUREVOICE         0x0150 /* Qualcomm, Inc. */
#define  WAVE_FORMAT_QUALCOMM_HALFRATE          0x0151 /* Qualcomm, Inc. */
#define  WAVE_FORMAT_TUBGSM                     0x0155 /* Ring Zero Systems, Inc. */
#define  WAVE_FORMAT_MSAUDIO1                   0x0160 /* Microsoft Corporation */
#define  WAVE_FORMAT_WMAUDIO2                   0x0161 /* Microsoft Corporation */
#define  WAVE_FORMAT_WMAUDIO3                   0x0162 /* Microsoft Corporation */
#define  WAVE_FORMAT_WMAUDIO_LOSSLESS           0x0163 /* Microsoft Corporation */
#define  WAVE_FORMAT_WMASPDIF                   0x0164 /* Microsoft Corporation */
#define  WAVE_FORMAT_UNISYS_NAP_ADPCM           0x0170 /* Unisys Corp. */
#define  WAVE_FORMAT_UNISYS_NAP_ULAW            0x0171 /* Unisys Corp. */
#define  WAVE_FORMAT_UNISYS_NAP_ALAW            0x0172 /* Unisys Corp. */
#define  WAVE_FORMAT_UNISYS_NAP_16K             0x0173 /* Unisys Corp. */
#define  WAVE_FORMAT_SYCOM_ACM_SYC008           0x0174 /* SyCom Technologies */
#define  WAVE_FORMAT_SYCOM_ACM_SYC701_G726L     0x0175 /* SyCom Technologies */
#define  WAVE_FORMAT_SYCOM_ACM_SYC701_CELP54    0x0176 /* SyCom Technologies */
#define  WAVE_FORMAT_SYCOM_ACM_SYC701_CELP68    0x0177 /* SyCom Technologies */
#define  WAVE_FORMAT_KNOWLEDGE_ADVENTURE_ADPCM  0x0178 /* Knowledge Adventure, Inc. */
#define  WAVE_FORMAT_FRAUNHOFER_IIS_MPEG2_AAC   0x0180 /* Fraunhofer IIS */
#define  WAVE_FORMAT_DTS_DS                     0x0190 /* Digital Theatre Systems, Inc. */
#define  WAVE_FORMAT_CREATIVE_ADPCM             0x0200 /* Creative Labs, Inc */
#define  WAVE_FORMAT_CREATIVE_FASTSPEECH8       0x0202 /* Creative Labs, Inc */
#define  WAVE_FORMAT_CREATIVE_FASTSPEECH10      0x0203 /* Creative Labs, Inc */
#define  WAVE_FORMAT_UHER_ADPCM                 0x0210 /* UHER informatic GmbH */
#define  WAVE_FORMAT_ULEAD_DV_AUDIO             0x0215 /* Ulead Systems, Inc. */
#define  WAVE_FORMAT_ULEAD_DV_AUDIO_1           0x0216 /* Ulead Systems, Inc. */
#define  WAVE_FORMAT_QUARTERDECK                0x0220 /* Quarterdeck Corporation */
#define  WAVE_FORMAT_ILINK_VC                   0x0230 /* I-link Worldwide */
#define  WAVE_FORMAT_RAW_SPORT                  0x0240 /* Aureal Semiconductor */
#define  WAVE_FORMAT_ESST_AC3                   0x0241 /* ESS Technology, Inc. */
#define  WAVE_FORMAT_GENERIC_PASSTHRU           0x0249
#define  WAVE_FORMAT_IPI_HSX                    0x0250 /* Interactive Products, Inc. */
#define  WAVE_FORMAT_IPI_RPELP                  0x0251 /* Interactive Products, Inc. */
#define  WAVE_FORMAT_CS2                        0x0260 /* Consistent Software */
#define  WAVE_FORMAT_SONY_SCX                   0x0270 /* Sony Corp. */
#define  WAVE_FORMAT_SONY_SCY                   0x0271 /* Sony Corp. */
#define  WAVE_FORMAT_SONY_ATRAC3                0x0272 /* Sony Corp. */
#define  WAVE_FORMAT_SONY_SPC                   0x0273 /* Sony Corp. */
#define  WAVE_FORMAT_TELUM_AUDIO                0x0280 /* Telum Inc. */
#define  WAVE_FORMAT_TELUM_IA_AUDIO             0x0281 /* Telum Inc. */
#define  WAVE_FORMAT_NORCOM_VOICE_SYSTEMS_ADPCM 0x0285 /* Norcom Electronics Corp. */
#define  WAVE_FORMAT_FM_TOWNS_SND               0x0300 /* Fujitsu Corp. */
#define  WAVE_FORMAT_MICRONAS                   0x0350 /* Micronas Semiconductors, Inc. */
#define  WAVE_FORMAT_MICRONAS_CELP833           0x0351 /* Micronas Semiconductors, Inc. */
#define  WAVE_FORMAT_BTV_DIGITAL                0x0400 /* Brooktree Corporation */
#define  WAVE_FORMAT_INTEL_MUSIC_CODER          0x0401 /* Intel Corp. */
#define  WAVE_FORMAT_INDEO_AUDIO                0x0402 /* Ligos */
#define  WAVE_FORMAT_QDESIGN_MUSIC              0x0450 /* QDesign Corporation */
#define  WAVE_FORMAT_ON2_VP7_AUDIO              0x0500 /* On2 Technologies */
#define  WAVE_FORMAT_ON2_VP6_AUDIO              0x0501 /* On2 Technologies */
#define  WAVE_FORMAT_VME_VMPCM                  0x0680 /* AT&T Labs, Inc. */
#define  WAVE_FORMAT_TPC                        0x0681 /* AT&T Labs, Inc. */
#define  WAVE_FORMAT_LIGHTWAVE_LOSSLESS         0x08AE /* Clearjump */
#define  WAVE_FORMAT_OLIGSM                     0x1000 /* Ing C. Olivetti & C., S.p.A. */
#define  WAVE_FORMAT_OLIADPCM                   0x1001 /* Ing C. Olivetti & C., S.p.A. */
#define  WAVE_FORMAT_OLICELP                    0x1002 /* Ing C. Olivetti & C., S.p.A. */
#define  WAVE_FORMAT_OLISBC                     0x1003 /* Ing C. Olivetti & C., S.p.A. */
#define  WAVE_FORMAT_OLIOPR                     0x1004 /* Ing C. Olivetti & C., S.p.A. */
#define  WAVE_FORMAT_LH_CODEC                   0x1100 /* Lernout & Hauspie */
#define  WAVE_FORMAT_LH_CODEC_CELP              0x1101 /* Lernout & Hauspie */
#define  WAVE_FORMAT_LH_CODEC_SBC8              0x1102 /* Lernout & Hauspie */
#define  WAVE_FORMAT_LH_CODEC_SBC12             0x1103 /* Lernout & Hauspie */
#define  WAVE_FORMAT_LH_CODEC_SBC16             0x1104 /* Lernout & Hauspie */
#define  WAVE_FORMAT_NORRIS                     0x1400 /* Norris Communications, Inc. */
#define  WAVE_FORMAT_ISIAUDIO_2                 0x1401 /* ISIAudio */
#define  WAVE_FORMAT_SOUNDSPACE_MUSICOMPRESS    0x1500 /* AT&T Labs, Inc. */
#define  WAVE_FORMAT_MPEG_ADTS_AAC              0x1600 /* Microsoft Corporation */
#define  WAVE_FORMAT_MPEG_RAW_AAC               0x1601 /* Microsoft Corporation */
#define  WAVE_FORMAT_MPEG_LOAS                  0x1602 /* Microsoft Corporation (MPEG-4 Audio Transport Streams (LOAS/LATM) */
#define  WAVE_FORMAT_NOKIA_MPEG_ADTS_AAC        0x1608 /* Microsoft Corporation */
#define  WAVE_FORMAT_NOKIA_MPEG_RAW_AAC         0x1609 /* Microsoft Corporation */
#define  WAVE_FORMAT_VODAFONE_MPEG_ADTS_AAC     0x160A /* Microsoft Corporation */
#define  WAVE_FORMAT_VODAFONE_MPEG_RAW_AAC      0x160B /* Microsoft Corporation */
#define  WAVE_FORMAT_MPEG_HEAAC                 0x1610 /* Microsoft Corporation (MPEG-2 AAC or MPEG-4 HE-AAC v1/v2 streams with any payload (ADTS, ADIF, LOAS/LATM, RAW). Format block includes MP4 AudioSpecificConfig() -- see HEAACWAVEFORMAT below */
#define  WAVE_FORMAT_VOXWARE_RT24_SPEECH        0x181C /* Voxware Inc. */
#define  WAVE_FORMAT_SONICFOUNDRY_LOSSLESS      0x1971 /* Sonic Foundry */
#define  WAVE_FORMAT_INNINGS_TELECOM_ADPCM      0x1979 /* Innings Telecom Inc. */
#define  WAVE_FORMAT_LUCENT_SX8300P             0x1C07 /* Lucent Technologies */
#define  WAVE_FORMAT_LUCENT_SX5363S             0x1C0C /* Lucent Technologies */
#define  WAVE_FORMAT_CUSEEME                    0x1F03 /* CUSeeMe */
#define  WAVE_FORMAT_NTCSOFT_ALF2CM_ACM         0x1FC4 /* NTCSoft */
#define  WAVE_FORMAT_DVM                        0x2000 /* FAST Multimedia AG */
#define  WAVE_FORMAT_DTS2                       0x2001 
#define  WAVE_FORMAT_MAKEAVIS                   0x3313 
#define  WAVE_FORMAT_DIVIO_MPEG4_AAC            0x4143 /* Divio, Inc. */
#define  WAVE_FORMAT_NOKIA_ADAPTIVE_MULTIRATE   0x4201 /* Nokia */
#define  WAVE_FORMAT_DIVIO_G726                 0x4243 /* Divio, Inc. */
#define  WAVE_FORMAT_LEAD_SPEECH                0x434C /* LEAD Technologies */
#define  WAVE_FORMAT_LEAD_VORBIS                0x564C /* LEAD Technologies */
#define  WAVE_FORMAT_WAVPACK_AUDIO              0x5756 /* xiph.org */
#define  WAVE_FORMAT_ALAC                       0x6C61 /* Apple Lossless */
#define  WAVE_FORMAT_OGG_VORBIS_MODE_1          0x674F /* Ogg Vorbis */
#define  WAVE_FORMAT_OGG_VORBIS_MODE_2          0x6750 /* Ogg Vorbis */
#define  WAVE_FORMAT_OGG_VORBIS_MODE_3          0x6751 /* Ogg Vorbis */
#define  WAVE_FORMAT_OGG_VORBIS_MODE_1_PLUS     0x676F /* Ogg Vorbis */
#define  WAVE_FORMAT_OGG_VORBIS_MODE_2_PLUS     0x6770 /* Ogg Vorbis */
#define  WAVE_FORMAT_OGG_VORBIS_MODE_3_PLUS     0x6771 /* Ogg Vorbis */
#define  WAVE_FORMAT_3COM_NBX                   0x7000 /* 3COM Corp. */
#define  WAVE_FORMAT_OPUS                       0x704F /* Opus */
#define  WAVE_FORMAT_FAAD_AAC                   0x706D
#define  WAVE_FORMAT_AMR_NB                     0x7361 /* AMR Narrowband */
#define  WAVE_FORMAT_AMR_WB                     0x7362 /* AMR Wideband */
#define  WAVE_FORMAT_AMR_WP                     0x7363 /* AMR Wideband Plus */
#define  WAVE_FORMAT_GSM_AMR_CBR                0x7A21 /* GSMA/3GPP */
#define  WAVE_FORMAT_GSM_AMR_VBR_SID            0x7A22 /* GSMA/3GPP */
#define  WAVE_FORMAT_COMVERSE_INFOSYS_G723_1    0xA100 /* Comverse Infosys */
#define  WAVE_FORMAT_COMVERSE_INFOSYS_AVQSBC    0xA101 /* Comverse Infosys */
#define  WAVE_FORMAT_COMVERSE_INFOSYS_SBC       0xA102 /* Comverse Infosys */
#define  WAVE_FORMAT_SYMBOL_G729_A              0xA103 /* Symbol Technologies */
#define  WAVE_FORMAT_VOICEAGE_AMR_WB            0xA104 /* VoiceAge Corp. */
#define  WAVE_FORMAT_INGENIENT_G726             0xA105 /* Ingenient Technologies, Inc. */
#define  WAVE_FORMAT_MPEG4_AAC                  0xA106 /* ISO/MPEG-4 */
#define  WAVE_FORMAT_ENCORE_G726                0xA107 /* Encore Software */
#define  WAVE_FORMAT_ZOLL_ASAO                  0xA108 /* ZOLL Medical Corp. */
#define  WAVE_FORMAT_SPEEX_VOICE                0xA109 /* xiph.org */
#define  WAVE_FORMAT_VIANIX_MASC                0xA10A /* Vianix LLC */
#define  WAVE_FORMAT_WM9_SPECTRUM_ANALYZER      0xA10B /* Microsoft */
#define  WAVE_FORMAT_WMF_SPECTRUM_ANAYZER       0xA10C /* Microsoft */
#define  WAVE_FORMAT_GSM_610                    0xA10D
#define  WAVE_FORMAT_GSM_620                    0xA10E 
#define  WAVE_FORMAT_GSM_660                    0xA10F 
#define  WAVE_FORMAT_GSM_690                    0xA110 
#define  WAVE_FORMAT_GSM_ADAPTIVE_MULTIRATE_WB  0xA111 
#define  WAVE_FORMAT_POLYCOM_G722               0xA112 /* Polycom */
#define  WAVE_FORMAT_POLYCOM_G728               0xA113 /* Polycom */
#define  WAVE_FORMAT_POLYCOM_G729_A             0xA114 /* Polycom */
#define  WAVE_FORMAT_POLYCOM_SIREN              0xA115 /* Polycom */
#define  WAVE_FORMAT_GLOBAL_IP_ILBC             0xA116 /* Global IP */
#define  WAVE_FORMAT_RADIOTIME_TIME_SHIFT_RADIO 0xA117 /* RadioTime */
#define  WAVE_FORMAT_NICE_ACA                   0xA118 /* Nice Systems */
#define  WAVE_FORMAT_NICE_ADPCM                 0xA119 /* Nice Systems */
#define  WAVE_FORMAT_VOCORD_G721                0xA11A /* Vocord Telecom */
#define  WAVE_FORMAT_VOCORD_G726                0xA11B /* Vocord Telecom */
#define  WAVE_FORMAT_VOCORD_G722_1              0xA11C /* Vocord Telecom */
#define  WAVE_FORMAT_VOCORD_G728                0xA11D /* Vocord Telecom */
#define  WAVE_FORMAT_VOCORD_G729                0xA11E /* Vocord Telecom */
#define  WAVE_FORMAT_VOCORD_G729_A              0xA11F /* Vocord Telecom */
#define  WAVE_FORMAT_VOCORD_G723_1              0xA120 /* Vocord Telecom */
#define  WAVE_FORMAT_VOCORD_LBC                 0xA121 /* Vocord Telecom */
#define  WAVE_FORMAT_NICE_G728                  0xA122 /* Nice Systems */
#define  WAVE_FORMAT_FRACE_TELECOM_G729         0xA123 /* France Telecom */
#define  WAVE_FORMAT_CODIAN                     0xA124 /* CODIAN */
#define  WAVE_FORMAT_DOLBY_AC4                  0xAC40 /* Dolby AC-4 */
#define  WAVE_FORMAT_FLAC                       0xF1AC /* flac.sourceforge.net */
#pragma endregion

#pragma pack(1)
typedef char BOOL;
typedef uint32_t FOURCC;

enum
{
	FALSE,
	TRUE
};
struct RIFFHeader
{
	FOURCC ID;
	uint32_t size;
};
struct RIFFChunkHeader
{
	struct RIFFHeader header;
	FOURCC format;	//Can be WAVE
};

struct RIFFWaveFormat
{
	uint16_t audioFormat;
	uint16_t numChannels;
	uint32_t sampleRate;
	uint32_t byteRate;
	uint16_t blockAlign;
	uint16_t bitsPerSample;
	uint16_t extraParamSize; // Not in PCM
};

// https://tech.ebu.ch/docs/tech/tech3285.pdf
struct BroadcastExtensionChunk
{
	char Description[256];
	char Originator[32];
	char OriginatorReference[32];
	char OriginationDate[10];
	char OriginationTime[8];
	uint32_t TimeReferenceLow;
	uint32_t TimeReferenceHigh;
	uint16_t Version;
	uint8_t UMID[64];
	uint16_t LoudnessValue;
	uint16_t LoudnessRange;
	uint16_t MaxTruePeakLevel;
	uint16_t MaxMomentaryLoudness;
	uint16_t MaxShortTermLoudness;
	char Reserved[180];
	char CodingHistory[];
};
#pragma pack()

const char* infoCCs[] =
{ "IARL","IART","ICMS","ICMT","ICOP","ICRD","ICRP","IDIM","IDPI","IENG","IGNR","IKEY","ILGT","IMED","INAM",	"IPLT","IPRD",	"ISBJ","ISFT","ISHP","ISRC","ISRF","ITCH", };

const char* infoDescriptions[] = { "Archival Location", "Artist", "Commissioned", "Comments", "Copyright", "Creation Date", "Cropped", "Dimensions", "Dots Per Inch", "Engineer", "Genre", "Keywords", "Lightness", "Medium", "Name", "Palette Setting", "Product", "Subject", "Software", "Sharpness", "Source", "Source Form", "Technician" };

#define sep	L","
#define se	","
//Globals
char outputCSV[_MAX_PATH];
FILE* outputFile = NULL;

char ansiCodePageOutput[64] = { 0 };

struct RIFFWaveFormat waveFormat;
struct BroadcastExtensionChunk bextChunk;
const char* infoTags[sizeof(infoCCs) / sizeof(char*)];

BOOL quietMode;

void ParseRIFF(FILE*);
void WriteOutput(const char*);
void Msg(const char*, ...);

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		Msg("usage: chicheck sound.wav [output.csv] [ansi codepage num] [-q]]");
		return -1;
	}

	if (argc > 2)
	{
		strcpy(outputCSV, argv[2]);
		int fileExists = _access(outputCSV, 0);
		outputFile = fopen(outputCSV, "at, ccs=UTF-8")$;
		if (fileExists == -1 && outputFile != NULL)
		{
			wchar_t buffer[2048];
			wcscpy(buffer, L"Filename"sep L"Encoding"sep L" Channels"sep L" Sample Rate"sep L" Byte Rate"sep L" Block Alignment"sep L" Bits per Sample"sep L" ");
			for (int i = 0; i < sizeof(infoDescriptions) / sizeof(char*); i++)
			{
				wchar_t wDescription[128];
				mbstowcs(wDescription, infoDescriptions[i], sizeof(wDescription) / sizeof(wchar_t));
				wcscat(buffer, wDescription);
				wcscat(buffer, sep);
			}
			wcscat(buffer, L"Description"sep L" Originator"sep L" Origination Date"sep L" Origination Time");
			wcscat(buffer, L"\n");
			//fputws(L"sep="sep L"\n",outputFile);
			fputws(buffer, outputFile);
		}
	}

	if (argc > 3)
	{
		strcpy(ansiCodePageOutput, argv[3]);
	}

	for (int i = 3; i < argc; i++)
	{
		if(strcmp(argv[i],"-q") == 0)
			quietMode = TRUE;

	}
	char fileName[_MAX_PATH];
	strcpy(fileName, argv[1]);
	Msg("File: %s\n", fileName);
	FILE* pFile = fopen(fileName, "rb")$;
	if (!pFile)
		return -1;
	uint32_t magicNumber = 0;
	fread(&magicNumber, sizeof(magicNumber), 1, pFile);

	switch (magicNumber)
	{
	case 'FFIR':		//RIFF, wave
		ParseRIFF(pFile);
		break;
	}
	fclose(pFile);
	if (outputFile)
	{
		WriteOutput(fileName);
		fclose(outputFile);
	}
}

void ParseWave(FILE*, const struct RIFFChunkHeader*);
void ParseRIFF(FILE* file)
{
	struct RIFFChunkHeader fileHeader;
	fseek(file, 0, SEEK_SET);
	fread(&fileHeader, sizeof(struct RIFFChunkHeader), 1, file);
	Msg("File Header:\n");
	Msg("File ID: %.4s\n", &fileHeader.header.ID);
	Msg("Size: %i bytes\n", fileHeader.header.size);
	Msg("Format: %.4s\n", &fileHeader.format);
	Msg("\n");

	switch (fileHeader.format)
	{
	case 'EVAW': //Wave
		ParseWave(file, &fileHeader);
		break;
	}
}
void ParseWaveFormat(FILE*);
void ParseList(FILE*, long);
void ParseBroadcastExtension(FILE*);

void ParseWave(FILE* file, const struct RIFFChunkHeader* fileHeader)
{
	while (ftell(file) < fileHeader->header.size)
	{
		struct RIFFHeader subChunkHeader;
		char hack;
		fread(&hack, sizeof(char), 1, file);
		if (hack != 0)
			fseek(file, -1, SEEK_CUR);

		fread(&subChunkHeader, sizeof(struct RIFFHeader), 1, file);
		Msg("Chunk ID: %.4s\n", &subChunkHeader.ID);
		Msg("Chunk Size: %i bytes\n", subChunkHeader.size);

		switch (subChunkHeader.ID)
		{
		case ' tmf':  // 'fmt '
			ParseWaveFormat(file);
			break;
		case 'TSIL': //LIST
			ParseList(file,subChunkHeader.size);
			break;
		case 'txeb': //bext
			ParseBroadcastExtension(file);
			break;
		default:
			Msg("Don't know how to parse this chunk :(\n");
			break;
		case 'atad': //data
			break;
		}
		Msg("\n");
		fseek(file, subChunkHeader.size, SEEK_CUR);
	}
}

const char* WaveFormatAsString(int);
void ParseWaveFormat(FILE* file)
{
	fread(&waveFormat, sizeof(struct RIFFWaveFormat), 1, file);
	Msg("Format Chunk\n");

	Msg("Wave Format: %s\n", WaveFormatAsString(waveFormat.audioFormat));
	Msg("%i channel(s)\n", waveFormat.numChannels);
	Msg("Sample Rate: %iHz\n", waveFormat.sampleRate);
	Msg("Byte Rate: %i bytes/s\n", waveFormat.byteRate);
	Msg("Block Alignment: %i bytes\n", waveFormat.blockAlign);
	Msg("Bits Per Sample: %i\n", waveFormat.bitsPerSample);
	Msg("Extra format info size: %i bytes\n", waveFormat.extraParamSize);

	fseek(file, -(long)sizeof(struct RIFFWaveFormat), SEEK_CUR);
}


const char* WaveFormatAsString(int format)
{
	switch (format)
	{
	default:
	case WAVE_FORMAT_UNKNOWN:
		return "Unknown Format";
	case WAVE_FORMAT_PCM:
		return "Microsoft PCM";
	case WAVE_FORMAT_ADPCM:
		return "Microsoft ADPCM";
	case WAVE_FORMAT_IEEE_FLOAT:
		return "Microsoft PCM in IEEE floating-point format";
	case WAVE_FORMAT_VSELP:
		return "Compaq VSELP";
	case WAVE_FORMAT_IBM_CVSD:
		return "IBM CVSD";
	case WAVE_FORMAT_ALAW:
		return "Microsoft A-law";
	case WAVE_FORMAT_MULAW:
		return "Microsoft μ-law";
	case WAVE_FORMAT_DTS:
		return "Microsoft Digital Theater Systems (DTS)";
	case WAVE_FORMAT_DRM:
		return "Microsoft DRM encoded";
	case WAVE_FORMAT_WMAVOICE9:
		return "Microsoft Windows Media Audio 9 Voice";
	case WAVE_FORMAT_WMAVOICE10:
		return "Microsoft Windows Media Audio 10 Voice";
	case WAVE_FORMAT_OKI_ADPCM:
		return "OKI ADPCM";
	case WAVE_FORMAT_DVI_ADPCM:	//WAVE_FORMAT_IMA_ADPCM
		return "Intel DVI ADPCM";
	case WAVE_FORMAT_MEDIASPACE_ADPCM:
		return "MediaSpace ADPCM";
	case WAVE_FORMAT_SIERRA_ADPCM:
		return "Sierra ADPCM";
	case WAVE_FORMAT_G723_ADPCM:
		return "Antex G723 ADPCM";
	case WAVE_FORMAT_DIGISTD:
		return "DSP Solutions DIGISTD";
	case WAVE_FORMAT_DIGIFIX:
		return "DSP Solutions DIGIFIX";
	case WAVE_FORMAT_DIALOGIC_OKI_ADPCM:
		return "Dialogic OKI ADPCM";
	case WAVE_FORMAT_MEDIAVISION_ADPCM:
		return "Media Vision ADPCM";
	case WAVE_FORMAT_CU_CODEC:
		return "Hewlett Packard CU Codec";
	case WAVE_FORMAT_HP_DYN_VOICE:
		return "Hewlett Packard Dynamic Voice ";
	case WAVE_FORMAT_YAMAHA_ADPCM:
		return "Yamaha ADPCM";
	case WAVE_FORMAT_SONARC:
		return "Speech Compression Sonarc";
	case WAVE_FORMAT_DSPGROUP_TRUESPEECH:
		return "DSP Group True Speech";
	case WAVE_FORMAT_ECHOSC1:
		return "Echo Speech EchoSC1";
	case WAVE_FORMAT_AUDIOFILE_AF36:
		return "Virtual Music Audiofile AF36";
	case WAVE_FORMAT_APTX:
		return "Audio Processing Technology aptX";
	case WAVE_FORMAT_AUDIOFILE_AF10:
		return "Virtual Music Audiofile AF10";
	case WAVE_FORMAT_PROSODY_1612:
		return "Aculab Prosody 1612";
	case WAVE_FORMAT_LRC:
		return "Merging Technologies LRC";
	case WAVE_FORMAT_DOLBY_AC2:
		return "Dolby AC-2";
	case WAVE_FORMAT_GSM610:
		return "Microsoft GSM6.10";
	case WAVE_FORMAT_MSNAUDIO:
		return "Microsoft MSN Audio";
	case WAVE_FORMAT_ANTEX_ADPCME:
		return "Antex APDCME";
	case WAVE_FORMAT_CONTROL_RES_VQLPC:
		return "Control Resources VQLPC";
	case WAVE_FORMAT_DIGIREAL:
		return "DSP Solutions Real WAVE";
	case WAVE_FORMAT_DIGIADPCM:
		return "DSP Solutions APDCM";
	case WAVE_FORMAT_CONTROL_RES_CR10:
		return "Control Resources CR10";
	case WAVE_FORMAT_NMS_VBXADPCM:
		return "Natural MicroSystem VBXADPCM";
	case WAVE_FORMAT_CS_IMAADPCM:
		return "Crystal Semiconductor IMA ADPCM / Roland RDAC";
	case WAVE_FORMAT_ECHOSC3:
		return "Echo Speech EchoSC3";
	case WAVE_FORMAT_ROCKWELL_ADPCM:
		return "Rockwell ADPCM";
	case WAVE_FORMAT_ROCKWELL_DIGITALK:
		return "Rockwell DIGITALK";
	case WAVE_FORMAT_XEBEC:
		return "Xebec";
	case WAVE_FORMAT_G721_ADPCM:
		return "Antex G.721";
	case WAVE_FORMAT_G728_CELP:
		return "Antex G.728 CELP";
	case WAVE_FORMAT_MSG723:
		return "Microsoft G.723";
	case WAVE_FORMAT_INTEL_G723_1:
		return "Intel G.723-1";
	case WAVE_FORMAT_INTEL_G729:
		return "Intel G.729";
	case WAVE_FORMAT_SHARP_G726:
		return "Sharp G.726";
	case WAVE_FORMAT_MPEG:
		return "Microsoft MPEG";
	case WAVE_FORMAT_RT24:
		return "InSoft RT24";
	case WAVE_FORMAT_PAC:
		return "InSoft PAC";
	case WAVE_FORMAT_MPEGLAYER3:
		return "ISO/MPEG Layer 3";
	case WAVE_FORMAT_LUCENT_G723:
		return "Lucent G.723";
	case WAVE_FORMAT_CIRRUS:
		return "Cirrus";
	case WAVE_FORMAT_ESPCM:
		return "ESS ESPCM";
	case WAVE_FORMAT_VOXWARE:
		return "Voxware";
	case WAVE_FORMAT_CANOPUS_ATRAC:
		return "Canopus Atrac";
	case WAVE_FORMAT_G726_ADPCM:
		return "APICOM G.726 ADPCM";
	case WAVE_FORMAT_G722_ADPCM:
		return "APICOM G.722 ADPCM";
	case WAVE_FORMAT_DSAT:
		return "Microsoft DSAT";
	case WAVE_FORMAT_VOXWARE_BYTE_ALIGNED:
		return "Voxware Byte-Aligned";
	case WAVE_FORMAT_VOXWARE_AC8:
		return "Voxware AC8";
	case WAVE_FORMAT_VOXWARE_AC10:
		return "Voxware AC10";
	case WAVE_FORMAT_VOXWARE_AC16:
		return "Voxware AC16";
	case WAVE_FORMAT_VOXWARE_AC20:
		return "Voxware AC20";
	case WAVE_FORMAT_VOXWARE_RT24:
		return "Voxware RT24";
	case WAVE_FORMAT_VOXWARE_RT29:
		return "Voxware RT29";
	case WAVE_FORMAT_VOXWARE_RT29HW:
		return "Voxware RT29HW";
	case WAVE_FORMAT_VOXWARE_VR12:
		return "Voxware VR12";
	case WAVE_FORMAT_VOXWARE_VR18:
		return "Voxware VR18";
	case WAVE_FORMAT_VOXWARE_TQ40:
		return "Voxware TQ40";
	case WAVE_FORMAT_VOXWARE_SC3:
		return "Voxware SC3";
	case WAVE_FORMAT_VOXWARE_SC3_1:
		return "Voxware SC3-1";
	case WAVE_FORMAT_SOFTSOUND:
		return "Softsound";
	case WAVE_FORMAT_VOXWARE_TQ60:
		return "Voxware TQ60";
	case WAVE_FORMAT_MSRT24:
		return "Microsoft RT24";
	case WAVE_FORMAT_G729A:
		return "AT&T G.729A";
	case WAVE_FORMAT_MVI_MVI2:
		return "Motion Pixels MVI2";
	case WAVE_FORMAT_DF_G726:
		return "DataFusion G.726";
	case WAVE_FORMAT_DF_GSM610:
		return "DataFusion GSM610";
	case WAVE_FORMAT_ISIAUDIO:
		return "Iterated Systems ISIAudio";
	case WAVE_FORMAT_ONLIVE:
		return "OnLive!";
	case WAVE_FORMAT_MULTITUDE_FT_SX20:
		return "Multitude FT SX20";
	case WAVE_FORMAT_INFOCOM_ITS_G721_ADPCM:
		return "Infocom ITS G721 ADPCM";
	case WAVE_FORMAT_CONVEDIA_G729:
		return "Convedia G.729";
	case WAVE_FORMAT_CONGRUENCY:
		return "Congruency";
	case WAVE_FORMAT_SBC24:
		return "Siemens SBC24";
	case WAVE_FORMAT_DOLBY_AC3_SPDIF:
		return "Sonic Foundry Dolby AC3 SPDIF";
	case WAVE_FORMAT_MEDIASONIC_G723:
		return "Mediasonic G.723";
	case WAVE_FORMAT_PROSODY_8KBPS:
		return "Aculab Prosody 8kbps";
	case WAVE_FORMAT_ZYXEL_ADPCM:
		return "ZyXEL ADPCM";
	case WAVE_FORMAT_PHILIPS_LPCBB:
		return "Philips LPCBB";
	case WAVE_FORMAT_PACKED:
		return "Studer Packed";
	case WAVE_FORMAT_MALDEN_PHONYTALK:
		return "Malden Phonytalk";
	case WAVE_FORMAT_RACAL_RECORDER_GSM:
		return "Racal Recorders GSM";
	case WAVE_FORMAT_RACAL_RECORDER_G720_A:
		return "Racal Recorderss G.720-A";
	case WAVE_FORMAT_RACAL_RECORDER_G723_1:
		return "Racal Recorders G.723-1";
	case WAVE_FORMAT_RACAL_RECORDER_TETRA_ACELP:
		return "Racal Recorders Tetra ACELP";
	case WAVE_FORMAT_NEC_AAC:
		return "NEC AAC";
	case WAVE_FORMAT_RAW_AAC1:
		return "Raw AAC1";
	case WAVE_FORMAT_RHETOREX_ADPCM:
		return "Rhetorex ADPCM";
	case WAVE_FORMAT_IRAT:
		return "BeCubed IRAT";
	case WAVE_FORMAT_VIVO_G723:
		return "Vivo G.723";
	case WAVE_FORMAT_VIVO_SIREN:
		return "Vivo Siren";
	case WAVE_FORMAT_PHILIPS_CELP:
		return "Philips CELP";
	case WAVE_FORMAT_PHILIPS_GRUNDIG:
		return "Philips Grundig";
	case WAVE_FORMAT_DIGITAL_G723:
		return "Digial Equipment G.723";
	case WAVE_FORMAT_SANYO_LD_ADPCM:
		return "Sanyo LD ADPCM";
	case WAVE_FORMAT_SIPROLAB_ACEPLNET:
		return "Sipro Lab ACEPLNET";
	case WAVE_FORMAT_SIPROLAB_ACELP4800:
		return "Sipro Lab ACELP4800";
	case WAVE_FORMAT_SIPROLAB_ACELP8V3:
		return "Sipro Lab ACELP8V3";
	case WAVE_FORMAT_SIPROLAB_G729:
		return "Sipro Lab G.729";
	case WAVE_FORMAT_SIPROLAB_G729A:
		return "Sipro Lab G.729A";
	case WAVE_FORMAT_SIPROLAB_KELVIN:
		return "Sipro Lab Kelvin";
	case WAVE_FORMAT_VOICEAGE_AMR:
		return "VoiceAge AMR";
	case WAVE_FORMAT_G726ADPCM:
		return "Dictaphone G.726 ADPCM";
	case WAVE_FORMAT_DICTAPHONE_CELP68:
		return "Dictaphone CELP68";
	case WAVE_FORMAT_DICTAPHONE_CELP54:
		return "Dictaphone CELP54";
	case WAVE_FORMAT_QUALCOMM_PUREVOICE:
		return "Qualcomm Pure Voice";
	case WAVE_FORMAT_QUALCOMM_HALFRATE:
		return "Qualcomm Half Rate";
	case WAVE_FORMAT_TUBGSM:
		return "Ring Zero TUBGSM";
	case WAVE_FORMAT_MSAUDIO1:
		return "Microsoft Audio 1";
	case WAVE_FORMAT_WMAUDIO2:
		return "Microsoft Windows Media Audio";
	case WAVE_FORMAT_WMAUDIO3:
		return "Microsoft Windows Media Audio Professiona";
	case WAVE_FORMAT_WMAUDIO_LOSSLESS:
		return "Microsoft Windows Media Audio Lossless";
	case WAVE_FORMAT_WMASPDIF:
		return "Microsoft Windows Media Audio over S/PDIF";
	case WAVE_FORMAT_UNISYS_NAP_ADPCM:
		return "Unisys NAP ADPCM";
	case WAVE_FORMAT_UNISYS_NAP_ULAW:
		return "Unisys NAP μ-law";
	case WAVE_FORMAT_UNISYS_NAP_ALAW:
		return "Unisys NAP a-law";
	case WAVE_FORMAT_UNISYS_NAP_16K:
		return "Unisys NAP 16K";
	case WAVE_FORMAT_SYCOM_ACM_SYC008:
		return "Sycom ACM SYC008";
	case WAVE_FORMAT_SYCOM_ACM_SYC701_G726L:
		return "Sycom ACM SYC701 G.726";
	case WAVE_FORMAT_SYCOM_ACM_SYC701_CELP54:
		return "Sycom ACM SYC701 CELP54";
	case WAVE_FORMAT_SYCOM_ACM_SYC701_CELP68:
		return "Sycom ACM SYC701 CELP68";
	case WAVE_FORMAT_KNOWLEDGE_ADVENTURE_ADPCM:
		return "Knowledge Adventure ADPCM";
	case WAVE_FORMAT_FRAUNHOFER_IIS_MPEG2_AAC:
		return "Fraunhofer IIS MPEG2 AAC";
	case WAVE_FORMAT_DTS_DS:
		return "Digital Theatre Systems DS";
	case WAVE_FORMAT_CREATIVE_ADPCM:
		return "Creative Labs ADPCM";
	case WAVE_FORMAT_CREATIVE_FASTSPEECH8:
		return "Creative Labs Fast Speech 8";
	case WAVE_FORMAT_CREATIVE_FASTSPEECH10:
		return "Creative Labs Fast Speech 10";
	case WAVE_FORMAT_UHER_ADPCM:
		return "UHER ADPCM";
	case WAVE_FORMAT_ULEAD_DV_AUDIO:
		return "Ulead DV Audio";
	case WAVE_FORMAT_ULEAD_DV_AUDIO_1:
		return "Ulead DV Audio 1";
	case WAVE_FORMAT_QUARTERDECK:
		return "Quarterdeck";
	case WAVE_FORMAT_ILINK_VC:
		return "I-link VC";
	case WAVE_FORMAT_RAW_SPORT:
		return "Aureal Raw Sport";
	case WAVE_FORMAT_ESST_AC3:
		return "ESS AC3";
	case WAVE_FORMAT_GENERIC_PASSTHRU:
		return "Generic Passthru";
	case WAVE_FORMAT_IPI_HSX:
		return "Interactive Products HSX";
	case WAVE_FORMAT_IPI_RPELP:
		return "Interactive Product RPELP";
	case WAVE_FORMAT_CS2:
		return "Consistent Software CS2";
	case WAVE_FORMAT_SONY_SCX:
		return "Sony SCX";
	case WAVE_FORMAT_SONY_SCY:
		return "Sony SCY";
	case WAVE_FORMAT_SONY_ATRAC3:
		return "Sony Atrac3";
	case WAVE_FORMAT_SONY_SPC:
		return "Sony SPC";
	case WAVE_FORMAT_TELUM_AUDIO:
		return "Telum Audio";
	case WAVE_FORMAT_TELUM_IA_AUDIO:
		return "Telum IA Audio";
	case WAVE_FORMAT_NORCOM_VOICE_SYSTEMS_ADPCM:
		return "Norcom ADPCM";
	case WAVE_FORMAT_FM_TOWNS_SND:
		return "Fujitsu TOWNS";
	case WAVE_FORMAT_MICRONAS:
		return "Micronas";
	case WAVE_FORMAT_MICRONAS_CELP833:
		return "Micronas CELP833";
	case WAVE_FORMAT_BTV_DIGITAL:
		return "Brooktree BTV Digita";
	case WAVE_FORMAT_INTEL_MUSIC_CODER:
		return "Intel Music Coder";
	case WAVE_FORMAT_INDEO_AUDIO:
		return "Ligos Indeo Audio";
	case WAVE_FORMAT_QDESIGN_MUSIC:
		return "QDesign Music";
	case WAVE_FORMAT_ON2_VP7_AUDIO:
		return "On2 VP7";
	case WAVE_FORMAT_ON2_VP6_AUDIO:
		return "On2 VP6";
	case WAVE_FORMAT_VME_VMPCM:
		return "AT&T VMPCM";
	case WAVE_FORMAT_TPC:
		return "AT&T TPC";
	case WAVE_FORMAT_LIGHTWAVE_LOSSLESS:
		return "Clearjump Lightwave Lossless";
	case WAVE_FORMAT_OLIGSM:
		return "Olivetti GSM";
	case WAVE_FORMAT_OLIADPCM:
		return "Olivetti ADPCM";
	case WAVE_FORMAT_OLICELP:
		return "Olivetti CELP";
	case WAVE_FORMAT_OLISBC:
		return "Olivetti SBC";
	case WAVE_FORMAT_OLIOPR:
		return "Olivetti OPR";
	case WAVE_FORMAT_LH_CODEC:
		return "Lernout & Hauspie";
	case WAVE_FORMAT_LH_CODEC_CELP:
		return "Lernout & Hauspie CELP";
	case WAVE_FORMAT_LH_CODEC_SBC8:
		return "Lernout & Hauspie SBC8";
	case WAVE_FORMAT_LH_CODEC_SBC12:
		return "Lernout & Hauspie SBC12";
	case WAVE_FORMAT_LH_CODEC_SBC16:
		return "Lernout & Hauspie SBC16";
	case WAVE_FORMAT_NORRIS:
		return "Norris";
	case WAVE_FORMAT_ISIAUDIO_2:
		return "ISIAudio 2";
	case WAVE_FORMAT_SOUNDSPACE_MUSICOMPRESS:
		return "AT&T Soundspace Musicompress";
	case WAVE_FORMAT_MPEG_ADTS_AAC:
		return "Microsoft MPEG ADTS AAC";
	case WAVE_FORMAT_MPEG_RAW_AAC:
		return "Microsoft MPEG RAW AAC";
	case WAVE_FORMAT_MPEG_LOAS:
		return "Microsoft MPEG LOAS";
	case WAVE_FORMAT_NOKIA_MPEG_ADTS_AAC:
		return "Microsoft Nokia MPEG ADTS AAC";
	case WAVE_FORMAT_NOKIA_MPEG_RAW_AAC:
		return "Microsoft Nokia MPEG RAW AAC";
	case WAVE_FORMAT_VODAFONE_MPEG_ADTS_AAC:
		return "Microsoft Vodafone MPEG ADTS AAC";
	case WAVE_FORMAT_VODAFONE_MPEG_RAW_AAC:
		return "Microsoft Vodafone MPEG RAW AAC";
	case WAVE_FORMAT_MPEG_HEAAC:
		return "Microsoft MPEG HEAAC";
	case WAVE_FORMAT_VOXWARE_RT24_SPEECH:
		return "Voxware RT24 Speech";
	case WAVE_FORMAT_SONICFOUNDRY_LOSSLESS:
		return "Sonic Foundry Lossless";
	case WAVE_FORMAT_INNINGS_TELECOM_ADPCM:
		return "Innings ADPCM";
	case WAVE_FORMAT_LUCENT_SX8300P:
		return "Lucent SX8300P";
	case WAVE_FORMAT_LUCENT_SX5363S:
		return "Lucent SX5363S";
	case WAVE_FORMAT_CUSEEME:
		return "CUSeeMe";
	case WAVE_FORMAT_NTCSOFT_ALF2CM_ACM:
		return "NTCSoft ALF2CM ACM";
	case WAVE_FORMAT_DVM:
		return "FAST Multimedia DVM";
	case WAVE_FORMAT_DTS2:
		return "DTS2";
	case WAVE_FORMAT_MAKEAVIS:
		return "MAKEAVIS";
	case WAVE_FORMAT_DIVIO_MPEG4_AAC:
		return "Divio MPEG4 AAC";
	case WAVE_FORMAT_NOKIA_ADAPTIVE_MULTIRATE:
		return "Nokia Adaptive Multirate";
	case WAVE_FORMAT_DIVIO_G726:
		return "Divio G.726";
	case WAVE_FORMAT_LEAD_SPEECH:
		return "LEAD Speech";
	case WAVE_FORMAT_LEAD_VORBIS:
		return "LEAD Vorbis";
	case WAVE_FORMAT_WAVPACK_AUDIO:
		return "xiph.org Wavpack";
	case WAVE_FORMAT_ALAC:
		return "Apple ALAC";
	case WAVE_FORMAT_OGG_VORBIS_MODE_1:
		return "Ogg Vorbis Mode 1";
	case WAVE_FORMAT_OGG_VORBIS_MODE_2:
		return "Ogg Vorbis Mode 2";
	case WAVE_FORMAT_OGG_VORBIS_MODE_3:
		return "Ogg Vorbis Mode 3";
	case WAVE_FORMAT_OGG_VORBIS_MODE_1_PLUS:
		return "Ogg Vorbis Mode 1 Plus";
	case WAVE_FORMAT_OGG_VORBIS_MODE_2_PLUS:
		return "Ogg Vorbis Mode 2 Plus";
	case WAVE_FORMAT_OGG_VORBIS_MODE_3_PLUS:
		return "Ogg Vorbis Mode 3 Plus";
	case WAVE_FORMAT_3COM_NBX:
		return "3COM NBX";
	case WAVE_FORMAT_OPUS:
		return "Opus";
	case WAVE_FORMAT_FAAD_AAC:
		return "FAAD AAC";
	case WAVE_FORMAT_AMR_NB:
		return "AMR Narrowband";
	case WAVE_FORMAT_AMR_WB:
		return "AMR Wideband";
	case WAVE_FORMAT_AMR_WP:
		return "AMR Wideband Plus";
	case WAVE_FORMAT_GSM_AMR_CBR:
		return "GSM AMR CBR";
	case WAVE_FORMAT_GSM_AMR_VBR_SID:
		return "GSM AMR VBR SID";
	case WAVE_FORMAT_COMVERSE_INFOSYS_G723_1:
		return "Comverse Infosys G.723-1";
	case WAVE_FORMAT_COMVERSE_INFOSYS_AVQSBC:
		return "Comverse Infosys AVQSBC";
	case WAVE_FORMAT_COMVERSE_INFOSYS_SBC:
		return "Comverse Infosys SBC";
	case WAVE_FORMAT_SYMBOL_G729_A:
		return "Symbol G.729-A";
	case WAVE_FORMAT_VOICEAGE_AMR_WB:
		return "VoiceAge AMR WB";
	case WAVE_FORMAT_INGENIENT_G726:
		return "Ingenient G.726";
	case WAVE_FORMAT_MPEG4_AAC:
		return "MPEG4 AAC";
	case WAVE_FORMAT_ENCORE_G726:
		return "Encore G.726";
	case WAVE_FORMAT_ZOLL_ASAO:
		return "ZOLL ASAO";
	case WAVE_FORMAT_SPEEX_VOICE:
		return "xiph.org Speex Voice";
	case WAVE_FORMAT_VIANIX_MASC:
		return "Vianix Masc";
	case WAVE_FORMAT_WM9_SPECTRUM_ANALYZER:
		return "Microsoft Windows Media 9 Spectrum Analyzer";
	case WAVE_FORMAT_WMF_SPECTRUM_ANAYZER:
		return "Microsoft Windows Media Foundation Spectrum Analyzer";
	case WAVE_FORMAT_GSM_610:
		return "GSM 610";
	case WAVE_FORMAT_GSM_620:
		return "GSM 620";
	case WAVE_FORMAT_GSM_660:
		return "GSM 660";
	case WAVE_FORMAT_GSM_690:
		return "GSM 690";
	case WAVE_FORMAT_GSM_ADAPTIVE_MULTIRATE_WB:
		return "GSM Adaptive Multirate WB";
	case WAVE_FORMAT_POLYCOM_G722:
		return "Polycom G.722";
	case WAVE_FORMAT_POLYCOM_G728:
		return "Polycom G.728";
	case WAVE_FORMAT_POLYCOM_G729_A:
		return "Polycom G.729-A";
	case WAVE_FORMAT_POLYCOM_SIREN:
		return "Polycom Siren";
	case WAVE_FORMAT_GLOBAL_IP_ILBC:
		return "Global IP ILBC";
	case WAVE_FORMAT_RADIOTIME_TIME_SHIFT_RADIO:
		return "RadioTime Time Shift Radio";
	case WAVE_FORMAT_NICE_ACA:
		return "Nice ACA";
	case WAVE_FORMAT_NICE_ADPCM:
		return "Nice ADPCM";
	case WAVE_FORMAT_VOCORD_G721:
		return "Vocord G.721";
	case WAVE_FORMAT_VOCORD_G726:
		return "Vocord G.726";
	case WAVE_FORMAT_VOCORD_G722_1:
		return "Vocord G.722-1";
	case WAVE_FORMAT_VOCORD_G728:
		return "Vocord G.728";
	case WAVE_FORMAT_VOCORD_G729:
		return "Vocord G.729";
	case WAVE_FORMAT_VOCORD_G729_A:
		return "Vocord G.729-A";
	case WAVE_FORMAT_VOCORD_G723_1:
		return "Vocord G.723-1";
	case WAVE_FORMAT_VOCORD_LBC:
		return "Vocord LBC";
	case WAVE_FORMAT_NICE_G728:
		return "Nice G.728";
	case WAVE_FORMAT_FRACE_TELECOM_G729:
		return "France Telecom G.729";
	case WAVE_FORMAT_CODIAN:
		return "CODIAN";
	case WAVE_FORMAT_DOLBY_AC4:
		return "Dolby AC-4";
	case WAVE_FORMAT_FLAC:
		return "FLAC";
}
}

void ParseInfo(FILE*, long, long);
void ParseList(FILE* file, long listSize)
{
	long listPos = ftell(file);
	FOURCC listType;
	fread(&listType, sizeof(FOURCC), 1, file);

	switch (listType)
	{
	case 'OFNI': //INFO
		ParseInfo(file, listSize, listPos);
		break;
	default:
		Msg("Unknown LIST type\n");
	}
	fseek(file, -(long)sizeof(FOURCC), SEEK_CUR);
}
int IndexOfInfoTag(FOURCC);
char* memstr(const void* memory, const char* str2, size_t size);
void ParseInfo(FILE* file, long listSize, long listPos)
{
#if 0
	while (ftell(file) < listPos + listSize)
	{
		struct RIFFHeader infoHeader;
		fread(&infoHeader, sizeof(infoHeader), 1, file);
		char* infoString = calloc(infoHeader.size, sizeof(char));
		fread(infoString, sizeof(char), infoHeader.size, file);
		int idx = IndexOfInfoTag(infoHeader.ID);
		if (idx == -1)
		{
			Msg("Unknown Info tag %.4s\n", &infoHeader.ID);
			continue;
		}
		char hack = getc(file);
		if (hack != 0)
			fseek(file, -1, SEEK_CUR);
		Msg("%s: %s\n", infoDescriptions[idx], infoString);
	}
#else
	char* buffer = calloc(listSize, sizeof(char));
	fread(buffer, listSize, 1, file);
	fseek(file, -listSize, SEEK_CUR);
	
	for (int i = 0; i < sizeof(infoCCs) / sizeof(char*); i++)
	{
		struct RIFFHeader *infoHeader = memstr(buffer, infoCCs[i],listSize);
		if (!infoHeader)
			continue;
		infoTags[i] = (char*)infoHeader + sizeof(struct RIFFHeader);
		Msg("%s : %s\n", infoDescriptions[i], infoTags[i]);
	}
	Msg("\n");
#endif
}

int IndexOfInfoTag(FOURCC idTag)
{
	for (int i = 0; i < sizeof(infoCCs) / sizeof(char*); i++)
	{
		if (strncmp(infoCCs[i], &idTag, sizeof(FOURCC)) == 0)
		{
			return i;
		}
	}
	return -1;
}

char* memstr(const void* memory, const char* str2, size_t size)
{
	for (int i = 0; i < size - strlen(str2); i++)
	{
		void* buf1 = (char*)memory + i;
		if (memcmp(buf1, str2, strlen(str2)) == 0)
			return buf1;
	}
	return 0;
}

void ParseBroadcastExtension(FILE* pFile)
{
	fread(&bextChunk, sizeof(struct BroadcastExtensionChunk), 1, pFile);
	Msg("Broadcast Extension Chunk\n");
	Msg("Description : %s\n", bextChunk.Description);
	Msg("Originator : %s\n", bextChunk.Originator);
	Msg("Originator Reference : %s\n", bextChunk.OriginatorReference);
	Msg("Origination Date : %.10s\n", bextChunk.OriginationDate);
	Msg("Origination Time : %.8s\n", bextChunk.OriginationTime);
	Msg("Time Reference Low : %i\n", bextChunk.TimeReferenceLow);
	Msg("Time Reference Low : %i\n", bextChunk.TimeReferenceHigh);
	Msg("Version : %i\n", bextChunk.Version);
	Msg("UMID : %s\n", bextChunk.UMID);
	Msg("Loudness Value : %i LUFS\n", bextChunk.LoudnessValue);
	Msg("Loudness Range : %i LU\n", bextChunk.LoudnessRange);
	Msg("Max True Peak Level : %i dBTP\n", bextChunk.MaxTruePeakLevel);
	Msg("Max Momentary Loudness : %i LUFS\n", bextChunk.MaxMomentaryLoudness);
	Msg("Max Short-term Loudness : %i LUFS\n", bextChunk.MaxShortTermLoudness);
	Msg("Reserved : %s\n", bextChunk.Reserved);
	//Msg("Coding History : %s\n", bextChunk.CodingHistory);
	fseek(pFile, -(long)sizeof(struct BroadcastExtensionChunk), SEEK_CUR);
}

#define BUFFER_SIZE 4096
void ConvertEncoding(char*, wchar_t*);

void WriteOutput(const char* fileName)
{
	char infoTagsString[1024];
	infoTagsString[0] = 0;
	for (int i = 0; i < sizeof(infoTags) / sizeof(char*); i++)
	{
		if (infoTags[i] != NULL)
		{
			strcat(infoTagsString, "\"");
			strcat(infoTagsString, infoTags[i]);
			strcat(infoTagsString, "\"");
		}
		strcat(infoTagsString, se);
	}
	char buffer[BUFFER_SIZE];
	wchar_t wBuffer[BUFFER_SIZE];
	sprintf_s(buffer, sizeof(buffer), "\"%s\""se "\"%s\""se "\"%i\""se "\"%i\""se "\"%i\""se "\"%i\""se "\"%i\""se " %s\"%s\""se "\"%s\""se "\"%.10s\""se "\"%.8s\"\n", fileName, WaveFormatAsString(waveFormat.audioFormat), waveFormat.numChannels, waveFormat.sampleRate, waveFormat.byteRate, waveFormat.blockAlign, waveFormat.bitsPerSample, infoTagsString, bextChunk.Description, bextChunk.Originator, bextChunk.OriginationDate, bextChunk.OriginationTime);
	ConvertEncoding(buffer,wBuffer);
	fputws(wBuffer, outputFile)$;
}

void ConvertEncoding(char* input, wchar_t* output)
{
	char locale[256];
	sprintf(locale, ".%s", ansiCodePageOutput);
	setlocale(LC_CTYPE, locale);
	mbstowcs(output, input, BUFFER_SIZE);
	setlocale(LC_CTYPE, "");
}
void Msg(char const* const format, ...)
{
	if (quietMode)
		return;
	va_list args;
	va_start(args, format);
	vprintf(format, args);
	va_end(args);
}