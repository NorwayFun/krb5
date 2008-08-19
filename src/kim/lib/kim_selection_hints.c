/*
 * Copyright 2005-2006 Massachusetts Institute of Technology.
 * All Rights Reserved.
 *
 * Export of this software from the United States of America may
 * require a specific license from the United States Government.
 * It is the responsibility of any person or organization contemplating
 * export to obtain such a license before exporting.
 * 
 * WITHIN THAT CONSTRAINT, permission to use, copy, modify, and
 * distribute this software and its documentation for any purpose and
 * without fee is hereby granted, provided that the above copyright
 * notice appear in all copies and that both that copyright notice and
 * this permission notice appear in supporting documentation, and that
 * the name of M.I.T. not be used in advertising or publicity pertaining
 * to distribution of the software without specific, written prior
 * permission.  Furthermore if you modify this software you must label
 * your software as modified software and not distribute it in such a
 * fashion that it might be confused with the original M.I.T. software.
 * M.I.T. makes no representations about the suitability of
 * this software for any purpose.  It is provided "as is" without express
 * or implied warranty.
 */

#include "kim_private.h"

/* ------------------------------------------------------------------------ */

struct kim_selection_hints_opaque {
    kim_string application_identifier;
    kim_string application_name;
    kim_string explanation;
    kim_options options;
    kim_boolean allow_user_interaction;
    kim_boolean use_cached_results;
    kim_string service_identity;
    kim_string client_realm;
    kim_string user;
    kim_string service_realm;
    kim_string service;
    kim_string server;
};

struct kim_selection_hints_opaque kim_selection_hints_initializer = { 
NULL,
NULL,
NULL,
KIM_OPTIONS_DEFAULT,
TRUE,
TRUE,
NULL,
NULL,
NULL,
NULL,
NULL,
NULL
};

/* ------------------------------------------------------------------------ */

static inline kim_error kim_selection_hints_allocate (kim_selection_hints *out_selection_hints)
{
    kim_error err = KIM_NO_ERROR;
    kim_selection_hints selection_hints = NULL;
    
    if (!err && !out_selection_hints) { err = param_error (1, "out_selection_hints", "NULL"); }
    
    if (!err) {
        selection_hints = malloc (sizeof (*selection_hints));
        if (!selection_hints) { err = os_error (errno); }
    }
    
    if (!err) {
        *selection_hints = kim_selection_hints_initializer;
        *out_selection_hints = selection_hints;
        selection_hints = NULL;
    }
    
    kim_selection_hints_free (&selection_hints);
    
    return check_error (err);    
}

/* ------------------------------------------------------------------------ */

kim_error kim_selection_hints_create (kim_selection_hints *out_selection_hints,
                                      kim_string           in_application_identifier)
{
    kim_error err = KIM_NO_ERROR;
    kim_selection_hints selection_hints = NULL;
    
    if (!err && !out_selection_hints      ) { err = param_error (1, "out_selection_hints", "NULL"); }
    if (!err && !in_application_identifier) { err = param_error (1, "in_application_identifier", "NULL"); }
    
    if (!err) {
        err = kim_selection_hints_allocate (&selection_hints);
    }
    
    if (!err) {
        err = kim_string_copy (&selection_hints->application_identifier, 
                               in_application_identifier);
    }
    
    if (!err) {
        *out_selection_hints = selection_hints;
        selection_hints = NULL;
    }
    
    kim_selection_hints_free (&selection_hints);
    
    return check_error (err);    
}

/* ------------------------------------------------------------------------ */

