/*
 * This Program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation; version 2 of the License.
 * 
 * This Program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along with
 * this Program; if not, write to the Free Software Foundation, Inc., 59 Temple
 * Place, Suite 330, Boston, MA 02111-1307 USA.
 *
 * Copyright (C) 2011  Babel srl 
 *
 * Author: Francesco Fiore <ffiore@babel.it> 
 *
 */ 

#include "libiassert.h"

/**
 * Install a signal handler.
 *
 * When not SIGALRM, every system call will be restarted
 *
 */
void ( *signal_handler(int signum, void (*func)(int) ) ) (int) {
    struct sigaction act, oact;

    // set an empty signal handler to func
    act.sa_handler = func;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;

    // interrupt system calls only
    // on SIGALRM
    // otherwise restart them
    if (signum != SIGALRM) {
#ifdef SA_RESTART
        act.sa_flags |= SA_RESTART;
#endif
    } else {
#ifdef SA_INTERRUPT
        act.sa_flags |= SA_INTERRUPT;
#endif
    }

    if (sigaction(signum, &act, &oact) == -1)
        return SIG_ERR;

    return (oact.sa_handler);
}
