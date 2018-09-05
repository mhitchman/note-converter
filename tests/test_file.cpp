#include <catch2/catch.hpp>
#include <Note.h>

TEST_CASE ( "Midi", "[midi]" )
{
    SECTION ( "MIDI -> MIDI" )
    {
	MidiNote midiNote(69);
	REQUIRE ( midiNote.get() == 69 );
    }

    SECTION ( "Frequency -> MIDI" )
    {
	MidiNote midiNote = Frequency(392);
	REQUIRE ( midiNote.get() == 67 );
    }

    SECTION ( "Pitch -> MIDI" )
    {
	MidiNote midiNote = Pitch("F4");
	REQUIRE ( midiNote.get() == 65 );
    }
}

TEST_CASE ( "Frequency" )
{
    SECTION ( "Frequency -> Frequency" )
    {
	Frequency frequency(440);
	REQUIRE ( frequency.get() == 440.0f );
    }

    SECTION ( "MIDI -> Frequency" )
    {
	Frequency frequency = MidiNote(67);
	REQUIRE ( frequency.get() == 392.0f );
    }

    SECTION ( "Pitch -> Frequency" )
    {
	Frequency frequency = Pitch("F4");
	REQUIRE ( frequency.get() == 349.23f );
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
