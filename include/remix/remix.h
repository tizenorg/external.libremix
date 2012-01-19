/*
 * libremix -- An audio mixing and sequencing library.
 *
 * Copyright (C) 2001 Commonwealth Scientific and Industrial Research
 * Organisation (CSIRO), Australia.
 * Copyright (C) 2003 Conrad Parker
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

/** \file
 * Base types and public interfaces to libremix
 *
 */

/*
 * Conrad Parker <conrad@metadecks.org>, August 2001
 */

#ifndef __REMIX_H__
#define __REMIX_H__

/** \mainpage
 *
 * \section Introduction
 *
 * Remix is an audio sequencing and mixing library that provides a
 * multichannel, sparse audio data container (streams), a structured mixing
 * abstraction (decks), and widely useful means of generating control data
 * (via envelopes) and of caching audio data.
 *
 * \subsection contents Contents
 *
 * - \link remix_deck.h Decks \endlink:
 * The Remix hierarchical mixing abstraction
 *
 * - \link remix_stream.h Streams \endlink:
 * The multichannel PCM stream abstraction
 *
 * - \link remix.h remix.h \endlink:
 * Documentation of the Remix C API
 *
 * - \link examples Examples \endlink:
 * Annotated example programs
 *
 * - \link configuration Configuration \endlink:
 * Customizing libremix.
 *
 * - \link building Building \endlink:
 * Information related to building software that uses libremix.
 *
 * \section licensing Licensing
 *
 * libremix is provided under the
 * \link lgpl GNU Lesser General Public License \endlink.
 *
 */

/** \defgroup lgpl Licensing
 * \section lgpl GNU Lesser General Public License
 *
 * \include COPYING
 */

/** \defgroup configuration Configuration
 * \section ./configure ./configure
 *
 * It is possible to customize the functionality of libremix
 * by using various ./configure flags when
 * building it from source.
 *
 * For general information about using ./configure, see the file
 * \link install INSTALL \endlink
 */

/** \defgroup install Installation
 * \section install INSTALL
 *
 * \include INSTALL
 */

/** \defgroup building Building against libremix
 *
 *
 * \section autoconf Using GNU autoconf
 *
 * If you are using GNU autoconf, you do not need to call pkg-config
 * directly. Use the following macro to determine if libremix is
 * available:
 *
 <pre>
 PKG_CHECK_MODULES(REMIX, remix >= 0.2.0,
                   HAVE_REMIX="yes", HAVE_REMIX="no")
 if test "x$HAVE_REMIX" = "xyes" ; then
   AC_SUBST(REMIX_CFLAGS)
   AC_SUBST(REMIX_LIBS)
 fi
 </pre>
 *
 * If libremix is found, HAVE_REMIX will be set to "yes", and
 * the autoconf variables REMIX_CFLAGS and REMIX_LIBS will
 * be set appropriately.
 *
 * \section pkg-config Determining compiler options with pkg-config
 *
 * If you are not using GNU autoconf in your project, you can use the
 * pkg-config tool directly to determine the correct compiler options.
 *
 <pre>
 REMIX_CFLAGS=`pkg-config --cflags remix`

 REMIX_LIBS=`pkg-config --libs remix`
 </pre>
 *
 */

/** \defgroup examples Example programs
 *
 * Example programs are fun for all the family.
 *
 * Here's some examples.
 * - \link noisedemo Noise demo \endlink
 * - \link squaredemo Square demo \endlink
 * - \link sndfiledemo Sndfile demo \endlink
 */

/** \defgroup noisedemo Noise demo
 *
 * Plays a sequence of short bursts of whitenoise.
 *
 * \include noisedemo.c noisedemo.c
 */

/** \defgroup squaredemo Square demo
 *
 * Plays a polyphonic sequence of musical notes generated by a builtin
 * square wave synthesizer.
 *
 * \include squaredemo.c squaredemo.c
 */

/** \defgroup sndfiledemo Sndfile demo
 *
 * Plays a sequence of notes using sound files from disk.
 *
 * \include sndfiledemo.c sndfiledemo.c
 */

#include <remix/remix_types.h>

