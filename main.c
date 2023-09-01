// Megalovania on a Raspberry Pi Pico with a buzzer

#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <string.h>
#include <ctype.h> // toupper
#include "pico/stdlib.h"

typedef enum
{
    NATURAL,
    SHARP,
    FLAT
} Accidental;

typedef struct Note
{
    char *note;
    Accidental accidental;
    uint16_t duration;
} Note;

// Define note durations (in milliseconds)
#define BPM 120
#define WHOLE 1000 / (BPM / 60)
#define HALF 500 / (BPM / 60)
#define QUARTER 250 / (BPM / 60)
#define EIGHTH 125 / (BPM / 60)
#define SIXTEENTH 62.5 / (BPM / 60)

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

// megalovania
// Define the melody as an array of notes and durations
Note melody[] = {
    {"D4", NATURAL, QUARTER},
    {"D4", NATURAL, QUARTER},
    {"D5", NATURAL, QUARTER},
    {"P0", NATURAL, QUARTER}, // stacatto
    {"A4", NATURAL, QUARTER},
    {"P0", NATURAL, QUARTER}, // stacatto
    {"P0", NATURAL, QUARTER}, // pause
    {"G4", SHARP, QUARTER},
    {"P0", NATURAL, QUARTER},
    {"G4", NATURAL, QUARTER},
    {"P0", NATURAL, QUARTER},
    {"F4", NATURAL, HALF},
    {"D4", NATURAL, QUARTER},
    {"F4", NATURAL, QUARTER},
    {"G4", NATURAL, QUARTER},

    {"C4", NATURAL, QUARTER},
    {"C4", NATURAL, QUARTER},
    {"D5", NATURAL, QUARTER},
    {"P0", NATURAL, QUARTER}, // stacatto
    {"A4", NATURAL, QUARTER},
    {"P0", NATURAL, QUARTER}, // stacatto
    {"P0", NATURAL, QUARTER}, // pause
    {"G4", SHARP, QUARTER},
    {"P0", NATURAL, QUARTER},
    {"G4", NATURAL, QUARTER},
    {"P0", NATURAL, QUARTER},
    {"F4", NATURAL, HALF},
    {"D4", NATURAL, QUARTER},
    {"F4", NATURAL, QUARTER},
    {"G4", NATURAL, QUARTER},

    {"B3", NATURAL, QUARTER},
    {"B3", NATURAL, QUARTER},
    {"D5", NATURAL, QUARTER},
    {"P0", NATURAL, QUARTER}, // stacatto
    {"A4", NATURAL, QUARTER},
    {"P0", NATURAL, QUARTER}, // stacatto
    {"P0", NATURAL, QUARTER}, // pause
    {"G4", SHARP, QUARTER},
    {"P0", NATURAL, QUARTER},
    {"G4", NATURAL, QUARTER},
    {"P0", NATURAL, QUARTER},
    {"F4", NATURAL, HALF},
    {"D4", NATURAL, QUARTER},
    {"F4", NATURAL, QUARTER},
    {"G4", NATURAL, QUARTER},

    {"B3", FLAT, QUARTER},
    {"B3", FLAT, QUARTER},
    {"D5", NATURAL, QUARTER},
    {"P0", NATURAL, QUARTER}, // stacatto
    {"A4", NATURAL, QUARTER},
    {"P0", NATURAL, QUARTER}, // stacatto
    {"P0", NATURAL, QUARTER}, // pause
    {"G4", SHARP, QUARTER},
    {"P0", NATURAL, QUARTER},
    {"G4", NATURAL, QUARTER},
    {"P0", NATURAL, QUARTER},
    {"F4", NATURAL, HALF},
    {"D4", NATURAL, QUARTER},
    {"F4", NATURAL, QUARTER},
    {"G4", NATURAL, QUARTER},
};

// Calculate the total number of notes in the melody
#define MELODY_LENGTH (sizeof(melody) / sizeof(melody[0]) / 2)

// Helper function to convert HZ to sleep time in us
#define hz_to_us(hz) (1000000 / hz)

int main()
{
    const uint BUZZER_PIN = 15;
    gpio_init(BUZZER_PIN);
    gpio_set_dir(BUZZER_PIN, GPIO_OUT);
    // Load the melody
    for (int i = 0; i < MELODY_LENGTH; i++)
    {
        // Calculate the hz
        float hz = calculate_frequency(melody[i]);
        // Convert to us sleep time
        uint16_t us = hz_to_us(hz);
        // Calculate the duration
        uint16_t duration = melody[i].duration;
        // Calculate the number of cycles
        uint16_t cycles = (hz * duration) / 1000;
        // Play the note or sleep for the duration of the pause
        if (hz == 0)
        {
            sleep_ms(duration);
            continue;
        }
        for (int j = 0; j < cycles; j++)
        {
            gpio_put(BUZZER_PIN, 1);
            sleep_us(us / 2);
            gpio_put(BUZZER_PIN, 0);
            sleep_us(us / 2);
        }
    }
}