kim_error kim_selection_hints_copy (kim_selection_hints *out_selection_hints,
                                    kim_selection_hints  in_selection_hints)
{
    kim_error err = KIM_NO_ERROR;
    kim_selection_hints selection_hints = NULL;
    
    if (!err && !out_selection_hints) { err = param_error (1, "out_selection_hints", "NULL"); }
    if (!err && !in_selection_hints ) { err = param_error (1, "in_selection_hints", "NULL"); }
    
    if (!err) {
        err = kim_selection_hints_allocate (&selection_hints);
    }
    
    if (!err) {
        err = kim_string_copy (&selection_hints->application_identifier, 
                               in_selection_hints->application_identifier);
    }
    
    if (!err && in_selection_hints->application_name) {
        err = kim_string_copy (&selection_hints->application_name, 
                               in_selection_hints->application_name);
    }
    
    if (!err && in_selection_hints->explanation) {
        err = kim_string_copy (&selection_hints->explanation, 
                               in_selection_hints->explanation);
    }
    
    if (!err && in_selection_hints->options) {
        err = kim_options_copy (&selection_hints->options, 
                                in_selection_hints->options);
    }
    
    if (!err && in_selection_hints->service_identity) {
        err = kim_string_copy (&selection_hints->service_identity, 
                               in_selection_hints->service_identity);
    }
    
    if (!err && in_selection_hints->client_realm) {
        err = kim_string_copy (&selection_hints->client_realm, 
                               in_selection_hints->client_realm);
    }
    
    if (!err && in_selection_hints->user) {
        err = kim_string_copy (&selection_hints->user, 
                               in_selection_hints->user);
    }
    
    if (!err && in_selection_hints->service_realm) {
        err = kim_string_copy (&selection_hints->service_realm, 
                               in_selection_hints->service_realm);
    }
    
    if (!err && in_selection_hints->service) {
        err = kim_string_copy (&selection_hints->service, 
                               in_selection_hints->service);
    }
    
    if (!err && in_selection_hints->server) {
        err = kim_string_copy (&selection_hints->server, 
                               in_selection_hints->server);
    }
    
    if (!err) {
        selection_hints->allow_user_interaction = in_selection_hints->allow_user_interaction;
        selection_hints->use_cached_results = in_selection_hints->use_cached_results;
        
        *out_selection_hints = selection_hints;
        selection_hints = NULL;
    }
    
    kim_selection_hints_free (&selection_hints);
    
    return check_error (err);    
}

/* ------------------------------------------------------------------------ */

kim_error kim_selection_hints_set_hint (kim_selection_hints io_selection_hints,
                                        kim_string          in_hint_key,
                                        kim_string          in_hint_string)
{
    kim_error err = KIM_NO_ERROR;
    
    if (!err && !io_selection_hints) { err = param_error (1, "io_selection_hints", "NULL"); }
    if (!err && !in_hint_key       ) { err = param_error (2, "in_hint_key", "NULL"); }
    if (!err && !in_hint_string    ) { err = param_error (3, "in_hint_string", "NULL"); }
    
    if (!err) {
        if (!strcmp (in_hint_key, kim_hint_key_client_realm)) {
            err = kim_string_copy (&io_selection_hints->client_realm, 
                                   in_hint_string);
            
        } else if (!strcmp (in_hint_key, kim_hint_key_user)) {
            err = kim_string_copy (&io_selection_hints->user, 
                                   in_hint_string);
            
        } else if (!strcmp (in_hint_key, kim_hint_key_service_realm)) {
            err = kim_string_copy (&io_selection_hints->service_realm, 
                                   in_hint_string);
            
        } else if (!strcmp (in_hint_key, kim_hint_key_service)) {
            err = kim_string_copy (&io_selection_hints->service, 
                                   in_hint_string);
            
        } else if (!strcmp (in_hint_key, kim_hint_key_server)) {
            err = kim_string_copy (&io_selection_hints->server, 
                                   in_hint_string);
            
        } else if (!strcmp (in_hint_key, kim_hint_key_service_identity)) {
            err = kim_string_copy (&io_selection_hints->service_identity, 
                                   in_hint_string);
            
        } else {
            err = kim_error_set_message_for_code (KIM_UNSUPPORTED_HINT_ECODE,
                                                  in_hint_key);
        }
    }
    
    return check_error (err);
}

