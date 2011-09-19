
#include <stdlib.h>
#include <stdio.h>

#include <remix/remix.h>

int
main (int argc, char ** argv)
{
  RemixEnv * env;
  RemixDeck * deck;
  RemixTrack * track;
  RemixLayer * l1, * l2, * sample_layer;
  RemixBase * sf1;
  RemixBase * player;
  RemixCount length;
  RemixPlugin * sf_plugin;
  RemixPlugin * player_plugin;

  CDSet * sf_parms;
  int i;
  int sf_path_key;
  RemixSound * sound;

  env = remix_init ();
  remix_set_samplerate(env, 8000);
  printf( "remix sample rate: %f\n", remix_get_samplerate(env));
  remix_set_channels (env, REMIX_STEREO);


  //############################   Setting files for MIXING ########################
  sf_plugin = remix_find_plugin (env, "builtin::sndfile_reader");   // keep the plugin list, no need to lookup everytime
   if (sf_plugin == NULL) {
     fprintf (stderr, "sf_plugin == NULL\n");
     exit (1);
   }
  sf_parms = cd_set_new (env);
  sf_path_key = remix_get_init_parameter_key (env, sf_plugin, "path");
  sf_parms = cd_set_insert (env, sf_parms, sf_path_key, CD_STRING(SAMPLEDIR "/M1F1-int16-AFsp.wav"));
  sf1 = remix_new (env, sf_plugin, sf_parms);

  deck = remix_deck_new (env);
  track = remix_track_new (env, deck);
  l1 = remix_layer_new_ontop (env, track, REMIX_TIME_SAMPLES);
  remix_sound_new (env, (RemixBase *)sf1, l1, REMIX_SAMPLES(7000), REMIX_SAMPLES(35000) );
  //################################################################################

   /////////////////////////////////  ADDING PLAYER ////////////////
   sample_layer = remix_layer_new_ontop (env, track, REMIX_TIME_SAMPLES);
   player_plugin = remix_find_plugin (env, "stream_player");   // keep the plugin list, no need to lookup everytime
     if (player_plugin == NULL) {
       fprintf (stderr, "player_plugin == NULL\n");
       exit (1);
     }
    player =  remix_new (env, player_plugin, NULL);
   remix_sound_new (env, (RemixBase *)player, sample_layer, REMIX_SAMPLES(0), REMIX_SAMPLES(35000));
   //////////////////////////////////////////////////////////////////

   remix_process (env, deck, 35000, RemixNone, RemixNone);
   exit (0);
}
