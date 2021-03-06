/*
 [The "BSD license"]
 Copyright (c) 2014 Rainer Mueller
 All rights reserved.

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions
 are met:

 1. Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.
 2. Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.
 3. The name of the author may not be used to endorse or promote products
    derived from this software without specific prior written permission.

 THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
/**
\file

\brief Test routines StdStream system device

\page Testprograms

\section Dation System Device StdStream
There are some tests to enshure proper operation of the StdStream system dation

*/
#include <gtest/gtest.h>
#include "Signals.h"
#include "StdStream.h"
#include "Log.h"
#include "Fixed.h"
#include "Character.h"
#include "Dation.h"
#include "DationPG.h"
#include "DationDim2.h"

using namespace std;

/**
Test ctor parameters for StdStream device
*/
TEST(StdStream, path) {
   pearlrt::Log::info("**** StdStream stream select tests ***");
   {
      ASSERT_NO_THROW(pearlrt::StdStream stdIn(0));
      ASSERT_NO_THROW(pearlrt::StdStream stdOut(1));
      ASSERT_NO_THROW(pearlrt::StdStream stdErr(2));

      ASSERT_THROW(
         pearlrt::StdStream str1(3),
         pearlrt::IllegalParamSignal);
      ASSERT_THROW(
         pearlrt::StdStream str2(-1),
         pearlrt::IllegalParamSignal);
   }
}

/**
  open close
*/
TEST(StdStream, openClose) {
   pearlrt::Log::info("**** StdStream openClose start ***");
   //---------------------------------------------------
   // tests legal operations
   pearlrt::SystemDationNB* work;
   pearlrt::StdStream stdIn(0);
   work = stdIn.dationOpen(NULL,
                          pearlrt::Dation::OLD |
                          pearlrt::Dation::IN);
   work->dationClose(pearlrt::Dation::PRM);

   pearlrt::StdStream stdOut(1);
   work = stdOut.dationOpen(NULL,
                          pearlrt::Dation::OLD |
                          pearlrt::Dation::OUT);
   work->dationClose(pearlrt::Dation::PRM);

   pearlrt::StdStream stdErr(2);
   work = stdErr.dationOpen(NULL,
                          pearlrt::Dation::OLD |
                          pearlrt::Dation::OUT);
   work->dationClose(pearlrt::Dation::PRM);

   ASSERT_THROW(
      work = stdIn.dationOpen("x.x",
                          pearlrt::Dation::OLD |
                          pearlrt::Dation::IDF |
                          pearlrt::Dation::IN),
      pearlrt::IllegalParamSignal);
}

/**
UserDations tests on stdOut
*/
TEST(StdStream, userDationStdOut) {
   pearlrt::Log::info("**** StdStream UserDations  start (StdOut) ***");

   pearlrt::StdStream stdOut(1);
   pearlrt::DationDim2 dim(80);
   pearlrt::Character<1> fn;
   ASSERT_THROW(
      pearlrt::DationPG console(&stdOut,
                             pearlrt::Dation::IN |
                             pearlrt::Dation::FORWARD |
                             pearlrt::Dation::STREAM |
                             pearlrt::Dation::NOCYCLIC,
                             &dim),
     pearlrt::IllegalParamSignal);

   ASSERT_THROW(
      pearlrt::DationPG console(&stdOut,
                             pearlrt::Dation::OUT |
                             pearlrt::Dation::DIRECT |
                             pearlrt::Dation::STREAM |
                             pearlrt::Dation::NOCYCLIC,
                             &dim),
     pearlrt::IllegalParamSignal);

   ASSERT_THROW(
      pearlrt::DationPG console(&stdOut,
                             pearlrt::Dation::OUT |
                             pearlrt::Dation::FORBACK |
                             pearlrt::Dation::STREAM |
                             pearlrt::Dation::NOCYCLIC,
                             &dim),
     pearlrt::IllegalParamSignal);

   pearlrt::DationPG console(&stdOut,
                             pearlrt::Dation::OUT |
                             pearlrt::Dation::FORWARD |
                             pearlrt::Dation::STREAM |
                             pearlrt::Dation::NOCYCLIC,
                             &dim);

   ASSERT_THROW(
      console.dationOpen(
         pearlrt::Dation::IDF ,
         &fn,
         NULL),
     pearlrt::IllegalParamSignal);
   pearlrt::Character<8> text("PEARL");

   ASSERT_THROW(
      console.dationOpen(
         pearlrt::Dation::OLD | pearlrt::Dation::IDF,
         &fn,
         NULL),
     pearlrt::IllegalParamSignal);

   ASSERT_THROW(
      console.dationOpen(
         pearlrt::Dation::CAN,
         (pearlrt::Character<1>*) 0, //&fn,
         NULL),
     pearlrt::IllegalParamSignal);
}

