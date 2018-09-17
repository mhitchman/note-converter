#include <Note.h>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <sstream>
#include <stdexcept>

/************
 * MIDINOTE *
 ************/

MidiNote::MidiNote(const Frequency& noteFrequency)
    :midiNote(0)
{
    midiNote = 12 * std::log2(noteFrequency.get() / 440) + 69;
}

MidiNote::MidiNote(const Pitch& notePitch)
    :MidiNote(notePitch.getMidi())
{}

int MidiNote::getRounded() const
{
    float note = midiNote;
    return std::round(note);
}


/*************
 * FREQUENCY *
 *************/

Frequency::Frequency(float noteFrequency)
    :frequency(noteFrequency)
{
    if (noteFrequency <= 0)
    {
	throw std::invalid_argument("Frequency must be greater than 0");
    }
}

Frequency::Frequency(const MidiNote& midiNote)
    :frequency(1.0)
{
    frequency = std::pow(2.0, (midiNote.get() - 69.0) / 12) * 440;
}

Frequency::Frequency(const Pitch& notePitch)
    :Frequency(notePitch.getMidi())
{}

double Frequency::getRounded() const
{
    std::stringstream ss;
    ss << std::setprecision(2) << std::fixed << frequency;
    double rounded;
    ss >> rounded;
    return rounded;
}


/*********
 * PITCH *
 *********/

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

Pitch::Pitch(const Frequency& noteFrequency)
{
    MidiNote midiStep(noteFrequency);
    *this = Pitch(midiStep);
}

Pitch::Pitch(const MidiNote& midiNote)
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
    note = possibleNoteNames.at(normalisedValue - difference);
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

Pitch& Pitch::operator=(const std::string& noteName)
{
    *this = Pitch(noteName);
    return *this;
}

Pitch& Pitch::operator=(const Frequency& noteFrequency)
{
    *this = Pitch(noteFrequency);
    return *this;
}

Pitch& Pitch::operator=(const Pitch& pitch)
{
    this->note = pitch.note;
    this->modifier = pitch.modifier;
    this->octave = pitch.octave;
    this->midiRepresentation = pitch.midiRepresentation;
    return *this;
}

Pitch& Pitch::operator=(const MidiNote& midiNote)
{
    *this = Pitch(midiNote);
    return *this;
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

void Pitch::convertToMidiRepresentation()
{
    // Get the index of the note from the possibleNoteNames array
    int noteIndex = std::distance(possibleNoteNames.begin(),
				  std::find(possibleNoteNames.begin(), possibleNoteNames.end(), note[0]));

    // Use that to get the lowest midi value for the note
    noteIndex = noteIndex < 3 ? 2 * noteIndex : noteIndex - 1 + noteIndex;

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

    const int notesInScale = 12;
    // Note name without an octave should be the equivalent to octave -1
    // e.g. prevents a having the same midi number as a0
    const int octaveNumber = octave.empty() ? -1 : std::stoi(octave);
    midiRepresentation = notesInScale + octaveNumber * notesInScale + noteIndex;
}  
