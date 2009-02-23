// ------------------------------------------------------
// Protrekkr
// Based on Juan Antonio Arguelles Rius's NoiseTrekker.
//
// Copyright (C) 2008-2009 Franck Charlet.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
//
//  1. Redistributions of source code must retain the above copyright notice,
//     this list of conditions and the following disclaimer.
//
//  2. Redistributions in binary form must reproduce the above copyright notice,
//     this list of conditions and the following disclaimer in the documentation
//     and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL FRANCK CHARLET OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
// OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
// HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
// LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
// OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
// SUCH DAMAGE.
// ------------------------------------------------------

#ifndef _REPLAY_H_
#define _REPLAY_H_

// ------------------------------------------------------
// Includes
#include "tb_303.h"
#include "cubic_spline.h"
#include "../sounddriver/include/sounddriver.h"
#include "samples_unpack.h"
#include "ptkreplay.h"
#include "synth.h"

// ------------------------------------------------------
// Constants
#define MAX_TRACKS 16
#define MAX_POLYPHONY 16
#define DEFAULT_POLYPHONY 5
#define MAX_FILTER 23
#define MAX_COMB_FILTERS 10
#define PI 3.1415926535897932384626433832795

#define SMP_PACK_GSM 0
#define SMP_PACK_MP3 1
#define SMP_PACK_TRUESPEECH 2
#define SMP_PACK_NONE 3
#define SMP_PACK_AT3 4

#define MAX_ROWS 128
#define MAX_SEQUENCES 256
#define MAX_INSTRS 128
#define MAX_PATTERNS 128
#define MAX_INSTRS_SPLITS 16
#define DEFAULT_PATTERN_LEN 64

#define NOTE_MAX 119
#define NOTE_OFF 120
#define NO_NOTE 121
#define NO_INSTR 255

#define PATTERN_NOTE1 0
#define PATTERN_INSTR1 1
#define PATTERN_NOTE2 2
#define PATTERN_INSTR2 3
#define PATTERN_NOTE3 4
#define PATTERN_INSTR3 5
#define PATTERN_NOTE4 6
#define PATTERN_INSTR4 7
#define PATTERN_NOTE5 8
#define PATTERN_INSTR5 9
#define PATTERN_NOTE6 10
#define PATTERN_INSTR6 11
#define PATTERN_NOTE7 12
#define PATTERN_INSTR7 13
#define PATTERN_NOTE8 14
#define PATTERN_INSTR8 15
#define PATTERN_NOTE9 16
#define PATTERN_INSTR9 17
#define PATTERN_NOTE10 18
#define PATTERN_INSTR10 19
#define PATTERN_NOTE11 20
#define PATTERN_INSTR11 21
#define PATTERN_NOTE12 22
#define PATTERN_INSTR12 23
#define PATTERN_NOTE13 24
#define PATTERN_INSTR13 25
#define PATTERN_NOTE14 26
#define PATTERN_INSTR14 27
#define PATTERN_NOTE15 28
#define PATTERN_INSTR15 29
#define PATTERN_NOTE16 30
#define PATTERN_INSTR16 31

#define PATTERN_VOLUME 32
#define PATTERN_PANNING 33
#define PATTERN_FX 34
#define PATTERN_FXDATA 35

// Old tracks definition
/*
#define OLD_PATTERN_NOTE 0
#define OLD_PATTERN_INSTR 1
#define OLD_PATTERN_VOLUME 2
#define OLD_PATTERN_PANNING 3
#define OLD_PATTERN_FX 4
#define OLD_PATTERN_FXDATA 5
*/

//#define PATTERN_NIBBLES 11
#define PATTERN_BYTES (PATTERN_FXDATA + 1)
#define PATTERN_ROW_LEN MAX_TRACKS * PATTERN_BYTES
#define PATTERN_TRACK_LEN MAX_ROWS * PATTERN_BYTES
#define PATTERN_LEN PATTERN_ROW_LEN * MAX_ROWS
#define PATTERN_POOL_SIZE PATTERN_LEN * MAX_PATTERNS

#define SAMPLESPERSEC 44100

#define FLANGER_LOPASS_CUTOFF 0.1f
#define FLANGER_LOPASS_RESONANCE 0.4f

#define SMP_LOOP_NONE 0
#define SMP_LOOP_FORWARD 1
#define SMP_LOOP_PINGPONG 2

#define SMP_LOOPING_FORWARD 0
#define SMP_LOOPING_BACKWARD 1

#define SYNTH_WAVE_OFF 0
#define SYNTH_WAVE_CURRENT 1

#define PLAYING_NOSAMPLE 0
#define PLAYING_SAMPLE 1
#define PLAYING_SAMPLE_NOTEOFF 2
#define PLAYING_STOCK 3

#define SYNTH_ATTACK 1
#define SYNTH_DECAY 2
#define SYNTH_SUSTAIN 3
#define SYNTH_RELEASE 4

// ------------------------------------------------------
// Structures

// SAMPLE COUNTER
struct smpos
{
#if defined(__BIG_ENDIAN__)
    Uint32 first;
    Uint32 last;
#else
    Uint32 last;
    Uint32 first;
#endif
};

union s_access
{
    smpos half;
    int64 absolu;
};

