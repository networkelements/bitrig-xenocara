# $OpenBSD: Makefile,v 1.8 2013/09/07 02:12:21 jsg Exp $
.include <bsd.xconf.mk>

SUBDIR= rbug softpipe trace

.if ${XENOCARA_BUILD_GALLIUM} == "llvm"
SUBDIR+= llvmpipe radeonsi
.endif

.if ((${XENOCARA_BUILD_GALLIUM:L} == "yes" || \
      ${XENOCARA_BUILD_GALLIUM} == "llvm") && \
    (${MACHINE} == i386 || ${MACHINE} == amd64 || ${MACHINE} == macppc || \
     ${MACHINE} == sparc64))
SUBDIR+= r300 r600
.endif

build depend all install clean cleandir: _SUBDIRUSE

.include <bsd.xorg.mk>
