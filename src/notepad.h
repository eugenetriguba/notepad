#ifndef NOTEPAD_H
#define NOTEPAD_H

typedef struct notepad_t notepad_t;
notepad_t *notepad_create(int file_descriptor);
void notepad_destroy(notepad_t *notepad);
void enable_raw_mode(notepad_t *notepad);
void disable_raw_mode(notepad_t *notepad);
void read_all_bytes(notepad_t *notepad);

int startup_notepad_app(notepad_t *notepad);

#endif /* NOTEPAD_H */