#if defined(__cplusplus)
extern "C" {
#endif

extern CDSet * REMIX_MONO;
extern CDSet * REMIX_STEREO;


/* RemixEnv */
RemixEnv * remix_init (void);
RemixEnv * remix_init_clone (RemixEnv * env);
void remix_purge (RemixEnv * env);
RemixError remix_last_error (RemixEnv * env);
char * remix_error_string (RemixEnv * env, RemixError error);
RemixSamplerate remix_set_samplerate (RemixEnv * env, RemixSamplerate samplerate);
RemixSamplerate remix_get_samplerate (RemixEnv * env);
RemixTempo remix_set_tempo (RemixEnv * env, RemixTempo tempo);
RemixTempo remix_get_tempo (RemixEnv * env);
CDSet * remix_set_channels (RemixEnv * env, CDSet * channelset);
CDSet * remix_get_channels (RemixEnv * env);

#if 0
  /* XXX */
/* Sources: Plugins, Samples etc. */
CDList * remix_open (SOUNDRENDER env, char * filename);
void remix_close (SOUNDRENDER env, RemixPlugin plugin);
#endif

/* Base objects */

RemixPlugin * remix_find_plugin (RemixEnv * env, char * identifier);

RemixBase * remix_new (RemixEnv * env, RemixPlugin * plugin, CDSet * parameters);
CDSet * remix_suggest (RemixEnv * env, RemixPlugin * plugin, CDSet * parameters);

int remix_get_init_parameter_key (RemixEnv * env, RemixPlugin * plugin, char * name);
int remix_get_parameter_key (RemixEnv * env, RemixBase * base, char * name);

RemixParameter remix_set_parameter (RemixEnv * env, RemixBase * base, int key,
				  RemixParameter parameter);
RemixParameter remix_get_parameter (RemixEnv * env, RemixBase * base, int key);
RemixParameterType remix_get_parameter_type (RemixEnv * env, RemixBase * base, int key);


RemixBase * remix_clone_subclass (RemixEnv * env, RemixBase * base);
int remix_destroy (RemixEnv * env, RemixBase * base);
int remix_destroy_list (RemixEnv * env, CDList * list);
RemixBase * remix_prepare (RemixEnv * env, RemixBase * base);
RemixCount remix_process (RemixEnv * env, RemixBase * base, RemixCount count,
		    RemixStream * input, RemixStream * output);
RemixCount remix_length (RemixEnv * env, RemixBase * base);
RemixCount remix_seek (RemixEnv * env, RemixBase * base, RemixCount offset, int whence);
RemixCount remix_tell (RemixEnv * env, RemixBase * base);
int remix_flush (RemixEnv * env, RemixBase * base);

RemixCount remix_set_mixlength (RemixEnv * env, RemixCount mixlength);
RemixCount remix_get_mixlength (RemixEnv * env);


int remix_is_writeable (RemixEnv * env, RemixBase * base);
int remix_is_seekable (RemixEnv * env, RemixBase * base);
int remix_is_cacheable (RemixEnv * env, RemixBase * base);
int remix_is_causal (RemixEnv * env, RemixBase * base);

char * remix_set_name (RemixEnv * env, RemixBase * base, char * name);
char * remix_get_name (RemixEnv * env, RemixBase * base);

#include <remix/remix_deck.h>
#include <remix/remix_envelope.h>
#include <remix/remix_stream.h>

/* SquareTone */
RemixBase * remix_squaretone_new (RemixEnv * env, float frequency);
float remix_squaretone_set_frequency (RemixEnv * env,
				      RemixBase * squaretone,
				      float frequency);
float remix_squaretone_get_frequency (RemixEnv * env,
				      RemixBase * squaretone);

/* Monitor */
RemixMonitor * remix_monitor_new (RemixEnv * env);

/* Scrubby */
RemixBase * remix_scrubby_new (RemixEnv * env);
RemixBase * remix_scrubby_set_source (RemixEnv * env, RemixBase * scrubby,
				      RemixBase * source);
RemixBase * remix_scrubby_get_source (RemixEnv * env, RemixBase * scrubby);
int remix_scrubby_set_direction (RemixEnv * env, RemixBase * scrubby, int direction);
int remix_scrubby_get_direction (RemixEnv * env, RemixBase * scrubby);

#include <remix/remix_time.h>

#include <remix/remix_meta.h>

#if defined(__cplusplus)
}
#endif

#endif /* __REMIX_H__ */
