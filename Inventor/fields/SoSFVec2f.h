#ifndef COIN_SOSFVEC2F_H
#define COIN_SOSFVEC2F_H

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

#include <Inventor/fields/SoSField.h>
#include <Inventor/fields/SoSubField.h>
#include <Inventor/SbVec2f.h>

#ifdef __PIVY__
%typemap(in) float xy[2] (float temp[2]) {
  convert_SbVec2f_array($input, temp);
  $1 = temp;
}

%rename(setValue_ff) SoSFVec2f::setValue(const float x, const float y);
%rename(setValue_vec) SoSFVec2f::setValue(SbVec2f const &);

%feature("shadow") SoSFVec2f::setValue(const float xy[2]) %{
def setValue(*args):
   if len(args) == 3:
      return apply(_pivy.SoSFVec2f_setValue_ff,args)
   elif isinstance(args[1],SbVec2f):
      return apply(_pivy.SoSFVec2f_setValue_vec,args)
   return apply(_pivy.SoSFVec2f_setValue,args)
%}
#endif

class COIN_DLL_API SoSFVec2f : public SoSField {
  typedef SoSField inherited;

  SO_SFIELD_HEADER(SoSFVec2f, SbVec2f, const SbVec2f &);

public:
  static void initClass(void);

#ifdef __PIVY__
  %extend {
        void __call__(float xy[2]) {
          self->setValue(xy);
        }
  }
#endif

  void setValue(const float x, const float y);
  void setValue(const float xy[2]);
};

#endif // !COIN_SOSFVEC2F_H
