#include <catch2/catch.hpp>
#include <cmath>
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
	REQUIRE ( midiNote.getRounded() == 67 );
	Frequency frequency = midiNote;
	REQUIRE ( frequency.getRounded() == 392.0 );
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
	REQUIRE ( frequency.get() == Approx(440.0) );
	REQUIRE ( frequency.getRounded() == 440.0 );
    }

    SECTION ( "MIDI -> Frequency" )
    {
	Frequency frequency = MidiNote(67);
	REQUIRE ( frequency.get() == Approx(392.0) );
	REQUIRE ( frequency.getRounded() == 392.0 );
    }

    SECTION ( "Pitch -> Frequency" )
    {
	Frequency frequency = Pitch("F4");
	REQUIRE ( frequency.get() == Approx(349.23) );
	REQUIRE ( frequency.getRounded() == 349.23 );
    }
}

TEST_CASE ( "Pitch" )
{
    SECTION ( "Pitch -> Pitch" )
    {
	Pitch pitch("A4");
	REQUIRE ( pitch.get() == "a4" );
    }

    SECTION ( "Frequency -> Pitch" )
    {
	Pitch pitch = Frequency(392.0);
	REQUIRE ( pitch.get() == "g4" );

	pitch = Frequency(13.75);
	REQUIRE ( pitch.get() == "a" );
    }

    SECTION ( "MIDI -> Pitch" )
    {
	{
	    Pitch pitch = MidiNote(69);
	    REQUIRE ( pitch.get() == "a4" );
	}
	{
	    Pitch pitch = MidiNote(3);
	    REQUIRE ( pitch.get() == "ds" );
	}
    }

    SECTION ( "MIDI Representation" )
    {
	Pitch pitch("A4");
	REQUIRE ( pitch.getMidi().get() == Approx(69.0f) );
    }
}
