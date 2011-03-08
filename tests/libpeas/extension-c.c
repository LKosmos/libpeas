/*
 * extension-c.c
 * This file is part of libpeas
 *
 * Copyright (C) 2010 - Garrett Regier
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU Library General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Library General Public License for more details.
 *
 *  You should have received a copy of the GNU Library General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "testing/testing-extension.h"
#include "introspection/introspection-callable.h"

static void
test_extension_c_instance_refcount (PeasEngine *engine)
{
  PeasPluginInfo *info;
  PeasExtension *extension;
  GObject *instance;

  info = peas_engine_get_plugin_info (engine, "extension-c");

  g_assert (peas_engine_load_plugin (engine, info));

  extension = peas_engine_create_extension (engine, info,
                                            INTROSPECTION_TYPE_CALLABLE,
                                            NULL);

  g_assert (PEAS_IS_EXTENSION (extension));

  g_object_get (extension, "instance", &instance, NULL);

  /* The refcount of the returned object should be 2:
   *  - one ref for the PeasExtension
   *  - one ref added by g_object_get()
   */
  g_assert_cmpint (instance->ref_count, ==, 2);
  g_object_unref (instance);

  g_object_unref (extension);
}

int
main (int   argc,
      char *argv[])
{
  g_test_init (&argc, &argv, NULL);
  g_type_init ();

  EXTENSION_TESTS (c);

  EXTENSION_TEST (c, "instance-refcount", instance_refcount);

  return testing_run_tests ();
}
