#include <Note.h>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <sstream>
#include <stdexcept>

MidiNote::MidiNote(Frequency noteFrequency)
    :midiNote(0)
{
    midiNote = 12 * std::log2(noteFrequency.get() / 440) + 69;
}

MidiNote::MidiNote(Pitch /*notePitch*/)
    :midiNote(0)
{
    
}

int MidiNote::getRounded()
{
    float note = midiNote;
    return std::round(note);
}

std::ostream& MidiNote::operator<<(std::ostream& os)
{
    os << midiNote;
    return os;
}

Frequency::Frequency(MidiNote midiNote)
    :frequency(0.0)
{
    frequency = std::pow(2.0, (midiNote.get() - 69.0) / 12) * 440;
}

Frequency::Frequency(Pitch /*notePitch*/)
    :frequency(0.0)
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

bool Pitch::validatePitchString(std::string pitchName)
{
    bool result = true;
    if ((pitchName.empty()) || (pitchName.length() > 3))
    {
	result = false;
    }
    else if (!std::all_of(pitchName.begin(),
			  pitchName.end(),
			  [](char c){ return std::isalnum(c); }))
    {
	result = false;
    }
    return result;
}

char Pitch::validateNoteName(char note)
{
    // If the note is valid return it as a string
    // Otherwise throw an error

    auto position = std::find(possibleNoteNames.begin(), possibleNoteNames.end(),  note); 
    if ( position == possibleNoteNames.end())
    {
	std::ostringstream err;
	err << "Invalid note name: " << note;
	throw std::invalid_argument(err.str());
    }

    return note;
}

std::string Pitch::validateModifier(const char& mod, bool throwError)
{
    // If it's a valid modifier return mod as a string
    // Otherwise return an empty string
    std::string result;
    result = ((mod == sharp) || (mod == flat)) ? std::string(1, mod) : "";

    if (result.empty() && throwError)
    {
	std::string err = "Invalid note modifier: ";
	err += mod;
	throw std::invalid_argument(err);
    }
    return result;
}

std::string Pitch::validateOctaveValue(char oct, bool throwError)
{
    std::string result;

    result = std::isdigit(oct) != 0 ? std::string(1, oct) : "";

    if (result.empty() && throwError)
    {
	std::string err = "Invalid octave value: ";
	err += oct;
	throw std::invalid_argument(err);
    }

    return result;
}

Pitch::Pitch(std::string noteName)
{
    std::transform(noteName.begin(), noteName.end(), noteName.begin(), ::tolower);
    if (!validatePitchString(noteName))
    {
	std::ostringstream err;
	err << "Invalid pitch name: " << noteName;
	throw std::invalid_argument(err.str());
    }

    note = validateNoteName(noteName[0]);
    
    switch(noteName.length())
    {
    case 2:
	modifier = validateModifier(noteName[1]);
	octave = validateOctaveValue(noteName[1]);
	if (modifier.empty() && octave.empty())
	{
	    std::string err = "Argument neither valid modifier or octave: ";
	    err += noteName[1];
	    throw std::invalid_argument(err);
	}
    	break;
    case 3:
	modifier = validateModifier(noteName[1], true);
	octave = validateOctaveValue(noteName[2], true);
    	break;
    }
    convertToMidiRepresentation();
}

void Pitch::convertToMidiRepresentation()
{

    int noteIndex = std::distance(possibleNoteNames.begin(),
				  std::find(possibleNoteNames.begin(), possibleNoteNames.end(), note[0]));
    if (!modifier.empty())
    {	
	if (modifier[0] == sharp)
	{
	    noteIndex++;
	}
	else if (modifier[0] == flat)
	{
	    noteIndex--;
	}
    }

    int notesInScale = 12;
    int octaveNumber = std::stoi(octave);
    midiRepresentation = notesInScale + octaveNumber * notesInScale + noteIndex;
}
    
Pitch& Pitch::operator=(const Frequency& /*noteFrequency*/)
{
    this->note = "garbage";
    this->modifier = "garbage";
    this->octave = "garbage";
    midiRepresentation = 0;
    return *this;
}

Pitch::Pitch(Frequency /*noteFrequency*/){}
Pitch::Pitch(MidiNote midiNote)
{
    midiRepresentation = midiNote;
    int normalisedValue = midiNote.getRounded() % 12;
    float difference;
    if (normalisedValue < 5)
    {
	difference = normalisedValue / 2.0f;
    }
    else
    {
	difference = (normalisedValue - 1) / 2.0f;
    }
    note = possibleNoteNames[normalisedValue - difference];
    float fractionalPart = std::modf(difference, &difference);
    if (fractionalPart != 0)
    {
	modifier = sharp;
    }

    int octaveNumber = std::floor(midiNote.getRounded() / 12.0f - 1.0);
    if (octaveNumber >= 0)
    {
	octave = std::to_string(octaveNumber);
    }
    else
    {
	octave.clear();
    }
}

std::ostream& Pitch::operator<<(std::ostream& os){ return os; }

Note::Note(std::string /*noteName*/){}
Note::Note(Frequency /*noteFrequency*/){}
Note::Note(Pitch /*notePitch*/){}
