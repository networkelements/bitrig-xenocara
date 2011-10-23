/**************************************************************************
 *
 * Copyright 2009 VMware, Inc.
 * All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sub license, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial portions
 * of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT.
 * IN NO EVENT SHALL VMWARE AND/OR ITS SUPPLIERS BE LIABLE FOR
 * ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 **************************************************************************/


#include "pipe/p_screen.h"
#include "pipe/p_state.h"
#include "util/u_memory.h"

#include "id_public.h"
#include "id_screen.h"
#include "id_context.h"
#include "id_objects.h"


static void
identity_screen_destroy(struct pipe_screen *_screen)
{
   struct identity_screen *id_screen = identity_screen(_screen);
   struct pipe_screen *screen = id_screen->screen;

   screen->destroy(screen);

   FREE(id_screen);
}

static const char *
identity_screen_get_name(struct pipe_screen *_screen)
{
   struct identity_screen *id_screen = identity_screen(_screen);
   struct pipe_screen *screen = id_screen->screen;

   return screen->get_name(screen);
}

static const char *
identity_screen_get_vendor(struct pipe_screen *_screen)
{
   struct identity_screen *id_screen = identity_screen(_screen);
   struct pipe_screen *screen = id_screen->screen;

   return screen->get_vendor(screen);
}

static int
identity_screen_get_param(struct pipe_screen *_screen,
                          enum pipe_cap param)
{
   struct identity_screen *id_screen = identity_screen(_screen);
   struct pipe_screen *screen = id_screen->screen;

   return screen->get_param(screen,
                            param);
}

static int
identity_screen_get_shader_param(struct pipe_screen *_screen,
                          unsigned shader, enum pipe_shader_cap param)
{
   struct identity_screen *id_screen = identity_screen(_screen);
   struct pipe_screen *screen = id_screen->screen;

   return screen->get_shader_param(screen, shader,
                            param);
}

static float
identity_screen_get_paramf(struct pipe_screen *_screen,
                           enum pipe_cap param)
{
   struct identity_screen *id_screen = identity_screen(_screen);
   struct pipe_screen *screen = id_screen->screen;

   return screen->get_paramf(screen,
                             param);
}

static boolean
identity_screen_is_format_supported(struct pipe_screen *_screen,
                                    enum pipe_format format,
                                    enum pipe_texture_target target,
                                    unsigned sample_count,
                                    unsigned tex_usage,
                                    unsigned geom_flags)
{
   struct identity_screen *id_screen = identity_screen(_screen);
   struct pipe_screen *screen = id_screen->screen;

   return screen->is_format_supported(screen,
                                      format,
                                      target,
                                      sample_count,
                                      tex_usage,
                                      geom_flags);
}

static struct pipe_context *
identity_screen_context_create(struct pipe_screen *_screen,
                               void *priv)
{
   struct identity_screen *id_screen = identity_screen(_screen);
   struct pipe_screen *screen = id_screen->screen;
   struct pipe_context *result;

   result = screen->context_create(screen, priv);
   if (result)
      return identity_context_create(_screen, result);
   return NULL;
}

static struct pipe_resource *
identity_screen_resource_create(struct pipe_screen *_screen,
                                const struct pipe_resource *templat)
{
   struct identity_screen *id_screen = identity_screen(_screen);
   struct pipe_screen *screen = id_screen->screen;
   struct pipe_resource *result;

   result = screen->resource_create(screen,
                                    templat);

   if (result)
      return identity_resource_create(id_screen, result);
   return NULL;
}

static struct pipe_resource *
identity_screen_resource_from_handle(struct pipe_screen *_screen,
                                     const struct pipe_resource *templ,
                                     struct winsys_handle *handle)
{
   struct identity_screen *id_screen = identity_screen(_screen);
   struct pipe_screen *screen = id_screen->screen;
   struct pipe_resource *result;

   /* TODO trace call */

   result = screen->resource_from_handle(screen, templ, handle);

   result = identity_resource_create(identity_screen(_screen), result);

   return result;
}

