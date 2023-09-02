// Megalovania on a Raspberry Pi Pico with a buzzer

#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <string.h>
#include <ctype.h> // toupper
#include "pico/stdlib.h"
#include "pico/multicore.h"

#include "megalovania.h"

float calculate_frequency(Note note)
{
    // Check if the note has two characters
    assert(strlen(note.note) == 2);
    // The first character is the note
    char note_char = note.note[0];
    // Upper case the note
    note_char = toupper(note_char);

    // The second character is the octave
    char octave_char = note.note[1];
    // Convert the octave to an integer
    int octave = octave_char - '0'; // '0' is 48 in ASCII so '1' - '0' = 1

    // If the note is a pause, return 0
    if (note_char == 'P')
    {
        return 0.0f;
    }

    // The frequency of A4 is 440 Hz
    // The distance from A4 in semitones
    int distance = (octave - 4) * 12;

    // Calculate the distance from A in semitones
    switch (note_char)
    {
    case 'A':
        break;
    case 'B':
        distance += 2;
        break;
    case 'C':
        distance -= 9;
        break;
    case 'D':
        distance -= 7;
        break;
    case 'E':
        distance -= 5;
        break;
    case 'F':
        distance -= 4;
        break;
    case 'G':
        distance -= 2;
        break;
    default:
        assert(0); // Invalid note
    }

    // Adjust the distance for the accidental
    switch (note.accidental)
    {
    case NATURAL:
        break;
    case SHARP:
        distance += 1;
        break;
    case FLAT:
        distance -= 1;
        break;
    default:
        assert(0); // Invalid accidental
    }

    // Calculate the frequency using the formula for the equal-tempered scale
    float frequency = 440.0f * powf(2.0f, distance / 12.0f);
    return frequency;
}

// Calculate the total number of notes in the melody
#define CORE0_MELODY_LENGTH (sizeof(melody_core0) / sizeof(Note))
#define CORE1_MELODY_LENGTH (sizeof(melody_core1) / sizeof(Note))

// Helper function to convert HZ to sleep time in us
#define hz_to_us(hz) (1000000 / hz)

;
void play_note(Note note, Core core)
{
    // Calculate the hz
    float hz = calculate_frequency(note);
    // Calculate the duration
    uint16_t duration = note.duration;
    // Convert to us sleep time
    uint16_t us = hz_to_us(hz);
    // Calculate the number of cycles
    uint16_t cycles = (hz * duration) / 1000;
    // Play the note or sleep for the duration of the pause
    if (hz == 0)
    {
        sleep_ms(duration);
        return;
    }
    for (int i = 0; i < cycles; i++)
    {
        switch (core)
        {
        case CORE_0:
            gpio_put(15, 1); // todo: use PWM for this
            sleep_us(us / 2);
            gpio_put(15, 0);
            sleep_us(us / 2);
            break;
        case CORE_1:
            gpio_put(14, 1);
            sleep_us(us / 2);
            gpio_put(14, 0);
            sleep_us(us / 2);
            break;
        default:
            assert(0); // Invalid core
        }
    }
}

void play_song0()
{
    for (int i = 0; i < CORE0_MELODY_LENGTH; i++)
    {
        play_note(melody_core0[i], CORE_0);
    }
    multicore_reset_core1();
}

void play_song1()
{
    for (int i = 0; i < CORE1_MELODY_LENGTH; i++)
    {
        play_note(melody_core1[i], CORE_1);
    }
}

void play_songs()
{
    multicore_launch_core1(play_song1);
    play_song0(CORE_0);
}

int main()
{
    // Setup pins
    const uint CORE0_BUZZER = 15;
    const uint CORE1_BUZZER = 14;
    const uint RESTART_BUTTON = 16;
    gpio_init(CORE0_BUZZER);
    gpio_init(CORE1_BUZZER);
    gpio_init(RESTART_BUTTON);
    gpio_set_dir(CORE0_BUZZER, GPIO_OUT);
    gpio_set_dir(CORE1_BUZZER, GPIO_OUT);
    gpio_set_dir(RESTART_BUTTON, GPIO_IN);
    gpio_pull_up(RESTART_BUTTON);

    play_songs();

    while (true)
    {
        if (gpio_get(RESTART_BUTTON))
        {
            play_songs();
        }
    }
}
