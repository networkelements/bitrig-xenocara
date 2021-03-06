/* -*- mode: C; c-file-style: "k&r"; tab-width 4; indent-tabs-mode: t; -*- */

/*
 * Copyright (C) 2014 Rob Clark <robclark@freedesktop.org>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * Authors:
 *    Rob Clark <robclark@freedesktop.org>
 */

#ifndef FREEDRENO_LOWERING_H_
#define FREEDRENO_LOWERING_H_

#include "pipe/p_shader_tokens.h"
#include "tgsi/tgsi_scan.h"

struct fd_lowering_config {
	/* For fragment shaders, generate a shader that emulates two
	 * sided color by inserting a BGCOLOR input for each COLOR
	 * input, and insert a CMP instruction to select the correct
	 * color to use based on the TGSI_SEMANTIC_FACE input.
	 *
	 * Note that drivers which use this to emulate two sided color
	 * will:
	 *  a) need to generate (on demand) alternate shaders to use
	 *     depending on the rasterizer state (ie. whether two
	 *     sided shading enabled)
	 *  b) expect to see the BGCOLOR semantic name in fragment
	 *     shaders.  During linkage, the driver should simply
	 *     map VS.OUT.BGCOLOR[n] to FS.IN.BGCOLOR[n] (in the
	 *     same was as linking other outs/ins).
	 */
	unsigned color_two_side : 1;

	/* TODO support for alpha_to_one as well?? */

	/* Individual OPC lowerings, if lower_<opc> is TRUE then
	 * enable lowering of TGSI_OPCODE_<opc>
	 */
	unsigned lower_DST : 1;
	unsigned lower_XPD : 1;
	unsigned lower_SCS : 1;
	unsigned lower_LRP : 1;
	unsigned lower_FRC : 1;
	unsigned lower_POW : 1;
	unsigned lower_LIT : 1;
	unsigned lower_EXP : 1;
	unsigned lower_LOG : 1;
	unsigned lower_DP4 : 1;
	unsigned lower_DP3 : 1;
	unsigned lower_DPH : 1;
	unsigned lower_DP2 : 1;
	unsigned lower_DP2A : 1;
};

const struct tgsi_token * fd_transform_lowering(
		const struct fd_lowering_config *config,
		const struct tgsi_token *tokens,
		struct tgsi_shader_info *info);

#endif /* FREEDRENO_LOWERING_H_ */
