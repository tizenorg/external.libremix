/*
 * squaredemo.c
 *
 * Copyright (C) 2001 Commonwealth Scientific and Industrial Research
 * Organisation (CSIRO), Australia.
 *
 * Permission to use, copy, modify, distribute, and sell this software and
 * its documentation for any purpose is hereby granted without fee, provided
 * that the above copyright notice appear in all copies and that both that
 * copyright notice and this permission notice appear in supporting
 * documentation.  No representations are made about the suitability of this
 * software for any purpose.  It is provided "as is" without express or
 * implied warranty.
 *
 */

#include <stdio.h>
#include <stdlib.h>

#include <remix/remix.h>

#define remix_add_sound_B(a,s,l,t1,t2) \
  remix_sound_new ((a), (s), (l), REMIX_BEAT24S(t1), REMIX_BEAT24S(t2))

#define BEAT 24
#define HALF_BEAT 12
#define QUARTER_BEAT 6
#define EIGHTH_BEAT 3

int
main (int argc, char ** argv)
{
  RemixEnv * env;
  RemixDeck * deck, * deck2;
  RemixTrack * track, * track2, * track3, * track4;
  RemixLayer * l1, * l2, * l3, * l4, * l5;
  RemixSound * s;
  RemixSquareTone * square1, * square2, * square3, * square4, * square5;
  RemixPlugin * noise_plugin;
  RemixBase * noise;
  RemixEnvelope * env1, * env2, * env3;
  RemixEnvelope * ge;
  RemixCount length;
  RemixMonitor * monitor;
  int b = 0, b2 = 0, mb;

  env = remix_init ();

  remix_set_tempo (env, 500);
  remix_set_channels (env, REMIX_STEREO);

  square1 = remix_squaretone_new (env, 100.0);
  remix_squaretone_add_channel (env, square1, 0 );

  square2 = remix_squaretone_new (env, 200.0);
  remix_squaretone_add_channel (env, square2, 0 );
  remix_squaretone_add_channel (env, square2, 1 );

  square3 = remix_squaretone_new (env, 385.0);
  remix_squaretone_add_channel (env, square3, 0 );

 // square4 = remix_squaretone_new (env, 231.0);
 // square5 = remix_squaretone_new (env, 165.0);

  monitor = remix_monitor_new (env);

  deck = remix_deck_new (env);
  track = remix_track_new (env, deck);
  l1 = remix_layer_new_ontop (env, track, REMIX_TIME_BEAT24S);
  s =  remix_sound_new (env, square1, l1, REMIX_BEAT24S(0), REMIX_BEAT24S(6));
  s =  remix_sound_new (env, square2, l1, REMIX_BEAT24S(8), REMIX_BEAT24S(12));
  s =  remix_sound_new (env, square3, l1, REMIX_BEAT24S(21), REMIX_BEAT24S(12));

/*
  remix_track_set_gain (env, track2, 0.6);

 ge = remix_envelope_new (env, REMIX_ENVELOPE_LINEAR);
 remix_envelope_set_timetype (env, ge, REMIX_TIME_SAMPLES);
 remix_envelope_add_point (env, ge, REMIX_BEAT24S(2), 0.6);
*/


  length = remix_length (env, deck);

  l2 = remix_layer_new_ontop (env, track, REMIX_TIME_SAMPLES);
  s = remix_sound_new (env, monitor, l2, REMIX_SAMPLES(0), REMIX_SAMPLES(length));
  //remix_sound_set_gain_envelope (env, s, ge);

  remix_process (env, deck, length, RemixNone, RemixNone);

  remix_purge (env);

  exit (0);
}

