#include <Note.h>
#include <clara.hpp>
#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
    std::string midiStr;
    std::string frequencyStr;
    std::string pitchName;

    auto cli = 	clara::Opt(midiStr, "MIDI")
	["-m"]["--midi"]
	("MIDI number") |
	clara::Opt(frequencyStr, "Frequency")
	["-f"]["--frequency"]
	("Frequency in Hz") |
	clara::Opt(pitchName, "Pitch name")
	["-p"]["--pitch"]
	("Pitch name");

    auto result = cli.parse(clara::Args(argc, argv));

    Note note;
    try
    {
	if (!pitchName.empty())
	{
	    note = Note(Pitch(pitchName));
	}
	else if (!midiStr.empty())
	{
	    note = Note(MidiNote(std::stof(midiStr)));
	}
	else if (!frequencyStr.empty())
	{
	    note = Note(Frequency(std::stod(frequencyStr)));
	}
    }
    catch(std::exception& e)
    {
	std::cerr << e.what() << '\n';
	std::exit(-1);
    }

    std::cout << "Pitch: " << note.getPitch() << '\n' <<
	"MIDI: " << note.getMidiNote() << '\n' <<
	"Frequency: " << note.getFrequency() << '\n';

    return 0;
}

