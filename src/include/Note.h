#include <string>
#include <iostream>

class Frequency;
class Pitch;

class MidiNote
{
public:
    MidiNote(){};
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
    Frequency(){};
    Frequency(float noteFrequency);
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
    std::string get(){ return noteNumber; }
    std::ostream& operator<<(std::ostream& os);
private:
    std::string noteNumber;
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
