#include <vector>
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

    int getRounded();
    float get(){ return midiNote; }
    std::ostream& operator<<(std::ostream& os);
private:
    float midiNote;
};

class Frequency
{
public:
    Frequency():frequency(0.0f){};
    Frequency(float noteFrequency):frequency(noteFrequency){}
    Frequency(MidiNote midiNote);
    Frequency(Pitch notePitch);
    double get(){ return frequency; }
    double getRounded();
    std::ostream& operator<<(std::ostream& os);
private:
    double frequency;
};

class Pitch
{
public:
    Pitch(){};
    Pitch(std::string noteName);
    Pitch(Frequency noteFrequency);
    Pitch(MidiNote midiNote);

    Pitch& operator=(const Frequency& noteFrequency);

    std::string get(){ return note + modifier + octave; }
    std::ostream& operator<<(std::ostream& os);
private:
    bool validatePitchString(std::string pitchName);
    char validateNoteName(char note);
    std::string validateModifier(const char& mod, bool throwError=false);
    std::string validateOctaveValue(char oct, bool throwError=false);
    void convertToMidiRepresentation();
    MidiNote midiRepresentation;
    const std::vector<char> possibleNoteNames = {'c', 'd', 'e', 'f', 'g', 'a', 'b'};
    const char sharp = 's';
    const char flat = 'f';
    std::string note;
    std::string modifier;
    std::string octave;
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
