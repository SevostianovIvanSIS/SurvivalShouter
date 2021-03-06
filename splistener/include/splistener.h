/*
 * splistener utilizes PocketSphinx to continuously 
 * recognize speech from a microphone and return spoken text.
 * The current version of splistener is NOT re-entrant;
 * only use this in one thread per application!
 *
 * PocketSphinx is Copyright (c) 1999-2008 Carnegie Mellon University.
 */

#include <stdint.h>

// You may modify these according to your needs
#define SPLBUFSIZE 2048
#define SPLEXPORT __declspec(dllexport)
#define SPLCLINK // if defined, sets C linkage

#ifdef SPLCLINK
extern "C" {
#endif

/**
 * Initializes the PocketSphinx decoder and 
 * begins recording from a microphone.
 *
 * Call before using other functions. All of these
 * parameters must be compatible with pocketsphinx
 * (see http://cmusphinx.sourceforge.net/wiki/tutorial
 * for more information and file formats).
 *
 * @param hmm_path Acoustic model directory that
 *                 should be used by the recognizer
 *                 (ex. pocketsphinx/model/en-us/en-us).
 * @param kws_path File with keywords to recognize in
 *                 keyword spotting mode, or NULL to use
 *                 full language search instead of keyword
 *                 search.
 * @param lm_path File with full language model to use.
 *                This is ignored when kws_path is provided
 *                and in that case can be NULL.
 * @param dict_path Dictionary file that should be used
 *                  for the desired language.
 * @param sample_rate The sample rate of the recording.
 * @param delay The amount of time in milliseconds 
 *              between decodings of microphone audio.
 * @return true if initialization was successful, 
 *         otherwise false.
 */
SPLEXPORT bool spInitListener(  const char *hmm_path, 
                                const char *kws_path, 
                                const char *lm_path, 
                                const char *dict_path, 
                                int32_t sample_rate = 16000, 
                                int delay = 100);

/**
 * Gets the last string of recognized speech
 * or an empty string if nothing has been 
 * decoded since the last call to spGetWords.
 *
 * Returns a writeable copy of the string for
 * compatibility with managed .NET environments.
 * If the caller is not in a managed environment,
 * it is the caller's responsibility to free the
 * returned string's memory.
 *
 * @return The last string of recognized speech
 *         or an empty string.
 */
SPLEXPORT char *spGetWords();

/**
 * Call at the end of a speech recognition application
 * to free splistener's resources.
 */
SPLEXPORT void spCleanUp();

/**
 * Gets the last error if there was one.
 * Returns a writeable copy of the string for 
 * compatibility with managed .NET environments.
 * If the caller is not in a managed environment,
 * it is the caller's responsibility to free the 
 * returned string's memory.
 *
 * If you want to be informed of errors in the
 * recording and decoding process, you will
 * have to check manually (perhaps periodically)
 * by calling spGetError.
 *
 * @return The last error message if there was an error,
 *         otherwise an empty string.
 */
SPLEXPORT char *spGetError();

#ifdef SPLCLINK
}
#endif
