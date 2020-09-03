// These two snippet, xxx_foreground.c and xxx_background.c, test the ability of
// multi-process application's standard output/error, by redirecting the file
// descriptor.
//
// This foreground snippet "broadcast" its stderr by setting a environment
// variable. Therefor, background snippet is able to get foreground stderr.
//
// Noted: the environment variable will be implicitly inherited by any program
// that foreground exec, according to `man execle/execpe`,
// > All other exec() functions (which do not include 'e' in the suffix) take
// > the environment for the new process image from the external variable
// > environ in the calling process.
// so, it is guaranteed that this environment variable is confined in foreground
// and its children.

#define ENV_PTS "ENV_PTS"
