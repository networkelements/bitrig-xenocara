# $OpenBSD: Makefile,v 1.6 2014/07/19 17:06:47 jsg Exp $
.include <bsd.xconf.mk>

LIB=		drm_intel

INCSDIR=	${X11BASE}/include/

CPPFLAGS+=	-I${.CURDIR}			\
		-I${.CURDIR}/..			\
		-I${X11BASE}/include		\
		-I/usr/include/dev/pci/drm 

INCS=		intel_aub.h		\
		intel_bufmgr.h

SRCS=		intel_bufmgr.c		\
		intel_bufmgr_fake.c	\
		intel_bufmgr_gem.c	\
		intel_decode.c		\
		mm.c

PKGCONFIG=	libdrm_intel.pc

LDADD+=		-L${X11BASE}/lib -lX11 -lpciaccess

.include <bsd.lib.mk>
.include <bsd.xorg.mk>
