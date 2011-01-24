/*
 * Copyright (c) 2011, Andrew Sorensen
 *
 * All rights reserved.
 *
 *
 * Redistribution and use in source and binary forms, with or without 
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, 
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation 
 *    and/or other materials provided with the distribution.
 *
 * Neither the name of the authors nor other contributors may be used to endorse
 * or promote products derived from this software without specific prior written 
 * permission.
 *
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
 * ARE DISCLEXTD. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE 
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include <iostream>

#include "pthread.h"

#include "EXTCondition.h"
#include "EXTMutex.h"


#define EXTCONDITION_DEBUG


namespace extemp
{
    EXTCondition::EXTCondition()
    {
        initialised = false;
    }
    
    
    EXTCondition::~EXTCondition()
    {
        destroy();
    }
    

   int EXTCondition::init()
    {
        int result = pthread_cond_init(&pthread_cond, NULL);
        initialised = ! result;
        
#ifdef _EXTCONDITION_DEBUG_
        if (result)
        {
            std::cerr << "Error initialising condition: " << result << std::endl;
        }
#endif

        return result;
    }

    
    void EXTCondition::destroy()
    {
        int result = 0;
        
        if (initialised)
        {
            initialised = false;
            result = pthread_cond_destroy(&pthread_cond);
        }

#ifdef _EXTCONDITION_DEBUG_
        if (result)
        {
            std::cerr << "Error destroying condition: " << result << std::endl;
        }
#endif
    }

    
    int EXTCondition::wait(EXTMutex *aimeMutex)
    {
        int result = pthread_cond_wait(&pthread_cond, &aimeMutex->pthread_mutex);

#ifdef _EXTCONDITION_DEBUG_
        if (result)
        {
            std::cerr << "Error waiting on condition: " << result << std::endl;
        }
#endif

        return result;
    }

    
    int EXTCondition::signal()
    {
        int result = pthread_cond_signal(&pthread_cond);

#ifdef _EXTCONDITION_DEBUG_
        if (result)
        {
            std::cerr << "Error signalling condition: " << result << std::endl;
        }
#endif

        return result;
    }
}