/* ------------------------------------------------------------------------ */

kim_error kim_selection_hints_get_hint (kim_selection_hints  in_selection_hints,
                                        kim_string           in_hint_key,
                                        kim_string          *out_hint_string)
{
    kim_error err = KIM_NO_ERROR;
    
    if (!err && !in_selection_hints) { err = param_error (1, "in_selection_hints", "NULL"); }
    if (!err && !in_hint_key       ) { err = param_error (2, "in_hint_key", "NULL"); }
    if (!err && !out_hint_string   ) { err = param_error (3, "out_hint_string", "NULL"); }
    
    if (!err) {
        if (!strcmp (in_hint_key, kim_hint_key_client_realm)) {
            err = kim_string_copy (out_hint_string, 
                                   in_selection_hints->client_realm);
            
        } else if (!strcmp (in_hint_key, kim_hint_key_user)) {
            err = kim_string_copy (out_hint_string, 
                                   in_selection_hints->user);
            
        } else if (!strcmp (in_hint_key, kim_hint_key_service_realm)) {
            err = kim_string_copy (out_hint_string, 
                                   in_selection_hints->service_realm);
            
        } else if (!strcmp (in_hint_key, kim_hint_key_service)) {
            err = kim_string_copy (out_hint_string, 
                                   in_selection_hints->service);
            
        } else if (!strcmp (in_hint_key, kim_hint_key_server)) {
            err = kim_string_copy (out_hint_string, 
                                   in_selection_hints->server);
            
        } else if (!strcmp (in_hint_key, kim_hint_key_service_identity)) {
            err = kim_string_copy (out_hint_string, 
                                   in_selection_hints->service_identity);
            
        } else {
            err = kim_error_set_message_for_code (KIM_UNSUPPORTED_HINT_ECODE,
                                                  in_hint_key);
        }
    }
    
    return check_error (err);
}

/* ------------------------------------------------------------------------ */

kim_error kim_selection_hints_set_application_name (kim_selection_hints io_selection_hints,
                                                    kim_string          in_application_name)
{
    kim_error err = KIM_NO_ERROR;
    
    if (!err && !io_selection_hints ) { err = param_error (1, "io_selection_hints", "NULL"); }
    if (!err && !in_application_name) { err = param_error (2, "in_application_name", "NULL"); }
    
    if (!err) {
        err = kim_string_copy (&io_selection_hints->application_name, in_application_name);
    }
    
    return check_error (err);
}

/* ------------------------------------------------------------------------ */

kim_error kim_selection_hints_get_application_name (kim_selection_hints  in_selection_hints,
                                                    kim_string          *out_application_name)
{
    kim_error err = KIM_NO_ERROR;
    
    if (!err && !in_selection_hints  ) { err = param_error (1, "in_selection_hints", "NULL"); }
    if (!err && !out_application_name) { err = param_error (2, "out_application_name", "NULL"); }
    
    if (!err) {
        if (in_selection_hints->application_name) {
            err = kim_string_copy (out_application_name, in_selection_hints->application_name);
        } else {
            *out_application_name = NULL;
        }
    }
    
    return check_error (err);
}

/* ------------------------------------------------------------------------ */

kim_error kim_selection_hints_set_explanation (kim_selection_hints io_selection_hints,
                                               kim_string          in_explanation)
{
    kim_error err = KIM_NO_ERROR;
    
    if (!err && !io_selection_hints) { err = param_error (1, "io_selection_hints", "NULL"); }
    if (!err && !in_explanation    ) { err = param_error (2, "in_explanation", "NULL"); }
    
    if (!err) {
        err = kim_string_copy (&io_selection_hints->explanation, in_explanation);
    }
    
    return check_error (err);
}

/* ------------------------------------------------------------------------ */

