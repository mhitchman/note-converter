#include <Note.h>
#include <cmath>
#include <iomanip>
#include <sstream>

MidiNote::MidiNote(Frequency noteFrequency)
{
    midiNote = 12 * std::log2(noteFrequency.get() / 440) + 69;
}
MidiNote::MidiNote(Pitch notePitch)
{
    
}

int MidiNote::getRounded()
{
    float note = midiNote;
    return std::round(note);
}

std::ostream& MidiNote::operator<<(std::ostream& os)
{
    return os << midiNote;
}

Frequency::Frequency(MidiNote midiNote)
{
    frequency = std::pow(2.0, (midiNote.get() - 69.0) / 12) * 440;
}

Frequency::Frequency(Pitch notePitch)
{

}

double Frequency::getRounded()
{
    std::stringstream ss;
    ss << std::setprecision(2) << std::fixed << frequency;
    double rounded;
    ss >> rounded;
    return rounded;
}

std::ostream& Frequency::operator<<(std::ostream& os)
{
    return os << frequency;
}

Pitch::Pitch(std::string noteName){}
Pitch::Pitch(Frequency noteFrequency){}
Pitch::Pitch(MidiNote midiNote){}
std::ostream& Pitch::operator<<(std::ostream& os){ return os; }

Note::Note(std::string noteName){}
Note::Note(Frequency noteFrequency){}
Note::Note(Pitch notePitch){}
