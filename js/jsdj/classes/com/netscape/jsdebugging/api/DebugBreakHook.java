/* -*- Mode: C; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 2 -*-
 *
 * The contents of this file are subject to the Netscape Public License
 * Version 1.0 (the "NPL"); you may not use this file except in
 * compliance with the NPL.  You may obtain a copy of the NPL at
 * http://www.mozilla.org/NPL/
 *
 * Software distributed under the NPL is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the NPL
 * for the specific language governing rights and limitations under the
 * NPL.
 *
 * The Initial Developer of this code under the NPL is Netscape
 * Communications Corporation.  Portions created by Netscape are
 * Copyright (C) 1998 Netscape Communications Corporation.  All Rights
 * Reserved.
 */

package com.netscape.jsdebugging.api;

/**
 * DebugBreakHook must be subclassed to respond to hooks
 * at a particular program instruction.
 */
public class DebugBreakHook extends Hook {

    /**
     * Override this method to respond just before a thread
     * reaches a particular instruction.
     */
    /* jband - 03/31/97 - I made this public to allow chaining */
    public void aboutToExecute(ThreadStateBase debug, PC pc) {
        // defaults to no action
    }
}
