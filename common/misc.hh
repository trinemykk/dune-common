// -*- tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 2 -*-
// vi: set et ts=4 sw=2 sts=2:
#ifndef __MISC_HH__
#define __MISC_HH__

#include <iostream>
#include <math.h>



//! Check condition at compilation time
template <bool flag> class CompileTimeChecker;

//! it exists only an implementation for true so the compiler throws an
//! error if the condition is false
template <> class CompileTimeChecker<true> { };


namespace Dune {
  /** @addtogroup Common

          @{
   */

  template<class T>
  T ABS (T t)
  {
    if (t<0) return -t;
    return t;
  }


  template <class T>
  T* realloc(T* & pointer, int size) {
    if (size==0) {
      std::cerr << "Warning request for realloc with size=0\n";
      size = 1;
    }
    pointer =
      static_cast<T*>(::realloc(static_cast<void*>(pointer),
                                size*sizeof(T)));
    if (pointer == 0)
      throw std::string("Bad realloc");
    return pointer;
  }

  template <class T>
  T* malloc(int size) {
    return static_cast<T*>(::malloc(size*sizeof(T)));
  }

  //********************************************************************
  //
  // generate filenames with timestep number in it
  //
  //********************************************************************

  template <typename T>
  inline const char *genFilename(T *path, T *fn, int ntime)
  {
    static char name[256];
    char         *cp;

    if (path == NULL || path[0] == '\0')
    {
      sprintf(name, "./%s", fn);
    }
    else
    {
      const char *cp = path;
      while (*cp)
        cp++;
      cp--;
      if (*cp == '/')
        sprintf(name, "%s%s", path, fn);
      else
        sprintf(name, "%s/%s", path, fn);
    }
    cp = name;
    while (*cp)
      cp++;
    sprintf(cp, "%010d", ntime);

    return( (T *) name);
  }

  /** @} */

}


#endif
