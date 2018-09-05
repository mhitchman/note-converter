#include <catch2/catch.hpp>
#include <Note.h>

TEST_CASE ( "Midi" )
{
    SECTION ( "MIDI -> MIDI" )
    {
	MidiNote midiNote(69);
	REQUIRE ( midiNote.get() == 69 );
    }

    SECTION ( "Frequency -> MIDI" )
    {
	MidiNote midiNote = Frequency(440);
	REQUIRE ( midiNote.get() == 69 );
    }

    SECTION ( "Pitch -> MIDI" )
    {
	MidiNote midiNote = Pitch("A4");
	REQUIRE ( midiNote.get() == 69 );
    }
}

TEST_CASE ( "Frequency" )
{
    SECTION ( "Frequency -> Frequency" )
    {
	Frequency frequency(440);
	REQUIRE ( frequency.get() == 440 );
    }

    SECTION ( "MIDI -> Frequency" )
    {
	Frequency frequency = MidiNote(69);
	REQUIRE ( frequency.get() == 440 );
    }

    SECTION ( "Pitch -> Frequency" )
    {
	Frequency frequency = Pitch("A4");
	REQUIRE ( frequency.get() == 440 );
    }
}

TEST_CASE ( "Pitch" )
{
    SECTION ( "Pitch -> Pitch" )
    {
	Pitch pitch("A4");
	REQUIRE ( pitch.get() == "A4" );
    }

    SECTION ( "Frequency -> Pitch" )
    {
	Pitch pitch = Frequency(440);
	REQUIRE ( pitch.get() == "A4" );

	pitch = Frequency(13.75);
	REQUIRE ( pitch.get() == "A" );
    }

    SECTION ( "MIDI -> Pitch" )
    {
	Pitch pitch = MidiNote(69);
	REQUIRE ( pitch.get() == "A4" );
    }
}