static boolean
identity_screen_resource_get_handle(struct pipe_screen *_screen,
                                    struct pipe_resource *_resource,
                                    struct winsys_handle *handle)
{
   struct identity_screen *id_screen = identity_screen(_screen);
   struct identity_resource *id_resource = identity_resource(_resource);
   struct pipe_screen *screen = id_screen->screen;
   struct pipe_resource *resource = id_resource->resource;

   /* TODO trace call */

   return screen->resource_get_handle(screen, resource, handle);
}



static void
identity_screen_resource_destroy(struct pipe_screen *screen,
                                 struct pipe_resource *_resource)
{
   identity_resource_destroy(identity_resource(_resource));
}


static struct pipe_resource *
identity_screen_user_buffer_create(struct pipe_screen *_screen,
                                   void *ptr,
                                   unsigned bytes,
                                   unsigned usage)
{
   struct identity_screen *id_screen = identity_screen(_screen);
   struct pipe_screen *screen = id_screen->screen;
   struct pipe_resource *result;

   result = screen->user_buffer_create(screen,
                                       ptr,
                                       bytes,
                                       usage);

   if (result)
      return identity_resource_create(id_screen, result);
   return NULL;
}



static void
identity_screen_flush_frontbuffer(struct pipe_screen *_screen,
                                  struct pipe_resource *_resource,
                                  unsigned level, unsigned layer,
                                  void *context_private)
{
   struct identity_screen *id_screen = identity_screen(_screen);
   struct identity_resource *id_resource = identity_resource(_resource);
   struct pipe_screen *screen = id_screen->screen;
   struct pipe_resource *resource = id_resource->resource;

   screen->flush_frontbuffer(screen,
                             resource,
                             level, layer,
                             context_private);
}

static void
identity_screen_fence_reference(struct pipe_screen *_screen,
                                struct pipe_fence_handle **ptr,
                                struct pipe_fence_handle *fence)
{
   struct identity_screen *id_screen = identity_screen(_screen);
   struct pipe_screen *screen = id_screen->screen;

   screen->fence_reference(screen,
                           ptr,
                           fence);
}

static int
identity_screen_fence_signalled(struct pipe_screen *_screen,
                                struct pipe_fence_handle *fence,
                                unsigned flags)
{
   struct identity_screen *id_screen = identity_screen(_screen);
   struct pipe_screen *screen = id_screen->screen;

   return screen->fence_signalled(screen,
                                  fence,
                                  flags);
}

static int
identity_screen_fence_finish(struct pipe_screen *_screen,
                             struct pipe_fence_handle *fence,
                             unsigned flags)
{
   struct identity_screen *id_screen = identity_screen(_screen);
   struct pipe_screen *screen = id_screen->screen;

   return screen->fence_finish(screen,
                               fence,
                               flags);
}

struct pipe_screen *
identity_screen_create(struct pipe_screen *screen)
{
   struct identity_screen *id_screen;

   id_screen = CALLOC_STRUCT(identity_screen);
   if (!id_screen) {
      return NULL;
   }

   id_screen->base.winsys = NULL;

   id_screen->base.destroy = identity_screen_destroy;
   id_screen->base.get_name = identity_screen_get_name;
   id_screen->base.get_vendor = identity_screen_get_vendor;
   id_screen->base.get_param = identity_screen_get_param;
   id_screen->base.get_shader_param = identity_screen_get_shader_param;
   id_screen->base.get_paramf = identity_screen_get_paramf;
   id_screen->base.is_format_supported = identity_screen_is_format_supported;
   id_screen->base.context_create = identity_screen_context_create;
   id_screen->base.resource_create = identity_screen_resource_create;
   id_screen->base.resource_from_handle = identity_screen_resource_from_handle;
   id_screen->base.resource_get_handle = identity_screen_resource_get_handle;
   id_screen->base.resource_destroy = identity_screen_resource_destroy;
   id_screen->base.user_buffer_create = identity_screen_user_buffer_create;
   id_screen->base.flush_frontbuffer = identity_screen_flush_frontbuffer;
   id_screen->base.fence_reference = identity_screen_fence_reference;
   id_screen->base.fence_signalled = identity_screen_fence_signalled;
   id_screen->base.fence_finish = identity_screen_fence_finish;

   id_screen->screen = screen;

   return &id_screen->base;
}
