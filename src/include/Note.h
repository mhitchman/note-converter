z#include <string>
#include <iostream>

class MidiNote
{
public:
    explicit MidiNote(int noteNumber);
    explicit MidiNote(Frequency noteFrequency);
    explicit MidiNote(Pitch notePitch);

    std::ostream& operator<<(std::ostream& os);
private:
    int midiNote;
};

class Frequency
{
public:
    explicit Frequency(float noteFrequency);
    explicit Frequency(MidiNote midiNote);
    explicit Frequency(Pitch notePitch);
private:
    float frequency;
};
class Pitch
{
public:
    explicit Pitch(std::string noteName);
    explicit Pitch(Frequency noteFrequency);
    explicit Pitch(Pitch notePitch);
private:
    std::string noteNumber;
};

class Note
{
public:
    explicit Note(std::string noteName);
    explicit Note(Frequency noteFrequency);
    explicit Note(Pitch notePitch);

    Frequency getFrequency() { return frequency; }
    MidiNote getMidiNote() { return midiNote; }
    Pitch getPitch() { return pitch; }

private:
    Frequency frequency;
    MidiNote midiNote;
    Pitch pitch;
};
