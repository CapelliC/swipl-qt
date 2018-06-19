/*  Part of SWI-Prolog interface to Qt

    Author:        Carlo Capelli
    E-mail:        cc.carlo.cap@gmail.com
    Copyright (c)  2013, Carlo Capelli
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions
    are met:

    1. Redistributions of source code must retain the above copyright
       notice, this list of conditions and the following disclaimer.

    2. Redistributions in binary form must reproduce the above copyright
       notice, this list of conditions and the following disclaimer in
       the documentation and/or other materials provided with the
       distribution.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
    "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
    LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
    FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
    COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
    INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
    BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
    CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
    LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
    ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
    POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef PREDICATE_H
#define PREDICATE_H

#include <SWI-cpp.h>

#ifndef NO_SHORTEN_INTERFACE

#include <QVector>

/** shorten interface */

typedef const char* CCP;
typedef const wchar_t* WCP;
typedef const void* CVP;
#define QCT QThread::currentThread()

#include <QString>

inline CCP S(const PlTerm &T) { return T; }

inline PlAtom W(const QString &s) {
    return PlAtom(s.toStdWString().data());
}
inline PlAtom A(QString s) {
    return W(s);
}

inline QString t2w(PlTerm t) {
    return QString::fromWCharArray(WCP(t));
}

inline QString serialize(PlTerm t) {
    wchar_t *s;

    if ( PL_get_wchars(t, NULL, &s, CVT_WRITEQ|BUF_RING) )
      return QString::fromWCharArray(s);

    throw PlTypeError("text", t);
    PL_THROWN(NULL);
}

typedef PlTerm T;
typedef PlTermv V;
typedef PlCompound C;
typedef PlTail L;

/** get back an object passed by pointer to Prolog */
template<typename Obj> Obj* pq_cast(T ptr) { return static_cast<Obj*>(static_cast<void*>(ptr)); }

inline PlTerm empty_list() {
    PlTerm el;
    PlTail EL(el);
    EL.close();
    return el;
}

inline PlTerm build_list(PlTerm host, QVector<PlTerm> ts) {
    PlTail l(host);
    for (auto x: ts)
        l.append(x);
    l.close();
    return host;
}

/** structureN(name): named compound term construction.
    For instance 'structure2(point)' enables
      point(X,Y)
    instead of
      PlCompound("point", PlTermv(X,Y))
 */
#define structure1(X) inline PlCompound X(T A) { return PlCompound(#X, V(A)); }
#define structure2(X) inline PlCompound X(T A, T B) { return PlCompound(#X, V(A, B)); }
#define structure3(X) inline PlCompound X(T A, T B, T C) { return PlCompound(#X, V(A, B, C)); }
#define structure4(X) inline PlCompound X(T A, T B, T C, T D) { return PlCompound(#X, V(A, B, C, D)); }
#define structure5(X) inline PlCompound X(T A, T B, T C, T D, T E) { return PlCompound(#X, V(A, B, C, D, E)); }

/** predicateN(name) : access Prolog predicate by name.
    For instance predicate2(member) enables
      if (member(X, Y))...
    instead of
      if (PlCall("member", PlTermv(X, Y)))...
 */
#define predicate0(P) inline int P() { return PlCall(#P); }
#define predicate1(P) inline int P(T A) { return PlCall(#P, V(A)); }
#define predicate2(P) inline int P(T A, T B) { return PlCall(#P, V(A, B)); }
#define predicate3(P) inline int P(T A, T B, T C) { return PlCall(#P, V(A, B, C)); }
#define predicate4(P) inline int P(T A, T B, T C, T D) { return PlCall(#P, V(A, B, C, D)); }
#define predicate5(P) inline int P(T A, T B, T C, T D, T E) { return PlCall(#P, V(A, B, C, D, E)); }

/** mod_predicateN(module,name) : access Prolog predicate by name and context module.
    For instance mod_predicate2(lists,member) enables
      if (member(X, Y))...
    instead of
      if (PlCall("lists", "member", PlTermv(X, Y)))...
 */
#define mod_predicate0(M,P) inline int P() { return PlCall(#M, #P); }
#define mod_predicate1(M,P) inline int P(T A) { return PlCall(#M, #P, V(A)); }
#define mod_predicate2(M,P) inline int P(T A, T B) { return PlCall(#M, #P, V(A, B)); }
#define mod_predicate3(M,P) inline int P(T A, T B, T C) { return PlCall(#M, #P, V(A, B, C)); }
#define mod_predicate4(M,P) inline int P(T A, T B, T C, T D) { return PlCall(#M, #P, V(A, B, C, D)); }
#define mod_predicate5(M,P) inline int P(T A, T B, T C, T D, T E) { return PlCall(#M, #P, V(A, B, C, D, E)); }

/** queryN(name) : multiple solution by name.
    For instance 'query3(select)' enables
      for (select s(X, Xs, Rs); s; ) {}
    instead of
      PlQuery s("select", PlTermv(X, X, Rs));
      while (s.next_solution()) {}
 */
#define LOOP__ { } operator bool() { return next_solution(); }
#define query0(P) struct P : PlQuery { P() : PlQuery(#P, V()) LOOP__ };
#define query1(P) struct P : PlQuery { P(T A) : PlQuery(#P, V(A)) LOOP__ };
#define query2(P) struct P : PlQuery { P(T A, T B) : PlQuery(#P, V(A, B)) LOOP__ };
#define query3(P) struct P : PlQuery { P(T A, T B, T C) : PlQuery(#P, V(A, B, C)) LOOP__ };
#define query4(P) struct P : PlQuery { P(T A, T B, T C, T D) : PlQuery(#P, V(A, B, C, D)) LOOP__ };
#define query5(P) struct P : PlQuery { P(T A, T B, T C, T D, T E) : PlQuery(#P, V(A, B, C, D, E)) LOOP__ };

#endif

#endif // PREDICATE_H
