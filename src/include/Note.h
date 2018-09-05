#include <string>
#include <iostream>

class Frequency;
class Pitch;

class MidiNote
{
public:
    MidiNote():midiNote(0){};
    MidiNote(int noteNumber):midiNote(noteNumber){}
    MidiNote(Frequency noteFrequency);
    MidiNote(Pitch notePitch);

    int get(){ return midiNote; }
    std::ostream& operator<<(std::ostream& os);
private:
    int midiNote;
};

class Frequency
{
public:
    Frequency():frequency(0.0f){};
    Frequency(float noteFrequency):frequency(noteFrequency){}
    Frequency(MidiNote midiNote);
    Frequency(Pitch notePitch);
    float get(){ return frequency; }
    std::ostream& operator<<(std::ostream& os);
private:
    float frequency;
};

class Pitch
{
public:
    Pitch(){};
    Pitch(std::string noteName);
    Pitch(Frequency noteFrequency);
    Pitch(MidiNote midiNote);
    std::string get(){ return pitch; }
    std::ostream& operator<<(std::ostream& os);
private:
    std::string pitch;
};

class Note
{
public:
    Note(std::string noteName);
    Note(Frequency noteFrequency);
    Note(Pitch notePitch);

    Frequency getFrequency() { return frequency; }
    MidiNote getMidiNote() { return midiNote; }
    Pitch getPitch() { return pitch; }

private:
    Frequency frequency;
    MidiNote midiNote;
    Pitch pitch;
};
