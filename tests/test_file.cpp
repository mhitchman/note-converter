#include <catch2/catch.hpp>
#include <cmath>
#include <Note.h>

TEST_CASE ( "Midi Construction", "[midi]" )
{
    SECTION ( "Default Constructor" )
    {
	MidiNote midiNote;
	REQUIRE ( midiNote.get() == 0.0f );
	REQUIRE ( midiNote.getRounded() == 0 );
    }

    SECTION ( "MIDI -> MIDI" )
    {
	MidiNote midiNote(69);
	REQUIRE ( midiNote.get() == 69.0f );
	REQUIRE ( midiNote.getRounded() == 69 );
    }

    SECTION ( "Frequency -> MIDI" )
    {
	MidiNote midiNote = Frequency(392.0);
	CHECK ( midiNote.get() == Approx(67.0f) );
	REQUIRE ( midiNote.getRounded() == 67 );
    }

    SECTION ( "Pitch -> MIDI" )
    {
	MidiNote midiNote = Pitch("F4");
	REQUIRE ( midiNote.get() == Approx(65.0f) );
	REQUIRE ( midiNote.getRounded() == 65 );
    }
}

TEST_CASE ( "Frequency Construction", "[frequency]" )
{
    SECTION ( "Default Constructor" )
    {
	Frequency frequency;
	REQUIRE ( frequency.get() == 1.0 );
	REQUIRE ( frequency.getRounded() == 1.0 );
    }

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
	CHECK ( pitch.getMidi().getRounded() == 69 );

	SECTION ( "Notename without octave" )
	{
	    Pitch pitch("A");
	    REQUIRE ( pitch.get() == "a" );
	    CHECK ( pitch.getMidi().getRounded() == 9 );
	}
    }

    SECTION ( "Frequency -> Pitch" )
    {
	Pitch pitch = Frequency(392.0);
	REQUIRE ( pitch.get() == "g4" );
	CHECK ( pitch.getMidi().getRounded() == 67 );

	pitch = Frequency(13.75);
	REQUIRE ( pitch.get() == "a" );
	CHECK ( pitch.getMidi().getRounded() == 9 );
    }

    SECTION ( "MIDI -> Pitch" )
    {

	Pitch pitch = MidiNote(69);
	REQUIRE ( pitch.get() == "a4" );
	CHECK ( pitch.getMidi().getRounded() == 69 );

	pitch = MidiNote(3);
	REQUIRE ( pitch.get() == "ds" );
	CHECK ( pitch.getMidi().getRounded() == 3 );
    }


}
