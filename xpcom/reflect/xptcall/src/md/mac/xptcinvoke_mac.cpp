/* -*- Mode: C; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
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

/* Platform specific code to invoke XPCOM methods on native objects */

#include "xptcprivate.h"

#ifndef XP_MAC
#error "This code is for Macintosh only"
#endif

extern "C" uint32
invoke_count_words(PRUint32 paramCount, nsXPTCVariant* s)
{
    PRUint32 result = 0;
    for(PRUint32 i = 0; i < paramCount; i++, s++)
    {
        if(s->IsPtrData())
        {
            result++;
            continue;
        }
        switch(s->type)
        {
        case nsXPTType::T_I8     :
        case nsXPTType::T_I16    :
        case nsXPTType::T_I32    :
            result++;
            break;
        case nsXPTType::T_I64    :
            result+=2;
            break;
        case nsXPTType::T_U8     :
        case nsXPTType::T_U16    :
        case nsXPTType::T_U32    :
            result++;
            break;
        case nsXPTType::T_U64    :
            result+=2;
            break;
        case nsXPTType::T_FLOAT  :
            result++;
            break;
        case nsXPTType::T_DOUBLE :
            result+=2;
            break;
        case nsXPTType::T_BOOL   :
        case nsXPTType::T_CHAR   :
        case nsXPTType::T_WCHAR  :
            result++;
            break;
        default:
            // all the others are plain pointer types
            result++;
            break;
        }
    }
    return result;
}

extern "C" void
invoke_copy_to_stack(PRUint32* d, PRUint32 paramCount, nsXPTCVariant* s, double *fprData)
{
	PRUint32 fpCount = 0;
    for(PRUint32 i = 0; i < paramCount; i++, d++, s++)
    {
        if(s->IsPtrData())
        {
            *((void**)d) = s->ptr;
            continue;
        }
        switch(s->type)
        {
        case nsXPTType::T_I8     : *((PRInt32*) d) = s->val.i8;          break;
        case nsXPTType::T_I16    : *((PRInt32*) d) = s->val.i16;         break;
        case nsXPTType::T_I32    : *((PRInt32*) d) = s->val.i32;         break;
        case nsXPTType::T_I64    : *((PRInt64*) d) = s->val.i64; d++;    break;
        case nsXPTType::T_U8     : *((PRUint32*) d) = s->val.u8;          break;
        case nsXPTType::T_U16    : *((PRUint32*)d) = s->val.u16;         break;
        case nsXPTType::T_U32    : *((PRUint32*)d) = s->val.u32;         break;
        case nsXPTType::T_U64    : *((PRUint64*)d) = s->val.u64; d++;    break;
        case nsXPTType::T_FLOAT  : *((float*)   d) = s->val.f;
        			   if (fpCount < 13)
        		               fprData[fpCount++] = s->val.f;
        			   break;
        case nsXPTType::T_DOUBLE : *((double*)  d) = s->val.d;   d++;
        			   if (fpCount < 13)
        			       fprData[fpCount++] = s->val.d;
        			   break;
        case nsXPTType::T_BOOL   : *((PRBool*)  d) = s->val.b;           break;
        case nsXPTType::T_CHAR   : *((PRInt32*)    d) = s->val.c;        break;
        case nsXPTType::T_WCHAR  : *((PRUint32*) d) = s->val.wc;         break;
        default:
            // all the others are plain pointer types
            *((void**)d) = s->val.p;
            break;
        }
    }
}

#pragma export on

extern "C" nsresult _XPTC_InvokeByIndex(nsISupports* that, PRUint32 methodIndex,
                   PRUint32 paramCount, nsXPTCVariant* params);

extern "C"
XPTC_PUBLIC_API(nsresult)
XPTC_InvokeByIndex(nsISupports* that, PRUint32 methodIndex,
                   PRUint32 paramCount, nsXPTCVariant* params)
{
    return _XPTC_InvokeByIndex(that, methodIndex, paramCount, params);
}    

#pragma export off
