#pragma once

#include <GL/gl33.h>
#define __GL_H__ // To ignore default gl.h on windows
#define __gl_h_  // To ignore default gl.h on linux
#define CALLBACK __stdcall // ???
#include <GL/glu.h>

// Variables holding gl function pointers
extern PFNGLGETSTRINGPROC glGetString;
extern PFNGLCLEARPROC glClear;
extern PFNGLCLEARCOLORPROC glClearColor;
extern PFNGLENABLEPROC glEnable;
extern PFNGLDISABLEPROC glDisable;
extern PFNGLBEGINPROC glBegin;
extern PFNGLENDPROC glEnd;
extern PFNGLVERTEX3FPROC glVertex3f;
extern PFNGLCOLOR3FPROC glColor3f;
extern PFNGLCOLOR3FVPROC glColor3fv;
extern PFNGLCOLOR3UBPROC glColor3ub;
extern PFNGLLOADIDENTITYPROC glLoadIdentity;
extern PFNGLMATRIXMODEPROC glMatrixMode;
extern PFNGLTRANSLATEFPROC glTranslatef;
extern PFNGLROTATEFPROC glRotatef;
extern PFNGLSCALEFPROC glScalef;
extern PFNGLPUSHMATRIXPROC glPushMatrix;
extern PFNGLPOPMATRIXPROC glPopMatrix;
extern PFNGLORTHOPROC glOrtho;
extern PFNGLPOLYGONMODEPROC glPolygonMode;

void loadGLFunctions();
