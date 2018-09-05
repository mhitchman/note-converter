#include <Note.h>
#include <cmath>

MidiNote::MidiNote(Frequency noteFrequency)
{
    float tmp = 12 * std::log2(noteFrequency.get() / 440) + 69;
    midiNote = static_cast<int>(tmp);
}
MidiNote::MidiNote(Pitch notePitch)
{
    
}

std::ostream& MidiNote::operator<<(std::ostream& os){ return os; }

Frequency::Frequency(float noteFrequency){}
Frequency::Frequency(MidiNote midiNote){}
Frequency::Frequency(Pitch notePitch){}
std::ostream& Frequency::operator<<(std::ostream& os){ return os; }

Pitch::Pitch(std::string noteName){}
Pitch::Pitch(Frequency noteFrequency){}
Pitch::Pitch(MidiNote midiNote){}
std::ostream& Pitch::operator<<(std::ostream& os){ return os; }

Note::Note(std::string noteName){}
Note::Note(Frequency noteFrequency){}
Note::Note(Pitch notePitch){}
