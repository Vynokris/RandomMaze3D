
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "gl.hpp"

PFNGLGETSTRINGPROC      glGetString      = nullptr;
PFNGLCLEARPROC          glClear          = nullptr;
PFNGLCLEARCOLORPROC     glClearColor     = nullptr;
PFNGLENABLEPROC         glEnable         = nullptr;
PFNGLDISABLEPROC        glDisable        = nullptr;
PFNGLBEGINPROC          glBegin          = nullptr;
PFNGLENDPROC            glEnd            = nullptr;
PFNGLVERTEX3FPROC       glVertex3f       = nullptr;
PFNGLCOLOR3FPROC        glColor3f        = nullptr;
PFNGLCOLOR3FVPROC       glColor3fv       = nullptr;
PFNGLCOLOR3UBPROC       glColor3ub       = nullptr;
PFNGLLOADIDENTITYPROC   glLoadIdentity   = nullptr;
PFNGLMATRIXMODEPROC     glMatrixMode     = nullptr;
PFNGLTRANSLATEFPROC     glTranslatef     = nullptr;
PFNGLROTATEFPROC        glRotatef        = nullptr;
PFNGLSCALEFPROC         glScalef         = nullptr;
PFNGLPUSHMATRIXPROC     glPushMatrix     = nullptr;
PFNGLPOPMATRIXPROC      glPopMatrix      = nullptr;
PFNGLORTHOPROC          glOrtho          = nullptr;
PFNGLPOLYGONMODEPROC    glPolygonMode    = nullptr;
PFNGLGENTEXTURESPROC    glGenTextures    = nullptr;
PFNGLDELETETEXTURESPROC glDeleteTextures = nullptr;
PFNGLBINDTEXTUREPROC    glBindTexture    = nullptr;
PFNGLTEXPARAMETERFPROC  glTexParameterf  = nullptr;
PFNGLTEXIMAGE2DPROC     glTexImage2D     = nullptr;
PFNGLGENERATEMIPMAPPROC glGenerateMipmap = nullptr;
PFNGLTEXCOORD2FPROC     glTexCoord2f     = nullptr;
PFNGLPIXELSTOREFPROC    glPixelStoref    = nullptr;
PFNGLLIGHTFPROC         glLightf         = nullptr;
PFNGLLIGHTFVPROC        glLightfv        = nullptr;
PFNGLCOLORMATERIALPROC  glColorMaterial  = nullptr;
PFNGLMATERIALFVPROC     glMaterialfv     = nullptr;

void loadGLFunctions()
{
    // Assign function pointers
    glGetString      = (PFNGLGETSTRINGPROC)     glfwGetProcAddress("glGetString");
    glClear          = (PFNGLCLEARPROC)         glfwGetProcAddress("glClear");
    glClearColor     = (PFNGLCLEARCOLORPROC)    glfwGetProcAddress("glClearColor");
    glEnable         = (PFNGLENABLEPROC)        glfwGetProcAddress("glEnable");
    glDisable        = (PFNGLDISABLEPROC)       glfwGetProcAddress("glDisable");
    glBegin          = (PFNGLBEGINPROC)         glfwGetProcAddress("glBegin");
    glEnd            = (PFNGLENDPROC)           glfwGetProcAddress("glEnd");
    glVertex3f       = (PFNGLVERTEX3FPROC)      glfwGetProcAddress("glVertex3f");
    glColor3f        = (PFNGLCOLOR3FPROC)       glfwGetProcAddress("glColor3f");
    glColor3fv       = (PFNGLCOLOR3FVPROC)      glfwGetProcAddress("glColor3fv");
    glColor3ub       = (PFNGLCOLOR3UBPROC)      glfwGetProcAddress("glColor3ub");
    glLoadIdentity   = (PFNGLLOADIDENTITYPROC)  glfwGetProcAddress("glLoadIdentity");
    glMatrixMode     = (PFNGLMATRIXMODEPROC)    glfwGetProcAddress("glMatrixMode");
    glTranslatef     = (PFNGLTRANSLATEFPROC)    glfwGetProcAddress("glTranslatef");
    glRotatef        = (PFNGLROTATEFPROC)       glfwGetProcAddress("glRotatef");
    glScalef         = (PFNGLSCALEFPROC)        glfwGetProcAddress("glScalef");
    glPushMatrix     = (PFNGLPUSHMATRIXPROC)    glfwGetProcAddress("glPushMatrix");
    glPopMatrix      = (PFNGLPOPMATRIXPROC)     glfwGetProcAddress("glPopMatrix");
    glOrtho          = (PFNGLORTHOPROC)         glfwGetProcAddress("glOrtho");
    glPolygonMode    = (PFNGLPOLYGONMODEPROC)   glfwGetProcAddress("glPolygonMode");
    glGenTextures    = (PFNGLGENTEXTURESPROC)   glfwGetProcAddress("glGenTextures");
    glDeleteTextures = (PFNGLDELETETEXTURESPROC)glfwGetProcAddress("glDeleteTextures");
    glBindTexture    = (PFNGLBINDTEXTUREPROC)   glfwGetProcAddress("glBindTexture");
    glTexParameterf  = (PFNGLTEXPARAMETERFPROC) glfwGetProcAddress("glTexParameterf");
    glTexImage2D     = (PFNGLTEXIMAGE2DPROC)    glfwGetProcAddress("glTexImage2D");
    glGenerateMipmap = (PFNGLGENERATEMIPMAPPROC)glfwGetProcAddress("glGenerateMipmap");
    glTexCoord2f     = (PFNGLTEXCOORD2FPROC)    glfwGetProcAddress("glTexCoord2f");
    glPixelStoref    = (PFNGLPIXELSTOREFPROC)   glfwGetProcAddress("glPixelStoref");
    glLightf         = (PFNGLLIGHTFPROC)        glfwGetProcAddress("glLightf");
    glLightfv        = (PFNGLLIGHTFVPROC)       glfwGetProcAddress("glLightfv");
    glColorMaterial  = (PFNGLCOLORMATERIALPROC) glfwGetProcAddress("glColorMaterial");
    glMaterialfv     = (PFNGLMATERIALFVPROC)    glfwGetProcAddress("glMaterialfv");
}