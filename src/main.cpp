#include <Note.h>
#include <clara.hpp>
#include <iomanip>
#include <iostream>
#include <ostream>
#include <string>

int main(int argc, char* argv[])
{
    bool showHelp = false;
    std::string midiStr;
    bool outputMidi = false;
    std::string frequencyStr;
    bool outputFrequency = false;
    std::string pitchName;
    bool outputPitch = false;

    auto cli =
	clara::Help(showHelp) |
	clara::Opt(midiStr, "MIDI")
	["-m"]["--midi"]
	("Input MIDI number") |
	clara::Opt(frequencyStr, "Frequency")
	["-f"]["--frequency"]
	("Input frequency in Hz") |
	clara::Opt(pitchName, "Pitch name")
	["-p"]["--pitch"]
	("Input pitch name") |
	clara::Opt(outputMidi)
	["-i"]["--output-midi"]
	("Whether to output MIDI") |
	clara::Opt(outputFrequency)
	["-y"]["--output-freq"]
	("Whether to output frequency (Hz)") |
	clara::Opt(outputPitch)
	["-n"]["--output-pitch"]
	("Whether to output pitch");

    auto result = cli.parse(clara::Args(argc, argv));


    if (showHelp)
    {
	std::cout << "\nnoteconv\n\n"
		  << "Provide one input unit and whichever outputs desired.\n"
		  << "If more than one input is provided they will be read in\n"
		  << "the order Pitch, MIDI, Frequency (e.g. if Pitch and\n"
		  << "Frequency are provided only Pitch will be used). If no\n"
		  << "output is provided then all units will be printed.\n\n"
		  << cli << '\n';

	exit(0);
    }
    
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

    std::ostringstream resultOutput;

    // If all the options are false we want to print everything
    if (!outputPitch && !outputMidi && !outputFrequency)
    {
	outputPitch = true;
	outputMidi = true;
	outputFrequency = true;
    }

    if (outputPitch)
    {
	resultOutput << "Pitch: " << note.getPitch() << '\n';
    }
    if (outputMidi)
    {
	resultOutput << "MIDI: " << note.getMidiNote() << '\n';
    }
    if (outputFrequency)
    {
	resultOutput << "Frequency: " << note.getFrequency() << '\n';
    }

    std::cout << resultOutput.str();

    return 0;
}