// ------------------------------------------------------
// Variables
extern float decays[MAX_COMB_FILTERS][2];
extern int delays[MAX_COMB_FILTERS];       // delays for the comb filters
extern int counters[MAX_COMB_FILTERS];
extern char num_echoes;
extern unsigned char *RawPatterns;
extern int cPosition;
extern unsigned int lchorus_counter;
extern unsigned int rchorus_counter;
extern unsigned int lchorus_counter2;
extern unsigned int rchorus_counter2;
extern int lchorus_delay;
extern int rchorus_delay;
extern float mas_comp_threshold;
extern float mas_comp_ratio;
extern unsigned char nPatterns;
extern char Songtracks;
extern unsigned char sLength;
extern unsigned char pSequence[256];
extern short patternLines[MAX_ROWS];
extern char nameins[128][20];
extern char Midiprg[128];
extern unsigned char Synthprg[128];
extern char SampleType[128][16];
extern char SampleCompression[128];
extern char SampleName[128][16][64];
extern char Basenote[128][16];
extern Uint32 LoopStart[128][16];
extern Uint32 LoopEnd[128][16];
extern char LoopType[128][16];
extern Uint32 SampleNumSamples[128][16];
extern char Finetune[128][16];
extern float SampleVol[128][16];
extern float FDecay[128][16];
extern short *RawSamples[128][2][16];
extern char SampleChannels[128][16];
extern float TCut[MAX_TRACKS];
extern float ICut[MAX_TRACKS];
extern float TPan[MAX_TRACKS];
extern int FType[MAX_TRACKS];
extern int FRez[MAX_TRACKS];
extern float DThreshold[MAX_TRACKS];
extern float DClamp[MAX_TRACKS];
extern float DSend[MAX_TRACKS]; 
extern int CSend[MAX_TRACKS];
extern char Channels_Polyphony[MAX_TRACKS];
extern char compressor; // 0-->Off 1-->On
extern int c_threshold;
extern int BeatsPerMin;
extern int TicksPerBeat;
extern float mas_vol;

extern int delay_time;
extern float Feedback;
extern int DelayType;
extern float lchorus_feedback;
extern float rchorus_feedback;
extern int shuffle;

extern char CHAN_ACTIVE_STATE[256][16];
extern char CHAN_HISTORY_STATE[256][16];
extern float CCoef[MAX_TRACKS];
extern int CHAN_MIDI_PRG[MAX_TRACKS];

extern char LFO_ON[MAX_TRACKS];
extern float LFO_RATE[MAX_TRACKS];
extern float LFO_AMPL[MAX_TRACKS];

extern char FLANGER_ON[MAX_TRACKS];
extern float FLANGER_AMOUNT[MAX_TRACKS];
extern float FLANGER_DEPHASE[MAX_TRACKS];
extern float FLANGER_RATE[MAX_TRACKS];
extern float FLANGER_AMPL[MAX_TRACKS];
extern float FLANGER_GR[MAX_TRACKS];
extern float FLANGER_FEEDBACK[MAX_TRACKS];
extern int FLANGER_DELAY[MAX_TRACKS];
extern int FLANGER_OFFSET[MAX_TRACKS];

extern float foff2[MAX_TRACKS];
extern float foff1[MAX_TRACKS];

extern int CHAN_MUTE_STATE[MAX_TRACKS]; // 0->Normal 1->Muted
extern char Disclap[MAX_TRACKS];

extern char artist[20];
extern char style[20];

extern char beatsync[128];
extern short beatlines[128];

extern float REVERBFILTER;

extern float CustomVol[128];

#if !defined(__STAND_ALONE__)
extern unsigned int SubCounter;
extern int PosInTick;
extern int plx;
extern int Reserved_Sub_Channels[MAX_TRACKS][MAX_POLYPHONY];
extern int Locked_Sub_Channels[MAX_TRACKS][MAX_POLYPHONY];
extern int sp_Stage[MAX_TRACKS][MAX_POLYPHONY];
extern int sp_Stage2[MAX_TRACKS][MAX_POLYPHONY];
extern int sp_Stage3[MAX_TRACKS][MAX_POLYPHONY];
extern int L_MaxLevel;
extern int R_MaxLevel;
extern CSynth Synthesizer[MAX_TRACKS][MAX_POLYPHONY];
extern float Player_FD[MAX_TRACKS];
extern char sp_channelsample[MAX_TRACKS][MAX_POLYPHONY];
extern char sp_split[MAX_TRACKS][MAX_POLYPHONY];
#if defined(__PSP__)
extern volatile int Songplaying;
#else
extern int Songplaying;
#endif
extern int left_value;
extern int right_value;
extern SynthParameters PARASynth[128];
extern float ramper[MAX_TRACKS];
extern unsigned char nPatterns;
extern int delay_time;
extern int DelayType;
#endif

// ------------------------------------------------------
// Functions
void Pre_Song_Init(void);
void Sp_Player(void);
void Play_Instrument(int channel, int sub_channel,
                     float note, int sample,
                     float vol, unsigned int offset,
                     int glide, int Play_Selection, int midi_sub_channel);
void ResetFilters(int tr);
void ComputeStereo(int channel);
void GetPlayerValues(float master_coef);
void noteoff303(char strack);
void init_sample_bank(void);
void KillInst(int inst_nbr);
void Post_Song_Init(void);
void ResetSynthParameters(SynthParameters *TSP);
void Free_Samples(void);
void Mas_Compressor_Set_Variables(float treshold, float ratio);
int Get_Free_Sub_Channel(int channel, int polyphony);
int Get_Pattern_Offset(int pattern, int track, int row);

#endif