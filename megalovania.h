#include <stdio.h>

// Define note durations (in milliseconds)
#define BPM 120
#define WHOLE 1000 / (BPM / 60)
#define HALF 500 / (BPM / 60)
#define QUARTER 250 / (BPM / 60)
#define EIGHTH 125 / (BPM / 60)
#define SIXTEENTH 62.5 / (BPM / 60)

typedef enum
{
    NATURAL,
    SHARP,
    FLAT
} Accidental;

typedef enum
{
    CORE_0,
    CORE_1
} Core;

typedef struct Note
{
    char *note;
    Accidental accidental;
    uint16_t duration;
} Note;

// megalovania
// Define the melody as an array of notes and durations
// core0
Note melody_core0[] = {
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

// core 1
Note melody_core1[] = {
    {"P0", NATURAL, WHOLE},
    {"P0", NATURAL, WHOLE},
    {"P0", NATURAL, WHOLE},
    {"P0", NATURAL, WHOLE},

    {"P0", NATURAL, WHOLE},
    {"P0", NATURAL, WHOLE},
    {"P0", NATURAL, WHOLE},
    {"P0", NATURAL, WHOLE},

    {"P0", NATURAL, WHOLE},
    {"P0", NATURAL, WHOLE},
    {"P0", NATURAL, WHOLE},
    {"P0", NATURAL, WHOLE},

    {"P0", NATURAL, WHOLE},
    {"P0", NATURAL, WHOLE},
    {"P0", NATURAL, WHOLE},
    {"P0", NATURAL, WHOLE},
    // left starts

    {"D3", NATURAL, QUARTER},
    {"P0", NATURAL, QUARTER}, // stacatto
    {"D3", NATURAL, QUARTER},
    {"P0", NATURAL, QUARTER}, // stacatto
    {"D3", NATURAL, QUARTER},
    {"D3", NATURAL, QUARTER},
    {"P0", NATURAL, QUARTER},
    {"D3", NATURAL, QUARTER},
    {"P0", NATURAL, QUARTER},
    {"D3", NATURAL, QUARTER},
    {"P0", NATURAL, QUARTER},
    {"D3", NATURAL, QUARTER},
    {"D3", NATURAL, QUARTER},
    {"D3", NATURAL, QUARTER},
    {"D3", NATURAL, HALF},

    {"C3", NATURAL, QUARTER},
    {"P0", NATURAL, QUARTER}, // stacatto
    {"C3", NATURAL, QUARTER},
    {"P0", NATURAL, QUARTER}, // stacatto
    {"C3", NATURAL, QUARTER},
    {"C3", NATURAL, QUARTER},
    {"P0", NATURAL, QUARTER},
    {"C3", NATURAL, QUARTER},
    {"P0", NATURAL, QUARTER},
    {"C3", NATURAL, QUARTER},
    {"P0", NATURAL, QUARTER},
    {"C3", NATURAL, QUARTER},
    {"C3", NATURAL, QUARTER},
    {"C3", NATURAL, QUARTER},
    {"C3", NATURAL, HALF},

    {"B2", NATURAL, QUARTER},
    {"P0", NATURAL, QUARTER}, // stacatto
    {"B2", NATURAL, QUARTER},
    {"P0", NATURAL, QUARTER}, // stacatto
    {"B2", NATURAL, QUARTER},
    {"B2", NATURAL, QUARTER},
    {"P0", NATURAL, QUARTER},
    {"B2", NATURAL, QUARTER},
    {"P0", NATURAL, QUARTER},
    {"B2", NATURAL, QUARTER},
    {"P0", NATURAL, QUARTER},
    {"B2", NATURAL, QUARTER},
    {"B2", NATURAL, QUARTER},
    {"B2", NATURAL, QUARTER},
    {"B2", NATURAL, HALF},

    {"B2", FLAT, QUARTER},
    {"P0", NATURAL, QUARTER}, // stacatto
    {"B2", FLAT, QUARTER},
    {"P0", NATURAL, QUARTER}, // stacatto
    {"B2", FLAT, QUARTER},
    {"B2", FLAT, QUARTER},
    {"P0", NATURAL, QUARTER},
    {"B2", FLAT, QUARTER},
    {"P0", NATURAL, QUARTER},
    {"B2", FLAT, QUARTER},
    {"P0", NATURAL, QUARTER},
    {"B2", FLAT, QUARTER},
    {"B2", FLAT, QUARTER},
    {"B2", FLAT, QUARTER},
    {"B2", FLAT, HALF},
};