kim_error kim_selection_hints_get_explanation (kim_selection_hints  in_selection_hints,
                                               kim_string          *out_explanation)
{
    kim_error err = KIM_NO_ERROR;
    
    if (!err && !in_selection_hints) { err = param_error (1, "in_selection_hints", "NULL"); }
    if (!err && !out_explanation   ) { err = param_error (2, "out_explanation", "NULL"); }
    
    if (!err) {
        if (in_selection_hints->explanation) {
            err = kim_string_copy (out_explanation, in_selection_hints->explanation);
        } else {
            *out_explanation = NULL;
        }
    }
    
    return check_error (err);
}

/* ------------------------------------------------------------------------ */

kim_error kim_selection_hints_set_options (kim_selection_hints io_selection_hints,
                                           kim_options         in_options)
{
    kim_error err = KIM_NO_ERROR;
    
    if (!err && !io_selection_hints) { err = param_error (1, "io_selection_hints", "NULL"); }
    if (!err && !in_options        ) { err = param_error (2, "in_options", "NULL"); }
    
    if (!err) {
        err = kim_options_copy (&io_selection_hints->options, in_options);
    }
    
    return check_error (err);
}

/* ------------------------------------------------------------------------ */

kim_error kim_selection_hints_get_options (kim_selection_hints  in_selection_hints,
                                           kim_options         *out_options)
{
    kim_error err = KIM_NO_ERROR;
    
    if (!err && !in_selection_hints) { err = param_error (1, "in_selection_hints", "NULL"); }
    if (!err && !out_options       ) { err = param_error (2, "out_options", "NULL"); }
    
    if (!err) {
        if (in_selection_hints->options) {
            err = kim_options_copy (out_options, in_selection_hints->options);
        } else {
            *out_options = KIM_OPTIONS_DEFAULT;
        }
    }
    
    return check_error (err);
}

/* ------------------------------------------------------------------------ */

kim_error kim_selection_hints_set_allow_user_interaction (kim_selection_hints io_selection_hints,
                                                          kim_boolean         in_allow_user_interaction)
{
    kim_error err = KIM_NO_ERROR;
    
    if (!err && !io_selection_hints ) { err = param_error (1, "io_selection_hints", "NULL"); }
    
    if (!err) {
        io_selection_hints->allow_user_interaction = in_allow_user_interaction;
    }
    
    return check_error (err);
}

/* ------------------------------------------------------------------------ */

kim_error kim_selection_hints_get_allow_user_interaction (kim_selection_hints  in_selection_hints,
                                                          kim_boolean         *out_allow_user_interaction)
{
    kim_error err = KIM_NO_ERROR;
    
    if (!err && !in_selection_hints        ) { err = param_error (1, "in_selection_hints", "NULL"); }
    if (!err && !out_allow_user_interaction) { err = param_error (2, "out_allow_user_interaction", "NULL"); }
    
    if (!err) {
        *out_allow_user_interaction = in_selection_hints->allow_user_interaction;
    }
    
    return check_error (err);
}

/* ------------------------------------------------------------------------ */

kim_error kim_selection_hints_set_remember_identity (kim_selection_hints io_selection_hints,
                                                     kim_boolean         in_use_cached_results)
{
    kim_error err = KIM_NO_ERROR;
    
    if (!err && !io_selection_hints ) { err = param_error (1, "io_selection_hints", "NULL"); }
    
    if (!err) {
        io_selection_hints->use_cached_results = in_use_cached_results;
    }
    
    return check_error (err);
}

/* ------------------------------------------------------------------------ */

kim_error kim_selection_hints_get_remember_identity (kim_selection_hints  in_selection_hints,
                                                     kim_boolean         *out_use_cached_results)
{
    kim_error err = KIM_NO_ERROR;
    
    if (!err && !in_selection_hints    ) { err = param_error (1, "in_selection_hints", "NULL"); }
    if (!err && !out_use_cached_results) { err = param_error (2, "out_use_cached_results", "NULL"); }
    
    if (!err) {
        *out_use_cached_results = in_selection_hints->use_cached_results;
    }
    
    return check_error (err);
}

/* ------------------------------------------------------------------------ */

