#ifndef NOTE_H
#define NOTE_H

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
    MidiNote(const Frequency& noteFrequency);
    MidiNote(const Pitch& notePitch);

    int getRounded() const;
    float get() const { return midiNote; }
private:
    float midiNote;
};

class Frequency
{
public:
    Frequency():frequency(0.0f){};
    Frequency(float noteFrequency):frequency(noteFrequency){}
    Frequency(MidiNote midiNote);
    Frequency(const Pitch& notePitch);
    double get() const { return frequency; }
    double getRounded() const;
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
    Pitch& operator=(const Pitch& pitch);
    Pitch& operator=(const MidiNote& midiNote);

    std::string get(){ return note + modifier + octave; }
    MidiNote getMidi() const { return midiRepresentation; }
    
private:
    bool validatePitchString(std::string pitchName);
    char validateNoteName(char note);
    std::string validateModifier(const char& mod, bool throwError=false);
    std::string validateOctaveValue(char oct, bool throwError=false);
    void convertToMidiRepresentation();
   
    const std::vector<char> possibleNoteNames = {'c', 'd', 'e', 'f', 'g', 'a', 'b'};
    const char sharp = 's';
    const char flat = 'f';
    
    MidiNote midiRepresentation; 
    std::string note;
    std::string modifier;
    std::string octave;
};

class Note
{
public:
    Note(){};
    Note(const MidiNote& midiNote)
	: frequency(Frequency(midiNote)), midiNote(midiNote), pitch(Pitch(midiNote))
	{}
    Note(Frequency noteFrequency)
	: frequency(noteFrequency), midiNote(MidiNote(noteFrequency)), pitch(noteFrequency)
	{}
    Note(Pitch notePitch)
    : frequency(Frequency(notePitch)), midiNote(MidiNote(notePitch)), pitch(notePitch)
	{}

    double getFrequency() { return frequency.get(); }
    float getMidiNote() { return midiNote.get(); }
    std::string getPitch() { return pitch.get(); }

private:
    Frequency frequency;
    MidiNote midiNote;
    Pitch pitch;
};

#endif