/**
UserDations tests on stdIn
*/
TEST(StdStream, userDationStdIn) {
   pearlrt::Log::info("**** StdStream UserDations  start (StdIn) ***");

   pearlrt::StdStream stdIn(0);
   pearlrt::DationDim2 dim(80);
   pearlrt::Character<1> fn;
   ASSERT_THROW(
      pearlrt::DationPG console(&stdIn,
                             pearlrt::Dation::OUT |
                             pearlrt::Dation::FORWARD |
                             pearlrt::Dation::STREAM |
                             pearlrt::Dation::NOCYCLIC,
                             &dim),
     pearlrt::IllegalParamSignal);

   ASSERT_THROW(
      pearlrt::DationPG console(&stdIn,
                             pearlrt::Dation::IN |
                             pearlrt::Dation::DIRECT |
                             pearlrt::Dation::STREAM |
                             pearlrt::Dation::NOCYCLIC,
                             &dim),
     pearlrt::IllegalParamSignal);

   ASSERT_THROW(
      pearlrt::DationPG console(&stdIn,
                             pearlrt::Dation::IN |
                             pearlrt::Dation::FORBACK |
                             pearlrt::Dation::STREAM |
                             pearlrt::Dation::NOCYCLIC,
                             &dim),
     pearlrt::IllegalParamSignal);

   pearlrt::DationPG console(&stdIn,
                             pearlrt::Dation::IN |
                             pearlrt::Dation::FORWARD |
                             pearlrt::Dation::STREAM |
                             pearlrt::Dation::NOCYCLIC,
                             &dim);

   ASSERT_THROW(
      console.dationOpen(
         pearlrt::Dation::IDF ,
         &fn,
         NULL),
     pearlrt::IllegalParamSignal);
   pearlrt::Character<8> text("PEARL");

   ASSERT_THROW(
      console.dationOpen(
         pearlrt::Dation::OLD | pearlrt::Dation::IDF,
         &fn,
         NULL),
     pearlrt::IllegalParamSignal);

   ASSERT_THROW(
      console.dationOpen(
         pearlrt::Dation::CAN,
         (pearlrt::Character<1>*) 0, //&fn,
         NULL),
     pearlrt::IllegalParamSignal);
}
/**
Put/Get as  visibility test only
*/
TEST(StdStream, putGet) {
   pearlrt::Log::info("**** StdStream put get  start ***");

   pearlrt::StdStream stdOut(1);
   pearlrt::DationDim2 dim(80);
   pearlrt::Character<1> fn;
   pearlrt::DationPG console(&stdOut,
                             pearlrt::Dation::OUT |
                             pearlrt::Dation::FORWARD |
                             pearlrt::Dation::STREAM |
                             pearlrt::Dation::NOCYCLIC,
                             &dim);
   ASSERT_NO_THROW(
      console.dationOpen(
         0, //pearlrt::Dation::ANY ,
         (pearlrt::Character<1>*) 0, //&fn,
         NULL));
   pearlrt::Character<8> text("PEARL");
   pearlrt::Fixed<31>  x(42);
   console.toA(text);
   console.toSkip(1);
   console.toF(x, (pearlrt::Fixed<15>)3);

   pearlrt::StdStream stdIn(0);
   pearlrt::DationPG keyboard(&stdIn,
                             pearlrt::Dation::IN |
                             pearlrt::Dation::FORWARD |
                             pearlrt::Dation::STREAM |
                             pearlrt::Dation::NOCYCLIC,
                             &dim);
   ASSERT_NO_THROW(
      keyboard.dationOpen(
         0, //pearlrt::Dation::ANY ,
         (pearlrt::Character<1>*) 0, //&fn,
         NULL));
   keyboard.fromA(text);
   keyboard.fromSkip(1);
   keyboard.fromF(x, (pearlrt::Fixed<15>)3);
   keyboard.fromSkip(1);
   keyboard.dationClose();

   pearlrt::Character<8> result("Result: ");
   console.toA(result);
   console.toA(text);
   console.toX(5);
   console.toF(x, (pearlrt::Fixed<15>)3);
   console.toSkip(1);
   console.dationClose();
}
