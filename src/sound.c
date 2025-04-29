#include "sound.h"
#include "tonc.h" // Include the Tonc library for GBA hardware access

// Defines for frequency control
#define SFREQ_HOLD 0           // Continuous play
#define SFREQ_TIMED 0x4000     // Timed play
#define SFREQ_RESET 0x8000     // Reset sound
#define SFREQ_RATE_MASK 0x07FF // Mask to extract the rate
#define SFREQ_RATE_SHIFT 0     // Shift for frequency rate
#define SFREQ_RATE(n)                                                          \
  ((n) << SFREQ_RATE_SHIFT) // Macro for setting frequency rate
#define SFREQ_BUILD(rate, timed, reset)                                        \
  (((rate)&SFREQ_RATE_MASK) | ((timed) << 14) |                                \
   ((reset) << 15)) // Build the frequency register value

// Function to initialize the sound system
void sound_init() {
  // Set up the Sound Control Registers
  REG_SNDSTAT = SSTAT_ENABLE; // Enable the sound system
  REG_SND1CNT_L = 0;          // Initialize sound channel 1 (no envelope)
  REG_SND1CNT_X = 0;          // Disable sweep on channel 1
}

// Function to stop the tone by resetting the sound
void stop_tone() {
  // Reset the sound on channel 1 (stop the tone)
  REG_SND1CNT_H = SFREQ_BUILD(0, 0, 1); // Reset sound immediately
}

// Function to play a tone at a specific frequency
void play_tone(int frequency) {
  // Calculate the frequency for the tone (0-2047 range)
  int n = 2048 - (131072 / frequency); // Formula for frequency calculation

  // Set up the frequency control register with the calculated frequency
  REG_SND1CNT_L =
      (15 << 12) | (0 << 11) | (7 << 8); // Envelope: 15 volume, no decay
  REG_SND1CNT_X = 0;                     // Disable sweep
  REG_SND1CNT_H =
      SFREQ_BUILD(n, SFREQ_HOLD, 0); // Set frequency, hold sound indefinitely

  // Optionally, add a delay if you want the tone to play for a certain amount
  // of time. A simple delay using a for-loop or timer can be added here if
  // necessary.
}
