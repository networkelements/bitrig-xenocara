# $OpenBSD: Makefile,v 1.2 2013/09/05 15:11:59 jsg Exp $

LIB = llvmpipe

SRCS = \
	lp_bld_alpha.c \
	lp_bld_blend.c \
	lp_bld_blend_aos.c \
	lp_bld_blend_logicop.c \
	lp_bld_depth.c \
	lp_bld_interp.c \
	lp_clear.c \
	lp_context.c \
	lp_draw_arrays.c \
	lp_fence.c \
	lp_flush.c \
	lp_jit.c \
	lp_memory.c \
	lp_perf.c \
	lp_query.c \
	lp_rast.c \
	lp_rast_debug.c \
	lp_rast_tri.c \
	lp_scene.c \
	lp_scene_queue.c \
	lp_screen.c \
	lp_setup.c \
	lp_setup_line.c \
	lp_setup_point.c \
	lp_setup_tri.c \
	lp_setup_vbuf.c \
	lp_state_blend.c \
	lp_state_clip.c \
	lp_state_derived.c \
	lp_state_fs.c \
	lp_state_setup.c \
	lp_state_gs.c \
	lp_state_rasterizer.c \
	lp_state_sampler.c \
	lp_state_so.c \
	lp_state_surface.c \
	lp_state_vertex.c \
	lp_state_vs.c \
	lp_surface.c \
	lp_tex_sample.c \
	lp_texture.c

CPPFLAGS+= -I${GALLIUM}/drivers/llvmpipe

lp_test_sincos.o: sse_mathfun.h

.include <bsd.xorg.mk>
