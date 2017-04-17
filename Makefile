KMOD=	mac_rtprio

SRCS=	vnode_if.h \
		mac_rtprio.c

.include <bsd.kmod.mk>

