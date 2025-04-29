#pragma once

#define REG_SNDSTAT                                                            \
  *((volatile u16 *)0x04000074) // Sound status (enable/disable)
#define REG_SND1CNT_L                                                          \
  *((volatile u16 *)0x04000080) // Sound channel 1 control low
#define REG_SND1CNT_H                                                          \
  *((volatile u16 *)0x04000082) // Sound channel 1 control high
#define REG_SND1CNT_X                                                          \
  *((volatile u16 *)0x04000084) // Sound channel 1 control extended
#define REG_SND2CNT_L                                                          \
  *((volatile u16 *)0x04000088) // Sound channel 2 control low
#define REG_SND2CNT_H                                                          \
  *((volatile u16 *)0x0400008A) // Sound channel 2 control high

// Function prototype for playing sound
void sound_init();
void stop_tone();
void play_tone(int frequency);
