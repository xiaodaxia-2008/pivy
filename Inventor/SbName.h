#ifndef COIN_SBNAME_H
#define COIN_SBNAME_H

/**************************************************************************\
 *
 *  This file is part of the Coin 3D visualization library.
 *  Copyright (C) 1998-2003 by Systems in Motion.  All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  ("GPL") version 2 as published by the Free Software Foundation.
 *  See the file LICENSE.GPL at the root directory of this source
 *  distribution for additional information about the GNU GPL.
 *
 *  For using Coin with software that can not be combined with the GNU
 *  GPL, and for taking advantage of the additional benefits of our
 *  support services, please contact Systems in Motion about acquiring
 *  a Coin Professional Edition License.
 *
 *  See <URL:http://www.coin3d.org> for  more information.
 *
 *  Systems in Motion, Teknobyen, Abels Gate 5, 7030 Trondheim, NORWAY.
 *  <URL:http://www.sim.no>.
 *
\**************************************************************************/

#include <Inventor/SbBasic.h>

class SbString;

#ifdef __PIVY__
%rename(SbName_char) SbName::SbName(const char * nameString);
%rename(SbName_str) SbName::SbName(const SbString & str);
%rename(SbName_name) SbName::SbName(const SbName & name);

%feature("shadow") SbName::SbName %{
def __init__(self,*args):
   if len(args) == 1:
      if isinstance(args[0], SbName):
         self.this = apply(_pivy.new_SbName_str,args)
         self.thisown = 1
         return
      elif isinstance(args[0], SbName):
         self.this = apply(_pivy.new_SbName_name,args)
         self.thisown = 1
         return
      else:
         self.this = apply(_pivy.new_SbName_char,args)
         self.thisown = 1
         return
   self.this = apply(_pivy.new_SbName,args)
   self.thisown = 1
%}
#endif

class COIN_DLL_API SbName {
public:
  SbName(void);
  SbName(const char * nameString);
  SbName(const SbString & str);
  SbName(const SbName & name);
  ~SbName(void);

  const char * getString(void) const;
  int getLength(void) const;
  static SbBool isIdentStartChar(const char c);
  static SbBool isIdentChar(const char c);
  static SbBool isBaseNameStartChar(const char c);
  static SbBool isBaseNameChar(const char c);

  int operator ! (void) const;
  friend COIN_DLL_API int operator == (const SbName & lhs, const char * rhs);
  friend COIN_DLL_API int operator == (const char * lhs, const SbName & rhs);
  friend COIN_DLL_API int operator == (const SbName & lhs, const SbName & rhs);
  friend COIN_DLL_API int operator != (const SbName & lhs, const char * rhs);
  friend COIN_DLL_API int operator != (const char * lhs, const SbName & rhs);
  friend COIN_DLL_API int operator != (const SbName & lhs, const SbName & rhs);

  operator const char * (void) const;

private:
  const class SbNameEntry * entry;
};
COIN_DLL_API int operator == (const SbName & lhs, const char * rhs);
COIN_DLL_API int operator == (const char * lhs, const SbName & rhs);
COIN_DLL_API int operator == (const SbName & lhs, const SbName & rhs);
COIN_DLL_API int operator != (const SbName & lhs, const char * rhs);
COIN_DLL_API int operator != (const char * lhs, const SbName & rhs);
COIN_DLL_API int operator != (const SbName & lhs, const SbName & rhs);

#endif // !COIN_SBNAME_H