kim_error kim_selection_hints_get_identity (kim_selection_hints  in_selection_hints,
                                            kim_identity        *out_identity)
{
    kim_error err = KIM_NO_ERROR;
    kim_identity identity = NULL;
    kim_ccache ccache = NULL;
    
    if (!err && !in_selection_hints) { err = param_error (1, "in_selection_hints", "NULL"); }
    if (!err && !out_identity      ) { err = param_error (2, "out_identity", "NULL"); }
    
    if (!err && in_selection_hints->use_cached_results) {
        err = kim_os_selection_hints_lookup_identity (in_selection_hints, &identity);
    }
    
    if (!err && !identity && in_selection_hints->allow_user_interaction) {
#warning GUI to let user pick identity here   
    }
    
    if (!err) {
        *out_identity = identity;
        identity = NULL;
    }
    
    kim_identity_free (&identity);
    kim_ccache_free (&ccache);
    
    return check_error (err);
}

/* ------------------------------------------------------------------------ */

kim_error kim_selection_hints_remember_identity (kim_selection_hints in_selection_hints,
                                                 kim_identity        in_identity)
{
    kim_error err = KIM_NO_ERROR;
    
    if (!err && !in_selection_hints) { err = param_error (1, "in_selection_hints", "NULL"); }
    if (!err && !in_identity       ) { err = param_error (2, "in_identity", "NULL"); }
    
    if (!err) {
        err = kim_os_selection_hints_remember_identity (in_selection_hints, 
                                                        in_identity);
    }
    
    return check_error (err);
}

/* ------------------------------------------------------------------------ */

kim_error kim_selection_hints_forget_identity (kim_selection_hints in_selection_hints)
{
    kim_error err = KIM_NO_ERROR;
    
    if (!err && !in_selection_hints) { err = param_error (1, "in_selection_hints", "NULL"); }
    
    if (!err) {
        err = kim_os_selection_hints_forget_identity (in_selection_hints);
    }
    
    return check_error (err);
}

/* ------------------------------------------------------------------------ */

kim_error kim_selection_hints_get_preference_strings (kim_selection_hints                   in_selection_hints,
                                                      kim_selection_hints_preference_strings *io_preference_strings)
{
    kim_error err = KIM_NO_ERROR;
    
    if (!err && !in_selection_hints   ) { err = param_error (1, "in_selection_hints", "NULL"); }
    if (!err && !io_preference_strings) { err = param_error (2, "io_preference_strings", "NULL"); }
    
    if (!err) {
        io_preference_strings->application_identifier = in_selection_hints->application_identifier;
        io_preference_strings->service_identity       = in_selection_hints->service_identity;
        io_preference_strings->client_realm           = in_selection_hints->client_realm;
        io_preference_strings->user                   = in_selection_hints->user;
        io_preference_strings->service_realm          = in_selection_hints->service_realm;
        io_preference_strings->service                = in_selection_hints->service;
        io_preference_strings->server                 = in_selection_hints->server;
    }
    
    return check_error (err);
}

/* ------------------------------------------------------------------------ */

void kim_selection_hints_free (kim_selection_hints *io_selection_hints)
{
    if (io_selection_hints && *io_selection_hints) {
        kim_string_free  (&(*io_selection_hints)->application_identifier);
        kim_string_free  (&(*io_selection_hints)->application_name);
        kim_string_free  (&(*io_selection_hints)->explanation);
        kim_options_free (&(*io_selection_hints)->options);
        kim_string_free  (&(*io_selection_hints)->service_identity);
        kim_string_free  (&(*io_selection_hints)->client_realm);
        kim_string_free  (&(*io_selection_hints)->user);
        kim_string_free  (&(*io_selection_hints)->service_realm);
        kim_string_free  (&(*io_selection_hints)->service);
        kim_string_free  (&(*io_selection_hints)->server);
        free (*io_selection_hints);
        *io_selection_hints = NULL;
    }
}

